/*
	Name: cTab_fnc_close
	
	Author(s):
		Gundy
	
	Description:
		Initiates the closing of currently open interface
	
	Parameters:
		No Parameters
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		[] call cTab_fnc_close;
*/

private ["_displayName","_display"];

if !(isNil "cTabIfOpen") then {
	// [_ifType,_displayName,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId]
	_displayName = cTabIfOpen select 1;
	_display = uiNamespace getVariable _displayName;
	
	_display closeDisplay 0;
	if !([_displayName] call cTab_fnc_isDialog) then {
		[] call cTab_fnc_onIfclose;
	};
};

true