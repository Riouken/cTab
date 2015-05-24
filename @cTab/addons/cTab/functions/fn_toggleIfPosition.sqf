/*
	Name: cTab_fnc_toggleIfPosition
	
	Author(s):
		Gundy
	
	Description:
		Toggle position of interface (display only) from left to right
		
	
	Parameters:
		NONE
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		[] call cTab_fnc_toggleIfPosition;
*/

// bail if there is no interface open
if (isNil "cTabIfOpen") exitWith {false};

_displayName = cTabIfOpen select 1;

// bail if this is a dialog
if ([_displayName] call cTab_fnc_isDialog) exitWith {false};

_dspIfPosition = [_displayName,"dspIfPosition"] call cTab_fnc_getSettings;

// bail if that setting doesn't exist
if (isNil "_dspIfPosition") exitWith {false};

// toggle position
[_displayName,[["dspIfPosition",!_dspIfPosition]]] call cTab_fnc_setSettings;

true