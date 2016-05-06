/*
	Author: Jiri Wainar, modified by Gundy to fix return of "nil" (line 63), see http://feedback.arma3.com/view.php?id=20643

	Description:
	Searches the associative array for the 1st occurance of the key string and returns the value associated with it.

	Syntax:
	_value = [_associativeArray:array,_key:string,_defaultValue] call cTab_fnc_getFromPairs;

	Example:
	2 = [[["apple",3],["pear",2]],"pear"] call cTab_fnc_getFromPairs;

	Returns:
	* if found: value stored under the key
	* if not found: nil or _defaultValue
*/

private ["_pairs","_key","_default","_value"];

_pairs 	 = [_this,0,[],[[]]] call bis_fnc_param;
_key 	 = [_this,1,"",[""]] call bis_fnc_param;

if (count _this > 2) then
{
	_default = [_this,2] call bis_fnc_param;
}
else
{
	_default = nil;
};


{
	if (typeName _x != typeName []) exitWith
	{
		["Every item in the pair array must be an array!"] call BIS_fnc_error;
	};
	if (count _x  != 2) exitWith
	{
		["Pair array must contain exactly 2 items, key and value!"] call BIS_fnc_error;
	};
	if (isNil{_x select 0}) exitWith
	{
		["Key cannot be nil!"] call BIS_fnc_error;
	};
	if (typeName(_x select 0) != typeName "") exitWith
	{
		["Key must be a string!"] call BIS_fnc_error;
	};
	if (isNil{_x select 1}) exitWith
	{
		["Value cannot be nil!"] call BIS_fnc_error;
	};


	if (_key == (_x select 0)) exitwith
	{
		_value = _x select 1;
	};
}
forEach _pairs;

if (isNil "_value") exitWith {if (isNil "_default") then {nil} else {_default}};

_value