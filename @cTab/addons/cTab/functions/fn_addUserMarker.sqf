/*
	Name: cTab_fnc_addUserMarkerList
	
	Author(s):
		Gundy

	Description:
		Add a new user marker to the list and broadcast it. This function is called on the server.
		
		List format:
			Index 0: ARRAY  - marker position
			Index 1: STRING - path to marker icon
			Index 2: STRING - path to marker size icon
			Index 3: STRING - direction of reported movement
			Index 4: ARRAY  - marker color
			Index 5: STRING - marker time
			Index 6: STRING - marker time
	
	Parameters:
		0: STRING - Encryption Key for this marker
		1: ARRAY  - markerData
	
	Returns:
		BOOLEAN - Always TRUE
	
	Example:
		["bluefor",[[1714.35,5716.82,0],"\cTab\img\o_inf_rifle.paa","",700,[0.5,0,0,1],"12:00",""]]call cTab_fnc_addUserMarkerList;
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