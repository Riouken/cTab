/*
	Name: cTab_fnc_deleteUserMarker
	
	Author(s):
		Gundy

	Description:
		Delete user placed marker at provided index and broadcast the result. This function is called on the server.

	Parameters:
		0: STRING  - Encryption Key for this marker
		1: INTEGER - Index position of marker to delete
	Optional:
		2: INTEGER - Transaction ID
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		// Client requesting marker deletion and server receiving request
		["bluefor",5] call cTab_fnc_deleteUserMarker;
		
		// Client receiving request for marker deletion (from server)
		["bluefor",5,158] call cTab_fnc_deleteUserMarker;
*/

private ["_encryptionKey","_markerIndex","_transactionId","_userMarkerList","_removeIndex"];

_encryptionKey = _this select 0;
_markerIndex = _this select 1;
_transactionId = _this select 2; // not set when initiated from client

call {
	// If received on the server
	if (isServer) exitWith {
		if (isNil "_transactionId") then {
			// get the marker list that corresponds to the encryption key
			_userMarkerList = [cTab_userMarkerLists,_encryptionKey] call cTab_fnc_getFromPairs;

			// try to find the marker to be removed
			_removeIndex = -1;
			{
				if (_x select 0 == _markerIndex) exitWith {_removeIndex = _forEachIndex};
			} forEach _userMarkerList;
			
			// if the marker could be found, remove it
			if (_removeIndex != -1) then {
				0 = _userMarkerList deleteAt _removeIndex;
				[cTab_userMarkerLists,_encryptionKey,_userMarkerList] call cTab_fnc_setToPairs;
				
				// Send deleteUserMarker command to all clients
				cTab_userMarkerTransactionId = cTab_userMarkerTransactionId + 1;
				[[_encryptionKey,_markerIndex,cTab_userMarkerTransactionId],"cTab_fnc_deleteUserMarker",true,false,true] call bis_fnc_MP;
				
				// If this was run on a client-server (i.e. in single player or locally hosted), update the marker list
				if (hasInterface && {_encryptionKey == call cTab_fnc_getPlayerEncryptionKey}) then {
					call cTab_fnc_updateUserMarkerList;
				};
			};
		};
	};

	// If received on a client, sent by the server
	if (hasInterface && !isNil "_transactionId") exitWith {
		call {
			if (cTab_userMarkerTransactionId == _transactionId) exitWith {};
			if (cTab_userMarkerTransactionId != (_transactionId -1)) exitWith {
				// get full list
				["Transaction ID check failed! Had %1, received %2. Requesting user marker list.",cTab_userMarkerTransactionId,_transactionId] call bis_fnc_error;
				[] call cTab_fnc_getUserMarkerList;
			};
			cTab_userMarkerTransactionId = _transactionId;
			
			// get the marker list that corresponds to the encryption key
			_userMarkerList = [cTab_userMarkerLists,_encryptionKey] call cTab_fnc_getFromPairs;

			// try to find the marker to be removed
			_removeIndex = -1;
			{
				if (_x select 0 == _markerIndex) exitWith {_removeIndex = _forEachIndex};
			} forEach _userMarkerList;
			
			// if the marker could be found, remove it
			if (_removeIndex != -1) then {
				0 = _userMarkerList deleteAt _removeIndex;
				[cTab_userMarkerLists,_encryptionKey,_userMarkerList] call cTab_fnc_setToPairs;
				// only update the user marker list if the marker was deleted from the player's side
				if (_encryptionKey == call cTab_fnc_getPlayerEncryptionKey) then {
					call cTab_fnc_updateUserMarkerList;
				};
			};
		};
	};
	
	// If received on a client, to be sent to the server
	if (hasInterface) then {
		[_this,"cTab_fnc_deleteUserMarker",false,false,true] call bis_fnc_MP;
	};
};

true