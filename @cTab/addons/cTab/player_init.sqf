// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

// keys.sqf parses the userconfig
#include "functions\keys.sqf"
#include "\cTab\shared\cTab_gui_macros.hpp"

// Get a rsc layer for for our displays
cTabRscLayer = ["cTab"] call BIS_fnc_rscLayer;
cTabRscLayerMailNotification = ["cTab_mailNotification"] call BIS_fnc_rscLayer;

// Set up side specific encryption keys
if (isNil "cTab_encryptionKey_west") then {
	cTab_encryptionKey_west = "bluefor";
};
if (isNil "cTab_encryptionKey_east") then {
	cTab_encryptionKey_east = "opfor";
};
if (isNil "cTab_encryptionKey_guer") then {
	cTab_encryptionKey_guer = call {
		if (([west,resistance] call BIS_fnc_areFriendly) and {!([east,resistance] call BIS_fnc_areFriendly)}) exitWith {
			"bluefor"
		};
		if (([east,resistance] call BIS_fnc_areFriendly) and {!([west,resistance] call BIS_fnc_areFriendly)}) exitWith {
			"opfor"
		};
		"independent"
	};
};
if (isNil "cTab_encryptionKey_civ") then {
	cTab_encryptionKey_civ = "civilian";
};

// set current player object in cTab_player and run a check on every frame to see if there is a change
cTab_player = objNull;
["cTab_checkForPlayerChange", "onEachFrame", {
	if !(cTab_player isEqualTo (missionNamespace getVariable ["BIS_fnc_moduleRemoteControl_unit",player])) then {
		cTab_player = missionNamespace getVariable ["BIS_fnc_moduleRemoteControl_unit",player];
		// close any interface that might still be open
		call cTab_fnc_close;
		//prep the arrays that will hold ctab data
		cTabBFTmembers = [];
		cTabBFTgroups = [];
		cTabBFTvehicles = [];
		cTabUAVlist = [];
		cTabHcamlist = [];
		call cTab_fnc_updateLists;
		call cTab_fnc_updateUserMarkerList;
		// remove msg notification
		cTabRscLayerMailNotification cutText ["", "PLAIN"];
	};
}] call BIS_fnc_addStackedEventHandler;

/*
Figure out the scaling factor based on the current map (island) being played
Requires the scale of the map control to be at 0.001
*/
call {
	private ["_displayName","_display","_mapCtrl","_mapScreenPos","_mapScreenX_left","_mapScreenH","_mapScreenY_top","_mapScreenY_middle","_mapWorldY_top","_mapWorldY_middle"];
	
	_displayName = "cTab_mapSize_dsp";
	cTabRscLayer cutRsc [_displayName,"PLAIN",0, false];
	while {isNull (uiNamespace getVariable _displayName)} do {};
	_display = uiNamespace getVariable _displayName;
	_mapCtrl = _display displayCtrl 1110;

	// get the screen postition of _mapCtrl as [x, y, w, h]
	_mapScreenPos = ctrlPosition _mapCtrl;

	// Find the screen coordinate for the left side
	_mapScreenX_left = _mapScreenPos select 0;
	// Find the screen height
	_mapScreenH	= _mapScreenPos select 3;
	// Find the screen coordinate for top Y 
	_mapScreenY_top = _mapScreenPos select 1;
	// Find the screen coordinate for middle Y 
	_mapScreenY_middle = _mapScreenY_top + _mapScreenH / 2;

	// Get world coordinate for top Y in meters
	_mapWorldY_top = (_mapCtrl ctrlMapScreenToWorld [_mapScreenX_left,_mapScreenY_top]) select 1;
	// Get world coordinate for middle Y in meters
	_mapWorldY_middle = (_mapCtrl ctrlMapScreenToWorld [_mapScreenX_left,_mapScreenY_middle]) select 1;

	// calculate the difference between top and middle world coordinates, devide by the screen height and return
	cTabMapScaleFactor = (abs(_mapWorldY_middle - _mapWorldY_top)) / _mapScreenH;

	_display closeDisplay 0;
	uiNamespace setVariable [_displayName, displayNull];
};

cTabMapScaleUAV = 0.8 / cTabMapScaleFactor;
cTabMapScaleHCam = 0.3 / cTabMapScaleFactor;

cTabDisplayPropertyGroups = [
	["cTab_Tablet_dlg","Tablet"],
	["cTab_Android_dlg","Android"],
	["cTab_Android_dsp","Android"],
	["cTab_FBCB2_dlg","FBCB2"],
	["cTab_TAD_dsp","TAD"],
	["cTab_TAD_dlg","TAD"],
	["cTab_microDAGR_dsp","MicroDAGR"],
	["cTab_microDAGR_dlg","MicroDAGR"]
];

cTabSettings = [];

[cTabSettings,"COMMON",[
	["mode","BFT"],
	["mapScaleMin",0.1],
	["mapScaleMax",2 ^ round(sqrt(2666 * cTabMapScaleFactor / 1024))]
]] call BIS_fnc_setToPairs;

[cTabSettings,"Main",[
]] call BIS_fnc_setToPairs;

[cTabSettings,"Tablet",[
	["mode","DESKTOP"],
	["showIconText",true],
	["mapWorldPos",[]],
	["mapScale",2],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
	["mapType","SAT"],
	["uavCam",""],
	["hCam",""],
	["mapTools",true]
]] call BIS_fnc_setToPairs;

[cTabSettings,"Android",[
	["mode","BFT"],
	["showIconText",true],
	["mapWorldPos",[]],
	["mapScale",0.4],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
	["mapType","SAT"],
	["showMenu",false],
	["mapTools",true]
]] call BIS_fnc_setToPairs;

[cTabSettings,"FBCB2",[
	["mapWorldPos",[]],
	["showIconText",true],
	["mapScale",2],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
	["mapType","SAT"],
	["mapTools",true]
]] call BIS_fnc_setToPairs;

