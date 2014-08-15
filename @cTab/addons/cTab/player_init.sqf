// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

// keys.sqf parses the userconfig
#include "functions\keys.sqf";

// add cTab_FBCB2_updatePulse event handler triggered periodically by the server
["cTab_FBCB2_updatePulse",{
	[] spawn {
		call cTab_fnc_update_lists;
	};
}] call CBA_fnc_addEventHandler;

//prep the arrays that will hold ctab data
cTabBFTlist = [];
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
		case "j198_ftb": {_mapSize = 7168}; //Ft. Benning - US Army Infantry School
		case "mbg_celle2": {_mapSize = 12288}; //Celle 2
		case "ProvingGrounds_PMC": {_mapSize = 2048}; //ProvingGrounds_PMC
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

/*
TAD setup
*/
// set initial TAD map scale in km
cTabTADmapScale = 2;
cTabTADmapScaleCtrl = cTabTADmapScale / cTabMapScaleFactor;
// define min and max TAD map scales in km
cTabTADmapScaleMin = 2;
cTabTADmapScaleMax = 2 ^ round(sqrt(_mapSize / 1024));
// set icon size of own vehicle on TAD
cTabTADownIconBaseSize = 18;
cTabTADownIconScaledSize = cTabTADownIconBaseSize / (0.86 / (safezoneH * 0.8));
// set TAD font colour to neon green
cTabTADfontColour = [57/255, 255/255, 20/255, 1];
// set TAD group colour to purple
cTabTADgroupColour = [25/255, 25/255, 112/255, 1];
// set TAD highlight colour to neon yellow
cTabTADhighlightColour = [243/255, 243/255, 21/255, 1];

/*
microDAGR setup
*/
// set initial TAD map scale in km
cTabMicroDAGRmapScale = 0.4;
cTabMicroDAGRmapScaleCtrl = cTabMicroDAGRmapScale / cTabMapScaleFactor;
// define min and max TAD map scales in km
cTabMicroDAGRmapScaleMin = 0.1;
cTabMicroDAGRmapScaleMax = 2 ^ round(sqrt(_mapSize / 1024));
// set TAD font colour to neon green
cTabMicroDAGRfontColour = [57/255, 255/255, 20/255, 1];
// set TAD group colour to purple
cTabMicroDAGRgroupColour = [25/255, 25/255, 112/255, 1];
// set TAD highlight colour to neon yellow
cTabMicroDAGRhighlightColour = [243/255, 243/255, 21/255, 1];

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
		cTab_vehicleClass_has_FBCB2 = ["MRAP_01_base_F","Wheeled_APC_F","Tank","Truck_01_base_F"];
	};
};

// define vehicles that have TAD
if (isNil "cTab_vehicleClass_has_TAD") then {
	if (!isNil "cTab_vehicleClass_has_TAD_server") then {
		cTab_vehicleClass_has_TAD = cTab_vehicleClass_has_TAD_server;
	} else {
		cTab_vehicleClass_has_TAD = ["Helicopter","Plane"];
	};
};

// fnc to set various text and icon sizes
cTab_fnc_update_txt_size = {
	cTabIconSize = cTabTxtFctr * 2;
	cTabTxtSize = cTabTxtFctr / 12 * 0.035;
	cTabAirContactSize = cTabTxtFctr / 12 * 32;
	cTabAirContactDummySize = cTabTxtFctr / 12 * 20;
};
// Beginning text and icon size
cTabTxtFctr = 12;
call cTab_fnc_update_txt_size;
cTabBFTtxt = true;

//set up array for user stored icons, data waits here until it is sent out to other clients.
// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
cTabUserSelIcon = [[],"","",500,[],""];

// Base defines.
cTabUserIconList = [];
cTabUavViewActive = false;
cTabHCamViewActive = false;

// Initialize all uiNamespace variables
uiNamespace setVariable ["cTab_main_dlg", displayNull];
uiNamespace setVariable ["cTab_Android_dlg", displayNull];
uiNamespace setVariable ["cTab_Veh_dlg", displayNull];
uiNamespace setVariable ["cTab_TAD_dsp", displayNull];
uiNamespace setVariable ["cTab_TAD_display", displayNull];
uiNamespace setVariable ["cTab_hCam_dlg", displayNull];
uiNamespace setVariable ["cTab_uav_dlg", displayNull];

// Set up the array that will hold text messages.
player setVariable ["ctab_messages",[]];

