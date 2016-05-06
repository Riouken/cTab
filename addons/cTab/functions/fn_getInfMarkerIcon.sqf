/*
 	Name: cTab_fnc_getInfMarkerIcon
 	
 	Author(s):
		Gundy

 	Description:
		Fetch infantry marker, based on Shack Tactical ST_STHud_GetMarkerName

	Parameters:
	(Optional)
		0: OBJECT - Unit to return infantry marker for
 	
 	Returns:
		STRING - Path to infantry marker
 	
 	Example:
		player call cTab_fnc_getInfMarkerIcon;
*/

private "_unit";

_unit = _this;

if (getNumber(configFile >> "CfgVehicles" >> typeOf(_unit) >> "attendant") == 1) exitWith {
	"\A3\ui_f\data\map\vehicleicons\iconManMedic_ca.paa"
};
if (getNumber(configFile >> "CfgVehicles" >> typeOf(_unit) >> "engineer") == 1) exitWith {
	"\A3\ui_f\data\map\vehicleicons\iconManEngineer_ca.paa"
};
if (leader(_unit) == _unit) exitWith {
	"\A3\ui_f\data\map\vehicleicons\iconManLeader_ca.paa"
};
// This appears to be the most consistent way to detect that a weapon is an
// MG of some sort. These pictures are the overlays for the BIS team hud.
if (getText(configFile >> "CfgWeapons" >> primaryWeapon(_unit) >> "UIPicture") == "\a3\weapons_f\data\ui\icon_mg_ca.paa") exitWith {
	"\A3\ui_f\data\map\vehicleicons\iconManMG_ca.paa"
};
// Do something similar for launchers.
if (getText(configFile >> "CfgWeapons" >> secondaryWeapon(_unit) >> "UIPicture") == "\a3\weapons_f\data\ui\icon_at_ca.paa") exitWith {
	"\A3\ui_f\data\map\vehicleicons\iconManAT_ca.paa"
};
"\A3\ui_f\data\map\vehicleicons\iconMan_ca.paa"