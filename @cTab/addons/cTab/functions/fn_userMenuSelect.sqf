/*
	Name: cTab_fnc_userMenuSelect
	
	Author(s):
		Gundy, Riouken
	
	Description:
		Process user menu select events, initiated by "\cTab\shared\cTab_markerMenu_controls.hpp"
		
	
	Parameters:
		0: INTEGER - Type of user menu select event
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		[1] call cTab_fnc_userMenuSelect;
*/

private ["_type","_displayName","_display","_idcToShow","_control","_uav","_data","_camPos"];

disableSerialization;

_type = _this select 0;
_displayName = cTabIfOpen select 1;
_display = (uiNamespace getVariable _displayName);

_idcToShow = 0;

call {
	// send cTabUserSelIcon to server
	if (_type == 1) exitWith {
		cTabUserMarkerList pushBack [-1,cTabUserSelIcon call cTab_fnc_translateUserMarker];
		['cTab_addUserMarker',[call cTab_fnc_getPlayerEncryptionKey,cTabUserSelIcon]] call CBA_fnc_clientToServerEvent;
	};
	
	// Lock UAV cam to clicked position
	if (_type == 2) exitWith {
		_uav = objNull;
		_data = [_displayName,"uavCam"] call cTab_fnc_getSettings;
		// see if given UAV name is still in the list of valid UAVs
		{
			if (_data == str _x) exitWith {_uav = _x;};
		} count cTabUAVlist;
		if !(isNull _uav) then {
			_camPos = cTabUserSelIcon select 0;
			_uav lockCameraTo [_camPos + [getTerrainHeightASL _camPos],[0]];
		};
	};

	_idcToShow = call {
		if (_type == 11) exitWith {3301};
		if (_type == 12) exitWith {3303};
		if (_type == 13) exitWith {3304};
		if (_type == 14) exitWith {
			if (cTabUserSelIcon select 1 != 0) then {
				cTabUserSelIcon set [2,0];
				3304
			} else {3307};
		};
		if (_type == 21) exitWith {3305};
		if (_type == 31) exitWith {3306};
	};
};

// Hide all menu controls
{ctrlShow [_x,false];} count [3300,3301,3302,3303,3304,3305,3306,3307];

// Bring the menu control we want to show into position and show it
if (_idcToShow != 0) then {
	_control = _display displayCtrl _idcToShow;
	_control ctrlSetPosition cTabUserPos;
	_control ctrlCommit 0;
	_control ctrlShow true;
};

true