// fnc handling post dialog / display load handling (register event handlers)
cTab_fnc_onIfOpen = {
	_player = _this select 1;
	_vehicle = _this select 2;
	_playerKilledEhId = _player addEventHandler ["killed",{call cTab_fnc_close}];
	if (_vehicle != _player) then {
		_vehicleGetOutEhId = _vehicle addEventHandler ["GetOut",{call cTab_fnc_close}];
		cTabIfOpen = [_this select 0,_this select 3,_this select 4,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId];
	} else {
		cTabIfOpen = [_this select 0,_this select 3,_this select 4,_player,_playerKilledEhId,_vehicle,nil];
	};
	call cTab_fnc_OSD_update;
};

// fnc handling IF_Main keydown event
cTab_fnc_onIfMainPressed = {
	if (cTabUavViewActive) exitWith {
		objNull remoteControl ((crew cTabActUav) select 1);
		player switchCamera 'internal';
		cTabUavViewActive = false;
		true
	};
	if (cTabHCamViewActive) exitWith {
		objNull remoteControl cTabActHcam;
		player switchCamera 'internal';
		cTabHCamViewActive = false;
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
	
	if (({_vehicle isKindOf _x} count cTab_vehicleClass_has_TAD) > 0 && {_player in [driver _vehicle,_vehicle turretUnit[0]]}) exitWith {
		cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
		nul = [0,_player,_vehicle] execVM "cTab\TAD\cTab_TAD_gui_start.sqf";
		true
	};
	
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\microDAGR\cTab_microDAGR_display_start.sqf";
		true
	};
	
	// -- todo - update to CBA_fnc_find to increase performance in EH.
	if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\cTab_gui_start.sqf";
		true
	};
	
	if (({_vehicle isKindOf _x} count cTab_vehicleClass_has_FBCB2) > 0 && {
			!((_player in (assignedCargo _vehicle)) && {[typeOf _vehicle] call BIS_fnc_crewCount >= 3})
		}) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\bft\veh\cTab_Veh_gui_start.sqf";
		true
	};
	
	// -- todo - update to CBA_fnc_find to increase performance in EH.
	if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
		nul = [0,_player,_vehicle] execVM "cTab\bft\cTab_android_gui_start.sqf";
		true
	};
	false
};

// fnc handling IF_Secondary keydown event
cTab_fnc_onIfSecondaryPressed = {
	_return = false;
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 1}) exitWith {
		// close Secondary
		call cTab_fnc_close;
		true
	};
	_player = player;
	_vehicle = vehicle _player;
	if (({_vehicle isKindOf _x} count cTab_vehicleClass_has_TAD) > 0 && {_player in [driver _vehicle,_vehicle turretUnit[0]]}) exitWith {
		if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 0}) then {
			// close Main
			call cTab_fnc_close;
		};
		if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
			nul = [1,_player,_vehicle] execVM "cTab\cTab_gui_start.sqf";
			_return = true;
		};
		cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
		nul = [1,_player,_vehicle] execVM "cTab\TAD\cTab_TAD_dialog_start.sqf";
		true
	};
	if ([_player,["ItemMicroDAGR"]] call cTab_fnc_checkGear) exitWith {
		if (!isNil "cTabIfOpen" && {cTabIfOpen select 0 == 0}) then {
			// close Main
			call cTab_fnc_close;
		};
		if ([_player,["ItemcTab"]] call cTab_fnc_checkGear) exitWith {
			nul = [1,_player,_vehicle] execVM "cTab\cTab_gui_start.sqf";
			_return = true;
		};
		if (({_vehicle isKindOf _x} count cTab_vehicleClass_has_FBCB2) > 0 && {
			!((_player in (assignedCargo _vehicle)) && {[typeOf _vehicle] call BIS_fnc_crewCount >= 3})
		}) exitWith {
			nul = [1,_player,_vehicle] execVM "cTab\bft\veh\cTab_Veh_gui_start.sqf";
			_return = true;
		};
		if ([_player,["ItemAndroid"]] call cTab_fnc_checkGear) exitWith {
			nul = [1,_player,_vehicle] execVM "cTab\bft\cTab_android_gui_start.sqf";
			_return = true;
		};
		nul = [1,_player,_vehicle] execVM "cTab\microDAGR\cTab_microDAGR_dialog_start.sqf";
		true
	};
	_return
};

// fnc handling Zoom_In keydown event
cTab_fnc_onZoomInPressed = {
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 2 == 'cTab_TAD_dsp'}) exitWith {
		if (cTabTADmapScale / 2 > cTabTADmapScaleMin) then {
			cTabTADmapScale = cTabTADmapScale / 2;
		} else {
			cTabTADmapScale = cTabTADmapScaleMin;
		};
		cTabTADmapScaleCtrl = cTabTADmapScale / cTabMapScaleFactor;
		call cTab_fnc_OSD_update;
		true
	};
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 2 == 'cTab_microDAGR_dsp'}) exitWith {
		if (cTabMicroDAGRmapScale / 2 > cTabMicroDAGRmapScaleMin) then {
			cTabMicroDAGRmapScale = cTabMicroDAGRmapScale / 2;
		} else {
			cTabMicroDAGRmapScale = cTabMicroDAGRmapScaleMin;
		};
		cTabMicroDAGRmapScaleCtrl = cTabMicroDAGRmapScale / cTabMapScaleFactor;
		true
	};
	false
};

