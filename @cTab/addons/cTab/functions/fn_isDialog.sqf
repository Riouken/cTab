/*
 	Name: cTab_fnc_isDialog
 	
 	Author(s):
		Gundy

 	Description:
		Check if interface name ends with "dlg"
	
	Parameters:
		0: Name of interface
 	
 	Returns:
		BOOLEAN - True if interface name ends with "dlg"
 	
 	Example:
 		// returns true
		["cTab_Tablet_dlg"] call cTab_fnc_isDialog;
		
		// returns false
		["cTab_TAD_dsp"] call cTab_fnc_isDialog;
*/

private ["_interfaceName","_charArray","_charArraylen","_subArray","_subString"];

_interfaceName = _this select 0;
_charArray = toArray _interfaceName;
_charArraylen = count _charArray;
_subArray = [];
for "_i" from (_charArraylen - 3) to (_charArraylen - 1) do {
	_subArray pushBack (_charArray select _i);
};
_subString = toString _subArray;

if (_subString == "dlg") then {true} else {false};