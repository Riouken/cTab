/*
	Name: cTab_fnc_translateUserMarker
	
	Author(s):
		michail-nikolaev (nkey, TFAR)

	Description:
		For a given curator key press event, find a matching key handler that was registered with CBA's keybind system. If a match was found, execute the corresponding CBA key handler event.
	
	Parameters:
		0: ARRAY  - KeyDown / KeyUp event attributes
		1: STRING - "keyDown" or "keyUp"
	
	Returns:
		BOOLEAN - If event was found and executed upon
	
	Example:
		(findDisplay 312) displayAddEventHandler ["KeyDown", "[_this, 'keydown'] call cTab_fnc_processCuratorKey"];
		(findDisplay 312) displayAddEventHandler ["KeyUp", "[_this, 'keyup'] call cTab_fnc_processCuratorKey"];
*/

private ["_keys", "_pressed", "_result"];

_pressed = _this select 0;
_result = false;
{		
	if (_x select 0 == "cTab") then {
		_keys = _x select 2;				
		if ((_keys select 0 == _pressed select 1) && {(_keys select 1) isEqualTo (_pressed select 2)} && {(_keys select 2) isEqualTo  (_pressed select 3)} && {(_keys select 3) isEqualTo (_pressed select 4)}) exitWith {
			_result = _this call CBA_events_fnc_keyHandler;
		};
	};
	true;
} count cba_keybinding_handlers;

_result;