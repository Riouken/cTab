/*
 	Name: cTab_fnc_updateLists
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Update lists of cTab units and vehicles
		Lists updated:
			cTabBFTmembers
			cTabBFTgroups
			cTabBFTvehicles
			cTabHcamlist
		
		List format (all except cTabHcamlist):
			Index 0: Unit object
			Index 1: Path to icon A
			Index 2: Path to icon B (either group size or wingmen)
			Index 3: Text to display
			Index 4: String of group index

	
	Parameters:
		NONE
 	
 	Returns:
		BOOLEAN - Always TRUE
 	
 	Example:
		call cTab_fnc_updateLists;
*/

private ["_cTabBFTmembers","_cTabBFTgroups","_cTabBFTvehicles","_cTabHcamlist"];

_cTabBFTmembers = []; // members of player's group
_cTabBFTgroups = []; // other groups
_cTabBFTvehicles = []; // all vehicles
_cTabHcamlist = [];  // units with a helmet cam

/*
cTabBFTmembers --- GROUP MEMBERS
*/
{
	if ((_x != player) && {[_x,["ItemcTab","ItemAndroid","ItemMicroDAGR"]] call cTab_fnc_checkGear}) then {
		_cTabBFTmembers pushBack [_x,_x call cTab_fnc_GetInfMarkerIcon,"",name _x,str([_x] call CBA_fnc_getGroupIndex)];
	};
} count units group player;

/*
cTabBFTgroups --- GROUPS
Groups on our side that player is not a member of. Use the leader for positioning if he has a Tablet or Android.
Else, search through the group and use the first member we find equipped with a Tablet or Android for positioning.
Should that person be inside a vehicle, do not add the group.
*/
{
	if ((side _x == cTabSide) && {_x != group player}) then {
		_leader = objNull;
		call {
			if ([leader _x,["ItemcTab","ItemAndroid"]] call cTab_fnc_checkGear) exitWith {_leader = leader _x;};
			{
				if ([_x,["ItemcTab","ItemAndroid"]] call cTab_fnc_checkGear) exitWith {_leader = _x;};
			} count units _x;
		};
		if ((!IsNull _leader) && {_leader == vehicle _leader}) then {
			_groupSize = count units _x;
			_sizeIcon = call {
				if (_groupSize <= 5) exitWith {"\A3\ui_f\data\map\markers\nato\group_0.paa"};
				if (_groupSize <= 10) exitWith {"\A3\ui_f\data\map\markers\nato\group_1.paa"};
				"\A3\ui_f\data\map\markers\nato\group_2.paa"
			};
			_cTabBFTgroups pushBack [_leader,"\A3\ui_f\data\map\markers\nato\b_inf.paa",_sizeIcon,groupID _x,""];
		};
	};
} count allGroups;

/*
cTabBFTvehicles --- VEHICLES
Vehciles on our side, that are not empty and that player is not sitting in.
*/
{
	if ((side _x == cTabSide) && {count (crew _x) > 0} && {_x != vehicle player}) then {
		_groupID = if (group _x == group player) then {str([_x] call CBA_fnc_getGroupIndex)} else {""};
		_name = groupID group _x;
		_iconA = "\A3\ui_f\data\map\markers\nato\b_unknown.paa";
		_iconB = "";
		call {
			if (_x isKindOf "Car_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_motor_inf.paa";};
			if (_x isKindOf "Wheeled_APC_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
			if (_x isKindOf "Truck_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_service.paa";};
			if (_x isKindOf "UAV") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_uav.paa";};
			if (_x isKindOf "UAV_01_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_uav.paa";};
			if (_x isKindOf "Helicopter") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_air.paa"; _iconB = "\cTab\img\icon_air_contact_ca.paa";};
			if (_x isKindOf "Plane") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_plane.paa"; _iconB = "\cTab\img\icon_air_contact_ca.paa";};
			if (_x isKindOf "MBT_01_arty_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
			if (_x isKindOf "MBT_01_mlrs_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
			if (_x isKindOf "MBT_02_arty_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
			if (_x isKindOf "Tank") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
			if (_x isKindOf "StaticMortar") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_mortar.paa";};
		};
		_cTabBFTvehicles pushBack [_x,_iconA,_iconB,_name,_groupID];
	};
} count vehicles;

/*
cTabHcamlist --- HELMET CAMS
*/
{
	if (side _x == cTabSide) then {
		if (headgear _x in cTab_helmetClass_has_HCam || {[_x,["ItemcTabHCam"]] call cTab_fnc_checkGear}) then {
			_cTabHcamlist pushBack _x;
		};
	};
} count allUnits;

// replace the global list arrays in the end so that we avoid them being empty unnecessarily
cTabBFTmembers = [] + _cTabBFTmembers;
cTabBFTgroups = [] + _cTabBFTgroups;
cTabBFTvehicles = [] + _cTabBFTvehicles;
cTabHcamlist = [] + _cTabHcamlist;

true