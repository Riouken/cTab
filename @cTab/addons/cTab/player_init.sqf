// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

// keys.sqf parses the userconfig
#include "functions\keys.sqf";
#include "cTab_gui_macros.hpp";

//prep the arrays that will hold ctab data
cTabBFTmembers = [];
cTabBFTgroups = [];
cTabBFTvehicles = [];
cTabHcamlist = [];

if (isnil ("cTabSide")) then {cTabSide = west;}; 

// Get a rsc layer for for our displays
cTabrscLayer = ["cTab"] call BIS_fnc_rscLayer;

/*
 figure out the scaling factor based on the map being played
 on Stratis we have a map scaling factor of 3.125 km per ctrlMapScale
 Stratis map size is 8192 (Altis is 30720)
 8192 / 3.125 = 2621.44
 Divide the actual mapSize by this factor to obtain the scaling factor
 It seems to work fine
 Unfortunately the map size is not configured properly for some custom maps,
 so these have to be hard-coded until that changes.
*/
_mapSize = (getNumber (configFile>>"CfgWorlds">>worldName>>"mapSize"));
if (_mapSize == 0) then {
	switch (worldName) do {
		case "Altis": {_mapSize = 30720};
		case "Bootcamp_ACR": {_mapSize = 3840}; //Bukovina
		case "Chernarus": {_mapSize = 15360};
		case "Desert_E": {_mapSize = 2048}; //Desert
		case "fallujah": {_mapSize = 10240}; //Fallujah
		case "fata": {_mapSize = 10240}; //PR FATA
		case "Intro": {_mapSize = 5120}; //Rahmadi
		case "j198_ftb": {_mapSize = 7168}; //Ft. Benning - US Army Infantry School
		case "mbg_celle2": {_mapSize = 12288}; //Celle 2
		case "Mountains_ACR": {_mapSize = 6400}; //Takistan Mountains
		case "Porto": {_mapSize = 5120}; //Porto
		case "ProvingGrounds_PMC": {_mapSize = 2048}; //Proving Grounds
		case "Sara": {_mapSize = 20480}; //Sahrani
		case "Sara_dbe1": {_mapSize = 20480}; //United Sahrani
		case "SaraLite": {_mapSize = 10240}; //Southern Sahrani
		case "Shapur_BAF": {_mapSize = 2048}; //Shapur
		case "Stratis": {_mapSize = 8192};
		case "Takistan": {_mapSize = 12800};
		case "utes": {_mapSize = 5120}; //Utes
		case "VR": {_mapSize = 8192}; //Virtual Reality
		case "Woodland_ACR": {_mapSize = 7680}; //Bystrica
		case "Zargabad": {_mapSize = 8192};
		default {_mapSize = 8192};
	};
};
cTabMapScaleFactor = _mapSize / 2621.44;
cTabMapScaleUAV = 0.8 / cTabMapScaleFactor;
cTabMapScaleHCam = 0.3 / cTabMapScaleFactor;

cTabDisplayPropertyGroups = [
	["cTab_Tablet_dlg", "Tablet"],
	["cTab_Android_dlg", "Main"],
	["cTab_FBCB2_dlg", "FBCB2"],
	["cTab_TAD_dsp","TAD"],
	["cTab_TAD_dlg","TAD"],
	["cTab_microDAGR_dsp","MicroDAGR"],
	["cTab_microDAGR_dlg","MicroDAGR"],
	["cTab_Android_msg_dlg", "Main"]
];

cTabSettings = [];

[cTabSettings,"COMMON",[
	["mode","BFT"],
	["showIconText",true],
	["mapScaleMax",2 ^ round(sqrt(_mapSize / 1024))],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN]]],
	["mapType","SAT"]
]] call BIS_fnc_setToPairs;

[cTabSettings,"Main",[
]] call BIS_fnc_setToPairs;

[cTabSettings,"Tablet",[
	["mode","DESKTOP"],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
	["hCam",""],
	["mapTools",true]
]] call BIS_fnc_setToPairs;

