// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

disableSerialization;

#include <\cTab\cTab_gui_macros.hpp>

cTabUserPos = [];

_display = (uiNamespace getVariable "cTab_Android_dlg");

ctrlShow [IDC_CTAB_LOADINGTXT,true];
_loadingCtrl = _display displayCtrl IDC_CTAB_LOADINGTXT;
waitUntil {ctrlShown _loadingCtrl};

_displayItems = [
	3300,3301,3302,3303,3304,3305,3306,
	IDC_CTAB_GROUP_MENU,
	IDC_CTAB_GROUP_MESSAGE,
	IDC_CTAB_GROUP_COMPOSE,
	IDC_CTAB_SCREEN,
	IDC_CTAB_SCREEN_TOPO,
	IDC_CTAB_OSD_HOOK_GRID,
	IDC_CTAB_OSD_HOOK_ELEVATION,
	IDC_CTAB_OSD_HOOK_DST,
	IDC_CTAB_OSD_HOOK_DIR
];
_displayItemsToShow = [];

_mode = _this select 0;

call {
	// ---------- BFT -----------
	if (_mode == "BFT") exitWith {
		_mapTypes = ["cTab_Android_dlg","mapTypes"] call cTab_fnc_getSettings;
		_mapType = ["cTab_Android_dlg","mapType"] call cTab_fnc_getSettings;
		_mapIDC = [_mapTypes,_mapType] call cTab_fnc_getFromPairs;
		
		_displayItemsToShow pushBack _mapIDC;
		
		_mapTools = ["cTab_Android_dlg","mapTools"] call cTab_fnc_getSettings;
		if (_mapTools) then {
			{0 = _displayItemsToShow pushBack _x} count [IDC_CTAB_OSD_HOOK_GRID,IDC_CTAB_OSD_HOOK_ELEVATION,IDC_CTAB_OSD_HOOK_DST,IDC_CTAB_OSD_HOOK_DIR];
		};
		
		_showMenu = ["cTab_Android_dlg","showMenu"] call cTab_fnc_getSettings;
		if (_showMenu) then	{
			_displayItemsToShow pushBack IDC_CTAB_GROUP_MENU;
		};
	};
	// ---------- MESSAGING READ -----------
	if (_mode == "MESSAGE") exitWith {
		_displayItemsToShow pushBack IDC_CTAB_GROUP_MESSAGE;
		call cTab_msg_gui_load;
		cTabRscLayerMailNotification cutText ["", "PLAIN"];
	};
	// ---------- MESSAGING COMPOSE -----------
	if (_mode == "COMPOSE") exitWith {
		_displayItemsToShow pushBack IDC_CTAB_GROUP_COMPOSE;
		call cTab_msg_gui_load;
	};
};

// hide every _displayItems not in _displayItemsToShow
{ctrlShow [_x,_x in _displayItemsToShow];} count _displayItems;

ctrlShow [IDC_CTAB_LOADINGTXT,false];
