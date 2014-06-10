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

/*
TAD setup
*/
// Get a rsc layer for TAD monitor
cTabTADrscLayer = ["cTab_TAD"] call BIS_fnc_rscLayer;
// initialize TAD as not open
cTabTADopen = false;
// set initial TAD map scale in km
cTabTADmapScale = 2;
// define min and max TAD map scales in km
cTabTADmapScaleMin = 2;
cTabTADmapScaleMax = 32;
/*
 figure out the scaling factor based on the map being played
 on Stratis we have a map scaling factor of 3.125 km per ctrlMapScale
 Stratis map size is 8192 (Altis is 30720)
 8192 / 3.125 = 2621.44
 Divide the actual mapSize by this factor to obtain the scaling factor
 It seems to work fine
*/
_mapSize = (getNumber (configFile>>"CfgWorlds">>worldName>>"mapSize"));
cTabMapScaleFactor = _mapSize / 2621.44;
// set TAD font colour to neon green
cTabTADfontColour = [57/255, 255/255, 20/255, 1];
// set TAD highlight colour to neon yellow
cTabTADhighlightColour = [243/255, 243/255, 21/255, 1];

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

// temp assignmet gets set later when user selects a uav.
cTabActUav = player;

// Begining text and icon size
cTabTxtFctr = 12;
cTabBFTtxt = true;

//set up array for user stored icons, data waits here until it is sent out to other clients.
// cTabUserSelIcon = [_pos,_texture1,_texture2,_dir,_color,_text];
cTabUserSelIcon = [[],"","",500,[],""];

// Base defines.
cTabUserIconList = [];
cTabUavViewActive = false;
cTabHCamViewActive = false;

// Set up the array that will hold text messages.
player setVariable ["ctab_messages",[]];

