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

private ["_interfaceInit","_settings","_display","_displayName","_null","_osdCtrl","_text","_mode","_mapTypes","_mapType","_mapIDC","_targetMapName","_targetMapIDC","_targetMapCtrl","_previousMapCtrl","_previousMapIDC","_renderTarget","_loadingCtrl","_targetMapScale","_mapScaleKm","_mapScaleMin","_mapScaleMax","_mapScaleTxt","_mapWorldPos","_targetMapWorldPos","_displayItems","_btnActCtrl","_displayItemsToShow","_mapTools","_showMenu","_data","_uavListCtrl","_hcamListCtrl","_index","_isDialog","_background","_brightness","_nightMode","_backgroundPosition","_backgroundPositionX","_backgroundPositionW","_backgroundConfigPositionX","_xOffset","_dspIfPosition","_backgroundOffset","_ctrlPos","_mousePos"];
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
		// ------------ DISPLAY POSITION ------------
		if (_x select 0 == "dspIfPosition") exitWith {
			_dspIfPosition = _x select 1;
			
			if !(_isDialog) then {
				// get the current position of the background control
				_backgroundPosition = [_displayName] call cTab_fnc_getBackgroundPosition;
				_backgroundPositionX = _backgroundPosition select 0 select 0;
				_backgroundPositionW = _backgroundPosition select 0 select 2;
				
				// get the original position of the background control
				_backgroundConfigPositionX = _backgroundPosition select 1 select 0;
				
				// figure out if we need to do anything
				if !((_backgroundPositionX != _backgroundConfigPositionX) isEqualTo _dspIfPosition) then {
					// calculate offset required to shift position to the opposite
					_xOffset = if (_backgroundPositionX == _backgroundConfigPositionX) then {
							2 * safeZoneX + safeZoneW - _backgroundPositionW - 2 * _backgroundPositionX
						} else {
							_backgroundConfigPositionX - _backgroundPositionX
						};
					[_displayName,[_xOffset,0]] call cTab_fnc_setInterfacePosition;
				};
			};
		};
		// ------------ DIALOG POSITION ------------
		if (_x select 0 == "dlgIfPosition") exitWith {
			_backgroundOffset = _x select 1;
			
			if (_isDialog) then {
				if (_backgroundOffset isEqualTo []) then {
					_backgroundOffset = if (_interfaceInit) then {
							[0,0]
						} else {
							// reset to defaults
							_backgroundPosition = [_displayName] call cTab_fnc_getBackgroundPosition;
							[(_backgroundPosition select 1 select 0) - (_backgroundPosition select 0 select 0),(_backgroundPosition select 1 select 1) - (_backgroundPosition select 0 select 1)]
						};
				};
				if !(_backgroundOffset isEqualTo [0,0]) then {
					// move by offset
					[_displayName,_backgroundOffset] call cTab_fnc_setInterfacePosition;
				};
			};
		};
		// ------------ BRIGHTNESS ------------
		// Value ranges from 0 to 1, 0 being off and 1 being full brightness
		if (_x select 0 == "brightness") exitWith {
			_osdCtrl = _display displayCtrl IDC_CTAB_BRIGHTNESS;
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
				if (_displayName in ["cTab_Tablet_dlg"]) exitWith {
					if (_nightMode) then {"\cTab\img\tablet_background_night_ca.paa"} else {"\cTab\img\tablet_background_ca.paa"};
				};
				""
			};
			if (_background != "") then {
				(_display displayCtrl IDC_CTAB_BACKGROUND) ctrlSetText _background;
				// call brightness adjustment if this is outside of interface init
				if (!_interfaceInit) then {
					_settings pushBack ["brightness",[_displayName,"brightness"] call cTab_fnc_getSettings];
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
					IDC_CTAB_OSD_HOOK_DIR,
					IDC_CTAB_NOTIFICATION]
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
					IDC_CTAB_OSD_HOOK_DIR,
					IDC_CTAB_NOTIFICATION]
				};
				if (_displayName in ["cTab_FBCB2_dlg","cTab_TAD_dlg"]) exitWith {
					[3300,3301,3302,3303,3304,3305,3306,3307,
					IDC_CTAB_NOTIFICATION]
				};
				[IDC_CTAB_NOTIFICATION] // default
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
							_displayItemsToShow append [
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
								_settings pushBack ["mapScaleDlg",[_displayName,"mapScaleDlg"] call cTab_fnc_getSettings];
								_settings pushBack ["mapWorldPos",[_displayName,"mapWorldPos"] call cTab_fnc_getSettings];
							};
						};
					};
					// ---------- _NOT_ BFT -----------
					if (_isDialog) then {
						_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
						if (count _mapTypes > 1) then {
							_targetMapName = [_displayName,"mapType"] call cTab_fnc_getSettings;
							_targetMapIDC = [_mapTypes,_targetMapName] call cTab_fnc_getFromPairs;
							_targetMapCtrl = _display displayCtrl _targetMapIDC;
							
							// If we find the map to be shown, we are switching away from BFT. Lets save map scale and position
							if (ctrlShown _targetMapCtrl) then {
								_mapScale = cTabMapScale * cTabMapScaleFactor / 0.86 * (safezoneH * 0.8);
								[_displayName,[["mapWorldPos",cTabMapWorldPos],["mapScaleDlg",_mapScale]],false] call cTab_fnc_setSettings;
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
						_btnActCtrl ctrlSetTooltip "View Gunner Optics";
						_settings pushBack ["uavListUpdate",true];
						if (!_interfaceInit) then {
							_settings pushBack ["uavCam",[_displayName,"uavCam"] call cTab_fnc_getSettings];
						};
					};
					// ---------- HELMET CAM -----------
					if (_mode == "HCAM") exitWith {
						_displayItemsToShow = [
							IDC_CTAB_GROUP_HCAM,
							IDC_CTAB_MINIMAPBG,
							IDC_CTAB_CTABHCAMMAP
						];
						_btnActCtrl ctrlSetTooltip "Toggle Fullscreen";
						_settings pushBack ["hCamListUpdate",true];
						if (!_interfaceInit) then {
							_settings pushBack ["hCam",[_displayName,"hCam"] call cTab_fnc_getSettings];
						};
					};
					// ---------- MESSAGING -----------
					if (_mode == "MESSAGE") exitWith {
						_displayItemsToShow = [IDC_CTAB_GROUP_MESSAGE];
						call cTab_msg_gui_load;
						cTabRscLayerMailNotification cutText ["", "PLAIN"];
						_btnActCtrl ctrlSetTooltip "";
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
					_mapScaleTxt = if (_mapScaleKm > 1) then {
							_mapScaleKm / 2
					} else {
						[_mapScaleKm / 2,0,1] call CBA_fnc_formatNumber
					};
					_osdCtrl ctrlSetText format ["%1",_mapScaleTxt];	
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
				} else {
					[] call cTab_fnc_deleteUAVcam;
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
				} else {
					[] call cTab_fnc_deleteHelmetCam;
				}
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
		// ------------ UAV List Update ------------
		if (_x select 0 == "uavListUpdate") exitWith {
			if (_mode == "UAV") then {
				_data = [_displayName,"uavCam"] call cTab_fnc_getSettings;
				_uavListCtrl = _display displayCtrl IDC_CTAB_CTABUAVLIST;
				lbClear _uavListCtrl;
				_uavListCtrl lbSetCurSel -1;
				// Populate list of UAVs
				{
					if (!(crew _x isEqualTo [])) then {
						_index = _uavListCtrl lbAdd format ["%1:%2 (%3)",groupId group _x,[_x] call CBA_fnc_getGroupIndex,getText (configfile >> "cfgVehicles" >> typeOf _x >> "displayname")];
						_uavListCtrl lbSetData [_index,str _x];
					};
				} count cTabUAVlist;
				lbSort [_uavListCtrl, "ASC"];
				if (_data != "") then {
					// Find last selected UAV and select if found
					for "_x" from 0 to (lbSize _uavListCtrl - 1) do {
						if (_data == _uavListCtrl lbData _x) exitWith {
							if (lbCurSel _uavListCtrl != _x) then {
								_uavListCtrl lbSetCurSel _x;
							};
						};
					};
					// If no UAV could be selected, clear last selected UAV
					if (lbCurSel _uavListCtrl == -1) then {
						[_displayName,[["uavCam",""]]] call cTab_fnc_setSettings;
					};
				};
			};
		};
		// ------------ HCAM List Update ------------
		if (_x select 0 == "hCamListUpdate") exitWith {
			if (_mode == "HCAM") then {
				_data = [_displayName,"hCam"] call cTab_fnc_getSettings;
				_hcamListCtrl = _display displayCtrl IDC_CTAB_CTABHCAMLIST;
				// Populate list of HCAMs
				lbClear _hcamListCtrl;
				_hcamListCtrl lbSetCurSel -1;
				{
					_index = _hcamListCtrl lbAdd format ["%1:%2 (%3)",groupId group _x,[_x] call CBA_fnc_getGroupIndex,name _x];
					_hcamListCtrl lbSetData [_index,str _x];
				} count cTabHcamlist;
				lbSort [_hcamListCtrl, "ASC"];
				if (_data != "") then {
					// Find last selected hCam and select if found
					for "_x" from 0 to (lbSize _hcamListCtrl - 1) do {
						if (_data == _hcamListCtrl lbData _x) exitWith {
							if (lbCurSel _hcamListCtrl != _x) then {
								_hcamListCtrl lbSetCurSel _x;
							};
						};
					};
					// If no hCam could be selected, clear last selected hCam
					if (lbCurSel _hcamListCtrl == -1) then {
						[_displayName,[["hCam",""]]] call cTab_fnc_setSettings;
					};
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

// now hide the "Loading" control since we are done
if (!isNull _loadingCtrl) then {
	// move mouse cursor to the center of the screen if its a dialog
	if (_interfaceInit && _isDialog) then {
		_ctrlPos = ctrlPosition _loadingCtrl;
		// put the mouse position in the center of the screen
		_mousePos = [(_ctrlPos select 0) + ((_ctrlPos select 2) / 2),(_ctrlPos select 1) + ((_ctrlPos select 3) / 2)];
		// delay moving the mouse cursor by one frame using a PFH, for some reason its not working without
		[{
			[_this select 1] call CBA_fnc_removePerFrameHandler;
			setMousePosition (_this select 0);
		},0,_mousePos] call CBA_fnc_addPerFrameHandler;
	};
	
	_loadingCtrl ctrlShow false;
	while {ctrlShown _loadingCtrl} do {};
};

// call notification system
if (_interfaceInit) then {[] call cTab_fnc_processNotifications};

true