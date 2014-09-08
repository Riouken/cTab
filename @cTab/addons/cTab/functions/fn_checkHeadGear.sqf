/*
 	Name: cTab_fnc_checkHeadGear
 	
 	Author(s):
		Gundy

 	Description:
		Check a unit's helmet against a list of helmet types
	
	Parameters:
		0: OBJECT - Unit object to check gear on
		1: ARRAY  - Array of item names to search for
 	
 	Returns:
		BOOLEAN - If at least one of the items passed in parameter 1 was found or not
 	
 	Example:
		_playerHasHelmetCam = [player,["H_HelmetB_light","H_Helmet_Kerry","H_HelmetSpecB","H_HelmetO_ocamo"]] call cTab_fnc_checkHeadGear;
*/

private ["_unit","_items","_chk_all_items","_entry"]; 

_unit = _this select 0;
_items = _this select 1;
_chk_all_items= [];
_entry = configfile >> "CfgWeapons" >> headgear _unit;

while {isclass _entry} do {
	_chk_all_items set [count _chk_all_items,configname _entry];
	_entry = inheritsfrom _entry;
};

{_x in _chk_all_items} count _items > 0