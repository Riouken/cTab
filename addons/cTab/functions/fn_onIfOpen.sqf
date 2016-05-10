/*
	Name: cTab_fnc_onIfOpen
	
	Author(s):
		Gundy
	
	Description:
		Handles dialog / display setup, called by "onLoad" event
	
	Parameters:
		0: Display
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		// open TAD display as main interface type
		[_dispaly] call cTab_fnc_onIfOpen;
*/

private [];

uiNamespace setVariable [cTabIfOpen select 1,_this select 0];

[] call cTab_fnc_updateInterface;

cTabIfOpenStart = false;

true