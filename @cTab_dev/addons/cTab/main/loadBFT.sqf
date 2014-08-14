// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

disableSerialization;

#include <\cTab\cTab_gui_macros.hpp>
#include <\cTab\usermenu_gui_macros.hpp>
cTabUserPos = [];

_display = (uiNamespace getVariable "cTab_main_dlg");
_popup = [3300,3301,3302,3303,3304,3305,3306];

{
	ctrlShow [_x, false];
	
} forEach _popup;

_loadingTxt = _display displayCtrl IDC_CTAB_LOADINGTXT;
_cntrlBFTicon = _display displayCtrl IDC_CTAB_ACTBFTTXT;
_cntrlUAVicon = _display displayCtrl IDC_CTAB_ACTUAVTXT;
_cntrlHcamicon = _display displayCtrl IDC_CTAB_ACTVIDTXT;
_cntrlMSGicon = _display displayCtrl IDC_CTAB_ACTMSGTXT;
_cntrlBFTicon ctrlShow False;
_cntrlUAVicon ctrlShow False;
_cntrlHcamicon ctrlShow False;
_cntrlMSGicon ctrlShow False;


_cntrlBFTMap = _display displayCtrl IDC_CTAB_SCREEN;
_cntrlBFTMap ctrlShow True;


cTabUserOptions = [];
cTabUserSelIcon = [[],"","",500,cTabColorRed];




