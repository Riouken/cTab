/*
 	Name: cTab_fnc_updateInterface
 	
 	Author(s):
		Gundy

 	Description:
		Update current interface (display or dialog) to match current settings.
		If no parameters are specified, all interface elements are updated

	Parameters:
	(Optional)
		0: ARRAY - Property pairs in the form of [["propertyName",propertyValue],[...]]
 	
 	Returns:
		BOOLEAN - Always true
 	
 	Example:
		[["mapType","SAT"],["mapScale","4"]] call cTab_fnc_updateInterface;
*/

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_ifName","_settings","_display","_displayName","_null","_osdCtrl","_text","_mode","_mapTypes","_targetMapName","_targetMapIDC","_targetMapCtrl","_previousMapCtrl","_renderTarget"];
disableSerialization;

if (isNil "cTabIfOpen") exitWith {};
_displayName = cTabIfOpen select 1;
_display = uiNamespace getVariable _displayName;
_interfaceInit = false;
_loadingCtrl = _display displayCtrl IDC_CTAB_LOADINGTXT;
_targetMapCtrl = controlNull;
_targetMapScale = nil;
_targetMapWorldPos = nil;

_mode = [_displayName,"mode"] call cTab_fnc_getSettings;

if (count _this == 1) then {
	_settings = _this select 0;
} else {
	// Retrieve all settings for the currently open interface
	_settings = [_displayName] call cTab_fnc_getSettings;
	_interfaceInit = true;
	
	// show "Loading" control to hide all the action while its going on
	if (!isNull _loadingCtrl) then {
		_loadingCtrl ctrlShow true;
		while {!ctrlShown _loadingCtrl} do {};
	};
};

