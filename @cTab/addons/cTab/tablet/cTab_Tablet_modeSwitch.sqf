// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

disableSerialization;

#include "\cTab\shared\cTab_gui_macros.hpp"

cTabUserPos = [];

_display = (uiNamespace getVariable "cTab_Tablet_dlg");

ctrlShow [IDC_CTAB_LOADINGTXT,true];
_loadingCtrl = _display displayCtrl IDC_CTAB_LOADINGTXT;
waitUntil {ctrlShown _loadingCtrl};

_btnActCtrl = _display displayCtrl IDC_CTAB_BTNACT;

_displayItems = [
	3300,3301,3302,3303,3304,3305,3306,
	IDC_CTAB_GROUP_DESKTOP,
	IDC_CTAB_GROUP_UAV,
	IDC_CTAB_GROUP_HCAM,
	IDC_CTAB_GROUP_MESSAGE,
	IDC_CTAB_MINIMAPBG,
	IDC_CTAB_CTABHCAMMAP,
	IDC_CTAB_CTABUAVMAP,
	IDC_CTAB_SCREEN,
	IDC_CTAB_SCREEN_TOPO,
	IDC_CTAB_HCAM_FULL,
	IDC_CTAB_OSD_HOOK_GRID,
	IDC_CTAB_OSD_HOOK_ELEVATION,
	IDC_CTAB_OSD_HOOK_DST,
	IDC_CTAB_OSD_HOOK_DIR
];
_displayItemsToShow = [];

_mode = _this select 0;

call {
	// ---------- DESKTOP -----------
	if (_mode == "DESKTOP") exitWith {
		_displayItemsToShow = [IDC_CTAB_GROUP_DESKTOP];
		_btnActCtrl ctrlSetText "";
		_btnActCtrl ctrlSetTooltip "";
	};
	// ---------- BFT -----------
	if (_mode == "BFT") exitWith {
		_mapTypes = ["cTab_Tablet_dlg","mapTypes"] call cTab_fnc_getSettings;
		_mapType = ["cTab_Tablet_dlg","mapType"] call cTab_fnc_getSettings;
		_mapIDC = [_mapTypes,_mapType] call cTab_fnc_getFromPairs;
		
		_displayItemsToShow = [_mapIDC];
		
		_mapTools = ["cTab_Tablet_dlg","mapTools"] call cTab_fnc_getSettings;
		if (_mapTools) then {
			_displayItemsToShow = _displayItemsToShow + [IDC_CTAB_OSD_HOOK_GRID,IDC_CTAB_OSD_HOOK_ELEVATION,IDC_CTAB_OSD_HOOK_DST,IDC_CTAB_OSD_HOOK_DIR];
		};
		
		_btnActCtrl ctrlSetTooltip "";
	};
	// ---------- UAV -----------
	if (_mode == "UAV") exitWith {
		_displayItemsToShow = [IDC_CTAB_GROUP_UAV,IDC_CTAB_MINIMAPBG,IDC_CTAB_CTABUAVMAP];
		_data = ["cTab_Tablet_dlg","uavCam"] call cTab_fnc_getSettings;
		_btnActCtrl ctrlSetTooltip "View Optics";
		_uavListCtrl = _display displayCtrl IDC_CTAB_CTABUAVLIST;
		lbClear _uavListCtrl;
		// Populate list of UAVs
		{
			if (!(crew _x isEqualTo [])) then {
				_index = _uavListCtrl lbAdd (str _x);
				_uavListCtrl lbSetData [_index,str _x];
			};
		} count allUnitsUav;
		lbSort [_uavListCtrl, "ASC"];
		for "_x" from 0 to (lbSize _uavListCtrl - 1) do {
			if (_data == _uavListCtrl lbData _x) exitWith {
				if (lbCurSel _uavListCtrl != _x) then {
					_uavListCtrl lbSetCurSel _x;
					[_data,[[0,"rendertarget8"],[1,"rendertarget9"]]] spawn cTab_fnc_createUavCam;
				};
			};
		};
		if (lbCurSel _uavListCtrl == -1) then {
			[] spawn cTab_fnc_deleteUAVcam;
		};
	};
	// ---------- HELMET CAM -----------
	if (_mode == "HCAM") exitWith {
		_displayItemsToShow = [IDC_CTAB_GROUP_HCAM,IDC_CTAB_MINIMAPBG,IDC_CTAB_CTABHCAMMAP];
		_data = ["cTab_Tablet_dlg","hCam"] call cTab_fnc_getSettings;
		_btnActCtrl ctrlSetTooltip "Toggle Fullscreen";
		_hcamListCtrl = _display displayCtrl IDC_CTAB_CTABHCAMLIST;
		// Populate list of HCAMs
		lbClear _hcamListCtrl;
		{
			_index = _hcamListCtrl lbAdd format ["%2 (%1:%3)",groupId group _x,name _x,[_x] call CBA_fnc_getGroupIndex];
			_hcamListCtrl lbSetData [_index,str _x];
		} count cTabHcamlist;
		lbSort [_hcamListCtrl, "ASC"];
		for "_x" from 0 to (lbSize _hcamListCtrl - 1) do {
			if (_data == _hcamListCtrl lbData _x) exitWith {
				if (lbCurSel _hcamListCtrl != _x) then {
					_hcamListCtrl lbSetCurSel _x;
					['rendertarget12',_data] spawn cTab_fnc_createHelmetCam;
				};
			};
		};
		if (lbCurSel _hcamListCtrl == -1) then {
			call cTab_fnc_deleteHelmetCam;
		};
	};
	// ---------- MESSAGING -----------
	if (_mode == "MESSAGE") exitWith {
		_displayItemsToShow = [IDC_CTAB_GROUP_MESSAGE];
		call cTab_msg_gui_load;
		cTabRscLayerMailNotification cutText ["", "PLAIN"];
	};
	// ---------- FULLSCREEN HCAM -----------
	if (_mode == "HCAM_FULL") exitWith {
		_displayItemsToShow = [IDC_CTAB_HCAM_FULL];
		_data = ["cTab_Tablet_dlg","hCam"] call cTab_fnc_getSettings;
		_btnActCtrl ctrlSetTooltip "Toggle Fullscreen";
		['rendertarget13',_data] spawn cTab_fnc_createHelmetCam;
	};
};

// hide every _displayItems not in _displayItemsToShow
{ctrlShow [_x,_x in _displayItemsToShow];} count _displayItems;

ctrlShow [IDC_CTAB_LOADINGTXT,false];