[cTabSettings,"FBCB2",[
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
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
	["mapScale",2],
	["mapScaleMin",2],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO],["BLK",IDC_CTAB_SCREEN_BLACK]]],
	["mapType","SAT"]
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
	["mapScale",0.4],
	["mapScaleMin",0.1],
	["mapTypes",[["SAT",IDC_CTAB_SCREEN],["TOPO",IDC_CTAB_SCREEN_TOPO]]],
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
		_classNames pushBack _x;
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
		_classNames pushBack _x;
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
		_classNames pushBack _x;
	};
} count cTab_helmetClass_has_HCam;
// iterate through all class names and add child classes, so we end up with a list of helmet classes that have the defined helmet classes as parents
{
	_childClasses = "inheritsFrom _x == (configfile >> 'CfgWeapons' >> '" + _x + "')" configClasses (configfile >> "CfgWeapons");
	{
		_childClassName = configName _x;
		if (_classNames find _childClassName == -1) then {
			_classNames pushBack configName _x;
		};
	} count _childClasses;
} forEach _classNames;
cTab_helmetClass_has_HCam = [] + _classNames;

// add cTab_FBCB2_updatePulse event handler triggered periodically by the server
["cTab_FBCB2_updatePulse",cTab_fnc_updateLists] call CBA_fnc_addEventHandler;

/*
Function that determines if a unit sits in the front-section of a cTab enabled vehicle.
The front seciton-of a vehilce is defined as:
- Ground vehicles, everyone in the same compartment as the driver, including the driver.
  Excluded are people sitting in the cargo / passenger compartment of a Truck or APC
- Aircraft, pilot and co-pilot / gunner, but not door gunners or any passengers
Parameter 0: Unit object to check
Parameter 1: Vehicle object to check against
Parameter 2: String of device to check for (current options are: "FBCB2" and "TAD")
Returns: True if unit is in the front-section of a cTab enabled vehicle, false if not
*/
cTab_fnc_unitInEnabledVehicleSeat = {
	private ["_return","_unit","_vehicle","_vehicle","_typeClassList","_coPilotTurret"]; 
	_return = false;
	_unit = _this select 0;
	_vehicle = _this select 1;
	_type = _this select 2;
	
	switch (_type) do {
	    case "FBCB2": {_typeClassList = cTab_vehicleClass_has_FBCB2;};
		case "TAD": {_typeClassList = cTab_vehicleClass_has_TAD;};
		default {_typeClassList = [];};
	};
	
	{
		if (_vehicle isKindOf _x) exitWith {
			call {
				if (_unit == driver _vehicle) exitWith {_return = true;};
				if (_type == "FBCB2") exitWith {
					call {
						_cargoIndex = _vehicle getCargoIndex _unit; // 0-based seat number in cargo, -1 if not in cargo
						if (_cargoIndex == -1) exitWith {_return = true;}; // if not in cargo, _unit must be gunner or commander
						_cargoCompartments = getArray (configFile/"CfgVehicles"/typeOf _vehicle/"cargoCompartments");
						if (count _cargoCompartments > 1) then {
							// assume the vehicle setup is correct if there is more than one cargo compartment
							_cargoIsCoDriver = getArray (configFile/"CfgVehicles"/typeOf _vehicle/"cargoIsCoDriver");
							if (_cargoIndex < count _cargoIsCoDriver - 1) then {_return = true;};
						} else {
							// assume the vehicle setup is not correct if there is just one cargo compartment
							_transportSoldier = getNumber (configFile/"CfgVehicles"/typeOf _vehicle/"transportSoldier");
							// assume that if a vehicle carries less than 5 passengers, they all sit with the driver
							If (_transportSoldier < 5) then {_return = true;};
						};
					};
				};
				if (_type == "TAD") exitWith {
					call {
						if (_vehicle isKindOf "kyo_MH47E_base") exitWith {_coPilotTurret = 2};
						_coPilotTurret = 0; // default
					};
					if (_unit == _vehicle turretUnit[_coPilotTurret]) then {_return = true;};
				};
			};
		};
	} forEach _typeClassList;
	_return
};

/*
Function to determine map center position of given map control
Parameter 0: Map control
Returns: 2D world coordinates of map center
*/
cTab_fnc_ctrlMapCenter = {
	_ctrlScreen = _this select 0;
	_ctrlPos = ctrlPosition _ctrlScreen;
	_ctrlPosCenter = [(_ctrlPos select 0) + ((_ctrlPos select 2) / 2),(_ctrlPos select 1) + ((_ctrlPos select 3) / 2)];
	_ctrlScreen ctrlMapScreenToWorld _ctrlPosCenter
};

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

// fnc to pre-Calculate TAD and MicroDAGR map scales
cTab_fnc_update_mapScaleFactor = {
	cTabTADmapScaleCtrl = (["cTab_TAD_dsp","mapScale"] call cTab_fnc_getSettings) / cTabMapScaleFactor;
	cTabMicroDAGRmapScaleCtrl = (["cTab_microDAGR_dsp","mapScale"] call cTab_fnc_getSettings) / cTabMapScaleFactor;
	true
};
call cTab_fnc_update_mapScaleFactor;