/*
TAD setup
*/
// set icon size of own vehicle on TAD
cTabTADownIconBaseSize = 18;
cTabTADownIconScaledSize = cTabTADownIconBaseSize / (0.86 / (safezoneH * 0.8));
// set TAD font colour to neon green
cTabTADfontColour = [57/255, 255/255, 20/255, 1];
// set TAD group colour to purple
cTabTADgroupColour = [255/255, 0/255, 255/255, 1];
// set TAD highlight colour to neon yellow
cTabTADhighlightColour = [243/255, 243/255, 21/255, 1];

[cTabSettings,"TAD",[
	["mapWorldPos",[]],
	["showIconText",true],
	["mapScale",2],
	["mapScaleMin",2],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO],["BLK",IDC_CTAB_SCREEN_BLACK]]],
	["mapType","SAT"],
	["mapTools",true]
]] call BIS_fnc_setToPairs;

/*
microDAGR setup
*/
// set MicroDAGR font colour to neon green
cTabMicroDAGRfontColour = [57/255, 255/255, 20/255, 1];
// set MicroDAGR group colour to purple
cTabMicroDAGRgroupColour = [25/255, 25/255, 112/255, 1];
// set MicroDAGR highlight colour to neon yellow
cTabMicroDAGRhighlightColour = [243/255, 243/255, 21/255, 1];

[cTabSettings,"MicroDAGR",[
	["mapWorldPos",[]],
	["showIconText",true],
	["mapScale",0.4],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
	["mapType","SAT"],
	["mapTools",true]
]] call BIS_fnc_setToPairs;

// set base colors from BI -- Helps keep colors matching if user changes colors in options.
_r = profilenamespace getvariable ['Map_BLUFOR_R',0];
_g = profilenamespace getvariable ['Map_BLUFOR_G',0.8];
_b = profilenamespace getvariable ['Map_BLUFOR_B',1];
_a = profilenamespace getvariable ['Map_BLUFOR_A',0.8];
cTabColorBlue = [_r,_g,_b,_a];

_r = profilenamespace getvariable ['Map_OPFOR_R',0];
_g = profilenamespace getvariable ['Map_OPFOR_G',1];
_b = profilenamespace getvariable ['Map_OPFOR_B',1];
_a = profilenamespace getvariable ['Map_OPFOR_A',0.8];
cTabColorRed = [_r,_g,_b,_a];

_r = profilenamespace getvariable ['Map_Independent_R',0];
_g = profilenamespace getvariable ['Map_Independent_G',1];
_b = profilenamespace getvariable ['Map_Independent_B',1];
_a = profilenamespace getvariable ['Map_OPFOR_A',0.8];
cTabColorGreen = [_r,_g,_b,_a];

// define vehicles that have FBCB2 monitor
if (isNil "cTab_vehicleClass_has_FBCB2") then {
	if (!isNil "cTab_vehicleClass_has_FBCB2_server") then {
		cTab_vehicleClass_has_FBCB2 = cTab_vehicleClass_has_FBCB2_server;
	} else {
		cTab_vehicleClass_has_FBCB2 = ["MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank","Truck_01_base_F","Truck_03_base_F"];
	};
};
// strip list of invalid config names and duplicates to save time checking through them later
_classNames = [];
{
	if (isClass (configfile >> "CfgVehicles" >> _x) && _classNames find _x == -1) then {
		0 = _classNames pushBack _x;
	};
} count cTab_vehicleClass_has_FBCB2;
cTab_vehicleClass_has_FBCB2 = [] + _classNames;

// define vehicles that have TAD
if (isNil "cTab_vehicleClass_has_TAD") then {
	if (!isNil "cTab_vehicleClass_has_TAD_server") then {
		cTab_vehicleClass_has_TAD = cTab_vehicleClass_has_TAD_server;
	} else {
		cTab_vehicleClass_has_TAD = ["Helicopter","Plane"];
	};
};
// strip list of invalid config names and duplicates to save time checking through them later
_classNames = [];
{
	if (isClass (configfile >> "CfgVehicles" >> _x) && _classNames find _x == -1) then {
		0 = _classNames pushBack _x;
	};
} count cTab_vehicleClass_has_TAD;
cTab_vehicleClass_has_TAD = [] + _classNames;

// define items that enable head cam
if (isNil "cTab_helmetClass_has_HCam") then {
	if (!isNil "cTab_helmetClass_has_HCam_server") then {
		cTab_helmetClass_has_HCam = cTab_helmetClass_has_HCam_server;
	} else {
		cTab_helmetClass_has_HCam = ["H_HelmetB_light","H_Helmet_Kerry","H_HelmetSpecB","H_HelmetO_ocamo","BWA3_OpsCore_Fleck_Camera","BWA3_OpsCore_Schwarz_Camera","BWA3_OpsCore_Tropen_Camera"];
	};
};
// strip list of invalid config names and duplicates to save time checking through them later
_classNames = [];
{
	if (isClass (configfile >> "CfgWeapons" >> _x) && _classNames find _x == -1) then {
		0 = _classNames pushBack _x;
	};
} count cTab_helmetClass_has_HCam;
// iterate through all class names and add child classes, so we end up with a list of helmet classes that have the defined helmet classes as parents
{
	_childClasses = "inheritsFrom _x == (configfile >> 'CfgWeapons' >> '" + _x + "')" configClasses (configfile >> "CfgWeapons");
	{
		_childClassName = configName _x;
		if (_classNames find _childClassName == -1) then {
			0 = _classNames pushBack configName _x;
		};
	} count _childClasses;
} forEach _classNames;
cTab_helmetClass_has_HCam = [] + _classNames;

// add cTab_updatePulse event handler triggered periodically by the server
["cTab_updatePulse",cTab_fnc_updateLists] call CBA_fnc_addEventHandler;

