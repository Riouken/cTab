/*
	Name: cTab_fnc_addUserMarkerList
	
	Author(s):
		Gundy

	Description:
		Add a new user marker to the list and broadcast it. This function is called on the server.
	
	Parameters:
		0: STRING - Encryption Key for this marker
		1: ARRAY  - markerData
	
	Returns:
		BOOLEAN - Always TRUE
	
	Example:
		["bluefor",[[1714.35,5716.82],0,0,0,"12:00"]]call cTab_fnc_addUserMarkerList;
*/

private ["_encryptionKey","_newIndex"];

_encryptionKey = _this select 0;
_newIndex = [cTab_userMarkerIndices,_encryptionKey,1] call cTab_fnc_addToPairs;

[cTab_userMarkerLists,_encryptionKey,[[_newIndex,_this select 1]]] call cTab_fnc_addToPairs;

// Push the updated marker list out to all clients
publicVariable "cTab_userMarkerLists";

// If this got called on a client, make sure the list is updated
if (hasInterface) then {call cTab_fnc_updateUserMarkerList};

true