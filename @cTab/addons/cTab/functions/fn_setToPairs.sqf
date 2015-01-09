/*
	Author: Jiri Wainar
	Modified by: Gundy

	Description:
	Sets an item in pair array to given value.

	Remarks:
	Works similar to the BIS_fnc_addToPairs but it doesn't try to add values. It just overwrites the volue if the key already exists.

	Example:
	[["apple",3],["pear",10]] = [[["apple",3],["pear",2]],"pear",10] call BIS_fnc_setToPairs;
*/

private ["_pairs","_key","_value","_index"];

_pairs	= [_this,0,[],[[]]] call bis_fnc_param;
_key 	= [_this,1,"",[""]] call bis_fnc_param;
_value	= [_this,2,1] call bis_fnc_param;
_index  = -1;

{
	if (typeName _x != typeName []) exitWith
	{
		["Every item in the pair array must be an array!"] call BIS_fnc_error;
		_index = -2;
	};
	if (count _x  != 2) exitWith
	{
		["Pair array must contain exactly 2 items, key and value!"] call BIS_fnc_error;
		_index = -2;
	};
	if (isNil{_x select 0}) exitWith
	{
		["Key cannot be nil!"] call BIS_fnc_error;
		_index = -2;
	};
	if (typeName(_x select 0) != typeName "") exitWith
	{
		["Key must be a string!"] call BIS_fnc_error;
		_index = -2;
	};
	if (isNil{_x select 1}) exitWith
	{
		["Value cannot be nil!"] call BIS_fnc_error;
		_index = -2;
	};
	if (_key == (_x select 0)) exitWith
	{
		_index = _forEachIndex;
	};
}
forEach _pairs;

//error occured, exit
if (_index == -2) exitWith {_pairs};

//key not found, add the new entry
if (_index == -1) then
{
	_pairs pushBack [_key, _value];
}
//key found, overwrite the existing entry
else
{
	_pairs set [_index, [_key, _value]];
};

_pairs