/*
	Name: cTab_fnc_getBackground
	
	Author(s):
		Gundy

	Description:
		Return the correct background for a given interface, depending on the nightMode setting

	Parameters:
		0: STRING - uiNamespace variable for which to toggle mode for
	
	Returns:
		STRING - Path to background PAA file
		
	Example:
		_background = "cTab_TAD_dsp" call cTab_fnc_getBackground;
*/

private ["_nightMode","_backgroundDay","_backgroundNight"];

_nightMode = [_this,"nightMode"] call cTab_fnc_getSettings;

_backgroundDay = "";
_backgroundNight = "";

call {
	if (_this in ["cTab_TAD_dsp","cTab_TAD_dlg"]) exitWith {
		_backgroundDay = "\cTab\img\TAD_background_ca.paa";
		_backgroundNight = "\cTab\img\TAD_background_night_ca.paa";
	};
	/*if (_this == "cTab_Tablet_dlg") exitWith {};
	if (_this in ["cTab_Android_dsp","cTab_Android_dlg"]) exitWith {};
	if (_this == "cTab_FBCB2_dlg") exitWith {};
	if (_this in ["cTab_microDAGR_dsp","cTab_microDAGR_dlg"]) exitWith {};*/
};

if (_nightMode == 1 || {_nightMode == 2 && (sunOrMoon < 0.2)}) then {_backgroundNight} else {_backgroundDay};