/*
	Name: cTab_fnc_lockUavCamTo
	
	Author(s):
		Gundy

	Description:
		Lock the currently selected UAV's gunner camera to the provided coordinates
	
	Parameters:
		0: ARRAY - 2D or 3D position
	
	Returns:
		BOOLEAN - If UAV was found
	
	Example:
		[getPos player] call cTab_fnc_lockUavCamTo;
*/

private ["_displayName","_uav","_data","_camPos"];

_displayName = cTabIfOpen select 1;
_uav = objNull;
_data = [_displayName,"uavCam"] call cTab_fnc_getSettings;

// see if given UAV name is still in the list of valid UAVs
{
	if (_data == str _x) exitWith {_uav = _x;};
} count cTabUAVlist;

if !(isNull _uav) exitWith {
	_camPos = _this select 0;
	if (count _camPos == 2) then {
		_camPos = _camPos + [getTerrainHeightASL _camPos];
	};
	_uav lockCameraTo [_camPos,[0]];
	
	true
};

false