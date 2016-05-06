/*
	Name: cTab_fnc_getBackgroundPosition
	
	Author(s):
		Gundy
	
	Description:
		Get the current and config position of the interface background element
	
	Parameters:
		0: STRING - uiNamespace variable name of interface
	
	Returns:
		ARRAY - interface position and config position
			0: ARRAY - interface position in the form of [x,y,w,h]
			1: ARRAY - interface config position in the form of [x,y,w,h], empty array if background could not be found
	
	Example:
		["cTab_Tablet_dlg"] call cTab_fnc_getBackgroundPosition;
*/

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_displayName","_display","_isDialog","_backgroundCtrl","_backgroundClassName","_backgroundPosition","_backgroundConfigPosition","_displayConfigContainers"];

_displayName = _this select 0;
_display = uiNamespace getVariable _displayName;
_isDialog = [_displayName] call cTab_fnc_isDialog;

// get both classes "controls" and "controlsBackground" if they exist
_displayConfigContainers = if (_isDialog) then {
		"true" configClasses (configFile >> _displayName)
	} else {
		"true" configClasses (configFile >> "RscTitles" >> _displayName)
	};

// get the class name and current position
_backgroundCtrl = _display displayCtrl IDC_CTAB_BACKGROUND;
_backgroundClassName = ctrlClassName _backgroundCtrl;
_backgroundPosition = ctrlPosition _backgroundCtrl;

// get the original position of the background control
_backgroundConfigPosition = [];
{
	if (isClass _x) then {
		if (isClass (_x >> _backgroundClassName)) exitWith {
			_backgroundConfigPosition = [
					getNumber (_x >> _backgroundClassName >> "x"),
					getNumber (_x >> _backgroundClassName >> "y"),
					getNumber (_x >> _backgroundClassName >> "w"),
					getNumber (_x >> _backgroundClassName >> "h")
				];
		};
	};
} forEach _displayConfigContainers;

[_backgroundPosition,_backgroundConfigPosition]