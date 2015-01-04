/*
	Name: cTab_fnc_broadcastUserMarkerList
	
	Author(s):
		Gundy

	Description:
		Add a new user marker to the list and broadcast it
		
		List format:
			Index 0: ARRAY  - marker position
			Index 1: STRING - path to marker icon
			Index 2: STRING - path to marker size icon
			Index 3: STRING - direction of reported movement
			Index 4: ARRAY  - marker color
			Index 5: STRING - marker time
			Index 6: STRING - marker time
	
	Parameters:
		NONE
	
	Returns:
		BOOLEAN - Always TRUE
	
	Example:
		call cTab_fnc_broadcastUserMarkerList;
*/

private ["_playerEncryptionKey","_cTabUserMarkerListString","_cTabUserMarkerList"];

_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
_cTabUserMarkerListString = format ["cTab_userMarkerList_%1",_playerEncryptionKey];
_cTabUserMarkerList = missionNamespace getVariable [_cTabUserMarkerListString,[]];

0 = _cTabUserMarkerList pushBack cTabUserSelIcon;
missionNamespace setVariable [_cTabUserMarkerListString,_cTabUserMarkerList];
publicVariable _cTabUserMarkerListString;
call cTab_fnc_updateUserMarkerList;

true