// Base defines.
cTabUserIconList = [];
cTabUavViewActive = false;
cTabCursorOnMap = false;
cTabMapCursorPos = [0,0];

// Initialize all uiNamespace variables
uiNamespace setVariable ["cTab_Tablet_dlg", displayNull];
uiNamespace setVariable ["cTab_Android_dlg", displayNull];
uiNamespace setVariable ["cTab_FBCB2_dlg", displayNull];
uiNamespace setVariable ["cTab_TAD_dsp", displayNull];
uiNamespace setVariable ["cTab_TAD_dlg", displayNull];
uiNamespace setVariable ["cTab_microDAGR_dsp", displayNull];
uiNamespace setVariable ["cTab_microDAGR_dlg", displayNull];
uiNamespace setVariable ['cTab_Android_msg_dlg', displayNull];

// Set up the array that will hold text messages.
player setVariable ["ctab_messages",[]];

/*
Function handling post dialog / display load handling (register event handlers)
Parameter 0: Interface type, 0 = Main, 1 = Secondary
Parameter 1: Unit to register killed eventhandler for
Parameter 2: Vehicle to register GetOut eventhandler for
Parameter 3: Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
No return

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
	_player = _this select 1;
	_vehicle = _this select 2;
	_playerKilledEhId = _player addEventHandler ["killed",{call cTab_fnc_close}];
	if (_vehicle != _player) then {
		_vehicleGetOutEhId = _vehicle addEventHandler ["GetOut",{call cTab_fnc_close}];
		cTabIfOpen = [_this select 0,_this select 3,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId];
	} else {
		cTabIfOpen = [_this select 0,_this select 3,_player,_playerKilledEhId,_vehicle,nil];
	};
	call cTab_fnc_updateInterface;
};

/*
Function handling IF_Main keydown event
Based on player equipment and the vehicle type he might be in, open or close a cTab device as Main interface.
No Parameters
Returns TRUE when action was taken (interface opened or closed)
Returns FALSE when no action was taken (i.e. player has no cTab device / is not in cTab enabled vehicle)
*/
cTab_fnc_onIfMainPressed = {
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
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 1}) then {
		// close Secondary
		call cTab_fnc_close;
	};
	_player = player;
	_vehicle = vehicle _player;
	
	if ([_player,_vehicle,"TAD"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
		nul = [0,_player,_vehicle] execVM "cTab\TAD\cTab_TAD_display_start.sqf";
		true
	};
	
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\microDAGR\cTab_microDAGR_display_start.sqf";
		true
	};
	
	if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\tablet\cTab_Tablet_dialog_start.sqf";
		true
	};
	
	if ([_player,_vehicle,"FBCB2"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\bft\veh\cTab_Veh_gui_start.sqf";
		true
	};
	
	if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\bft\cTab_android_gui_start.sqf";
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
	_player = player;
	_vehicle = vehicle _player;
	if ([_player,_vehicle,"TAD"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
		if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 0}) then {
			// close Main
			call cTab_fnc_close;
		};
		call {	
			if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
				nul = [1,_player,_vehicle] execVM "cTab\tablet\cTab_Tablet_dialog_start.sqf";
			};
			cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
			nul = [1,_player,_vehicle] execVM "cTab\TAD\cTab_TAD_dialog_start.sqf";
		};
		true
	};
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 0}) then {
			// close Main
			call cTab_fnc_close;
		};
		call {
			if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
				nul = [1,_player,_vehicle] execVM "cTab\tablet\cTab_Tablet_dialog_start.sqf";
			};
			if ([_player,_vehicle,"FBCB2"] call cTab_fnc_unitInEnabledVehicleSeat) exitWith {
				nul = [1,_player,_vehicle] execVM "cTab\bft\veh\cTab_Veh_gui_start.sqf";
			};
			if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
				nul = [1,_player,_vehicle] execVM "cTab\bft\cTab_android_gui_start.sqf";
			};
			nul = [1,_player,_vehicle] execVM "cTab\microDAGR\cTab_microDAGR_dialog_start.sqf";
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
	if (isNil "cTabIfOpen") exitWith {false};
	_displayName = cTabIfOpen select 1;
	if (_displayName in ["cTab_TAD_dsp","cTab_microDAGR_dsp"]) exitWith {
		_mapScale = [_displayName,"mapScale"] call cTab_fnc_getSettings;
		_mapScaleMin = [_displayName,"mapScaleMin"] call cTab_fnc_getSettings;
		if (_mapScale / 2 > _mapScaleMin) then {
			_mapScale = _mapScale / 2;
		} else {
			_mapScale = _mapScaleMin;
		};
		_mapScale = [_displayName,[["mapScale",_mapScale]]] call cTab_fnc_setSettings;
		call cTab_fnc_update_mapScaleFactor;
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
	if (isNil "cTabIfOpen") exitWith {false};
	_displayName = cTabIfOpen select 1;
	if (_displayName in ["cTab_TAD_dsp","cTab_microDAGR_dsp"]) exitWith {
		_mapScale = [_displayName,"mapScale"] call cTab_fnc_getSettings;
		_mapScaleMax = [_displayName,"mapScaleMax"] call cTab_fnc_getSettings;
		if (_mapScale * 2 < _mapScaleMax) then {
			_mapScale = _mapScale * 2;
		} else {
			_mapScale = _mapScaleMax;
		};
		_mapScale = [_displayName,[["mapScale",_mapScale]]] call cTab_fnc_setSettings;
		call cTab_fnc_update_mapScaleFactor;
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
	if (!isNil "cTabIfOpen") then {
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
		call cTabHcamDelCam;
		cTabCursorOnMap = false;
		cTabIfOpen = nil;
	};
};

/*
Function to retrieve current in-game time in HH:MM format
No Parameters
Returns string in format "HH:MM"
*/
cTab_fnc_currentTime = {
	_date = date;
	_hour = date select 3;
	_min = date select 4;
	if (_hour < 10) then {_hour = format ["0%1", _hour];};
	if (_min < 10) then {_min = format ["0%1", _min];};
	format ["%1:%2", _hour, _min]
};

/*
Function to calculate octant from direction
Parameter 0: Octant in degrees
Return: String of matching octant
*/
cTab_fnc_degreeToOctant = {
	_dir = _this select 0;
	_octant = round (_dir / 45);
	["N ","NE","E ","SE","S ","SW","W ","NW","N "] select _octant
};

// fnc to fetch infantry marker, based on Shack Tactical ST_STHud_GetMarkerName
cTab_fnc_GetInfMarkerIcon =
{
	private "_unit";
	_unit = _this;
	if (getNumber(configFile >> "CfgVehicles" >> typeOf(_unit) >> "attendant") == 1) exitWith {
		"\A3\ui_f\data\map\vehicleicons\iconManMedic_ca.paa";
	};
	if (getNumber(configFile >> "CfgVehicles" >> typeOf(_unit) >> "engineer") == 1) exitWith {
		"\A3\ui_f\data\map\vehicleicons\iconManEngineer_ca.paa";
	};
	if (leader(_unit) == _unit) exitWith {
		"\A3\ui_f\data\map\vehicleicons\iconManLeader_ca.paa";
	};
	// This appears to be the most consistent way to detect that a weapon is an
	// MG of some sort. These pictures are the overlays for the BIS team hud.
	if (getText(configFile >> "CfgWeapons" >> primaryWeapon(_unit) >> "UIPicture") == "\a3\weapons_f\data\ui\icon_mg_ca.paa") exitWith {
		"\A3\ui_f\data\map\vehicleicons\iconManMG_ca.paa";
	};
	// Do something similar for launchers.
	if (getText(configFile >> "CfgWeapons" >> secondaryWeapon(_unit) >> "UIPicture") == "\a3\weapons_f\data\ui\icon_at_ca.paa") exitWith {
		"\A3\ui_f\data\map\vehicleicons\iconManAT_ca.paa";
	};
	"\A3\ui_f\data\map\vehicleicons\iconMan_ca.paa";
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

/*
cTab_fnc_draw_markers = {
	_cntrlScreen = _this select 0;
	{
		private ["_marker","_pos","_type","_size","_icon","_colorType","_color","_brush","_brushType","_shape","_alpha","_dir","_text"];
		_marker = _x;
		
		_pos = getMarkerPos _marker;
		_type = getMarkerType _marker;
		_size = getMarkerSize _marker;
		_icon = getText(configFile/"CfgMarkers"/_type/"Icon");
		_colorType = getMarkerColor _marker;  
		if (_icon != "" && {_colorType == "Default"}) then {
			_color = getArray(configFile/"CfgMarkers"/_type/"color");
		} else {
			_color = getArray(configFile/"CfgMarkerColors"/_colorType/"color");
		};
		if (typeName (_color select 0) == "STRING") then {
			_color = [
				call compile (_color select 0),
				call compile (_color select 1),
				call compile (_color select 2),
				call compile (_color select 3)
			];
		};
		_brushType = markerBrush _marker;
		_brush = getText(configFile/"CfgMarkerBrushes"/_brushType/"texture");
		_shape = markerShape _marker;
		_alpha = markerAlpha _marker;
		_dir = markerDir _marker;
		_text = markerText _marker;
		
		switch (_shape) do {
		    case "ICON": {
		    	_cntrlScreen drawIcon [_icon,_color,_pos,(_size select 0) * cTabIconSize,(_size select 1) * cTabIconSize,_dir,_text,0,cTabTxtSize,"TahomaB"];
		    };
		    case "RECTANGLE": {
		    	_cntrlScreen drawRectangle [_pos,_size select 0,_size select 1,_dir,_color,_brush];
			};
			case "ELLIPSE": {
		    	_cntrlScreen drawEllipse [_pos,_size select 0,_size select 1,_dir,_color,_brush];
			};
		};
	} forEach allMapMarkers;
};
*/

/*
	Function to calculate and draw hook distance, direction, grid and arrow
	Parameter 0: Display used to write hook direction, distance and grid to
	Parameter 1: Map control to draw arrow on
	Parameter 2: Position A
	Parameter 3: Position B
	Parameter 4: Mode, 0 = Reference is A, 1 = Reference is B
	Returns TRUE
*/
cTab_fnc_draw_hook = {
	private ["_display","_cntrlScreen","_pos","_secondPos"]; 
	_display = _this select 0;
	_cntrlScreen = _this select 1;
	if (_this select 4 == 0) then {
		_pos = _this select 2;
		_secondPos = _this select 3;
	} else {
		_pos = _this select 3;
		_secondPos = _this select 2;
	};
	_dirToSecondPos = [_pos,_secondPos] call BIS_fnc_dirTo;
	_dstToSecondPos = [_pos,_secondPos] call BIS_fnc_distance2D;
	(_display displayCtrl IDC_CTAB_OSD_HOOK_GRID) ctrlSetText format ["%1", mapGridPosition _secondPos];
	(_display displayCtrl IDC_CTAB_OSD_HOOK_ELEVATION) ctrlSetText format ["%1m", round getTerrainHeightASL _secondPos];
	(_display displayCtrl IDC_CTAB_OSD_HOOK_DIR) ctrlSetText format ["%1 %2",[_dirToSecondPos,3] call CBA_fnc_formatNumber,[_dirToSecondPos] call cTab_fnc_degreeToOctant];
	(_display displayCtrl IDC_CTAB_OSD_HOOK_DST) ctrlSetText format ["%1km",[_dstToSecondPos / 1000,1,2] call CBA_fnc_formatNumber];
	
	// draw arror from current position to map centre on MicroDAGR
	_cntrlScreen drawArrow [_pos,_secondPos,cTabMicroDAGRhighlightColour];
	true
};

// This is drawn every frame on the tablet. fnc
cTabOnDrawbft = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;

	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,false] call cTab_fnc_drawBftVehicles;
	[_cntrlScreen] call cTab_fnc_drawBftGroups;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	
	// draw directional arrow at own location
	_playerPos = getPosASL player;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction vehicle player,"", 1,cTabTxtSize,"TahomaB"];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0] call cTab_fnc_draw_hook;
	};
	
	true
};

