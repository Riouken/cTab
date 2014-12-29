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

private["_markerIndex","_playerEncryptionKey","_cTabUserMarkerListString","_cTabUserMarkerList"];

_markerIndex = _this select 0;
_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
_cTabUserMarkerListString = format ["cTab_userMarkerList_%1",_playerEncryptionKey];
_cTabUserMarkerList = missionNamespace getVariable [_cTabUserMarkerListString,[]];

if (_markerIndex >= 0 && count _cTabUserMarkerList > _markerIndex) exitWith {
	_cTabUserMarkerList deleteAt _markerIndex;
	publicVariable _cTabUserMarkerListString;
	call cTab_fnc_updateUserMarkerList;
	
	true
};

false