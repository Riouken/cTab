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
			cTabUAVlist
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

private ["_cTabBFTmembers","_cTabBFTgroups","_cTabBFTvehicles","_cTabUAVlist","_cTabHcamlist","_validSides","_playerEncryptionKey","_playerVehicle","_playerGroup","_updateInterface"];

_cTabBFTmembers = []; // members of player's group
_cTabBFTgroups = []; // other groups
_cTabBFTvehicles = []; // all vehicles
_cTabUAVlist =  []; // all remote controllable UAVs
_cTabHcamlist = [];  // units with a helmet cam

_validSides = call cTab_fnc_getPlayerSides;

_playerVehicle = vehicle cTab_player;
_playerGroup = group cTab_player;

/*
cTabBFTmembers --- GROUP MEMBERS
*/
{
	if ((_x != cTab_player) && {[_x,["ItemcTab","ItemAndroid","ItemMicroDAGR"]] call cTab_fnc_checkGear}) then {
		0 = _cTabBFTmembers pushBack [_x,_x call cTab_fnc_getInfMarkerIcon,"",name _x,str([_x] call CBA_fnc_getGroupIndex)];
	};
} count units cTab_player;

/*
cTabBFTgroups --- GROUPS
Groups on our side that player is not a member of. Use the leader for positioning if he has a Tablet or Android.
Else, search through the group and use the first member we find equipped with a Tablet or Android for positioning.
*/
{
	if ((side _x in _validSides) && {_x != _playerGroup}) then {
		_leader = objNull;
		call {
			if ([leader _x,["ItemcTab","ItemAndroid"]] call cTab_fnc_checkGear) exitWith {_leader = leader _x;};
			{
				if ([_x,["ItemcTab","ItemAndroid"]] call cTab_fnc_checkGear) exitWith {_leader = _x;};
			} count units _x;
		};
		if !(IsNull _leader) then {
			_groupSize = count units _x;
			_sizeIcon = call {
				if (_groupSize <= 3) exitWith {"\A3\ui_f\data\map\markers\nato\group_0.paa"};
				if (_groupSize <= 9) exitWith {"\A3\ui_f\data\map\markers\nato\group_1.paa"};
				"\A3\ui_f\data\map\markers\nato\group_2.paa"
			};
			0 = _cTabBFTgroups pushBack [_leader,"\A3\ui_f\data\map\markers\nato\b_inf.paa",_sizeIcon,groupID _x,""];
		};
	};
} count allGroups;

/*
cTabBFTvehicles --- VEHICLES
Vehciles on our side, that are not empty and that player is not sitting in.
*/
{
	if ((side _x in _validSides) && {count (crew _x) > 0} && {_x != _playerVehicle}) then {
		_groupID = "";
		_name = "";
		_customName = _x getVariable ["cTab_groupId",""];
		call {
			if !(_customName isEqualTo "") exitWith {
				_name = _customName;
			};
			if (group _x == _playerGroup) then {
				_groupID = str([_x] call CBA_fnc_getGroupIndex)
			};
			_name = groupID group _x;
		};
		_iconA = "";
		_iconB = "";
		call {
			if (_x isKindOf "MRAP_01_base_F") exitWith {_iconA = "\cTab\img\b_mech_inf_wheeled.paa";};
			if (_x isKindOf "MRAP_02_base_F") exitWith {_iconA = "\cTab\img\b_mech_inf_wheeled.paa";};
			if (_x isKindOf "MRAP_03_base_F") exitWith {_iconA = "\cTab\img\b_mech_inf_wheeled.paa";};
			if (_x isKindOf "Wheeled_APC_F") exitWith {_iconA = "\cTab\img\b_mech_inf_wheeled.paa";};
			if (_x isKindOf "Truck_F" && {getNumber (configfile >> "cfgVehicles" >> typeOf _x >> "transportSoldier") > 2}) exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_motor_inf.paa";};
			if (_x isKindOf "Truck_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_support.paa";};
			if (_x isKindOf "Car_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_motor_inf.paa";};
			if (_x isKindOf "UAV") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_uav.paa";};
			if (_x isKindOf "UAV_01_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_uav.paa";};
			if (_x isKindOf "Helicopter") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_air.paa"; _iconB = "\cTab\img\icon_air_contact_ca.paa";};
			if (_x isKindOf "Plane") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_plane.paa"; _iconB = "\cTab\img\icon_air_contact_ca.paa";};
			if (_x isKindOf "Tank" && {getNumber (configfile >> "cfgVehicles" >> typeOf _x >> "transportSoldier") > 6}) exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_mech_inf.paa";};
			if (_x isKindOf "MBT_01_arty_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
			if (_x isKindOf "MBT_01_mlrs_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
			if (_x isKindOf "MBT_02_arty_base_F") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_art.paa";};
			if (_x isKindOf "Tank") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
			if (_x isKindOf "StaticMortar") exitWith {_iconA = "\A3\ui_f\data\map\markers\nato\b_mortar.paa";};
		};
		call {
			if (_iconA isEqualTo "" && {!(_x isKindOf "Static")} && {!(_x isKindOf "StaticWeapon")}) then {_iconA = "\A3\ui_f\data\map\markers\nato\b_unknown.paa";};
			if (_iconA isEqualTo "") exitWith {};
			0 = _cTabBFTvehicles pushBack [_x,_iconA,_iconB,_name,_groupID];
		};
	};
} count vehicles;

/*
cTabUAVlist --- UAVs
*/
{
	if (side _x in _validSides) then {
		0 = _cTabUAVlist pushBack _x;
	};
} count allUnitsUav;

/*
cTabHcamlist --- HELMET CAMS
Units on our side, that have either helmets that have been specified to include a helmet cam, or ItemCTabHCAM in their inventory.
*/
{
	if (side _x in _validSides) then {
		if (headgear _x in cTab_helmetClass_has_HCam || {[_x,["ItemcTabHCam"]] call cTab_fnc_checkGear}) then {
			0 = _cTabHcamlist pushBack _x;
		};
	};
} count allUnits;

// array to hold interface update commands
_updateInterface = [];

// replace the global list arrays in the end so that we avoid them being empty unnecessarily
cTabBFTmembers = [] + _cTabBFTmembers;
cTabBFTgroups = [] + _cTabBFTgroups;
cTabBFTvehicles = [] + _cTabBFTvehicles;
if !(cTabUAVlist isEqualTo _cTabUAVlist) then {
	cTabUAVlist = [] + _cTabUAVlist;
	_updateInterface pushBack ["uavListUpdate",true];
};
if !(cTabHcamlist isEqualTo _cTabHcamlist) then {
	cTabHcamlist = [] + _cTabHcamlist;
	_updateInterface pushBack ["hCamListUpdate",true];
};

// call interface updates
if (count _updateInterface > 0) then {
	[_updateInterface] call cTab_fnc_updateInterface;
};

true