// This is drawn every frame on the vehicle display. fnc
cTabOnDrawbftVeh = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,false] call cTab_fnc_drawBftVehicles;
	[_cntrlScreen] call cTab_fnc_drawBftGroups;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	// draw directional arrow at own location
	_playerPos = getPosASL player;
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction vehicle player,"", 1,cTabTxtSize,"TahomaB"];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0] call cTab_fnc_draw_hook;
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
	_playerPos = getPosASL player;
	_heading = direction vehicle player;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabTADmapScaleCtrl, _playerPos];
	ctrlMapAnimCommit _cntrlScreen;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,true] call cTab_fnc_drawBftVehicles;
	[_cntrlScreen] call cTab_fnc_drawBftGroups;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	// draw vehicle icon at own location
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// draw TAD overlay (two circles, one at full scale, the other at half scale + current heading)
	_cntrlScreen drawIcon ["\cTab\img\TAD_overlay_ca.paa",cTabTADfontColour,_playerPos,250,250,0,"",1,cTabTxtSize,"TahomaB"];
	
	// update time on TAD
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on TAD
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	true
};

// This is drawn every frame on the TAD dialog. fnc
cTabOnDrawbftTADdialog = {
	// is disableSerialization really required? If so, not sure this is the right place to call it
	disableSerialization;
	
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,true] call cTab_fnc_drawBftVehicles;
	[_cntrlScreen] call cTab_fnc_drawBftGroups;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	// current position
	_playerPos = getPosASL player;
	_heading = direction vehicle player;
	
	// draw vehicle icon at own location
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_playerPos,cTabTADownIconScaledSize,cTabTADownIconScaledSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on TAD	
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position of the current map centre on TAD
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition ([_cntrlScreen] call cTab_fnc_ctrlMapCenter)];
	
	true
};