// fnc for Key handler. 
cTab_keyDown = 
{
	private["_handled", "_ctrl", "_dikCode", "_shift", "_ctrlKey", "_alt","_vehicle"];
	_ctrl = _this select 0;
	_dikCode = _this select 1;
	_shift = _this select 2;
	_ctrlKey = _this select 3;
	_alt = _this select 4;
  
	_handled = false;

	// -todo - add userconfig so player can change key.
	if (_dikCode in (actionKeys "User12") && !_shift && !_ctrlKey && !_alt) then
	{
		_chk_items = (items player);
		_chk_asgnItems = (assignedItems player);
		
		if (cTabUavViewActive) exitWith {objNull remoteControl ((crew cTabActUav) select 1);player switchCamera 'internal';cTabUavViewActive = false;};
		if (cTabHCamViewActive) exitWith {objNull remoteControl cTabActHcam;player switchCamera 'internal';cTabHCamViewActive = false;};
	
		_chk_all_items = _chk_items + _chk_asgnItems;
		
		
		// -- todo - update to CBA_fnc_find to increase performance in EH.
		if (("ItemcTab" in _chk_all_items)) exitWith
		{
			
			if (isNull (findDisplay 1775154)) then {
					nul = [] execVM "cTab\cTab_gui_start.sqf";
					
				}else
				{
					closeDialog 0;

				};
			_handled = true;	
		};
		
		_vehicle = vehicle player;
		
		if (({_vehicle isKindOf _x} count cTab_vehicleClass_has_FBCB2) > 0) exitWith {
			if (isNull (findDisplay 1775144)) then 
				{
					nul = [] execVM "cTab\bft\veh\cTab_Veh_gui_start.sqf";
				}else
				{
					closeDialog 0;
				};
			_handled = true;
		};
		
		if (({_vehicle isKindOf _x} count cTab_vehicleClass_has_TAD) > 0) exitWith
		{
			// findDisplay to check for rsc layer? Could not get it to work
			if (!cTabTADopen) then 
			{
				if (player in [driver _vehicle,_vehicle turretUnit[0]]) then
				{
					cTabPlayerVehicleIcon = getText (configFile/"CfgVehicles"/typeOf _vehicle/"Icon");
					nul = [] execVM "cTab\TAD\cTab_TAD_gui_start.sqf";
					cTabTADopen = true;
					// Register Event Handler to be notified when the player exits the current vehicle
					cTabVehicleGetOutEhId = _vehicle addEventHandler ["GetOut",{_this call cTab_Close}];
				}
			}
			else
			{
				if (isNull (findDisplay 1775144)) then 
				{
					[_vehicle] call cTab_close;
				}
				else
				{
					closeDialog 0;
				};
			};
			_handled = true;
		};
		
		// -- todo - update to CBA_fnc_find to increase performance in EH.
		if ("ItemAndroid" in _chk_all_items) exitWith {
		
			if (isNull (findDisplay 177382)) then 
				{
					nul = [] execVM "cTab\bft\cTab_android_gui_start.sqf";
					
				}else
				{
					closeDialog 0;

				};
			_handled = true;
		};		
		
	};
	
	// TAD key handlers, process only if TAD is open
	if (cTabTADopen) then
	{
		if ((_dikCode in (actionKeys "ZoomIn")) && _shift && _ctrlKey && !_alt) exitWith
		{
			cTabTADmapScale = cTabTADmapScale / 2;
			if (cTabTADmapScale < cTabTADmapScaleMin) then {cTabTADmapScale = cTabTADmapScaleMin};
			_handled = true;
		};
		if ((_dikCode in (actionKeys "ZoomOut")) && _shift && _ctrlKey && !_alt) exitWith
		{
			cTabTADmapScale = cTabTADmapScale * 2 ;
			if (cTabTADmapScale > cTabTADmapScaleMax) then {cTabTADmapScale = cTabTADmapScaleMax};
			_handled = true;
		};
		if ((_dikCode in (actionKeys "User12")) && !_shift && _ctrlKey && !_alt) exitWith
		{
			if (isNull (findDisplay 1775144)) then 
			{
				nul = [] execVM "cTab\TAD\cTab_TAD_dialog_start.sqf";
			}else
			{
				closeDialog 0;
			};
			_handled = true;
		};
	};
	
	_handled;  
};