// fnc handling Zoom_Out keydown event
cTab_fnc_onZoomOutPressed = {
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 2 == 'cTab_TAD_dsp'}) exitWith {
		if (cTabTADmapScale * 2 < cTabTADmapScaleMax) then {
			cTabTADmapScale = cTabTADmapScale * 2;
		} else {
			cTabTADmapScale = cTabTADmapScaleMax;
		};
		cTabTADmapScaleCtrl = cTabTADmapScale / cTabMapScaleFactor;
		call cTab_fnc_OSD_update;
		true
	};
	if (!isNil "cTabIfOpen" && {cTabIfOpen select 2 == 'cTab_microDAGR_dsp'}) exitWith {
		if (cTabMicroDAGRmapScale * 2 < cTabMicroDAGRmapScaleMax) then {
			cTabMicroDAGRmapScale = cTabMicroDAGRmapScale * 2;
		} else {
			cTabMicroDAGRmapScale = cTabMicroDAGRmapScaleMax;
		};
		cTabMicroDAGRmapScaleCtrl = cTabMicroDAGRmapScale / cTabMapScaleFactor;
		true
	};
	false
};

// fnc to close cTab
cTab_fnc_close = {
	if (!isNil "cTabIfOpen") then {
		// [_ifType,_dialogId,_displayCtrl,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId]
		_ifType = cTabIfOpen select 0;
		_dialogId = cTabIfOpen select 1;
		_displayCtrl = cTabIfOpen select 2;
		_player = cTabIfOpen select 3;
		_playerKilledEhId = cTabIfOpen select 4;
		_vehicle = cTabIfOpen select 5;
		_vehicleGetOutEhId = cTabIfOpen select 6;
		
		if (!isNil "_dialogId" && {!isNull (findDisplay _dialogId)}) then {closeDialog 0;};
		if (!isNil "_displayCtrl") then {
			(uiNamespace getVariable _displayCtrl) closeDisplay 0;
			uiNamespace setVariable [_displayCtrl, displayNull];
		};
		if (!isNil "_playerKilledEhId") then {_player removeEventHandler ["killed",_playerKilledEhId]};
		if (!isNil "_vehicleGetOutEhId") then {_vehicle removeEventHandler ["GetOut",_vehicleGetOutEhId]};
		cTabIfOpen = nil;
	};
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

// fnc to toggle text next to icons
cTab_fnc_txt_tggl = {
	if (cTabBFTtxt) then {cTabBFTtxt = false} else {cTabBFTtxt = true};
	call cTab_fnc_OSD_update;
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

// fnc to updated OSD elements
cTab_fnc_OSD_update = {
	disableSerialization;
	_dialogId = cTabIfOpen select 1;
	_displayCtrl = cTabIfOpen select 2;
	if (!isNil "_dialogId") then {
		if (_dialogId == 1755424) exitWith {
			_display = uiNamespace getVariable "cTab_TAD_dialog";
			_cntrlScreen = _display displayCtrl 2610;
			if (cTabBFTtxt) then {
				_cntrlScreen ctrlSetText "ON";
			} else {
				_cntrlScreen ctrlSetText "OFF";
			};
		};
	} else {
		if (_displayCtrl == "cTab_TAD_dsp") exitWith {
			_display = uiNamespace getVariable _displayCtrl;
			// update current map scale on TAD
			// divide by 2 because we want to display the radius, not the diameter
			(_display displayCtrl 1204) ctrlSetText format ["%1", cTabTADmapScale / 2];
			
			_cntrlScreen = _display displayCtrl 2610;
			if (cTabBFTtxt) then {
				_cntrlScreen ctrlSetText "ON";
			} else {
				_cntrlScreen ctrlSetText "OFF";
			};
		};
	};
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

// This is drawn every frame on the tablet. fnc
cTabOnDrawbft = {

	_return = true;
	_display = (uiNamespace getVariable "cTab_main_dlg");
	_cntrlScreen = _display displayCtrl 1201;

	{
		_obj = _x select 0;
		_texture = _x select 1;
		_text = "";
		_pos = getPosASL _obj;
		
		if (cTabBFTtxt) then {_text = _x select 2;};
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];


	} forEach cTabBFTlist;
	
	
	if ((count cTabUserIconList) != 0) then 
	{
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			//hint str _x;
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];

			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
	
			if (_dir < 360) then
			{
			
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
		
			};

		
		} forEach cTabUserIconList;
	};
	
_return;
};

