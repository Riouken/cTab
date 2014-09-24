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
	// Thanks to KK for this great work around for delteing and resizing arrays of arrays: http://killzonekid.com/arma-scripting-tutorials-arrays-part-2/
	cTabUserIconList set [_markerIndex,"deletethis"];
	cTabUserIconList = cTabUserIconList - ["deletethis"];
	publicVariable "cTabUserIconList";
	true
};

false