// add event handler for when user markers get updated
"cTab_userMarkerLists" addPublicVariableEventHandler {call cTab_fnc_updateUserMarkerList};


// fnc to set various text and icon sizes
cTab_fnc_update_txt_size = {
	cTabIconSize = cTabTxtFctr * 2;
	cTabIconManSize = cTabIconSize * 0.75;
	cTabGroupOverlayIconSize = cTabIconSize * 1.625;
	cTabUserMarkerArrowSize = cTabTxtFctr * 8 * cTabMapScaleFactor;
	cTabTxtSize = cTabTxtFctr / 12 * 0.035;
	cTabAirContactGroupTxtSize = cTabTxtFctr / 12 * 0.060;
	cTabAirContactSize = cTabTxtFctr / 12 * 32;
	cTabAirContactDummySize = cTabTxtFctr / 12 * 20;
};
// Beginning text and icon size
cTabTxtFctr = 12;
call cTab_fnc_update_txt_size;
cTabBFTtxt = true;

// Draw Map Tolls (Hook)
cTabDrawMapTools = false;

// Base defines.
cTabUavViewActive = false;
cTabUAVcams = [];
cTabUavScriptHandle = scriptNull;
cTabCursorOnMap = false;
cTabMapCursorPos = [0,0];
cTabMapWorldPos = [];
cTabMapScale = 0.5;

// Initialize all uiNamespace variables
uiNamespace setVariable ["cTab_Tablet_dlg", displayNull];
uiNamespace setVariable ["cTab_Android_dlg", displayNull];
uiNamespace setVariable ["cTab_Android_dsp", displayNull];
uiNamespace setVariable ["cTab_FBCB2_dlg", displayNull];
uiNamespace setVariable ["cTab_TAD_dsp", displayNull];
uiNamespace setVariable ["cTab_TAD_dlg", displayNull];
uiNamespace setVariable ["cTab_microDAGR_dsp", displayNull];
uiNamespace setVariable ["cTab_microDAGR_dlg", displayNull];

// Set up the array that will hold text messages.
player setVariable ["ctab_messages",[]];

cTabIfOpenStart = false;

/*
Function handling post dialog / display load handling (register event handlers)
Parameter 0: Interface type, 0 = Main, 1 = Secondary
Parameter 1: Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
Parameter 2: Unit to register killed eventhandler for
Parameter 3: Vehicle to register GetOut eventhandler for
Returns: TRUE

This function will define cTabIfOpen, using the following format:
Parameter 0: Interface type, 0 = Main, 1 = Secondary
Parameter 1: Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
Parameter 2: Unit we registered the killed eventhandler for
Parameter 3: ID of registered eventhandler for killed event
Optional (only if unit is in a vehicle):
Parameter 4: Vehicle we registered the GetOut eventhandler for
Parameter 5: ID of registered eventhandler for GetOut event
*/
cTab_fnc_onIfOpen = {
	if (cTabIfOpenStart || (!isNil "cTabIfOpen")) exitWith {false};
	cTabIfOpenStart = true;
	
	_interfaceType = _this select 0;
	_displayName = _this select 1;
	_player = _this select 2;
	_vehicle = _this select 3;
	
	if ([_displayName] call cTab_fnc_isDialog) then {
		closeDialog 0;
		waitUntil {!dialog};
		createDialog _displayName;
		waitUntil {dialog};
	} else {
		cTabRscLayer cutRsc [_displayName,"PLAIN",0, false];
		waitUntil {!isNull (uiNamespace getVariable _displayName)};
	};
	
	_playerKilledEhId = _player addEventHandler ["killed",{call cTab_fnc_close}];
	if (_vehicle != _player) then {
		_vehicleGetOutEhId = _vehicle addEventHandler ["GetOut",{if (_this select 2 == cTab_player) then {call cTab_fnc_close}}];
		cTabIfOpen = [_interfaceType,_displayName,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId];
	} else {
		cTabIfOpen = [_interfaceType,_displayName,_player,_playerKilledEhId,_vehicle,nil];
	};
	
	call cTab_fnc_updateInterface;
	cTabIfOpenStart = false;
	
	true
};

