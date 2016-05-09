/*
	Name: cTab_fnc_addUserMarker
	
	Author(s):
		Gundy
	
	Description:
		Add a new user marker to the list and broadcast it. This function is called on the server.
	
	Parameters:
		0: STRING  - Encryption Key for this marker
		1: ARRAY   - markerData
	Optional:
		2: INTEGER - Transaction ID
	
	Returns:
		BOOLEAN - Always TRUE
	
	Example:
		// Client requesting marker addition and server receiving request
		["bluefor",[[1714.35,5716.82],0,0,0,"12:00",player]]call cTab_fnc_addUserMarker;
		
		// Client receiving marker addition (from server)
		["bluefor",[21,[[1714.35,5716.82],0,0,0,"12:00",player]],157]call cTab_fnc_addUserMarker;
*/

private ["_encryptionKey","_markerData","_transactionId"];

_encryptionKey = _this select 0;
_markerData = _this select 1;
_transactionId = _this select 2; // not set when initiated from client

call {
	// If received on the server
	if (isServer) exitWith {
		if (isNil "_transactionId") then {
			_phoneticAlphabet = ["Alpha", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliet", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "Xray", "Yankee", "Zulu"];
		
			// Label logistics markers.
			if (_markerData select 1 == 20) then { _markerData set [4, "VRP"]; };
			if (_markerData select 1 == 21) then { _markerData set [4, "CCP"]; };
			if (_markerData select 1 == 22) then { _markerData set [4, "BAS"]; };
			if (_markerData select 1 == 23) then { _markerData set [4, "HQ"]; };
		
			// Increment marker label.
			if (_markerData select 1 == 30) then {
				cTab_markerCounterMKR = cTab_markerCounterMKR + 1;
				_markerData set [4, format ["%1", cTab_markerCounterMKR]];
			};
			
			// Increment waypoint label.
			if (_markerData select 1 == 31) then {
				cTab_markerCounterWP = cTab_markerCounterWP + 1;
				_markerData set [4, format ["WP%1", cTab_markerCounterWP]];
			};
			
			// Increment LZ phonetic label (shared with DZ).
			if (_markerData select 1 == 32) then {
				_markerData set [4, format ["LZ %1", _phoneticAlphabet select cTab_markerCounterLZDZ]];
				cTab_markerCounterLZDZ = cTab_markerCounterLZDZ + 1;
				if (cTab_markerCounterLZDZ >= 25) then { cTab_markerCounterLZDZ = 0; };
			};
			
			// Increment DZ phonetic label (shared with LZ).
			if (_markerData select 1 == 33) then {
				_markerData set [4, format ["DZ %1", _phoneticAlphabet select cTab_markerCounterLZDZ]];
				cTab_markerCounterLZDZ = cTab_markerCounterLZDZ + 1;
				if (cTab_markerCounterLZDZ >= 25) then { cTab_markerCounterLZDZ = 0; };
			};
			
			// Increment OBJ phonetic label.
			if (_markerData select 1 == 34) then {
				_markerData set [4, format ["%1", _phoneticAlphabet select cTab_markerCounterOBJ]];
				cTab_markerCounterOBJ = cTab_markerCounterOBJ + 1;
				if (cTab_markerCounterOBJ >= 25) then { cTab_markerCounterOBJ = 0; };
			};
		
			// Increase transaction ID
			cTab_userMarkerTransactionId = cTab_userMarkerTransactionId + 1;
			_transactionId = cTab_userMarkerTransactionId;
			
			// Add marker data to list
			[cTab_userMarkerLists,_encryptionKey,[[_transactionId,_markerData]]] call cTab_fnc_addToPairs;
			
			// Send addUserMarker command to all clients
			[[_encryptionKey,[_transactionId,_markerData],_transactionId],"cTab_fnc_addUserMarker",true,false,true] call bis_fnc_MP;
			
			// If this was run on a client-server (i.e. in single player or locally hosted), update the marker list
			if (hasInterface && {_encryptionKey == call cTab_fnc_getPlayerEncryptionKey}) then {
				call cTab_fnc_updateUserMarkerList;
				if ((_markerData select 5) != cTab_player) then {
					["BFT",format ["New marker at #%1",mapGridPosition (_markerData select 0)],20] call cTab_fnc_addNotification;
				} else {
					["BFT","Marker added succesfully",3] call cTab_fnc_addNotification;
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
			[cTab_userMarkerLists,_encryptionKey,[_markerData]] call cTab_fnc_addToPairs;
			// only update the user marker list if the marker was added to the player's side
			if (_encryptionKey == call cTab_fnc_getPlayerEncryptionKey) then {
				call cTab_fnc_updateUserMarkerList;
				
				// add notification if marker was issued by someone else
				if ((_markerData select 1 select 5) != cTab_player) then {
					["BFT",format ["New marker at #%1",mapGridPosition (_markerData select 1 select 0)],20] call cTab_fnc_addNotification;
				} else {
					["BFT","Marker added succesfully",3] call cTab_fnc_addNotification;
				};
			};
		};
	};

	// If received on a client, to be sent to the server
	if (hasInterface) then {
		[_this,"cTab_fnc_addUserMarker",false,false,true] call bis_fnc_MP;
	};
};

true