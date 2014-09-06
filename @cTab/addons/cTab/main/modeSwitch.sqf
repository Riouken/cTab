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

_mode = _this select 0;

call {
	if (_mode == "DESKTOP") exitWith {
		_cntrlBFTMap = _display displayCtrl IDC_CTAB_SCREEN;
		_cntrlBFTMap ctrlShow False;
		_cntrlBFTMap = _display displayCtrl IDC_CTAB_SCREEN_TOPO;
		_cntrlBFTMap ctrlShow False;
		_loadingTxt = _display displayCtrl IDC_CTAB_LOADINGTXT;
		_loadingTxt ctrlShow False;

		_cntrlBFTicon = _display displayCtrl IDC_CTAB_ACTBFTTXT;
		_cntrlUAVicon = _display displayCtrl IDC_CTAB_ACTUAVTXT;
		_cntrlHcamicon = _display displayCtrl IDC_CTAB_ACTVIDTXT;
		_cntrlMSGicon = _display displayCtrl IDC_CTAB_ACTMSGTXT;
		_cntrlBFTicon ctrlShow True;
		_cntrlUAVicon ctrlShow True;
		_cntrlHcamicon ctrlShow True;
		_cntrlMSGicon ctrlShow True;
	};
	if (_mode == "BFT") exitWith {
		_loadingTxt = _display displayCtrl IDC_CTAB_LOADINGTXT;
		_cntrlBFTicon = _display displayCtrl IDC_CTAB_ACTBFTTXT;
		_cntrlUAVicon = _display displayCtrl IDC_CTAB_ACTUAVTXT;
		_cntrlHcamicon = _display displayCtrl IDC_CTAB_ACTVIDTXT;
		_cntrlMSGicon = _display displayCtrl IDC_CTAB_ACTMSGTXT;
		_cntrlBFTicon ctrlShow False;
		_cntrlUAVicon ctrlShow False;
		_cntrlHcamicon ctrlShow False;
		_cntrlMSGicon ctrlShow False;
		_loadingTxt ctrlShow False;

		_mapTypes = ["cTab_main_dlg","mapTypes"] call cTab_fnc_settings;
		_mapType = ["cTab_main_dlg","mapType"] call cTab_fnc_settings;
		_mapIDC = [_mapTypes,_mapType] call BIS_fnc_getFromPairs;
		_cntrlBFTMap = _display displayCtrl _mapIDC;
		_cntrlBFTMap ctrlShow True;
	};
};

cTabUserOptions = [];
cTabUserSelIcon = [[],"","",500,cTabColorRed];