{
	call {
		// ------------ MODE ------------
		if (_x select 0 == "mode") exitWith {
			_modeSwitchScript = call {
				if (_displayName == "cTab_Tablet_dlg") exitWith {"\cTab\tablet\cTab_Tablet_modeSwitch.sqf"};
				if (_displayName == "cTab_Android_dlg") exitWith {"\cTab\android\cTab_android_modeSwitch.sqf"};
				""
			};
			if (_modeSwitchScript != "") then {
				_null = [_displayName,_x select 1] execVM _modeSwitchScript;
			};
		};
		// ------------ SHOW ICON TEXT ------------
		if (_x select 0 == "showIconText") exitWith {
			_osdCtrl = _display displayCtrl IDC_CTAB_OSD_TXT_TGGL;
			if (!isNull _osdCtrl) then {
				_text = if (_x select 1) then {"ON"} else {"OFF"};
				_osdCtrl ctrlSetText _text;
			};
		};
		// ------------ MAP SCALE ------------
		if (_x select 0 == "mapScale") exitWith {
			if (_mode == "BFT") then {
				_mapScaleKm = _x select 1;
				if ([_displayName] call cTab_fnc_isDialog) then {
					_targetMapScale = _mapScaleKm / cTabMapScaleFactor * 0.86 / (safezoneH * 0.8);
				} else {
					// pre-Calculate map scales
					_mapScaleMin = [_displayName,"mapScaleMin"] call cTab_fnc_getSettings;
					_mapScaleMax = [_displayName,"mapScaleMax"] call cTab_fnc_getSettings;
					_mapScaleKm = call {
						if (_mapScaleKm >= _mapScaleMax) exitWith {_mapScaleMax};
						if (_mapScaleKm <= _mapScaleMin) exitWith {_mapScaleMin};
						// pick the next best scale that is an even multiple of the minimum map scale... It does tip in favour of the larger scale due to the use of logarithm, so its not perfect
						_mapScaleMin * 2 ^ round (log (_mapScaleKm / _mapScaleMin) / log (2))
					};
					if (_mapScaleKm != (_x select 1)) then {
						[_displayName,[["mapScale",_mapScaleKm]],false] call cTab_fnc_setSettings;
					};
					cTabMapScale = _mapScaleKm / cTabMapScaleFactor;
				};
				_osdCtrl = _display displayCtrl IDC_CTAB_OSD_MAP_SCALE;
				if (!isNull _osdCtrl) then {
					// divide by 2 because we want to display the radius, not the diameter
					_osdCtrl ctrlSetText format ["%1",_mapScaleKm / 2];
				};
			};
		};
		// ------------ MAP WORLD POSITION ------------
		if (_x select 0 == "mapWorldPos") exitWith {
			if (_mode == "BFT") then {
				if ([_displayName] call cTab_fnc_isDialog) then {
					_mapWorldPos = _x select 1;
					if !(_mapWorldPos isEqualTo []) then {
						_targetMapWorldPos = _mapWorldPos;
					};
				};
			};
		};
		// ------------ MAP TYPE ------------
		if (_x select 0 == "mapType") exitWith {
			_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
			if ((count _mapTypes > 1) && (_mode == "BFT")) then {
				_targetMapName = _x select 1;
				_targetMapIDC = [_mapTypes,_targetMapName] call cTab_fnc_getFromPairs;
				_targetMapCtrl = _display displayCtrl _targetMapIDC;
				
				if (!_interfaceInit && {[_displayName] call cTab_fnc_isDialog}) then {
					_previousMapCtrl = controlNull;
					{
						_previousMapIDC = _x select 1;
						_previousMapCtrl = _display displayCtrl _previousMapIDC;
						if (ctrlShown _previousMapCtrl) exitWith {};
						_previousMapCtrl = controlNull;
					} count _mapTypes;
					// See if _targetMapCtrl is already being shown
					if ((!ctrlShown _targetMapCtrl) && (_targetMapCtrl != _previousMapCtrl)) then {
						// Update _targetMapCtrl to scale and position of _previousMapCtrl
						if (isNil "_targetMapScale") then {_targetMapScale = ctrlMapScale _previousMapCtrl;};
						if (isNil "_targetMapWorldPos") then {_targetMapWorldPos = [_previousMapCtrl] call cTab_fnc_ctrlMapCenter};
					};
				};
				
				// Hide all unwanted map types
				{
					if (_x select 0 != _targetMapName) then {
						(_display displayCtrl (_x select 1)) ctrlShow false;
					};
				} count _mapTypes;
				
				// Update OSD element if it exists
				_osdCtrl = _display displayCtrl IDC_CTAB_OSD_MAP_TGGL;
				if (!isNull _osdCtrl) then {_osdCtrl ctrlSetText _targetMapName;};
				
				// show correct map contorl
				if (!ctrlShown _targetMapCtrl) then {
					_targetMapCtrl ctrlShow true;
					// wait until map control is shown, otherwise we can get in trouble with ctrlMapAnimCommit later on, depending on timing
					while {!ctrlShown _targetMapCtrl} do {};
				};
			};
		};
		// ------------ UAV CAM ------------
		if (_x select 0 == "uavCam") exitWith {
			if (_mode == "UAV") then {
				_data = _x select 1;
				if (_data != "") then {
					[_data,[[0,"rendertarget8"],[1,"rendertarget9"]]] spawn cTab_fnc_createUavCam;
				};
			};
		};
		// ------------ HCAM ------------
		if (_x select 0 == "hCam") exitWith {
			_renderTarget = call {
				if (_mode == "HCAM") exitWith {"rendertarget12"};
				if (_mode == "HCAM_FULL") exitWith {"rendertarget13"}
			};
			if (!isNil "_renderTarget") then {
				_data = _x select 1;
				if (_data != "") then {
					[_renderTarget,_data] spawn cTab_fnc_createHelmetCam;
				};
			};
		};
		// ------------ MAP TOOLS ------------
		if (_x select 0 == "mapTools") exitWith {
			cTabDrawMapTools = _x select 1;
			if (_mode == "BFT") then {
				if !(_displayName in ["cTab_TAD_dlg","cTab_TAD_dsp"]) then {
					{
						_osdCtrl = _display displayCtrl _x;
						if (!isNull _osdCtrl) then {
							_osdCtrl ctrlShow cTabDrawMapTools;
						};
					} count [IDC_CTAB_OSD_HOOK_GRID,IDC_CTAB_OSD_HOOK_DIR,IDC_CTAB_OSD_HOOK_DST,IDC_CTAB_OSD_HOOK_ELEVATION];
				};
				_osdCtrl = _display displayCtrl IDC_CTAB_OSD_HOOK_TGGL1;
				if (!isNull _osdCtrl) then {
					_text = if (_x select 1) then {"OWN"} else {"CURS"};
					_osdCtrl ctrlSetText _text;
				};
				_osdCtrl = _display displayCtrl IDC_CTAB_OSD_HOOK_TGGL2;
				if (!isNull _osdCtrl) then {
					_text = if (_x select 1) then {"CURS"} else {"OWN"};
					_osdCtrl ctrlSetText _text;
				};
			};
		};
		// ------------ MENU ------------
		if (_x select 0 == "showMenu") exitWith {
			_osdCtrl = _display displayCtrl IDC_CTAB_GROUP_MENU;
			if (!isNull _osdCtrl) then {
				if (_mode == "BFT") then {
					_osdCtrl ctrlShow (_x select 1);
				};
			};
		};
		// ----------------------------------
	};
} forEach _settings;

// update scale and world position if we have to. If so, fill in the blanks and make the changes
if ((!isNil "_targetMapScale") || (!isNil "_targetMapWorldPos")) then {
	if (!isNull _targetMapCtrl) then {
		_targetMapName = [_displayName,"mapType"] call cTab_fnc_getSettings;
		_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
		_targetMapIDC = [_mapTypes,_targetMapName] call cTab_fnc_getFromPairs;
		_targetMapCtrl = _display displayCtrl _targetMapIDC;
	};
	
	if (ctrlShown _targetMapCtrl) then {
		if (isNil "_targetMapScale") then {
			_targetMapScale = ctrlMapScale _targetMapCtrl;
		};
		if (isNil "_targetMapWorldPos") then {
			_targetMapWorldPos = [_targetMapCtrl] call cTab_fnc_ctrlMapCenter;
		};
		_targetMapCtrl ctrlMapAnimAdd [0,_targetMapScale,_targetMapWorldPos];
		ctrlMapAnimCommit _targetMapCtrl;
		while {!(ctrlMapAnimDone _targetMapCtrl)} do {};
	};
};

// now hide the "Loading" control since we are done
if (_interfaceInit && {!isNull _loadingCtrl}) then {
	_loadingCtrl ctrlShow false;
	while {ctrlShown _loadingCtrl} do {};
};

true