/*
Function handling IF_Main keydown event
Based on player equipment and the vehicle type he might be in, open or close a cTab device as Main interface.
No Parameters
Returns TRUE when action was taken (interface opened or closed)
Returns FALSE when no action was taken (i.e. player has no cTab device / is not in cTab enabled vehicle)
*/
cTab_fnc_onIfMainPressed = {
	if (cTabIfOpenStart) exitWith {false};
	_previousInterface = "";
	if (cTabUavViewActive) exitWith {
		objNull remoteControl ((crew cTabActUav) select 1);
		player switchCamera 'internal';
		cTabUavViewActive = false;
		true
	};
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 0}) exitWith {
		// close Main
		call cTab_fnc_close;
		true
	};
	if !(isNil "cTabIfOpen") then {
		_previousInterface = cTabIfOpen select 1;
		// close Secondary / Tertiary
		call cTab_fnc_close;
	};
	_player = cTab_player;
	_vehicle = vehicle _player;
	
	if ([_player,_vehicle,"TAD"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (_previousInterface != "cTab_TAD_dsp") then {
			cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
			//[0,_player,_vehicle] execVM "cTab\TAD\cTab_TAD_display_start.sqf";
			[0,"cTab_TAD_dsp",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_Android_dsp") then {
			[0,"cTab_Android_dsp",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_microDAGR_dsp") then {
			cTabMicroDAGRmode = if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) then {0} else {2};
			[0,"cTab_microDAGR_dsp",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,_vehicle,"FBCB2"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (_previousInterface != "cTab_FBCB2_dlg") then {
			[0,"cTab_FBCB2_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_Tablet_dlg") then {
			[0,"cTab_Tablet_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	
	false
};

/*
Function handling IF_Secondary keydown event
Based on player equipment and the vehicle type he might be in, open or close a cTab device as Secondary interface.
No Parameters
Returns TRUE when action was taken (interface opened or closed)
Returns FALSE when no action was taken (i.e. player has no cTab device / is not in cTab enabled vehicle)
*/
cTab_fnc_onIfSecondaryPressed = {
	if (cTabIfOpenStart) exitWith {false};
	_previousInterface = "";
	if (cTabUavViewActive) exitWith {
		objNull remoteControl ((crew cTabActUav) select 1);
		player switchCamera 'internal';
		cTabUavViewActive = false;
		true
	};
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 1}) exitWith {
		// close Secondary
		call cTab_fnc_close;
		true
	};
	if !(isNil "cTabIfOpen") then {
		_previousInterface = cTabIfOpen select 1;
		// close Main / Tertiary
		call cTab_fnc_close;
	};
	_player = cTab_player;
	_vehicle = vehicle _player;
	if ([_player,_vehicle,"TAD"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (_previousInterface != "cTab_TAD_dlg") then {
			cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
			[1,"cTab_TAD_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,_vehicle,"FBCB2"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (_previousInterface != "cTab_FBCB2_dlg") then {
			[1,"cTab_FBCB2_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_Android_dlg") then {
			[1,"cTab_Android_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_microDAGR_dlg") then {
			cTabMicroDAGRmode = if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) then {0} else {2};
			[1,"cTab_microDAGR_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_Tablet_dlg") then {
			[1,"cTab_Tablet_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	false
};

/*
Function handling IF_Tertiary keydown event
Based on player equipment and the vehicle type he might be in, open or close a cTab device as Tertiary interface.
No Parameters
Returns TRUE when action was taken (interface opened or closed)
Returns FALSE when no action was taken (i.e. player has no cTab device / is not in cTab enabled vehicle)
*/
cTab_fnc_onIfTertiaryPressed = {
	if (cTabIfOpenStart) exitWith {false};
	_previousInterface = "";
	if (cTabUavViewActive) exitWith {
		objNull remoteControl ((crew cTabActUav) select 1);
		player switchCamera 'internal';
		cTabUavViewActive = false;
		true
	};
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 2}) exitWith {
		// close Tertiary
		call cTab_fnc_close;
		true
	};
	if !(isNil "cTabIfOpen") then {
		_previousInterface = cTabIfOpen select 1;
		// close Main / Secondary
		call cTab_fnc_close;
	};
	_player = cTab_player;
	_vehicle = vehicle _player;
	if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_Tablet_dlg") then {
			[2,"cTab_Tablet_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_Android_dlg") then {
			[2,"cTab_Android_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		if (_previousInterface != "cTab_microDAGR_dlg") then {
			cTabMicroDAGRmode = if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) then {0} else {2};
			[2,"cTab_microDAGR_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,_vehicle,"TAD"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (_previousInterface != "cTab_TAD_dlg") then {
			cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
			[2,"cTab_TAD_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	if ([_player,_vehicle,"FBCB2"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (_previousInterface != "cTab_FBCB2_dlg") then {
			[2,"cTab_FBCB2_dlg",_player,_vehicle] spawn cTab_fnc_onIfOpen;
		};
		true
	};
	false
};

/*
Function handling Zoom_In keydown event
If supported cTab interface is visible, decrease map scale
Returns TRUE when action was taken
Returns FALSE when no action was taken (i.e. no interface open, or unsupported interface)
*/
cTab_fnc_onZoomInPressed = {
	if (cTabIfOpenStart || (isNil "cTabIfOpen")) exitWith {false};
	_displayName = cTabIfOpen select 1;
	if !([_displayName] call cTab_fnc_isDialog) exitWith {
		_mapScale = ([_displayName,"mapScale"] call cTab_fnc_getSettings) / 2;
		_mapScaleMin = [_displayName,"mapScaleMin"] call cTab_fnc_getSettings;
		if (_mapScale < _mapScaleMin) then {
			_mapScale = _mapScaleMin;
		};
		_mapScale = [_displayName,[["mapScale",_mapScale]]] call cTab_fnc_setSettings;
		true
	};
	false
};

/*
Function handling Zoom_Out keydown event
If supported cTab interface is visible, increase map scale
Returns TRUE when action was taken
Returns FALSE when no action was taken (i.e. no interface open, or unsupported interface)
*/
cTab_fnc_onZoomOutPressed = {
	if (cTabIfOpenStart || (isNil "cTabIfOpen")) exitWith {false};
	_displayName = cTabIfOpen select 1;
	if !([_displayName] call cTab_fnc_isDialog) exitWith {
		_mapScale = ([_displayName,"mapScale"] call cTab_fnc_getSettings) * 2;
		_mapScaleMax = [_displayName,"mapScaleMax"] call cTab_fnc_getSettings;
		if (_mapScale > _mapScaleMax) then {
			_mapScale = _mapScaleMax;
		};
		_mapScale = [_displayName,[["mapScale",_mapScale]]] call cTab_fnc_setSettings;
		true
	};
	false
};

/*
Function to close cTab interface
This function will close the currently open interface and remove any previously registered eventhandlers.
No Parameters.
No Return.
*/
cTab_fnc_close = {
	if (cTabIfOpenStart || (isNil "cTabIfOpen")) exitWith {false};
		
	// [_ifType,_displayName,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId]
	_ifType = cTabIfOpen select 0;
	_displayName = cTabIfOpen select 1;
	_player = cTabIfOpen select 2;
	_playerKilledEhId = cTabIfOpen select 3;
	_vehicle = cTabIfOpen select 4;
	_vehicleGetOutEhId = cTabIfOpen select 5;
	
	_display = uiNamespace getVariable _displayName;
	if (!isNil "_display") then {
		_display closeDisplay 0;
		uiNamespace setVariable [_displayName, displayNull];
	};
	if (!isNil "_playerKilledEhId") then {_player removeEventHandler ["killed",_playerKilledEhId]};
	if (!isNil "_vehicleGetOutEhId") then {_vehicle removeEventHandler ["GetOut",_vehicleGetOutEhId]};
	call cTab_fnc_deleteHelmetCam;
	[] spawn cTab_fnc_deleteUAVcam;
	
	// Save mapWorldPos and mapScale of current interface so it can be restored later
	call {
		if ([_displayName] call cTab_fnc_isDialog) exitWith {
			_mapScale = cTabMapScale * cTabMapScaleFactor / 0.86 * (safezoneH * 0.8);
			[_displayName,[["mapWorldPos",cTabMapWorldPos],["mapScale",_mapScale]],false] call cTab_fnc_setSettings;
		};
		[_displayName,[["mapWorldPos",[]]],false] call cTab_fnc_setSettings;
	};
	
	cTabCursorOnMap = false;
	cTabIfOpen = nil;
	cTabIfOpenStart = false;
	
	true
};

/*
Function to toggle text next to BFT icons
Parameter 0: String of uiNamespace variable for which to toggle showIconText for
Returns TRUE
*/
cTab_fnc_iconText_toggle = {
	_displayName = _this select 0;
	if (cTabBFTtxt) then {cTabBFTtxt = false} else {cTabBFTtxt = true};
	[_displayName,[["showIconText",cTabBFTtxt]]] call cTab_fnc_setSettings;
	true
};

/*
Function to toggle mapType to the next one in the list of available map types
Parameter 0: String of uiNamespace variable for which to toggle to mapType for
Returns TRUE
*/
cTab_fnc_mapType_toggle = {
	_displayName = _this select 0;
	_mapTypes = [_displayName,"mapTypes"] call cTab_fnc_getSettings;
	_currentMapType = [_displayName,"mapType"] call cTab_fnc_getSettings;
	_currentMapTypeIndex = [_mapTypes,_currentMapType] call BIS_fnc_findInPairs;
	if (_currentMapTypeIndex == count _mapTypes - 1) then {
		[_displayName,[["mapType",_mapTypes select 0 select 0]]] call cTab_fnc_setSettings;
	} else {
		[_displayName,[["mapType",_mapTypes select (_currentMapTypeIndex + 1) select 0]]] call cTab_fnc_setSettings;
	};
	true
};

/*
Function to toggle showMenu
Parameter 0: String of uiNamespace variable for which to toggle showMenu for
Returns TRUE
*/
cTab_fnc_showMenu_toggle = {
	_displayName = _this select 0;
	_showMenu = [_displayName,"showMenu"] call cTab_fnc_getSettings;
	_showMenu = !_showMenu;
	[_displayName,[["showMenu",_showMenu]]] call cTab_fnc_setSettings;
	true
};

/*
Function to toggle mode
Parameter 0: String of uiNamespace variable for which to toggle mode for
Returns TRUE
*/
cTab_fnc_mode_toggle = {
	_displayName = _this select 0;
	_mode = [_displayName,"mode"] call cTab_fnc_getSettings;
	
	call {
		if (_displayName == "cTab_Android_dlg") exitWith {
			call {
				if (_mode != "BFT") exitWith {_mode = "BFT"};
				_mode = "MESSAGE";
			};
		};
	};
	[_displayName,[["mode",_mode]]] call cTab_fnc_setSettings;
	true
};

// fnc to increase icon and text size
cTab_fnc_txt_size_inc = {
	cTabTxtFctr = cTabTxtFctr + 1;
	call cTab_fnc_update_txt_size;
};

// fnc to decrease icon and text size
cTab_fnc_txt_size_dec = {
	if (cTabTxtFctr > 1) then {cTabTxtFctr = cTabTxtFctr - 1};
	call cTab_fnc_update_txt_size;
};

// This is drawn every frame on the tablet. fnc
cTabOnDrawbft = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	cTabMapWorldPos = [_cntrlScreen] call cTab_fnc_ctrlMapCenter;
	cTabMapScale = ctrlMapScale _cntrlScreen;

	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,0] call cTab_fnc_drawBftMarkers;
	
	// draw directional arrow at own location
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on Tablet
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on Tablet
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on Tablet
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0,false] call cTab_fnc_drawHook;
	};
	
	true
};

// This is drawn every frame on the vehicle display. fnc
cTabOnDrawbftVeh = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	cTabMapWorldPos = [_cntrlScreen] call cTab_fnc_ctrlMapCenter;
	cTabMapScale = ctrlMapScale _cntrlScreen;
	
	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,0] call cTab_fnc_drawBftMarkers;
	
	// draw directional arrow at own location
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on FBCB2
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on FBCB2
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on FBCB2
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0,false] call cTab_fnc_drawHook;
	};
	
	true
};

// This is drawn every frame on the TAD display. fnc
cTabOnDrawbftTAD = {
	// is disableSerialization really required? If so, not sure this is the right place to call it
	disableSerialization;
	
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	// current position
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabMapScale, _playerPos];
	ctrlMapAnimCommit _cntrlScreen;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,1] call cTab_fnc_drawBftMarkers;
	
	// draw vehicle icon at own location
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// draw TAD overlay (two circles, one at full scale, the other at half scale + current heading)
	_cntrlScreen drawIcon ["\cTab\img\TAD_overlay_ca.paa",cTabTADfontColour,_playerPos,250,250,_heading,"",1,cTabTxtSize,"TahomaB"];
	
	// update time on TAD
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on TAD
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on TAD
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	
	// update current elevation (ASL) on TAD
	(_display displayCtrl IDC_CTAB_OSD_ELEVATION) ctrlSetText format ["%1m",[round (_playerPos select 2),3] call CBA_fnc_formatNumber];
	
	true
};

// This is drawn every frame on the TAD dialog. fnc
cTabOnDrawbftTADdialog = {
	// is disableSerialization really required? If so, not sure this is the right place to call it
	disableSerialization;
	
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	cTabMapWorldPos = [_cntrlScreen] call cTab_fnc_ctrlMapCenter;
	cTabMapScale = ctrlMapScale _cntrlScreen;
	
	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,1] call cTab_fnc_drawBftMarkers;
	
	// draw vehicle icon at own location
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_playerPos,cTabTADownIconScaledSize,cTabTADownIconScaledSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on TAD	
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position of the current player position
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on TAD
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	
	// update current elevation (ASL) on TAD
	(_display displayCtrl IDC_CTAB_OSD_ELEVATION) ctrlSetText format ["%1m",[round (_playerPos select 2),3] call CBA_fnc_formatNumber];
	
	// update hook information
	call {
		if (cTabDrawMapTools) exitWith {
			[_display,_cntrlScreen,_playerPos,cTabMapWorldPos,0,true] call cTab_fnc_drawHook;
		};
		[_display,_cntrlScreen,_playerPos,cTabMapWorldPos,1,true] call cTab_fnc_drawHook;
	};
	true
};