// This is drawn every frame on the vehicle display. fnc
cTabOnDrawbftVeh = {

	_return = true;
	_display = (uiNamespace getVariable "cTab_Veh_dlg");
	_cntrlScreen = _display displayCtrl 1201;

	{
		_obj = _x select 0;
		_texture = _x select 1;
		_text = "";
		_pos = getPosASL _obj;
		
		if (cTabBFTtxt) then {_text = _x select 2;};
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];


	} forEach cTabBFTlist;
	
	
	if ((count cTabUserIconList) != 0) then 
	{
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			//hint str _x;
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];

			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
	
			if (_dir < 360) then
			{
			
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
		
			};

		
		} forEach cTabUserIconList;
	};
	
_return;
};

// This is drawn every frame on the TAD display. fnc
cTabOnDrawbftTAD = {
	// is disableSerialization really required? If so, not sure this is the right place to call it
	disableSerialization;
	
	_return = true;
	_display = (uiNamespace getVariable "cTab_TAD_dsp");
	_cntrlScreen = _display displayCtrl 1201;
	
	//[_cntrlScreen] call cTab_fnc_draw_markers;
	
	// current position
	_mapCentrePos = getPosASL player;
	_heading = direction vehicle player;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabTADmapScaleCtrl, _mapCentrePos];
	ctrlMapAnimCommit _cntrlScreen;
	
	{
		_obj = _x select 0;
		// check if the player is not occupying the vehicle we are about to draw an icon for and don't draw if that's the case
		if (!(player in _obj)) then
		{
			_texture = _x select 1;
			_text = "";
			_pos = getPosASL _obj;
			if (cTabBFTtxt) then {_text = _x select 2;};
			// check if object is an air vehicle
			if (_obj isKindOf "Air") then
			{
				// check if air contact and player are in the same group group, if so, change _symbolColour
				if (player in units _obj) then {
					_groupIndex = _x select 3;
					_cntrlScreen drawIcon ["\cTab\img\icon_air_contact_ca.paa",cTabTADgroupColour,_pos,cTabAirContactSize,cTabAirContactSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
					//_cntrlScreen drawRectangle [_pos,30,40,0,[0,0,0,1],"#(rgb,1,1,1)color(0,0,0,1)"];
					_cntrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabTADgroupColour,_pos,0,0,0,_groupIndex,0,cTabTxtSize,"TahomaB","center"];
				} else {
					// draw air contact icon and dummy icon for the text to have a better alignment
					_cntrlScreen drawIcon ["\cTab\img\icon_air_contact_ca.paa",cTabTADfontColour,_pos,cTabAirContactSize,cTabAirContactSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
					//_cntrlScreen drawRectangle [[(_pos select 0) + 160 + 80,_pos select 1],160,40,0,[0,0,0,1],"#(rgb,1,1,1)color(0,0,0,1)"];
					_cntrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabTADfontColour,_pos,cTabAirContactDummySize,cTabAirContactDummySize,0,_text,0,cTabTxtSize,"TahomaB"];
				};
			}
			else
			{
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,_text,0,cTabTxtSize,"TahomaB"];
			};
		};
	} forEach cTabBFTlist;
	
	if ((count cTabUserIconList) != 0) then 
	{
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];
			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
			if (_dir < 360) then
			{
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
			};
		} forEach cTabUserIconList;
	};
	
	// draw vehicle icon at own location
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_mapCentrePos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// draw TAD overlay (two circles, one at full scale, the other at half scale + current heading)
	_cntrlScreen drawIcon ["\cTab\img\TAD_overlay_ca.paa",cTabTADfontColour,_mapCentrePos,250,250,0,"",1,cTabTxtSize,"TahomaB"];
	
	// update time on TAD
	_hour = date select 3;
	if (_hour < 10) then {
		_hour = format ["0%1", _hour];
	};
	_min = date select 4;
	if (_min < 10) then {
		_min = format ["0%1", _min];
	};

	(_display displayCtrl 1202) ctrlSetText format ["%1:%2", _hour, _min];
	
	// update grid position on TAD
	(_display displayCtrl 1203) ctrlSetText format ["%1", mapGridPosition _mapCentrePos];
	
	_return;
};

