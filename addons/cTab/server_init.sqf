// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

// define vehicles that have FBCB2 monitor and broadcast it
cTab_vehicleClass_has_FBCB2_server = ["MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank","Truck_01_base_F","Truck_03_base_F"];
publicVariable "cTab_vehicleClass_has_FBCB2_server";

// define vehicles that have TAD  and broadcast it
cTab_vehicleClass_has_TAD_server = ["Helicopter","Plane"];
publicVariable "cTab_vehicleClass_has_TAD_server";

// define items that have a helmet camera and broadcast it
cTab_helmetClass_has_HCam_server = ["H_HelmetB_light","H_Helmet_Kerry","H_HelmetSpecB","H_HelmetO_ocamo","BWA3_OpsCore_Fleck_Camera","BWA3_OpsCore_Schwarz_Camera","BWA3_OpsCore_Tropen_Camera"];
publicVariable "cTab_helmetClass_has_HCam_server";

// define marker counters and broadcast them
cTab_markerCounterMKR = 0;
cTab_markerCounterWP = 0;
cTab_markerCounterLZDZ = 0;
cTab_markerCounterOBJ = 0;
publicVariable "cTab_markerCounterMKR";
publicVariable "cTab_markerCounterWP";
publicVariable "cTab_markerCounterLZDZ";
publicVariable "cTab_markerCounterOBJ";

cTab_userMarkerLists = [];
cTab_userMarkerTransactionId = -1;

[] spawn {
	waituntil {time > 0};
	sleep .1;
	
	while {true} do {
		["cTab_updatePulse"] call CBA_fnc_globalEvent;
		sleep 30;
	};
};
