/*
 	Name: cTab_fnc_setSettings
 	
 	Author(s):
		Gundy

 	Description:
		Write cTab settings. Will call cTab_updateInterface for any setting that changed.

	Parameters:
		0: STRING - Name of uiNamespace display / dialog variable
		1: ARRAY  - Property pair(s) to write in the form of [["propertyName",propertyValue],[...]]
		
		(Optional)
		2: BOOLEAN - If set to false, do not update interface 
 	
 	Returns:
 		BOOLEAN - If settings could be stored
 	
 	Example:
		["cTab_Tablet_dlg",["mapType","SAT"],["mapScale","4"]] call cTab_fnc_setSettings;
*/

private ["_propertyGroupName","_commonProperties","_groupProperties","_properties","_commonPropertiesUpdate","_combinedPropertiesUpdate","_key","_value","_currentValue"];

_propertyGroupName = [cTabDisplayPropertyGroups,_this select 0] call cTab_fnc_getFromPairs;

// Exit with FALSE if uiNamespace variable cannot be found in cTabDisplayPropertyGroups
if (isNil "_propertyGroupName") exitWith {false};

_commonProperties = [cTabSettings,"COMMON"] call cTab_fnc_getFromPairs;
_groupProperties = [cTabSettings,_propertyGroupName] call cTab_fnc_getFromPairs;
if (isNil "_groupProperties") then {_groupProperties = [];};

_properties = _this select 1;

// Write multiple property pairs. If they exist in _groupProperties, write them there, else write them to COMMON. Only write if they exist and have changed.
_commonPropertiesUpdate = [];
_combinedPropertiesUpdate = [];
{
	_key = _x select 0;
	_value = _x select 1;
	call {
		_currentValue = [_groupProperties,_key] call cTab_fnc_getFromPairs;
		if (!isNil "_currentValue") exitWith {
			if !(_currentValue isEqualTo _value) then {
				[_combinedPropertiesUpdate,_key,_value] call BIS_fnc_setToPairs;
				[_groupProperties,_key,_value] call BIS_fnc_setToPairs;
			};
		};
		_currentValue = [_commonProperties,_key] call cTab_fnc_getFromPairs;
		if (!isNil "_currentValue") then {
			if  !(_currentValue isEqualTo _value) then {
				[_commonPropertiesUpdate,_key,_value] call BIS_fnc_setToPairs;
				[_commonProperties,_key,_value] call BIS_fnc_setToPairs;
			};
		};
	};
} forEach _properties;
[cTabSettings,_propertyGroupName,_groupProperties] call BIS_fnc_setToPairs;
[cTabSettings,"COMMON",_commonProperties] call BIS_fnc_setToPairs;

// Finally, call an interface update for the updated properties, but only if the currently interface uses the same property group, if not, pass changed common properties only.
if (!isNil "cTabIfOpen") then {
	call {
		_updateInterface = _this select 2;
		if (!isNil "_updateInterface" && {!_updateInterface}) exitWith {};
		if ((([cTabDisplayPropertyGroups,cTabIfOpen select 1] call cTab_fnc_getFromPairs) == _propertyGroupName) && {count _combinedPropertiesUpdate > 0}) exitWith {
			[_combinedPropertiesUpdate] call cTab_fnc_updateInterface;
		};
		if (count _commonPropertiesUpdate > 0) then {
			[_commonPropertiesUpdate] call cTab_fnc_updateInterface;
		};
	};
};

if (_combinedPropertiesUpdate isEqualTo [] && _combinedPropertiesUpdate isEqualTo []) exitWith {false};

true