/*
 	Name: cTab_fnc_onIfKeyDown
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Process onKeyDown events from cTab dialogs
		
	
	Parameters:
		0: OBJECT  - Display that called the onKeyDown event
		1: INTEGER - DIK code of onKeyDown event
		2: BOOLEAN - Shift key pressed
		3: BOOLEAN - Ctrl key pressed
		4: BOOLEAN - Alt key pressed
 	
 	Returns:
		BOOLEAN - If onKeyDown event was acted upon
 	
 	Example:
		[_display,_dikCode,_shiftKey,_ctrlKey,_altKey] call cTab_fnc_onIfKeyDown;
*/

private["_display","_handled","_dikCode","_shiftKey","_ctrlKey","_altKey","_displayName","_mapTypes","_currentMapType","_currentMapTypeIndex","_ctrlScreen","_markerIndex"];

_display = _this select 0;
_displayName = cTabIfOpen select 1;
_dikCode = _this select 1;
_shiftKey = _this select 2;
_ctrlKey = _this select 3;
_altKey = _this select 4;
_handled = false;

if (_dikCode == 59 && {_displayName in ["cTab_Tablet_dlg"]}) exitWith { // F1
	[_displayName,[["mode","BFT"]]] call cTab_fnc_setSettings;
	true
};
if (_dikCode == 60 && {_displayName in ["cTab_Tablet_dlg"]}) exitWith { // F2
	[_displayName,[["mode","UAV"]]] call cTab_fnc_setSettings;
	true
};
if (_dikCode == 61 && {_displayName in ["cTab_Tablet_dlg"]}) exitWith { // F3
	[_displayName,[["mode","HCAM"]]] call cTab_fnc_setSettings;
	true
};
if (_dikCode == 62 && {_displayName in ["cTab_Tablet_dlg"]}) exitWith { // F4
	[_displayName,[["mode","MESSAGE"]]] call cTab_fnc_setSettings;
	true
};
if (_dikCode == 64 && {_displayName in ["cTab_Tablet_dlg","cTab_TAD_dlg","cTab_microDAGR_dlg","cTab_FBCB2_dlg"]}) exitWith { // F6
	[_displayName] call cTab_fnc_mapType_toggle;
	true
};
if (_dikCode == 211 && {cTabCursorOnMap}) exitWith { // DELETE
	_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
	_currentMapType = [_displayName,"mapType"] call cTab_fnc_getSettings;
	_currentMapTypeIndex = [_mapTypes,_currentMapType] call BIS_fnc_findInPairs;
	_ctrlScreen = _display displayCtrl (_mapTypes select _currentMapTypeIndex select 1);
	_markerIndex = [_ctrlScreen,cTabMapCursorPos] call cTab_fnc_findUserMarker;
	[_markerIndex] call cTab_fnc_deleteUserMarker
};

false