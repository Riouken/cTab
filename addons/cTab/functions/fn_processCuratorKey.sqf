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

_processKeys = {
	private ["_mods","_key_pressed","_handler"];
	
	if ([_key, "ctab_"] call CBA_fnc_find == 0) then {
		_key_pressed = _value select 0;
		_mods = _value select 1;
		_handler = _value select 2;
		
		if ((_key_pressed == _pressed select 1) and {(_mods select 0) isEqualTo (_pressed select 2)} and {(_mods select 1) isEqualTo  (_pressed select 3)} and {(_mods select 2) isEqualTo (_pressed select 4)}) exitWith {
			_result = call _handler;
		};
	};
};

[if ((_this select 1) isEqualTo "keyup") then {CBA_events_keyhandlers_up} else {CBA_events_keyhandlers_down}, _processKeys] call CBA_fnc_hashEachPair;

_result;