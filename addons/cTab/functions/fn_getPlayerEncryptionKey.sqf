/*
	Name: cTab_fnc_getPlayerEncryptionKey
	
	Author(s):
		Gundy

	Description:
		Return the used encryption key for the currently controlled unit

	Parameters:
		NONE
	
	Returns:
		STRING - Encryption key
		
	Example:
		_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
*/

missionNamespace getVariable [format ["cTab_encryptionKey_%1",side cTab_player],""];