// This is drawn every frame on the TAD dialog. fnc
cTabOnDrawbftTADdialog = {
	// is disableSerialization really required? If so, not sure this is the right place to call it
	disableSerialization;
	_return = true;
	_display = (uiNamespace getVariable "cTab_TAD_dialog");
	_cntrlScreen = _display displayCtrl 1201;
	
	//[_cntrlScreen] call cTab_fnc_draw_markers;
	
	// current position
	_mapCentrePos = getPosASL player;
	_heading = direction vehicle player;
	
	{
		_obj = _x select 0;
		// check if the player is not occupying the vehicle we are about to draw an icon for and don't draw if that's the case
		if (!(player in _obj)) then
		{
			_texture = _x select 1;
			_text = "";
			_pos = getPosASL _obj;
			if (cTabBFTtxt) then {_text = _x select 2;};
			// check if object is an air vehicle
			if (_obj isKindOf "Air") then
			{
				// check if air contact and player are in the same group group, if so, change _symbolColour
				if (player in units _obj) then {
					_groupIndex = _x select 3;
					_cntrlScreen drawIcon ["\cTab\img\icon_air_contact_ca.paa",cTabTADgroupColour,_pos,cTabAirContactSize,cTabAirContactSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
					//_cntrlScreen drawRectangle [_pos,30,40,0,[0,0,0,1],"#(rgb,1,1,1)color(0,0,0,1)"];
					_cntrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabTADgroupColour,_pos,0,0,0,_groupIndex,0,cTabTxtSize,"TahomaB","center"];
				} else {
					// draw air contact icon and dummy icon for the text to have a better alignment
					_cntrlScreen drawIcon ["\cTab\img\icon_air_contact_ca.paa",cTabTADfontColour,_pos,cTabAirContactSize,cTabAirContactSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
					//_cntrlScreen drawRectangle [[(_pos select 0) + 160 + 80,_pos select 1],160,40,0,[0,0,0,1],"#(rgb,1,1,1)color(0,0,0,1)"];
					_cntrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabTADfontColour,_pos,cTabAirContactDummySize,cTabAirContactDummySize,0,_text,0,cTabTxtSize,"TahomaB"];
				};
			}
			else
			{
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,_text,0,cTabTxtSize,"TahomaB"];
			};
		};
	} forEach cTabBFTlist;
	
	if ((count cTabUserIconList) != 0) then 
	{
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];
			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
			if (_dir < 360) then
			{
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
			};
		} forEach cTabUserIconList;
	};
	
	// draw vehicle icon at own location
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_mapCentrePos,cTabTADownIconScaledSize,cTabTADownIconScaledSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	// update time on TAD
	_hour = date select 3;
	if (_hour < 10) then {
		_hour = format ["0%1", _hour];
	};
	_min = date select 4;
	if (_min < 10) then {
		_min = format ["0%1", _min];
	};

	(_display displayCtrl 1202) ctrlSetText format ["%1:%2", _hour, _min];
	
	// update grid position of the current map centre [0.5,0.5] on TAD
	(_display displayCtrl 1203) ctrlSetText format ["%1", mapGridPosition (_cntrlScreen ctrlMapScreenToWorld [0.5,0.5])];
	/*
	// update current map scale on TAD
	// divide by 2 because we want to display the radius, not the diameter
	(_display displayCtrl 1204) ctrlSetText format ["%1", cTabTADmapScale / 2];
	*/
	_return;
};

// This is drawn every frame on the android. fnc
cTabOnDrawbftAndroid = {

	_return = true;
	_display = (uiNamespace getVariable "cTab_Android_dlg");
	_cntrlScreen = _display displayCtrl 17354;

	{
		_obj = _x select 0;
		_texture = _x select 1;
		_text = "";
		_pos = getPosASL _obj;
		
		if (cTabBFTtxt) then {_text = _x select 2;};
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];


	} forEach cTabBFTlist;
	
	
	if ((count cTabUserIconList) != 0) then 
	{
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			//hint str _x;
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];

			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
	
			if (_dir < 360) then
			{
			
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
		
			};

		
		} forEach cTabUserIconList;
	};
	
_return;
};

// This is drawn every frame on the microDAGR display. fnc
cTabOnDrawbftmicroDAGRdsp = {
	_return = true;
	_display = (uiNamespace getVariable "cTab_microDAGR_dsp");
	_cntrlScreen = _display displayCtrl 1201;
	
	// current position
	_mapCentrePos = getPosASL player;
	_heading = direction vehicle player;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabMicroDAGRmapScaleCtrl, _mapCentrePos];
	ctrlMapAnimCommit _cntrlScreen;
	
	{
		_obj = _x select 0;
		// check if the player is not occupying the vehicle we are about to draw an icon for and don't draw if that's the case
		if (!(player in _obj)) then
		{
			_texture = _x select 1;
			_text = "";
			_pos = getPosASL _obj;
			// check if object is infantry, not currently in a vehicle and in the same group as the player
			if (((vehicle _obj) isKindOf "Man") && {player in units _obj}) exitWith {
				_texture = _obj call cTab_fnc_GetInfMarkerIcon;
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];
			};
			if (!((_obj isKindOf "Man") && {vehicle _obj != _obj})) then {
				if (cTabBFTtxt) then {_text = _x select 2;};
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];
			};
		};
	} forEach cTabBFTlist;
	
	if ((count cTabUserIconList) != 0) then {
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			//hint str _x;
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];

			if (_texture2 != "") then {
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
	
			if (_dir < 360) then {
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
			};
		} forEach cTabUserIconList;
	};
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_mapCentrePos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	_return;
};

