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
		[[["mapType","SAT"],["mapScaleDsp","4"]]] call cTab_fnc_updateInterface;
*/

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_interfaceInit","_settings","_display","_displayName","_null","_osdCtrl","_text","_mode","_mapTypes","_mapType","_mapIDC","_targetMapName","_targetMapIDC","_targetMapCtrl","_previousMapCtrl","_previousMapIDC","_renderTarget","_loadingCtrl","_targetMapScale","_mapScaleKm","_mapScaleMin","_mapScaleMax","_mapWorldPos","_targetMapWorldPos","_displayItems","_btnActCtrl","_displayItemsToShow","_mapTools","_showMenu","_data","_uavListCtrl","_hcamListCtrl","_index","_isDialog","_background","_brightness","_nightMode"];
disableSerialization;

if (isNil "cTabIfOpen") exitWith {false};
_displayName = cTabIfOpen select 1;
_display = uiNamespace getVariable _displayName;
_interfaceInit = false;
_loadingCtrl = _display displayCtrl IDC_CTAB_LOADINGTXT;
_targetMapCtrl = controlNull;
_targetMapScale = nil;
_targetMapWorldPos = nil;
_isDialog = [_displayName] call cTab_fnc_isDialog;

if (count _this == 1) then {
	_settings = _this select 0;
} else {
	// Retrieve all settings for the currently open interface
	_settings = [_displayName] call cTab_fnc_getSettings;
	_interfaceInit = true;
};

_mode = [_settings,"mode"] call cTab_fnc_getFromPairs;
if (isNil "_mode") then {
	_mode = [_displayName,"mode"] call cTab_fnc_getSettings;
	_loadingCtrl = displayNull;
} else {
	// show "Loading" control to hide all the action while its going on
	if (!isNull _loadingCtrl) then {
		_loadingCtrl ctrlShow true;
		while {!ctrlShown _loadingCtrl} do {};
	};
};

