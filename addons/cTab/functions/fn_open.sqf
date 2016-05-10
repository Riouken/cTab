/*
	Name: cTab_fnc_open
	
	Author(s):
		Gundy
	
	Description:
		Handles dialog / display startup and registering of event handlers
		
		This function will define cTabIfOpen, using the following format:
			Parameter 0: Interface type, 0 = Main, 1 = Secondary, 2 = Tertiary
			Parameter 1: Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
			Parameter 2: Unit we registered the killed eventhandler for
			Parameter 3: ID of registered eventhandler for killed event
			Parameter 4: Vehicle we registered the GetOut eventhandler for (even if no EH is registered)
			Parameter 5: ID of registered eventhandler for GetOut event (nil if no EH is registered)
			Parameter 6: ID of registered eventhandler for Draw3D event (nil if no EH is registered)
			Parameter 7: ID of registered eventhandler A.C.E medical_onUnconscious event (nil if no EH is registered)
			Parameter 8: ID of registered eventhandler A.C.E playerInventoryChanged event (nil if no EH is registered)
	
	Parameters:
		0: INTEGER - Interface type, 0 = Main, 1 = Secondary
		1: STRING  - Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
		2: OBJECT  - Unit to register killed eventhandler for
		3: OBJECT  - Vehicle to register GetOut eventhandler for
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		// open TAD display as main interface type
		[0,"cTab_TAD_dsp",player,vehicle player] call cTab_fnc_open;
*/

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_interfaceType","_displayName","_player","_vehicle","_playerKilledEhId","_vehicleGetOutEhId"];

if (cTabIfOpenStart || (!isNil "cTabIfOpen")) exitWith {false};
cTabIfOpenStart = true;

_interfaceType = _this select 0;
_displayName = _this select 1;
_player = _this select 2;
_vehicle = _this select 3;

_isDialog = [_displayName] call cTab_fnc_isDialog;

cTabIfOpen = [_interfaceType,_displayName,_player,
	_player addEventHandler ["killed",{[] call cTab_fnc_close}],
	_vehicle,nil,nil,nil,nil];

if (_vehicle != _player && (_isDialog || _displayName in ["cTab_TAD_dsp"])) then {
	cTabIfOpen set [5,
		_vehicle addEventHandler ["GetOut",{if (_this select 2 == cTab_player) then {[] call cTab_fnc_close}}]
	];
};

// Set up event handler to update display header / footer
if (_displayName in ["cTab_TAD_dsp","cTab_TAD_dlg"]) then {
	cTabIfOpen set [6,
		addMissionEventHandler ["Draw3D",{
			_display = uiNamespace getVariable (cTabIfOpen select 1);
			_veh = vehicle cTab_player;
			_playerPos = getPosASL _veh;
		
			// update time
			(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
			
			// update grid position
			(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
			
			// update current heading
			(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[direction _veh,3] call CBA_fnc_formatNumber];
			
			// update current elevation (ASL) on TAD
			(_display displayCtrl IDC_CTAB_OSD_ELEVATION) ctrlSetText format ["%1m",[round (_playerPos select 2),4] call CBA_fnc_formatNumber];
		}]
	];
} else {
	cTabIfOpen set [6,
		addMissionEventHandler ["Draw3D",{
			_display = uiNamespace getVariable (cTabIfOpen select 1);
			_veh = vehicle cTab_player;
			_heading = direction _veh;
			// update time
			(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
			
			// update grid position
			(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition getPosASL _veh];
			
			// update current heading
			(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
			(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
		}]
	];
};


// If ace_medical is used, register with medical_onUnconscious event
if (isClass (configfile >> "CfgPatches" >> "ace_medical")) then {
	cTabIfOpen set [7,
		["medical_onUnconscious",{
			if (_this select 0 == cTab_player && _this select 1) then {
				[] call cTab_fnc_close;
			};
		}] call ace_common_fnc_addEventHandler
	];
};

// If ace_common is used, register with playerInventoryChanged event
if (isClass (configfile >> "CfgPatches" >> "ace_common")) then {
	cTabIfOpen set [8,
		["playerInventoryChanged",{
			_this call cTab_fnc_onPlayerInventoryChanged;
		}] call ace_common_fnc_addEventHandler
	];
};

if (_isDialog) then {
	// Check if map and / or a dialog is open and close them
	if (visibleMap) then {openMap false};
	while {dialog} do {
 		closeDialog 0;
	};
	createDialog _displayName;
} else {
	cTabRscLayer cutRsc [_displayName,"PLAIN",0, false];
};

true