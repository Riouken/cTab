/*
	Name: cTab_fnc_dirTo
	
	Author(s):
		Gundy

	Description:
		Returns compass direction (horizontal) from first position to second position
	
	Parameters:
		0: ARRAY - 2D or 3D position
		1: ARRAY - 2D or 3D position
	
	Returns:
		FLOAT - Distance
	
	Example:
		[getPosATL player, [0,0,0]] call cTab_fnc_dirTo;
*/

private ["_pos1","_pos2","_vector","_dirTo"];

_pos1 = _this select 0;
_pos2 = _this select 1;

_dirTo = ((_pos2 select 0) - (_pos1 select 0)) atan2 ((_pos2 select 1) - (_pos1 select 1));

(_dirTo + 360) % 360