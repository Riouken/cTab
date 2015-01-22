/*
	Name: cTab_fnc_getUserMarkerList
	
	Author(s):
		Gundy

	Description:
		Issued from a client: Send command to server to receive the current user marker list
		Issued on the server: Send userMarkerList back to client

	Parameters:
		To send request to server
			NONE
		
		When server is receiving request from server
			0: OBJECT - Object local to client that is requesting
		
		When client is receiving the list
			0: ARRAY   - Current user marker list
			1: INTEGER - Current transaction ID
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		// Client requesting the list from the server
		[player] call cTab_fnc_getUserMarkerList;
		
		// Client receiving the list from the server
		[[userMarkerList],157] call cTab_fnc_getUserMarkerList;
*/

private [];

call {
	// Send request to Server
	if (count _this == 0) exitWith {
		if (hasInterface && !isServer) then {
			[[player],"cTab_fnc_getUserMarkerList",false,false,true] call bis_fnc_MP;
		};
	};
	
	// Request received by the server to send the current list, make sure its not a client at the same time
	// Only send the list if the transaction ID is not at its initial value, meaning the list is likely to have some meaningful data
	if (count _this == 1) exitWith {
		if (isServer && !hasInterface && (cTab_userMarkerTransactionId >= 0)) then {
			[[cTab_userMarkerLists,cTab_userMarkerTransactionId],"cTab_fnc_getUserMarkerList",_this select 0,false,true] call bis_fnc_MP;
		};
	};

	// Otherwise this is the list and transaction ID received by the client
	cTab_userMarkerLists = _this select 0;
	cTab_userMarkerTransactionId = _this select 1;

	if (hasInterface) then {call cTab_fnc_updateUserMarkerList;};
};

true