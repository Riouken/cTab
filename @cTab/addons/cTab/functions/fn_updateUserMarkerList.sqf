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

private ["_playerEncryptionKey"];

_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;

cTabUserMarkerList = [cTab_userMarkerLists,_playerEncryptionKey,[]] call cTab_fnc_getFromPairs;

true