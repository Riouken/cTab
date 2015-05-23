/*
	Name: cTab_fnc_distance2D
	
	Author(s):
		Gundy

	Description:
		Calculate the 2D distance between two positions
	
	Parameters:
		0: ARRAY - 2D or 3D position
		1: ARRAY - 2D or 3D position
	
	Returns:
		FLOAT - Distance
	
	Example:
		[getPosATL player, [0,0,0]] call cTab_fnc_distance2D;
*/

private ["_pos1","_pos2"];
_pos1 = _this select 0;
_pos2 = _this select 1;

// set height to 0;
_pos1 set [2,0];
_pos2 set [2,0];

_pos1 distance _pos2