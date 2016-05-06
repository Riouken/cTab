/*
 	Name: cTab_fnc_drawHook
 	
 	Author(s):
		Gundy

 	Description:
		Calculate and draw hook distance, direction, grid, elevation and arrow
	
	Parameters:
		0: OBJECT  - Display used to write hook direction, distance and grid to
		0: OBJECT  - Map control to draw arrow on
		2: ARRAY   - Position A
		3: ARRAY   - Position B
		4: INTEGER - Mode, 0 = Reference is A, 1 = Reference is B
		5: BOOLEAN - TAD, TRUE = TAD
 	
 	Returns:
		BOOLEAN - Always TRUE
 	
 	Example:
		[_display,_ctrlScreen,_playerPos,cTabMapCursorPos,0,false] call cTab_fnc_drawHook;
*/

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_display","_ctrlScreen","_pos","_secondPos","_dirToSecondPos","_dstToSecondPos"];

_display = _this select 0;
_ctrlScreen = _this select 1;
_pos = _this select 2;
_secondPos = _this select 3;
// draw arrow from current position to map centre
_dirToSecondPos = call {
	if (_this select 4 == 0) exitWith {
		_ctrlScreen drawArrow [_pos,_secondPos,cTabMicroDAGRhighlightColour];
		[_pos,_secondPos] call cTab_fnc_dirTo
	};
	_ctrlScreen drawArrow [_secondPos,_pos,cTabMicroDAGRhighlightColour];
	[_secondPos,_pos] call cTab_fnc_dirTo
};
_dstToSecondPos = [_pos,_secondPos] call cTab_fnc_distance2D;
call {
	// Call this if we are drawing for a TAD
	if (_this select 5) exitWith {
		(_display displayCtrl IDC_CTAB_OSD_HOOK_GRID) ctrlSetText format ["%1",mapGridPosition _secondPos];
		(_display displayCtrl IDC_CTAB_OSD_HOOK_ELEVATION) ctrlSetText format ["%1m",[round getTerrainHeightASL _secondPos,3] call CBA_fnc_formatNumber];
		(_display displayCtrl IDC_CTAB_OSD_HOOK_DIR) ctrlSetText format ["%1°/%2",[_dirToSecondPos,3] call CBA_fnc_formatNumber,[_dstToSecondPos / 1000,2,1] call CBA_fnc_formatNumber];
	};
	(_display displayCtrl IDC_CTAB_OSD_HOOK_GRID) ctrlSetText format ["%1",mapGridPosition _secondPos];
	(_display displayCtrl IDC_CTAB_OSD_HOOK_ELEVATION) ctrlSetText format ["%1m",round getTerrainHeightASL _secondPos];
	(_display displayCtrl IDC_CTAB_OSD_HOOK_DIR) ctrlSetText format ["%1° %2",[_dirToSecondPos,3] call CBA_fnc_formatNumber,[_dirToSecondPos] call cTab_fnc_degreeToOctant];
	(_display displayCtrl IDC_CTAB_OSD_HOOK_DST) ctrlSetText format ["%1km",[_dstToSecondPos / 1000,1,2] call CBA_fnc_formatNumber];
};

true