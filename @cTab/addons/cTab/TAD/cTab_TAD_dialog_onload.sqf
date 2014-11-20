// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

disableSerialization;

#include "\cTab\shared\cTab_gui_macros.hpp"
cTabUserPos = [];

_display = (uiNamespace getVariable "cTab_TAD_dlg");

/*
// change map centre to player position
_cntrlScreen = _display displayCtrl IDC_CTAB_SCREEN;
_cntrlScreen ctrlMapAnimAdd [0,ctrlMapScale _cntrlScreen,getPosASL player];
ctrlMapAnimCommit _cntrlScreen;
*/

_popup = [3300,3301,3302,3303,3304,3305,3306];

{
	ctrlShow [_x, false];
	
} forEach _popup;

/*
_cntrlBFTMap = _display displayCtrl IDC_CTAB_SCREEN;
_cntrlBFTMap ctrlShow False;

*/
