/*
	Name: cTab_fnc_setInterfacePosition
	
	Author(s):
		Gundy
	
	Description:
		Move the whole interface by a provided offset
	
	Parameters:
		0: STRING - uiNamespace variable name of interface
		1: ARRAY  - offset in the form of [x,y]
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		["cTab_Tablet_dlg",[0.2,0.1]] call cTab_fnc_setInterfacePosition;
*/

private ["_displayName","_xOffset","_yOffset","_display","_isDialog","_backgroundCtrl","_backgroundClassName","_displayConfigContainers","_displayConfigClasses","_idc","_ctrl","_ctrlPosition"];

_displayName = _this select 0;
_xOffset = _this select 1 select 0;
_yOffset = _this select 1 select 1;
_display = uiNamespace getVariable _displayName;
_isDialog = [_displayName] call cTab_fnc_isDialog;

// get both classes "controls" and "controlsBackground" if they exist
_displayConfigContainers = if (_isDialog) then {
		"true" configClasses (configFile >> _displayName)
	} else {
		"true" configClasses (configFile >> "RscTitles" >> _displayName)
	};

{
	if (isClass _x) then {
		_displayConfigClasses = "true" configClasses _x;
		{
			if (isClass _x) then {
				if (isNumber (_x >> "idc")) then {
					_idc = getNumber (_x >> "idc");
					if (_idc > 0) then {
						_ctrl = _display displayCtrl _idc;
						_ctrlPosition = ctrlPosition _ctrl;
						_ctrlPosition set [0,(_ctrlPosition select 0) + _xOffset];
						_ctrlPosition set [1,(_ctrlPosition select 1) + _yOffset];
						_ctrl ctrlSetPosition _ctrlPosition;
						_ctrl ctrlCommit 0;
					} else {diag_log str ["invalid IDC",_x]};
				} else {diag_log str ["missing IDC",_x]};
			};
		} forEach _displayConfigClasses;
	};
} forEach _displayConfigContainers;

true