// This is drawn every frame on the android dialog. fnc
cTabOnDrawbftAndroid = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	cTabMapWorldPos = [_cntrlScreen] call cTab_fnc_ctrlMapCenter;
	cTabMapScale = ctrlMapScale _cntrlScreen;

	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,0] call cTab_fnc_drawBftMarkers;
	
	// draw directional arrow at own location
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on android	
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on android
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on android
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0,false] call cTab_fnc_drawHook;
	};
	
	true
};

// This is drawn every frame on the android display. fnc
cTabOnDrawbftAndroidDsp = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabMapScale, _playerPos];
	ctrlMapAnimCommit _cntrlScreen;
	
	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,0] call cTab_fnc_drawBftMarkers;
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on android	
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on android
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on android
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	true
};

// This is drawn every frame on the microDAGR display. fnc
cTabOnDrawbftmicroDAGRdsp = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	// current position
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabMapScale, _playerPos];
	ctrlMapAnimCommit _cntrlScreen;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,cTabMicroDAGRmode] call cTab_fnc_drawBftMarkers;
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	true
};

// This is drawn every frame on the microDAGR dialog. fnc
cTabOnDrawbftMicroDAGRdlg = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	cTabMapWorldPos = [_cntrlScreen] call cTab_fnc_ctrlMapCenter;
	cTabMapScale = ctrlMapScale _cntrlScreen;
	
	// current position
	_veh = vehicle cTab_player;
	_playerPos = getPosASL _veh;
	_heading = direction _veh;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,cTabMicroDAGRmode] call cTab_fnc_drawBftMarkers;
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on MicroDAGR	
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1°",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0,false] call cTab_fnc_drawHook;
	};
	
	true
};

