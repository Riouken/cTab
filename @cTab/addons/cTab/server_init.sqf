// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

// define vehicles that have FBCB2 monitor and broadcast it
if (isArray (ConfigFile >> "cTab_settings" >> "cTab_vehicleClass_has_FBCB2")) then {
	cTab_vehicleClass_has_FBCB2_server = getArray (ConfigFile >> "cTab_settings" >> "cTab_vehicleClass_has_FBCB2");
} else {
	cTab_vehicleClass_has_FBCB2_server = ["MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank","Truck_01_base_F","Truck_03_base_F"];
};
publicVariable "cTab_vehicleClass_has_FBCB2_server";

// define vehicles that have TAD  and broadcast it
if (isArray (ConfigFile >> "cTab_settings" >> "cTab_vehicleClass_has_TAD")) then {
	cTab_vehicleClass_has_TAD_server = getArray (ConfigFile >> "cTab_settings" >> "cTab_vehicleClass_has_TAD");
} else {
	cTab_vehicleClass_has_TAD_server = ["Helicopter","Plane"];
};
publicVariable "cTab_vehicleClass_has_TAD_server";

// define items that have a helmet camera and broadcast it
if (isArray (ConfigFile >> "cTab_settings" >> "cTab_helmetClass_has_HCam")) then {
	cTab_helmetClass_has_HCam_server = getArray (ConfigFile >> "cTab_settings" >> "cTab_helmetClass_has_HCam");
} else {
	cTab_helmetClass_has_HCam_server = ["H_HelmetB_light","H_Helmet_Kerry","H_HelmetSpecB","H_HelmetO_ocamo","BWA3_OpsCore_Fleck_Camera","BWA3_OpsCore_Schwarz_Camera","BWA3_OpsCore_Tropen_Camera"];
};
publicVariable "cTab_helmetClass_has_HCam_server";

[] spawn {
	waituntil {time > 0};
	sleep .1;
	
	while {true} do {
		["cTab_FBCB2_updatePulse"] call CBA_fnc_globalEvent;
		sleep 10;
	};
};

/*
//prep the arrays that will hold ctab data
cTabBFTlist = [];
cTabHcamlist = [];

if (isnil ("cTabSide")) then {cTabSide = west;};

// Main loop to manage lists of people and veh that are shown in FBCB2
[] spawn {
	
	waituntil {time > 0};
	sleep .1;
	
	while {true} do
	{
		cTabBFTlist = [];
		cTabHcamlist = [];
		
		{
			
			if (side _x == cTabSide) then
			{
				_chk_all_items = (items _x) + (assignedItems _x);
				
				if (("ItemcTab" in _chk_all_items) || ("ItemAndroid" in _chk_all_items)) then
				{
					_name = groupID (group _x);
					_tmpArray = [_x,"\A3\ui_f\data\map\markers\nato\b_inf.paa",_name];
					cTabBFTlist set [count cTabBFTlist,_tmpArray];
				};
				
				if ("ItemcTabHCam" in _chk_all_items) then
				{
					cTabHcamlist set [count cTabHcamlist,_x];
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
				cTabBFTlist set [count cTabBFTlist,_tmpArray];
			};
			
		} forEach vehicles;
		
		publicVariable "cTabBFTlist";
		publicVariable "cTabHcamlist";
		sleep 20;
	};
	
};
*/