// This is drawn every frame on the android. fnc
cTabOnDrawbftAndroid = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;

	[_cntrlScreen,true] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen,false] call cTab_fnc_drawBftVehicles;
	[_cntrlScreen] call cTab_fnc_drawBftGroups;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,getPosASL player,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction vehicle player,"", 1,cTabTxtSize,"TahomaB"];
	
	true
};

// This is drawn every frame on the microDAGR display. fnc
cTabOnDrawbftmicroDAGRdsp = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	// current position
	_playerPos = getPosASL player;
	_heading = direction vehicle player;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabMicroDAGRmapScaleCtrl, _playerPos];
	ctrlMapAnimCommit _cntrlScreen;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	true
};

// This is drawn every frame on the microDAGR dialog. fnc
cTabOnDrawbftMicroDAGRdlg = {
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	
	// current position
	_playerPos = getPosASL player;
	_heading = direction vehicle player;
	
	[_cntrlScreen,false] call cTab_fnc_drawUserMarkers;
	[_cntrlScreen] call cTab_fnc_drawBftMembers;
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_playerPos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on MicroDAGR	
	(_display displayCtrl IDC_CTAB_OSD_TIME) ctrlSetText call cTab_fnc_currentTime;
	
	// update grid position on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_GRID) ctrlSetText format ["%1", mapGridPosition _playerPos];
	
	// update current heading on MicroDAGR
	(_display displayCtrl IDC_CTAB_OSD_DIR_DEGREE) ctrlSetText format ["%1",[_heading,3] call CBA_fnc_formatNumber];
	(_display displayCtrl IDC_CTAB_OSD_DIR_OCTANT) ctrlSetText format ["%1",[_heading] call cTab_fnc_degreeToOctant];
	
	// update hook information
	if (cTabDrawMapTools) then {
		[_display,_cntrlScreen,_playerPos,cTabMapCursorPos,0] call cTab_fnc_draw_hook;
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
	
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\markers\nato\b_uav.paa",cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,"",0,cTabTxtSize,"TahomaB"];
	
	_cntrlScreen ctrlMapAnimAdd [0,cTabMapScaleUAV,_pos];
	ctrlMapAnimCommit _cntrlScreen;
	true
};

// This is drawn every frame on the tablet helmet cam screen. fnc
cTabOnDrawHCam = {
	if (isNil 'cTabHcams') exitWith {};
	_camHost = cTabHcams select 2;
	if (_camHost == vehicle player) exitWith {};
	
	_cntrlScreen = _this select 0;
	_display = ctrlParent _cntrlScreen;
	_pos = getPosASL _camHost;
	
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabColorBlue,_pos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,direction _camHost,"",0,cTabTxtSize,"TahomaB"];
	
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
		["cTab","Zoom In",{call cTab_fnc_onZoomInPressed},[cTab_key_zoom_in_scancode] + cTab_key_zoom_in_modifiers] call cba_fnc_registerKeybind;
		["cTab","Zoom Out",{call cTab_fnc_onZoomOutPressed},[cTab_key_zoom_out_scancode] + cTab_key_zoom_out_modifiers] call cba_fnc_registerKeybind;
	} else {
		["cTab","Toggle Main Interface",{call cTab_fnc_onIfMainPressed},[actionKeys "User12" select 0,false,false,false]] call cba_fnc_registerKeybind;
		["cTab","Toggle Secondary Interface",{call cTab_fnc_onIfSecondaryPressed},[actionKeys "User12" select 0,false,true,false]] call cba_fnc_registerKeybind;
		["cTab","Zoom In",{call cTab_fnc_onZoomInPressed},[201,true,true,false]] call cba_fnc_registerKeybind;
		["cTab","Zoom Out",{call cTab_fnc_onZoomOutPressed},[209,true,true,false]] call cba_fnc_registerKeybind;
	};
};