// This is drawn every frame on the tablet uav screen. fnc
cTabOnDrawUAV = {
	if (isNil 'cTabActUav') exitWith {};
	if (cTabActUav == player) exitWith {};
	
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	_pos = getPosASL cTabActUav;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,0] call cTab_fnc_drawBftMarkers;
	
	// draw icon at own location
	_veh = vehicle cTab_player;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,getPosASL _veh,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction _veh,"", 1,cTabTxtSize,"TahomaB"];
	
	// draw icon at UAV location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabTADhighlightColour,_pos,cTabIconSize,cTabIconSize,direction cTabActUav,"",0,cTabTxtSize,"TahomaB"];
	
	_cntrlScreen ctrlMapAnimAdd [0,cTabMapScaleUAV,_pos];
	ctrlMapAnimCommit _cntrlScreen;
	true
};

// This is drawn every frame on the tablet helmet cam screen. fnc
cTabOnDrawHCam = {
	if (isNil 'cTabHcams') exitWith {};
	_camHost = cTabHcams select 2;
	
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	_pos = getPosASL _camHost;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,0] call cTab_fnc_drawBftMarkers;
	
	// draw icon at own location
	_veh = vehicle cTab_player;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,getPosASL _veh,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction _veh,"", 1,cTabTxtSize,"TahomaB"];
	
	// draw icon at helmet cam location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabTADhighlightColour,_pos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction _camHost,"",0,cTabTxtSize,"TahomaB"];
	
	_cntrlScreen ctrlMapAnimAdd [0,cTabMapScaleHCam,_pos];
	ctrlMapAnimCommit _cntrlScreen;
	true
};



//Main loop to add the key handler to the unit.
[] spawn {
	waitUntil {sleep 0.1;!(IsNull (findDisplay 46))};
	
	if (cTab_key_if_main_scancode != 0) then {
		["cTab","Toggle Main Interface",{call cTab_fnc_onIfMainPressed},[cTab_key_if_main_scancode] + cTab_key_if_main_modifiers] call cba_fnc_registerKeybind;
		["cTab","Toggle Secondary Interface",{call cTab_fnc_onIfSecondaryPressed},[cTab_key_if_secondary_scancode] + cTab_key_if_secondary_modifiers] call cba_fnc_registerKeybind;
		["cTab","Toggle Tertiary Interface",{call cTab_fnc_onIfTertiaryPressed},[cTab_key_if_tertiary_scancode] + cTab_key_if_tertiary_modifiers] call cba_fnc_registerKeybind;
		["cTab","Zoom In",{call cTab_fnc_onZoomInPressed},[cTab_key_zoom_in_scancode] + cTab_key_zoom_in_modifiers] call cba_fnc_registerKeybind;
		["cTab","Zoom Out",{call cTab_fnc_onZoomOutPressed},[cTab_key_zoom_out_scancode] + cTab_key_zoom_out_modifiers] call cba_fnc_registerKeybind;
	} else {
		["cTab","Toggle Main Interface",{call cTab_fnc_onIfMainPressed},[actionKeys "User12" select 0,false,false,false]] call cba_fnc_registerKeybind;
		["cTab","Toggle Secondary Interface",{call cTab_fnc_onIfSecondaryPressed},[actionKeys "User12" select 0,false,true,false]] call cba_fnc_registerKeybind;
		["cTab","Toggle Tertiary Interface",{call cTab_fnc_onIfTertiaryPressed},[actionKeys "User12" select 0,false,false,true]] call cba_fnc_registerKeybind;
		["cTab","Zoom In",{call cTab_fnc_onZoomInPressed},[201,true,true,false]] call cba_fnc_registerKeybind;
		["cTab","Zoom Out",{call cTab_fnc_onZoomOutPressed},[209,true,true,false]] call cba_fnc_registerKeybind;
	};
};