// This is drawn every frame on the microDAGR dialog. fnc
cTabOnDrawbftMicroDAGRdlg = {
	_return = true;
	_display = (uiNamespace getVariable "cTab_microDAGR_dlg");
	_cntrlScreen = _display displayCtrl 1201;
	
	// current position
	_mapCentrePos = getPosASL player;
	_heading = direction vehicle player;
	
	{
		_obj = _x select 0;
		// check if the player is not occupying the vehicle we are about to draw an icon for and don't draw if that's the case
		if (!(player in _obj)) then
		{
			_texture = _x select 1;
			_text = "";
			_pos = getPosASL _obj;
			// check if object is infantry, not currently in a vehicle and in the same group as the player
			if (((vehicle _obj) isKindOf "Man") && {player in units _obj}) exitWith {
				_texture = _obj call cTab_fnc_GetInfMarkerIcon;
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];
			};
			if (!((_obj isKindOf "Man") && {vehicle _obj != _obj})) then {
				if (cTabBFTtxt) then {_text = _x select 2;};
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];
			};
		};
	} forEach cTabBFTlist;
	
	if ((count cTabUserIconList) != 0) then {
		// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
		{
			_pos = _x select 0;
			//_WorldCoordtmp = screenToWorld _pos;
			//_WorldCoord = [_WorldCoordtmp select 0,_WorldCoordtmp select 1,0];
			_texture1 = _x select 1;
			_texture2 = _x select 2;
			_dir = _x select 3;
			_color = _x select 4;
			_text = "";
			if (cTabBFTtxt) then {_text = _x select 5;};
			//hint str _x;
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB"];

			if (_texture2 != "") then {
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
			};
	
			if (_dir < 360) then {
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
			};
		} forEach cTabUserIconList;
	};
	
	// draw directional arrow at own location
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabMicroDAGRfontColour,_mapCentrePos,cTabTADownIconBaseSize,cTabTADownIconBaseSize,_heading,"", 1,cTabTxtSize,"TahomaB"];
	
	_return;
};

// This is drawn every frame on the tablet uav screen. fnc
cTabOnDrawUAV = {
	if (isNil 'cTabActUav') exitWith {};
	if (cTabActUav == player) exitWith {};
	
	_display = (uiNamespace getVariable "cTab_UAV_dlg");
	_cntrlScreen = _display displayCtrl 1774;
	_pos = getPosASL cTabActUav;
	
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\markers\nato\b_uav.paa",cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,"",0,cTabTxtSize,"TahomaB"];
	
	_cntrlScreen ctrlMapAnimAdd [0,0.1,_pos];
	ctrlMapAnimCommit _cntrlScreen;
};