{
	call {
		// ------------ BRIGHTNESS ------------
		// Value ranges from 0 to 1, 0 being off and 1 being full brightness
		if (_x select 0 == "brightness") exitWith {
			_osdCtrl = _display displayCtrl IDC_CTAB_BIGHTNESS;
			if (!isNull _osdCtrl) then {
				_brightness = _x select 1;
				_nightMode = [_displayName,"nightMode"] call cTab_fnc_getSettings;
				// if we are running night mode, lower the brightness proportionally
				if (!isNil "_nightMode") then {
					if (_nightMode == 1 || {_nightMode == 2 && (sunOrMoon < 0.2)}) then {_brightness = _brightness * 0.7};
				};
				_osdCtrl ctrlSetBackgroundColor [0,0,0,1 - _brightness];
			};
		};
		
		// ------------ NIGHT MODE ------------
		// 0 = day mode, 1 = night mode, 2 = automatic
		if (_x select 0 == "nightMode") exitWith {
			_nightMode = _x select 1;
			// transform nightMode into boolean
			_nightMode = if (_nightMode == 1 || {_nightMode == 2 && (sunOrMoon < 0.2)}) then {true} else {false};
			_background = call {
				if (_displayName in ["cTab_TAD_dsp","cTab_TAD_dlg"]) exitWith {
					if (_nightMode) then {"\cTab\img\TAD_background_night_ca.paa"} else {"\cTab\img\TAD_background_ca.paa"};
				};
				if (_displayName in ["cTab_Android_dsp","cTab_Android_dlg"]) exitWith {
					if (_nightMode) then {"\cTab\img\android_background_night_ca.paa"} else {"\cTab\img\android_background_ca.paa"};
				};
				if (_displayName in ["cTab_microDAGR_dsp","cTab_microDAGR_dlg"]) exitWith {
					if (_nightMode) then {"\cTab\img\microDAGR_background_night_ca.paa"} else {"\cTab\img\microDAGR_background_ca.paa"};
				};
				""
			};
			if (_background != "") then {
				(_display displayCtrl IDC_CTAB_BACKGROUND) ctrlSetText _background;
				// call brightness adjustment if this is outside of interface init
				if (!_interfaceInit) then {
					[[["brightness",[_displayName,"brightness"] call cTab_fnc_getSettings]]] call cTab_fnc_updateInterface;
				};
			};
		};
		
		// ------------ MODE ------------
		if (_x select 0 == "mode") exitWith {
			cTabUserPos = [];
			
			_displayItems = call {				
				if (_displayName == "cTab_Tablet_dlg") exitWith {
					[3300,3301,3302,3303,3304,3305,3306,3307,
					IDC_CTAB_GROUP_DESKTOP,
					IDC_CTAB_GROUP_UAV,
					IDC_CTAB_GROUP_HCAM,
					IDC_CTAB_GROUP_MESSAGE,
					IDC_CTAB_MINIMAPBG,
					IDC_CTAB_CTABHCAMMAP,
					IDC_CTAB_CTABUAVMAP,
					IDC_CTAB_SCREEN,
					IDC_CTAB_SCREEN_TOPO,
					IDC_CTAB_HCAM_FULL,
					IDC_CTAB_OSD_HOOK_GRID,
					IDC_CTAB_OSD_HOOK_ELEVATION,
					IDC_CTAB_OSD_HOOK_DST,
					IDC_CTAB_OSD_HOOK_DIR]
				};
				if (_displayName == "cTab_Android_dlg") exitWith {
					[3300,3301,3302,3303,3304,3305,3306,3307,
					IDC_CTAB_GROUP_MENU,
					IDC_CTAB_GROUP_MESSAGE,
					IDC_CTAB_GROUP_COMPOSE,
					IDC_CTAB_SCREEN,
					IDC_CTAB_SCREEN_TOPO,
					IDC_CTAB_OSD_HOOK_GRID,
					IDC_CTAB_OSD_HOOK_ELEVATION,
					IDC_CTAB_OSD_HOOK_DST,
					IDC_CTAB_OSD_HOOK_DIR]
				};
				if (_displayName in ["cTab_FBCB2_dlg","cTab_TAD_dlg"]) exitWith {
					[3300,3301,3302,3303,3304,3305,3306,3307]
				};
				[] // default
			};
			if !(_displayItems isEqualTo []) then {
				_btnActCtrl = _display displayCtrl IDC_CTAB_BTNACT;
				_displayItemsToShow = [];
				
				call {
					// ---------- DESKTOP -----------
					if (_mode == "DESKTOP") exitWith {
						_displayItemsToShow pushback IDC_CTAB_GROUP_DESKTOP;
						_btnActCtrl ctrlSetText "";
						_btnActCtrl ctrlSetTooltip "";
					};
					// ---------- BFT -----------
					if (_mode == "BFT") exitWith {
						_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
						_mapType = [_displayName,"mapType"] call cTab_fnc_getSettings;
						_mapIDC = [_mapTypes,_mapType] call cTab_fnc_getFromPairs;
						
						_displayItemsToShow pushBack _mapIDC;
						
						_mapTools = [_displayName,"mapTools"] call cTab_fnc_getSettings;
						if (!isNil "_mapTools" && {_mapTools}) then {
							_displayItemsToShow = _displayItemsToShow + [
								IDC_CTAB_OSD_HOOK_GRID,
								IDC_CTAB_OSD_HOOK_ELEVATION,
								IDC_CTAB_OSD_HOOK_DST,
								IDC_CTAB_OSD_HOOK_DIR
							];
						};
						
						_showMenu = [_displayName,"showMenu"] call cTab_fnc_getSettings;
						if (!isNil "_showMenu" && {_showMenu}) then	{
							_displayItemsToShow pushBack IDC_CTAB_GROUP_MENU;
						};
						
						_btnActCtrl ctrlSetTooltip "";
						
						// update scale and world position when not on interface init
						if (!_interfaceInit) then {
							if (_isDialog) then {
								[[
									["mapScaleDlg",[_displayName,"mapScaleDlg"] call cTab_fnc_getSettings],
									["mapWorldPos",[_displayName,"mapWorldPos"] call cTab_fnc_getSettings]
								]] call cTab_fnc_updateInterface;
							};
						};
					};
					// ---------- UAV -----------
					if (_mode == "UAV") exitWith {
						_displayItemsToShow = [
							IDC_CTAB_GROUP_UAV,
							IDC_CTAB_MINIMAPBG,
							IDC_CTAB_CTABUAVMAP
						];
						_data = [_displayName,"uavCam"] call cTab_fnc_getSettings;
						_btnActCtrl ctrlSetTooltip "View Optics";
						_uavListCtrl = _display displayCtrl IDC_CTAB_CTABUAVLIST;
						lbClear _uavListCtrl;
						// Populate list of UAVs
						{
							if (!(crew _x isEqualTo [])) then {
								_index = _uavListCtrl lbAdd (str _x);
								_uavListCtrl lbSetData [_index,str _x];
							};
						} count cTabUAVlist;
						lbSort [_uavListCtrl, "ASC"];
						for "_x" from 0 to (lbSize _uavListCtrl - 1) do {
							if (_data == _uavListCtrl lbData _x) exitWith {
								if (lbCurSel _uavListCtrl != _x) then {
									_uavListCtrl lbSetCurSel _x;
									[_data,[[0,"rendertarget8"],[1,"rendertarget9"]]] spawn cTab_fnc_createUavCam;
								};
							};
						};
						if (lbCurSel _uavListCtrl == -1) then {
							[true] call cTab_fnc_deleteUAVcam;
						};
					};
					// ---------- HELMET CAM -----------
					if (_mode == "HCAM") exitWith {
						_displayItemsToShow = [
							IDC_CTAB_GROUP_HCAM,
							IDC_CTAB_MINIMAPBG,
							IDC_CTAB_CTABHCAMMAP
						];
						_data = [_displayName,"hCam"] call cTab_fnc_getSettings;
						_btnActCtrl ctrlSetTooltip "Toggle Fullscreen";
						_hcamListCtrl = _display displayCtrl IDC_CTAB_CTABHCAMLIST;
						// Populate list of HCAMs
						lbClear _hcamListCtrl;
						{
							_index = _hcamListCtrl lbAdd format ["%2 (%1:%3)",groupId group _x,name _x,[_x] call CBA_fnc_getGroupIndex];
							_hcamListCtrl lbSetData [_index,str _x];
						} count cTabHcamlist;
						lbSort [_hcamListCtrl, "ASC"];
						for "_x" from 0 to (lbSize _hcamListCtrl - 1) do {
							if (_data == _hcamListCtrl lbData _x) exitWith {
								if (lbCurSel _hcamListCtrl != _x) then {
									_hcamListCtrl lbSetCurSel _x;
									['rendertarget12',_data] spawn cTab_fnc_createHelmetCam;
								};
							};
						};
						if (lbCurSel _hcamListCtrl == -1) then {
							call cTab_fnc_deleteHelmetCam;
						};
					};
					// ---------- MESSAGING -----------
					if (_mode == "MESSAGE") exitWith {
						_displayItemsToShow = [IDC_CTAB_GROUP_MESSAGE];
						call cTab_msg_gui_load;
						cTabRscLayerMailNotification cutText ["", "PLAIN"];
					};
					// ---------- MESSAGING COMPOSE -----------
					if (_mode == "COMPOSE") exitWith {
						_displayItemsToShow pushBack IDC_CTAB_GROUP_COMPOSE;
						call cTab_msg_gui_load;
					};
					// ---------- FULLSCREEN HELMET CAM -----------
					if (_mode == "HCAM_FULL") exitWith {
						_displayItemsToShow = [IDC_CTAB_HCAM_FULL];
						_data = [_displayName,"hCam"] call cTab_fnc_getSettings;
						_btnActCtrl ctrlSetTooltip "Toggle Fullscreen";
						['rendertarget13',_data] spawn cTab_fnc_createHelmetCam;
					};
				};
				
				// hide every _displayItems not in _displayItemsToShow
				{(_display displayCtrl _x) ctrlShow (_x in _displayItemsToShow)} count _displayItems;
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
		// ------------ MAP SCALE DSP------------
		if (_x select 0 == "mapScaleDsp") exitWith {
			if (_mode == "BFT" && !_isDialog) then {
				_mapScaleKm = _x select 1;
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
					[_displayName,[["mapScaleDsp",_mapScaleKm]],false] call cTab_fnc_setSettings;
				};
				cTabMapScale = _mapScaleKm / cTabMapScaleFactor;
				
				_osdCtrl = _display displayCtrl IDC_CTAB_OSD_MAP_SCALE;
				if (!isNull _osdCtrl) then {
					// divide by 2 because we want to display the radius, not the diameter
					_osdCtrl ctrlSetText format ["%1",_mapScaleKm / 2];
				};
			};
		};
		// ------------ MAP SCALE DLG------------
		if (_x select 0 == "mapScaleDlg") exitWith {
			if (_mode == "BFT" && _isDialog) then {
				_mapScaleKm = _x select 1;
				_targetMapScale = _mapScaleKm / cTabMapScaleFactor * 0.86 / (safezoneH * 0.8);
			};
		};
		// ------------ MAP WORLD POSITION ------------
		if (_x select 0 == "mapWorldPos") exitWith {
			if (_mode == "BFT") then {
				if (_isDialog) then {
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
				
				if (!_interfaceInit && _isDialog) then {
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
	if (isNull _targetMapCtrl) then {
		_targetMapName = [_displayName,"mapType"] call cTab_fnc_getSettings;
		_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
		_targetMapIDC = [_mapTypes,_targetMapName] call cTab_fnc_getFromPairs;
		_targetMapCtrl = _display displayCtrl _targetMapIDC;
	};
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

// move mouse cursor to the center of the screen if its a dialog
if (_interfaceInit && _isDialog) then {setMousePosition [0.5,0.5];};

// now hide the "Loading" control since we are done
if (!isNull _loadingCtrl) then {
	_loadingCtrl ctrlShow false;
	while {ctrlShown _loadingCtrl} do {};
};

true