#include "\a3\editor_f\Data\Scripts\dikCodes.h"

_keyConfig = (configFile >> "cTab_keys");

cTab_key_if_main_scancode = DIK_H;
cTab_key_if_main_modifiers = [false,false,false];
if (isNumber (_keyConfig >> "if_main" >> "key")) then {
	cTab_key_if_main_scancode = getNumber (_keyConfig >> "if_main" >> "key")
};
{
	if (isNumber (_keyConfig >> "if_main" >> _x)) then {
		cTab_key_if_main_modifiers set [_forEachIndex,getNumber (_keyConfig >> "if_main" >> _x) == 1];
	};
} forEach ["shift","ctrl","alt"];

cTab_key_if_secondary_scancode = DIK_H;
cTab_key_if_secondary_modifiers = [false,true,false];
if (isNumber (_keyConfig >> "if_secondary" >> "key")) then {
	cTab_key_if_secondary_scancode = getNumber (_keyConfig >> "if_secondary" >> "key")
};
{
	if (isNumber (_keyConfig >> "if_secondary" >> _x)) then {
		cTab_key_if_secondary_modifiers set [_forEachIndex,getNumber (_keyConfig >> "if_secondary" >> _x) == 1];
	};
} forEach ["shift","ctrl","alt"];

cTab_key_if_tertiary_scancode = DIK_H;
cTab_key_if_tertiary_modifiers = [false,false,true];
if (isNumber (_keyConfig >> "if_tertiary" >> "key")) then {
	cTab_key_if_tertiary_scancode = getNumber (_keyConfig >> "if_tertiary" >> "key")
};
{
	if (isNumber (_keyConfig >> "if_tertiary" >> _x)) then {
		cTab_key_if_tertiary_modifiers set [_forEachIndex,getNumber (_keyConfig >> "if_tertiary" >> _x) == 1];
	};
} forEach ["shift","ctrl","alt"];

cTab_key_zoom_in_scancode = DIK_PGUP;
cTab_key_zoom_in_modifiers = [true,true,false];
if (isNumber (_keyConfig >> "zoom_in" >> "key")) then {
	cTab_key_zoom_in_scancode = getNumber (_keyConfig >> "zoom_in" >> "key")
};
{
	if (isNumber (_keyConfig >> "zoom_in" >> _x)) then {
		cTab_key_zoom_in_modifiers set [_forEachIndex,getNumber (_keyConfig >> "zoom_in" >> _x) == 1];
	};
} forEach ["shift","ctrl","alt"];

cTab_key_zoom_out_scancode = DIK_PGDN;
cTab_key_zoom_out_modifiers = [true,true,false];
if (isNumber (_keyConfig >> "zoom_out" >> "key")) then {
	cTab_key_zoom_out_scancode = getNumber (_keyConfig >> "zoom_out" >> "key")
};
{
	if (isNumber (_keyConfig >> "zoom_out" >> _x)) then {
		cTab_key_zoom_out_modifiers set [_forEachIndex,getNumber (_keyConfig >> "zoom_out" >> _x) == 1];
	};
} forEach ["shift","ctrl","alt"];

cTab_key_toggleIfPosition_scancode = DIK_HOME;
cTab_key_toggleIfPosition_modifiers = [true,true,false];
if (isNumber (_keyConfig >> "toggleIfPosition" >> "key")) then {
	cTab_key_zoom_out_scancode = getNumber (_keyConfig >> "toggleIfPosition" >> "key")
};
{
	if (isNumber (_keyConfig >> "toggleIfPosition" >> _x)) then {
		cTab_key_zoom_out_modifiers set [_forEachIndex,getNumber (_keyConfig >> "toggleIfPosition" >> _x) == 1];
	};
} forEach ["shift","ctrl","alt"];