// This is drawn every frame on the tablet helmet cam screen. fnc
cTabOnDrawHCam = {
	if (isNil 'cTabActHcam') exitWith {};
	if (cTabActHcam == player) exitWith {};
	
	_display = (uiNamespace getVariable "cTab_hCam_dlg");
	_cntrlScreen = _display displayCtrl 1774;
	_pos = getPosASL cTabActHcam;
	
	_cntrlScreen drawIcon ["\A3\ui_f\data\map\markers\nato\b_inf.paa",cTabColorBlue,_pos, cTabIconSize, cTabIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
	
	_cntrlScreen ctrlMapAnimAdd [0,0.1,_pos];
	ctrlMapAnimCommit _cntrlScreen;
};



//Main loop to add the key handler to the unit.
[] spawn {
	waitUntil {sleep 0.1;!(IsNull (findDisplay 46))};
	
	if (cTab_key_if_main_scancode != 0) then {
 		[cTab_key_if_main_scancode, cTab_key_if_main_modifiers, {call cTab_fnc_onIfMainPressed},"keydown","cTab_1"] call CBA_fnc_addKeyHandler;
		[cTab_key_if_secondary_scancode, cTab_key_if_secondary_modifiers, {call cTab_fnc_onIfSecondaryPressed},"keydown","cTab_2"] call CBA_fnc_addKeyHandler;
		[cTab_key_zoom_in_scancode, cTab_key_zoom_in_modifiers, {call cTab_fnc_onZoomInPressed},"keydown","cTab_3"] call CBA_fnc_addKeyHandler;
		[cTab_key_zoom_out_scancode, cTab_key_zoom_out_modifiers, {call cTab_fnc_onZoomOutPressed},"keydown","cTab_4"] call CBA_fnc_addKeyHandler;
	} else {
		[actionKeys "User12" select 0, [false,false,false], {call cTab_fnc_onIfMainPressed},"keydown","cTab_1"] call CBA_fnc_addKeyHandler;
		[actionKeys "User12" select 0, [false,true,false], {call cTab_fnc_onIfSecondaryPressed},"keydown","cTab_2"] call CBA_fnc_addKeyHandler;
		[201, [true,true,false], {call cTab_fnc_onZoomInPressed},"keydown","cTab_3"] call CBA_fnc_addKeyHandler;
		[209, [true,true,false], {call cTab_fnc_onZoomOutPressed},"keydown","cTab_4"] call CBA_fnc_addKeyHandler;
	};
};

// fnc for user menu opperation.
cTabUsrMenuSelect = {
	disableSerialization;
	_type = _this select 0;
	_dlg = _this select 1;
	_display = (uiNamespace getVariable _dlg);
	_return = True;
	
	switch (_type) do
	{
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
			_control = _display displayCtrl 3304;
			ctrlShow [3304, True];
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
	cTabUserSelIcon = [[],"","",500,[],""];
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
	player cameraEffect ["terminate","back"];
	_camArray = player getVariable "cTabHcams";
	camDestroy (_camArray select 0);
	deleteVehicle (_camArray select 1);
	player setVariable ["cTabHcams",nil];
	cTabActHcam = nil;
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

/*
fnc to check a units gear for certain items
Param 0: Unit object to check
Param 1: Array of items to search for
*/
cTab_fnc_checkGear = {
	_return = false;
	_unit = _this select 0;
	_items = _this select 1;
	
	_chk_all_items = (items _unit) + (assignedItems _unit);
	
	{
		if (_x in _chk_all_items) exitWith {_return = true};
	} forEach _items;
	
	_return;
};

// Main loop to manage lists of people and veh that are shown in FBCB2
cTab_fnc_update_lists = {
	_cTabBFTlist = [];
	_cTabHcamlist = [];
	
	{
		if (side _x == cTabSide) then
		{
			if ([_x,["ItemcTab","ItemAndroid","ItemMicroDAGR"]] call cTab_fnc_checkGear) then
			{
				_name = groupID (group _x);
				_groupIndex = str([_x] call CBA_fnc_getGroupIndex);
				_tmpArray = [_x,"\A3\ui_f\data\map\markers\nato\b_inf.paa",_name,_groupIndex];
				_cTabBFTlist set [count _cTabBFTlist,_tmpArray];
			};
			
			if ([_x,["ItemcTabHCam"]] call cTab_fnc_checkGear) then
			{
				_cTabHcamlist set [count _cTabHcamlist,_x];
			};
		};
		
	} forEach allUnits;
	
	{
		if ((count (crew _x) > 0) && (side _x == cTabSide)) then
		{
			_name = groupID (group _x);
			_txture = "\A3\ui_f\data\map\markers\nato\b_unknown.paa";
			_groupIndex = str([_x] call CBA_fnc_getGroupIndex);
			
			call {
				if (_x isKindOf "Car_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_motor_inf.paa";};
				if (_x isKindOf "Wheeled_APC_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
				if (_x isKindOf "Truck_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_service.paa";};
				if (_x isKindOf "UAV") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_uav.paa";};
				if (_x isKindOf "Helicopter") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_air.paa";};
				if (_x isKindOf "Plane") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_plane.paa";};
				if (_x isKindOf "MBT_01_arty_base_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
				if (_x isKindOf "MBT_01_mlrs_base_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
				if (_x isKindOf "MBT_02_arty_base_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
				if (_x isKindOf "Tank") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
				if (_x isKindOf "StaticMortar") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_mortar.paa";};
			};
			
			_tmpArray = [_x,_txture,_name,_groupIndex];
			_cTabBFTlist set [count _cTabBFTlist,_tmpArray];
		};
		
	} forEach vehicles;
	
	// replace the global list arrays in the end so that we avoid them being empty unnecessarily
	cTabBFTlist = [] + _cTabBFTlist;
	cTabHcamlist = [] + _cTabHcamlist;
};

cTab_spawn_msg_dlg = {
	closeDialog 0;
	waitUntil {!dialog};
	
	createDialog "cTab_msg_main_dlg";
	waitUntil {dialog};
	_this + [19457,nil] call cTab_fnc_onIfOpen;
};

cTab_msg_gui_load = 
{
	disableSerialization;
	_return = true;
	_display = (uiNamespace getVariable "cTab_msg_main_dlg");
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
	_display = (uiNamespace getVariable "cTab_msg_main_dlg");
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
	_display = (uiNamespace getVariable "cTab_msg_main_dlg");
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
	   
			if (!isnull (findDisplay 19457)) then 
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
	
cTab_load_BFT = {
	closeDialog 0;
	waitUntil {!dialog};
	
	createDialog "cTab_main_dlg";
	waitUntil {dialog};
	_this + [1775154,nil] call cTab_fnc_onIfOpen;
	_nop = [] execVM '\cTab\main\loadBFT.sqf';
};

cTab_keyDownShortcut = 
{
	private["_handled", "_ctrl", "_dikCode", "_shift", "_ctrlKey", "_alt","_target"];
	_ctrl = _this select 0;
	_dikCode = _this select 1;
	_shift = _this select 2;
	_ctrlKey = _this select 3;
	_alt = _this select 4;
	_fKeys = [59,60,61,62];
	_handled = false;

	if (_dikCode in _fKeys) then
	{
		switch (_dikCode) do
		{
			case 59:
			{
				_nop = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] spawn cTab_load_BFT;
				_handled = true;
			};

			case 60:
			{
				_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\uav\cTab_gui_uav_start.sqf';
				_handled = true;
			};
			
			case 61:
			{
				_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';
				_handled = true;
			};
			
			case 62:
			{
				_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] spawn cTab_spawn_msg_dlg;
				_handled = true;
			};
			
			default
			{
			};
		};
	
	};


	_handled;  
};	


cTab_hCam_Full_View = {
	if (isNil 'cTabActHcam') exitWith {false};
	if (vehicle cTabActHcam isKindOf "CAManBase") then 
	{
		player switchCamera 'Internal';
		cTabActHcam switchCamera 'Internal';
		closeDialog 0;
		cTabHCamViewActive = true;
	}
	else
	{
		player switchCamera "EXTERNAL";
		(vehicle cTabActHcam) switchCamera "EXTERNAL";
		closeDialog 0;
		cTabHCamViewActive = true;		
	};
};

// Function to find the closest marker to the places cursor.
cTabFindCloseUsrMkr = {
	
	private["_posToCheck","_i"];
	_posToCheck = _this select 0;
	_closestUsrMkr = 0;
	_closestDistanceToMkr = 20000;
	_setFirstAsClose = true;
	_return = (count cTabUserIconList) - 1;
	_distanceCheck = 0;
	_arrayToBeCheckedPos = [];
			
	// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
	{
		_arrayToBeCheckedPos = _x select 0;
		
		_distanceCheck = _arrayToBeCheckedPos distance _posToCheck;
		
		if (_setFirstAsClose) then {
			
			_closestUsrMkr = _forEachIndex;
			_closestDistanceToMkr = _distanceCheck;	
			_setFirstAsClose = false;	
		} else
		{
			if (_distanceCheck < _closestDistanceToMkr) then
			{
				_closestUsrMkr = _forEachIndex;
				_closestDistanceToMkr = _distanceCheck;
			};
			
		};		
	
		_return = _closestUsrMkr;
		
	} forEach cTabUserIconList;
	

_return;	
};



// Key handler to call for deleteing of user placed markers based on user cursor.
cTabDeleteUsrMkr = {
	
	private["_keyData", "_mapCtrl", "_mKey", "_mXPos", "_mYPos", "_mCtrlBool"];
	
	_keyData = _this select 3;
	
	_mKey = _keyData select 1;
	_mXPos = _keyData select 2;
	_mYPos = _keyData select 3;
	_mCtrlBool = _keyData select 5;
	
	disableSerialization;
	_dsp = _this select 0;
	_mainPop = _this select 1;
	_cntrlScreen = _this select 2;
	_sendingCtrlArry = _this select 3;
	_display = (uiNamespace getVariable _dsp);
	_mainPopup = _display displayCtrl _mainPop; // 3300
	_cntrlScreen = _display displayCtrl _cntrlScreen;  // 1201
	
	// Check if right mouse button is pressed (RMB)
	if (_mKey == 1) then 
	{		
		if (_mCtrlBool) then 
		{
			if ((count cTabUserIconList) > 0) then
			{
				_tempPosToCheck = _cntrlScreen ctrlMapScreenToWorld [_mXPos,_mYPos];
				_findCloseMarker = [_tempPosToCheck] call cTabFindCloseUsrMkr;
			
				// Thanks to KK for this great work around for delteing and resizing arrays of arrays: http://killzonekid.com/arma-scripting-tutorials-arrays-part-2/
				cTabUserIconList set [_findCloseMarker,"deletethis"];
				cTabUserIconList = cTabUserIconList - ["deletethis"];
				publicVariable "cTabUserIconList";
			};
				
		};
		
	
	};
	
	
};	