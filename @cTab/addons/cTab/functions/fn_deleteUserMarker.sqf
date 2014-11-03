/*
 	Name: cTab_fnc_deleteUserMarker
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Delete user placed marker at provided index

	Parameters:
		0: INTEGER - Index position of marker to delete
 	
 	Returns:
		BOOLEAN - If marker was deleted
 	
 	Example:
		_deleted = [5] call cTab_fnc_deleteUserMarker;
*/

private["_markerIndex"];

_markerIndex = _this select 0;
if (_markerIndex >= 0 && count cTabUserIconList > _markerIndex) exitWith {
	cTabUserIconList deleteAt _markerIndex;
	publicVariable "cTabUserIconList";
	true
};

false