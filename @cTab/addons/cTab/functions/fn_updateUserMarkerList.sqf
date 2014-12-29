/*
	Name: cTab_fnc_updateUserMarkerList
	
	Author(s):
		Gundy

	Description:
		Update lists of user markers
		
		List format:
			Index 0: ARRAY  - marker position
			Index 1: STRING - path to marker icon
			Index 2: STRING - path to marker size icon
			Index 3: STRING - direction of reported movement
			Index 4: ARRAY  - marker color
			Index 5: STRING - marker time
	
	Parameters:
		NONE
	
	Returns:
		BOOLEAN - Always TRUE
	
	Example:
		call cTab_fnc_updateUserMarkerList;
*/

private ["_playerEncryptionKey","_cTabUserMarkerListString"];

_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
_cTabUserMarkerListString = format ["cTab_userMarkerList_%1",_playerEncryptionKey];

cTabUserMarkerList = missionNamespace getVariable [_cTabUserMarkerListString,[]];

true