// fnc to close cTab
cTab_Close =
{
	_vehicle = _this select 0;
	if (cTabTADopen) then
	{
		// not sure which one is better, they both work
		// cTabTADrscLayer cutText ["", "PLAIN"];
		(uiNamespace getVariable "cTab_TAD_dsp") closeDisplay 0;
		cTabTADopen = false;
	};
	_vehicle removeEventHandler ["GetOut",cTabVehicleGetOutEhId];
};

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
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];


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
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];

			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, "", 0, 0.035,"TahomaB"];
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
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];


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
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];

			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, "", 0, 0.035,"TahomaB"];
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
	
	// current position
	_mapCentrePos = getPosASL player;
	_heading = direction player;
	// change scale of map and centre to player position
	_cntrlScreen ctrlMapAnimAdd [0, cTabTADmapScale / cTabMapScaleFactor, _mapCentrePos];
	ctrlMapAnimCommit _cntrlScreen;
	
	// draw vehicle icon at own location
	_cntrlScreen drawIcon [cTabPlayerVehicleIcon,cTabTADfontColour,_mapCentrePos,18,18,_heading,"", 1,0.035,"TahomaB"];
	
	// draw TAD overlay (two circles, one at full scale, the other at half scale + current heading)
	_cntrlScreen drawIcon ["\cTab\img\TAD_overlay_ca.paa",cTabTADfontColour,_mapCentrePos,250,250,_heading,"",1,0.035,"TahomaB"];
	
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
				// draw air contact icon and dummy icon for the text to have a better alignment
				_cntrlScreen drawIcon ["\cTab\img\icon_air_contact_ca.paa",cTabTADfontColour,_pos,32,32,direction _obj,"",0,0.035,"TahomaB"];
				_cntrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabColorBlue,_pos,20,20,0,_text,0,0.035,"TahomaB"];
			}
			else
			{
				_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos,cTabTxtFctr * 2,cTabTxtFctr * 2,0,_text,0,0.035,"TahomaB"];
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
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];
			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, "", 0, 0.035,"TahomaB"];
			};
			if (_dir < 360) then
			{
				_secondPos = [_pos,26,_dir] call BIS_fnc_relPos;
				_cntrlScreen drawArrow [_pos, _secondPos, _color];
			};
		} forEach cTabUserIconList;
	};
	
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
	
	// update current map scale on TAD
	// divide by 2 because we want to display the radius, not the diameter
	(_display displayCtrl 1204) ctrlSetText format ["%1", cTabTADmapScale / 2];
	
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
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];


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
		
			_cntrlScreen drawIcon [_texture1,_color,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];

			if (_texture2 != "") then 
			{
				_secondPos = [_pos,5,0] call BIS_fnc_relPos;
				_cntrlScreen drawIcon [_texture2,_color,_secondPos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, "", 0, 0.035,"TahomaB"];
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

// This is drawn every frame on the tablet uav screen. fnc
cTabOnDrawUAV = {

	_return = true;
	_display = (uiNamespace getVariable "cTab_UAV_dlg");
	_cntrlScreen = _display displayCtrl 1774;
	
	if ((count allUnitsUav) == 0) exitWith {};

	{
		_obj = _x ;
		_texture = "\A3\ui_f\data\map\markers\nato\b_uav.paa";
		_text = "";
		_pos = getPosASL _obj;
		
		//if (cTabBFTtxt) then {_text = _x select 2;};
		
		_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];


	} forEach allUnitsUav;
	
	if (cTabActUav == player) exitWith {};
	ctrlMapAnimClear _cntrlScreen;
	_cntrlScreen ctrlMapAnimAdd [0, 0.1, getPosASL cTabActUav];
	ctrlMapAnimCommit _cntrlScreen;
_return;
};

// This is drawn every frame on the tablet helmet cam screen. fnc
cTabOnDrawHCam = {

	_return = true;
	_display = (uiNamespace getVariable "cTab_hCam_dlg");
	_cntrlScreen = _display displayCtrl 1774;
		
	_obj = cTabActHcam;
	
	if (_obj == player) exitWith {};
	
	_texture = "\A3\ui_f\data\map\markers\nato\b_inf.paa";
	_text = "";
	_pos = getPosASL _obj;
		
	//if (cTabBFTtxt) then {_text = _x select 2;};
		
	_cntrlScreen drawIcon [_texture,cTabColorBlue,_pos, cTabTxtFctr * 2, cTabTxtFctr * 2, 0, _text, 0, 0.035,"TahomaB"];
	
	ctrlMapAnimClear _cntrlScreen;
	_cntrlScreen ctrlMapAnimAdd [0, 0.1, getPosASL _obj];
	ctrlMapAnimCommit _cntrlScreen;
_return;
};