// fnc for user menu opperation.
cTabUsrMenuSelect = {
	disableSerialization;
	_type = _this select 0;
	_dlg = cTabIfOpen select 1;
	_display = (uiNamespace getVariable _dlg);
	_return = True;
	
	switch (_type) do
	{
		case 0:
		{
			{ctrlShow [_x, False];} forEach [3300,3301,3302,3303,3304,3305,3306,3307];
		};
		
		case 11:
		{
			ctrlShow [3300, False];
			_control = _display displayCtrl 3301;
			ctrlShow [3301, True];
			_control ctrlSetPosition cTabUserPos;
			_control ctrlCommit 0;
		};

		case 12:
		{
			ctrlShow [3301, False];		
			_control = _display displayCtrl 3303;
			ctrlShow [3303, True];
			_control ctrlSetPosition cTabUserPos;
			_control ctrlCommit 0;
		};
		
		case 13:
		{
			ctrlShow [3303, False];
			ctrlShow [3307, False];
			_control = _display displayCtrl 3304;
			ctrlShow [3304, True];
			_control ctrlSetPosition cTabUserPos;
			_control ctrlCommit 0;
		};
		
		case 14:
		{
			if (cTabUserSelIcon select 1 != "\A3\ui_f\data\map\markers\nato\o_inf.paa") exitWith {
				cTabUserSelIcon set [2,""];
				[13] call cTabUsrMenuSelect;
			};
			ctrlShow [3303, False];
			_control = _display displayCtrl 3307;
			ctrlShow [3307, True];
			_control ctrlSetPosition cTabUserPos;
			_control ctrlCommit 0;
		};
		
		case 10:
		{
			ctrlShow [3304, False];
		};
		
		case 21:
		{
			ctrlShow [3300, False];
			_control = _display displayCtrl 3305;
			ctrlShow [3305, True];
			_control ctrlSetPosition cTabUserPos;
			_control ctrlCommit 0;
		};
		
		case 20:
		{
			ctrlShow [3305, False];
		};
		
		case 31:
		{
			ctrlShow [3300, False];
			_control = _display displayCtrl 3306;
			ctrlShow [3306, True];
			_control ctrlSetPosition cTabUserPos;
			_control ctrlCommit 0;
		};
			
		case 30:
		{
			ctrlShow [3306, False];
		};			
				
	};

_return;

};

