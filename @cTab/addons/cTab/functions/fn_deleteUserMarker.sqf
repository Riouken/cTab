/*
 	Name: cTab_fnc_deleteUserMarker
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Delete user placed marker at provided index and broadcast the result. This function is called on the server.

	Parameters:
		0: STRING  - Encryption Key for this marker
		1: INTEGER - Index position of marker to delete
 	
 	Returns:
		BOOLEAN - If marker was deleted
 	
 	Example:
		_deleted = ["bluefor",5] call cTab_fnc_deleteUserMarker;
*/

private["_encryptionKey","_markerIndex","_userMarkerList","_removeIndex"];

_encryptionKey = _this select 0;
_markerIndex = _this select 1;
_userMarkerList = [cTab_userMarkerLists,_encryptionKey] call cTab_fnc_getFromPairs;

_removeIndex = -1;
{
	if (_x select 0 == _markerIndex) exitWith {_removeIndex = _forEachIndex};
} forEach _userMarkerList;

if (_removeIndex != -1) exitWith {
	0 = _userMarkerList deleteAt _removeIndex;
	[cTab_userMarkerLists,_encryptionKey,_userMarkerList] call cTab_fnc_setToPairs;
	
	// Push the updated marker list out to all clients
	publicVariable "cTab_userMarkerLists";
	
	// If this got called on a client, make sure the list is updated
	if (hasInterface) then {call cTab_fnc_updateUserMarkerList};
	
	true
};

false