//Main loop to add the key handler to the unit.
[] spawn {
	waitUntil {sleep 0.1;!(IsNull (findDisplay 46))};
	
	if (cTab_key_if_main_scancode != 0) then {
 		// [cTab_key_if_main_scancode, cTab_key_if_main_modifiers, {call cTab_fnc_onIfMainPressed},"keydown","cTab_1"] call CBA_fnc_addKeyHandler;
		// [cTab_key_if_secondary_scancode, cTab_key_if_secondary_modifiers, {call cTab_fnc_onIfSecondaryPressed},"keydown","cTab_2"] call CBA_fnc_addKeyHandler;
		// [cTab_key_zoom_in_scancode, cTab_key_zoom_in_modifiers, {call cTab_fnc_onZoomInPressed},"keydown","cTab_3"] call CBA_fnc_addKeyHandler;
		// [cTab_key_zoom_out_scancode, cTab_key_zoom_out_modifiers, {call cTab_fnc_onZoomOutPressed},"keydown","cTab_4"] call CBA_fnc_addKeyHandler;
		
		[cTab_key_if_main_scancode,cTab_key_if_main_modifiers,{[
			"",
			cTab_key_if_main_scancode,
			cTab_key_if_main_modifiers select 0,
			cTab_key_if_main_modifiers select 1,
			cTab_key_if_main_modifiers select 2
		] call cTab_keyDown},"keydown","cTab_1"] call CBA_fnc_addKeyHandler;
		[cTab_key_if_secondary_scancode, cTab_key_if_secondary_modifiers, {[
			"",
			cTab_key_if_secondary_scancode,
			cTab_key_if_secondary_modifiers select 0,
			cTab_key_if_secondary_modifiers select 1,
			cTab_key_if_secondary_modifiers select 2
		] call cTab_keyDown},"keydown","cTab_2"] call CBA_fnc_addKeyHandler;
		[cTab_key_zoom_in_scancode, cTab_key_zoom_in_modifiers, {[
			"",
			cTab_key_zoom_in_scancode,
			cTab_key_zoom_in_modifiers select 0,
			cTab_key_zoom_in_modifiers select 1,
			cTab_key_zoom_in_modifiers select 2
		] call cTab_keyDown},"keydown","cTab_3"] call CBA_fnc_addKeyHandler;
		[cTab_key_zoom_out_scancode, cTab_key_zoom_out_modifiers, {[
			"",
			cTab_key_zoom_out_scancode,
			cTab_key_zoom_out_modifiers select 0,
			cTab_key_zoom_out_modifiers select 1,
			cTab_key_zoom_out_modifiers select 2
		] call cTab_keyDown},"keydown","cTab_4"] call CBA_fnc_addKeyHandler;
	} else {
		// [actionKeys "User12" select 0, [false,false,false], {call cTab_fnc_onIfMainPressed},"keydown","cTab_1"] call CBA_fnc_addKeyHandler;
		// [actionKeys "User12" select 0, [false,true,false], {call cTab_fnc_onIfSecondaryPressed},"keydown","cTab_2"] call CBA_fnc_addKeyHandler;
		// [actionKeys "ZoomIn" select 0, [true,true,false], {call cTab_fnc_onZoomInPressed},"keydown","cTab_3"] call CBA_fnc_addKeyHandler;
		// [actionKeys "ZoomOut" select 0, [true,true,false], {call cTab_fnc_onZoomOutPressed},"keydown","cTab_4"] call CBA_fnc_addKeyHandler;
		
		[actionKeys "User12" select 0, [false,false,false], {["",actionKeys "User12" select 0,false,false,false] call cTab_keyDown},"keydown","cTab_1"] call CBA_fnc_addKeyHandler;
		[actionKeys "User12" select 0, [false,true,false], {["",actionKeys "User12" select 0,false,true,false] call cTab_keyDown},"keydown","cTab_2"] call CBA_fnc_addKeyHandler;
		[actionKeys "ZoomIn" select 0, [true,true,false], {["",actionKeys "ZoomIn" select 0,true,true,false] call cTab_keyDown},"keydown","cTab_3"] call CBA_fnc_addKeyHandler;
		[actionKeys "ZoomOut" select 0, [true,true,false], {["",actionKeys "ZoomOut" select 0,true,true,false]call cTab_keyDown},"keydown","cTab_4"] call CBA_fnc_addKeyHandler;
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
	
	_return = true;
	player cameraEffect ["terminate","back"];
	_camArray = player getVariable "cTabUAVcams";
	_targets = _camArray select 2;
	camDestroy (_camArray select 0);
	camDestroy (_camArray select 1);
	{deleteVehicle _x;} forEach _targets;	
_return;
};

// fnc to delete cameras after helmet cam interface is closed.
cTabHcamDelCam = {
	
	_return = true;
	player cameraEffect ["terminate","back"];
	_camArray = player getVariable "cTabHcams";
	_targets = _camArray select 2;
	camDestroy (_camArray select 0);
	deleteVehicle (_camArray select 1);	
_return;
};

cTabUavTakeControl = {
	
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
	}else
	{
	
		["cTabUavNotAval",["Unable to access the UAV stream... Another user is streaming"]] call BIS_fnc_showNotification;
	
	};
_return;
};