// fnc to push out data from the user placed icon to all clents.
cTabUserIconPush = {
	// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
	
	//if ((count cTabUserIconList) == 0) exitWith {};
	
	_return = true;
	_nop = [cTabUserIconList,cTabUserSelIcon] call BIS_fnc_arrayPush;
	//hint str cTabUserIconList;
	publicVariable "cTabUserIconList";
	_return;
};

// fnc to delete cameras after UAV interface is closed.
cTabUavDelCam = {
	player cameraEffect ["terminate","back"];
	_camArray = player getVariable "cTabUAVcams";
	_targets = _camArray select 2;
	camDestroy (_camArray select 0);
	camDestroy (_camArray select 1);
	{deleteVehicle _x;} forEach _targets;
	player setVariable ["cTabUAVcams",nil];
	cTabActUav = nil;
	true
};

// fnc to delete cameras after helmet cam interface is closed.
cTabHcamDelCam = {
	if (!isNil "cTabHcams") then {
		_cam = cTabHcams select 0;
		_cam cameraEffect ["TERMINATE","BACK"];
		camDestroy _cam;
		deleteVehicle (cTabHcams select 1);
		cTabHcams = nil;
	};
	true
};

cTabUavTakeControl = {
	if (isNil 'cTabActUav') exitWith {false};
	_controlArray = uavControl cTabActUav;
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
		player remoteControl ((crew cTabActUav) select 1);
		 cTabActUav switchCamera "Gunner";
		closeDialog 0;
		cTabUavViewActive = true;
		[cTabActUav] spawn {
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

cTab_msg_gui_load = 
{
	disableSerialization;
	_return = true;
	_display = (uiNamespace getVariable "cTab_Tablet_dlg");
	_msgarry = player getVariable ["ctab_messages",[]];
	_msgControl = _display displayCtrl 15000;
	_plrlistControl = _display displayCtrl 15010;
	lbClear 15000;
	lbClear 15010;
	_plrList = playableUnits;
	
	if (count _plrList < 1) then { _plrList = switchableUnits;};
	
	uiNamespace setVariable ['cTab_msg_playerList', _plrList];
	// Messages
	if ((count _msgarry) > 0) then 
	{
		{		
			_title =  _x select 0;
			_msgIsRead = _x select 2;
			_img = "";
			if (_msgIsRead) then 
			{
				_img = "\cTab\img\icoOpenmail.paa";
			}
			else
			{
				_img = "\cTab\img\icoUnopenedmail.paa";
			};
		
			_index = _msgControl lbAdd _title;
			_index = _msgControl lbSetPicture [_forEachIndex,_img];
		
		} forEach _msgarry;
	};
	
	{
		_index = _plrlistControl lbAdd name _x;
		if (!([_x,["ItemcTab"]] call cTab_fnc_checkGear)) then { _plrlistControl lbSetColor [_forEachIndex, [1,0,0,1]];};
		
	} forEach _plrList;
	
	367 cutText ["", "PLAIN"];
	_return;
};

cTab_msg_get_mailTxt = 
{
	disableSerialization;
	_return = true;
	_index = _this select 1;
	_display = (uiNamespace getVariable "cTab_Tablet_dlg");
	_msgArray = player getVariable ["ctab_messages",[]];
	_msgName = (_msgArray select _index) select 0;
	_msgtxt = (_msgArray select _index) select 1;
	_msgArray set [_index,[_msgName,_msgtxt,true]];
	   
	player setVariable ["ctab_messages",_msgArray];
	
	_nop = [] call cTab_msg_gui_load;
	
	_txtControl = _display displayCtrl 18510;

	_nul = _txtControl ctrlSetText  _msgtxt;
	
	_return;
};

cTabGetTime = 
{
	_return = "";
    _seconds = time;   
    _hours = floor(_seconds / 3600);
    _seconds = _seconds - (_hours * 3600);
    _tensOfMinutes = floor(_seconds / 600);
    _seconds = _seconds - (_tensOfMinutes * 600);
    _minutes = floor(_seconds / 60);
    _seconds = _seconds - (_minutes * 60);
    _tensOfSeconds = floor(_seconds / 10);
    _wholeSeconds = floor(_seconds - (_tensOfSeconds * 10));

    _return = format ["%1:%2%3:%4%5", _hours, _tensOfMinutes, _minutes,_tensOfSeconds, _wholeSeconds];
	
	_return;

};

cTab_msg_Send = 
{
	disableSerialization;
	_return = true;
	_display = (uiNamespace getVariable "cTab_Tablet_dlg");
	_plrLBctrl = _display displayCtrl 15010;
	_msgBodyctrl = _display displayCtrl 14000;
	_plrList = (uiNamespace getVariable "cTab_msg_playerList");
	
	_indices = lbSelection _plrLBctrl;
	
	if (_indices isEqualTo []) exitWith {false};
	
	_hr = date select 3;
	_min = date select 4;
	_msgTitle = str _hr + ":"+ str _min + " - " + name player;
	_msgBody = ctrlText _msgBodyctrl;
	
	{
		_recip = _plrList select _x;
		
		["cTab_msg_receive", [_recip,_msgTitle,_msgBody]] call CBA_fnc_whereLocalEvent;
		
	} forEach _indices;
	
	_nop = ["cTabMsgSent",[]] call bis_fnc_showNotification;
	_return;
};

["cTab_msg_receive", 
  { 
       _msgTitle = _this select 1;
	   _msgBody = _this select 2;
	   _msgarry = player getVariable ["ctab_messages",[]];
	   _msgarry set [count _msgarry,[_msgTitle,_msgBody,false]];
	   
	   player setVariable ["ctab_messages",_msgarry];
	   
	   if ([player,["ItemcTab"]] call cTab_fnc_checkGear) then 
	   {
			_nop = ["cTabNewMsg",["You have a new Text Message!"]] call bis_fnc_showNotification;
	   
			if (!isNil "cTabIfOpen" && {cTabIfOpen select 1 == "cTab_Tablet_dlg"}) then 
			{
				_nop = [] call cTab_msg_gui_load;
				367 cutRsc ["cTab_Mail_ico_disp", "PLAIN"];
			}
			else
			{
				367 cutRsc ["cTab_Mail_ico_disp", "PLAIN"]; //show
			};
		};
  }
] call CBA_fnc_addLocalEventHandler; 
	
cTab_msg_delete_all = 
{
	player setVariable ["ctab_messages",[]];
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

// I think we should start breaking out the functions like this to help keep it organized. This function file is starting to get pretty long.
// Eventualy we can move the rest to this format, but all work going forward I will be breaking the functions into their respective folders and just #including them here.

#include <\cTab\msg\cTab_fnc_msg.hpp>	