// fnc for user menu opperation.
cTabUsrMenuSelect = {
	private ["_type","_displayName","_display","_idcToShow","_control"];
	
	disableSerialization;
	_type = _this select 0;
	_displayName = cTabIfOpen select 1;
	_display = (uiNamespace getVariable _displayName);
	
	_idcToShow = 0;
	
	call {
		// send cTabUserSelIcon to server
		if (_type == 1) exitWith {
			cTabUserMarkerList pushBack [-1,cTabUserSelIcon call cTab_fnc_translateUserMarker];
			['cTab_addUserMarker',[call cTab_fnc_getPlayerEncryptionKey,cTabUserSelIcon]] call CBA_fnc_clientToServerEvent;
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
		};
	};
	
	// Hide all menu controls
	{ctrlShow [_x,false];} count [3300,3301,3302,3303,3304,3305,3306,3307];
	
	// Bring the menu control we want to show into position and show it
	if (_idcToShow != 0) then {
		_control = _display displayCtrl _idcToShow;
		_control ctrlSetPosition cTabUserPos;
		_control ctrlCommit 0;
		_control ctrlShow true;
	};
	
	true
};

cTabUavTakeControl = {
	if (isNil 'cTabActUav') exitWith {false};
	_uav = cTabActUav;
	_controlArray = uavControl _uav;
	_canControl = true;
	_return = true;
	
	if (count _controlArray > 0) then 
	{
		if (_controlArray select 1 == "GUNNER") then
			{
				_canControl = false;
			};
	};	
	
	if (count _controlArray > 2) then 
	{	
		if (_controlArray select 1 == "GUNNER") then
			{
				_canControl = false;
			};
		if (_controlArray select 3 == "GUNNER") then
			{
				_canControl = false;
			};	
	};
	
	if (_canControl) then
	{
		player remoteControl ((crew _uav) select 1);
		_uav switchCamera "Gunner";
		closeDialog 0;
		cTabUavViewActive = true;
		[_uav] spawn {
			_remote = _this select 0;
			waitUntil {cameraOn != _remote};
			cTabUavViewActive = false;
		};
	}else
	{
	
		["cTabUavNotAval",["Unable to access the UAV stream... Another user is streaming"]] call BIS_fnc_showNotification;
	
	};
_return;
};

cTab_msg_gui_load = {
	disableSerialization;
	_return = true;
	_display = uiNamespace getVariable (cTabIfOpen select 1);
	_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
	_msgArray = cTab_player getVariable [format ["cTab_messages_%1",_playerEncryptionKey],[]];
	_msgControl = _display displayCtrl IDC_CTAB_MSG_LIST;
	_plrlistControl = _display displayCtrl IDC_CTAB_MSG_RECIPIENTS;
	lbClear _msgControl;
	lbClear _plrlistControl;
	_plrList = playableUnits;
	_validSides = call cTab_fnc_getPlayerSides;
	
	// turn this on for testing, otherwise not really usefull, since sending to an AI controlled, but switchable unit will send the message to the player himself
	/*if (count _plrList < 1) then { _plrList = switchableUnits;};*/
	
	uiNamespace setVariable ['cTab_msg_playerList', _plrList];
	// Messages
	{
		_title =  _x select 0;
		_msgState = _x select 2;
		_img = call {
			if (_msgState == 0) exitWith {"\cTab\img\icoUnopenedmail.paa"};
			if (_msgState == 1) exitWith {"\cTab\img\icoOpenmail.paa"};
			if (_msgState == 2) exitWith {"\cTab\img\icon_sentMail_ca.paa"};
		};
		_index = _msgControl lbAdd _title;
		_msgControl lbSetPicture [_index,_img];
		_msgControl lbSetTooltip [_index,_title];
	} count _msgArray;
	
	{
		if ((side _x in _validSides) && {_x != cTab_player} && {isPlayer _x} && {[_x,["ItemcTab","ItemAndroid"]] call cTab_fnc_checkGear}) then {
			_index = _plrlistControl lbAdd name _x;
			_plrlistControl lbSetData [_index,str _x];
		};
	} count _plrList;
	
	lbSort [_plrlistControl, "ASC"];
	
	_return;
};

cTab_msg_get_mailTxt = {
	disableSerialization;
	_return = true;
	_index = _this select 1;
	_display = uiNamespace getVariable (cTabIfOpen select 1);
	_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
	_msgArray = cTab_player getVariable [format ["cTab_messages_%1",_playerEncryptionKey],[]];
	_msgName = (_msgArray select _index) select 0;
	_msgtxt = (_msgArray select _index) select 1;
	_msgState = (_msgArray select _index) select 2;
	if (_msgState == 0) then {
		_msgArray set [_index,[_msgName,_msgtxt,1]];
		cTab_player setVariable [format ["cTab_messages_%1",_playerEncryptionKey],_msgArray];
	};
	
	_nop = [] call cTab_msg_gui_load;
	
	_txtControl = _display displayCtrl IDC_CTAB_MSG_CONTENT;

	_nul = _txtControl ctrlSetText  _msgtxt;
	
	_return;
};

