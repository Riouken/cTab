/*
	Name: cTab_fnc_userMenuSelect
	
	Author(s):
		Gundy, Riouken
	
	Description:
		Process user menu select events, initiated by "\cTab\shared\cTab_markerMenu_controls.hpp"
		
	
	Parameters:
		0: INTEGER - Type of user menu select event - if this doesn't match a valid type it will be considered to be an IDC
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		[1] call cTab_fnc_userMenuSelect;
*/

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_type","_displayName","_display","_idcToShow","_control","_controlPos","_screenPos","_screenEdgeX","_screenEdgeY","_controlEdgeX","_controlEdgeY"];

disableSerialization;

_type = _this select 0;
_displayName = cTabIfOpen select 1;
_display = (uiNamespace getVariable _displayName);

_idcToShow = 0;

call {
	// send cTabUserSelIcon to server
	if (_type == 1) exitWith {
		cTabUserSelIcon pushBack cTab_player;
		[call cTab_fnc_getPlayerEncryptionKey,cTabUserSelIcon] call cTab_fnc_addUserMarker;
	};
	
	// Lock UAV cam to clicked position
	if (_type == 2) exitWith {
		[cTabUserSelIcon select 0] call cTab_fnc_lockUavCamTo;
	};

	_idcToShow = call {
		if (_type == 11) exitWith {3301};
		if (_type == 12) exitWith {3303};
		if (_type == 13) exitWith {3304};
		if (_type == 14) exitWith {
			if (cTabUserSelIcon select 1 != 0) then {
				cTabUserSelIcon set [2,0];
				3304
			} else {3307};
		};
		if (_type == 21) exitWith {3305};
		if (_type == 31) exitWith {3306};
		_type;
	};
};

// Hide all menu controls
{ctrlShow [_x,false];} count [3300,3301,3302,3303,3304,3305,3306,3307];

// Bring the menu control we want to show into position and show it
if (_idcToShow != 0) then {
	_control = _display displayCtrl _idcToShow;
	if !(isNull _control) then {
		_controlPos = ctrlPosition _control;
		
		// figure out screen edge positions and where the edges of the control would be if we were just to move it blindly to cTabUserPos
		_screenPos = ctrlPosition (_display displayCtrl IDC_CTAB_LOADINGTXT);
		_screenEdgeX = (_screenPos select 0) + (_screenPos select 2);
		_screenEdgeY = (_screenPos select 1) + (_screenPos select 3);
		_controlEdgeX = (cTabUserPos select 0) + (_controlPos select 2);
		_controlEdgeY = (cTabUserPos select 1) + (_controlPos select 3);
		
		// if control would be clipping the right edge, correct control position
		if (_controlEdgeX > _screenEdgeX) then {
			_controlPos set [0,_screenEdgeX - (_controlPos select 2)];
		} else {
			_controlPos set [0,cTabUserPos select 0];
		};
		// if control would be clipping the bottom edge, correct control position
		if (_controlEdgeY > _screenEdgeY) then {
			_controlPos set [1,_screenEdgeY - (_controlPos select 3)];
		} else {
			_controlPos set [1,cTabUserPos select 1];
		};
		
		// move to position and show
		_control ctrlSetPosition _controlPos;
		_control ctrlCommit 0;
		_control ctrlShow true;
		ctrlSetFocus _control;
	};
};

true