// fnc to check players gear for ctab.
cTabCheckGear = {
	
	_unit = _this select 0;
	_return = false;
	
	_chk_all_items = (items _unit) + (assignedItems _unit);
	
	if (("ItemcTab" in _chk_all_items) || ("ItemAndroid" in _chk_all_items)) then
	{
		_return = true;
	};
	
	_return;
};

// fnc to check if unit has helmet cam.
hCamCheckGear = {
	
	_unit = _this select 0;
	_return = false;
	
	_chk_all_items = (items _unit) + (assignedItems _unit);
	
	if (("ItemcTabHCam" in _chk_all_items)) then
	{
		_return = true;
	};
	
	_return;
};

// Main loop to manage lists of people and veh that are shown in FBCB2
cTab_fnc_update_lists = {
	_cTabBFTlist = [];
	_cTabHcamlist = [];
	
	{
		if (side _x == cTabSide) then
		{
			if ([_x] call cTabCheckGear) then
			{
				_name = groupID (group _x);
				_tmpArray = [_x,"\A3\ui_f\data\map\markers\nato\b_inf.paa",_name];
				_cTabBFTlist set [count _cTabBFTlist,_tmpArray];
			};
			
			if ([_x] call hCamCheckGear) then
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
			
			call {
				if (_x isKindOf "Car_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_motor_inf.paa";};
				if (_x isKindOf "Wheeled_APC_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
				if (_x isKindOf "Truck_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_service.paa";};
				if (_x isKindOf "Helicopter") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_air.paa";};
				if (_x isKindOf "Plane") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_plane.paa";};
				if (_x isKindOf "Tank") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
			};
			
			_tmpArray = [_x,_txture,_name];
			_cTabBFTlist set [count _cTabBFTlist,_tmpArray];
		};
		
	} forEach vehicles;
	
	// replace the global list arrays in the end so that we avoid them being empty unnecessarily
	cTabBFTlist = [] + _cTabBFTlist;
	cTabHcamlist = [] + _cTabHcamlist;
};

cTab_spawn_msg_dlg = 
{
	closeDialog 0;

	ShowDialog = {
		sleep 0.01;
		_ok = createDialog "cTab_msg_main_dlg";
		waitUntil { !dialog };
	};
 
	_void = [] call ShowDialog;

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
		if (!([_x] call cTabCheckGear)) then { _plrlistControl lbSetColor [_forEachIndex, [1,0,0,1]];};
		
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
	   
	   if ([player] call cTabCheckGear) then 
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
	
cTab_load_BFT = 
{
	closeDialog 0;

	ShowDialog = {
		sleep 0.01;
		_ok = createDialog "cTab_main_dlg";
		sleep .5;
	    _nop = [] execVM '\cTab\main\loadBFT.sqf';
		waitUntil { !dialog };
	};
 
	_void = [] call ShowDialog;

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
				_nop = [] spawn cTab_load_BFT;
				_handled = true;
			};

			case 60:
			{
				_ok = [] execVM 'cTab\uav\cTab_gui_uav_start.sqf';
				_handled = true;
			};
			
			case 61:
			{
				_ok = [] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';
				_handled = true;
			};
			
			case 62:
			{
				_ok = [] spawn cTab_spawn_msg_dlg;
				_handled = true;
			};
			
			default
			{
			};
		};
	
	};


	_handled;  
};	


cTab_hCam_Full_View = 
{

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