cTab_msg_Send = {
	private ["_return","_display","_plrLBctrl","_msgBodyctrl","_plrList","_indices","_time","_msgTitle","_msgBody","_recip","_recipientNames","_msgArray","_playerEncryptionKey"];
	disableSerialization;
	_return = true;
	_display = uiNamespace getVariable (cTabIfOpen select 1);
	_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
	_plrLBctrl = _display displayCtrl IDC_CTAB_MSG_RECIPIENTS;
	_msgBodyctrl = _display displayCtrl IDC_CTAB_MSG_COMPOSE;
	_plrList = (uiNamespace getVariable "cTab_msg_playerList");
	
	_indices = lbSelection _plrLBctrl;
	
	if (_indices isEqualTo []) exitWith {false};
	
	_time = call cTab_fnc_currentTime;
	_msgTitle = format ["%1 - %2",_time,name cTab_player];
	_msgBody = ctrlText _msgBodyctrl;
	if (_msgBody isEqualTo "") exitWith {false};
	_recipientNames = "";
	
	{
		_data = _plrLBctrl lbData _x;
		_recip = objNull;
		{
			if (_data == str _x) exitWith {_recip = _x;};
		} count _plrList;
		
		if !(IsNull _recip) then {
			if (_recipientNames isEqualTo "") then {
				_recipientNames = name _recip;
			} else {
				_recipientNames = format ["%1; %2",_recipientNames,name _recip];
			};
			
			["cTab_msg_receive",[_recip,_msgTitle,_msgBody,_playerEncryptionKey]] call CBA_fnc_whereLocalEvent;
		};
	} forEach _indices;
	
	_msgArray = cTab_player getVariable [format ["cTab_messages_%1",_playerEncryptionKey],[]];
	_msgArray pushBack [format ["%1 - %2",_time,_recipientNames],_msgBody,2];
	cTab_player setVariable [format ["cTab_messages_%1",_playerEncryptionKey],_msgArray];
	
	if (!isNil "cTabIfOpen" && {[cTabIfOpen select 1,"mode"] call cTab_fnc_getSettings == "MESSAGE"}) then {
		call cTab_msg_gui_load;
	};
	
	playSound "cTab_mailSent";
	
	_return;
};

["cTab_msg_receive",
	{
		_msgRecipient = _this select 0;
		_msgTitle = _this select 1;
		_msgBody = _this select 2;
		_msgEncryptionKey = _this select 3;
		_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
		_msgArray = _msgRecipient getVariable [format ["cTab_messages_%1",_msgEncryptionKey],[]];
		_msgArray pushBack [_msgTitle,_msgBody,0];
		
		_msgRecipient setVariable [format ["cTab_messages_%1",_msgEncryptionKey],_msgArray];
		
		if (_msgRecipient == cTab_player && {_playerEncryptionKey == _msgEncryptionKey} && {[cTab_player,["ItemcTab","ItemAndroid"]] call cTab_fnc_checkGear}) then 
		{
			playSound "cTab_phoneVibrate";
			
			if (!isNil "cTabIfOpen" && {[cTabIfOpen select 1,"mode"] call cTab_fnc_getSettings == "MESSAGE"}) then 
			{
				_nop = [] call cTab_msg_gui_load;
			}
			else
			{
				cTabRscLayerMailNotification cutRsc ["cTab_Mail_ico_disp", "PLAIN"]; //show
			};
		};
	}
] call CBA_fnc_addLocalEventHandler;
	
cTab_msg_delete_all = {
	_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
	cTab_player setVariable [format ["cTab_messages_%1",_playerEncryptionKey],[]];
};

/*
Function to execute the correct action when btnACT is pressed on Tablet
No Parameters
Returns TRUE
*/
cTab_Tablet_btnACT = {
	_mode = ["cTab_Tablet_dlg","mode"] call cTab_fnc_getSettings;
	call {
		if (_mode == "UAV") exitWith {_nop = [] call cTabUavTakeControl;};
		if (_mode == "HCAM") exitWith {["cTab_Tablet_dlg",[["mode","HCAM_FULL"]]] call cTab_fnc_setSettings;};
		if (_mode == "HCAM_FULL") exitWith {["cTab_Tablet_dlg",[["mode","HCAM"]]] call cTab_fnc_setSettings;};
	};
	true
};

/*
Function called when DELETE button is pressed in messaging mode
Parameter 0: Name of uiNameSpace variable of display
Returns false if nothing was selected for deletion, else returns true
*/
cTab_fnc_onMsgBtnDelete = {
	_displayName = _this select 0;
	_display = uiNamespace getVariable _displayName;
	_msgLbCtrl = _display displayCtrl IDC_CTAB_MSG_LIST;
	_msgLbSelection = lbSelection _msgLbCtrl;
	
	if (count _msgLbSelection == 0) exitWith {false};
	_playerEncryptionKey = call cTab_fnc_getPlayerEncryptionKey;
	_msgArray = cTab_player getVariable [format ["cTab_messages_%1",_playerEncryptionKey],[]];
	
	// run through the selection backwards as otherwise the indices won't match anymore
	for "_i" from (count _msgLbSelection) to 0 step -1 do {
		_msgArray deleteAt (_msgLbSelection select _i);
	};
	cTab_player setVariable [format ["cTab_messages_%1",_playerEncryptionKey],_msgArray];
	
	_msgTextCtrl = _display displayCtrl IDC_CTAB_MSG_CONTENT;
	_msgTextCtrl ctrlSetText "No Message Selected";
	_nop = [] call cTab_msg_gui_load;
	true
};
