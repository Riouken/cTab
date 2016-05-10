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
		2: BOOLEAN - If set to false, do not update interface (default true)
		3: BOOLEAN - If set to true, update interface even if the values haven't changed (default false)
 	
 	Returns:
 		BOOLEAN - If settings could be stored
 	
 	Example:
		["cTab_Tablet_dlg",[["mapType","SAT"],["mapScaleDsp","4"]]] call cTab_fnc_setSettings;
		
		// Update mapWorldPos and update the interface even if the value has not changed
		["cTab_Tablet_dlg",[["mapWorldPos",getPosASL vehicle player]],true,true] call cTab_fnc_setSettings;
		
		// Update mapWorldPos and mapScale, but do not update the interface
		["cTab_Tablet_dlg",[["mapWorldPos",getPosASL vehicle player],["mapScaleDsp","2"]],false] call cTab_fnc_setSettings;
*/

private ["_propertyGroupName","_commonProperties","_groupProperties","_properties","_commonPropertiesUpdate","_combinedPropertiesUpdate","_key","_value","_currentValue","_updateInterface","_forceInterfaceUpdate"];

_propertyGroupName = [cTabDisplayPropertyGroups,_this select 0] call cTab_fnc_getFromPairs;

// Exit with FALSE if uiNamespace variable cannot be found in cTabDisplayPropertyGroups
if (isNil "_propertyGroupName") exitWith {false};

_commonProperties = [cTabSettings,"COMMON"] call cTab_fnc_getFromPairs;
_groupProperties = [cTabSettings,_propertyGroupName] call cTab_fnc_getFromPairs;
if (isNil "_groupProperties") then {_groupProperties = [];};

_properties = _this select 1;
_updateInterface = if (count _this > 2) then {_this select 2} else {true};
_forceInterfaceUpdate = if (count _this > 3) then {_this select 3} else {false};

// Write multiple property pairs. If they exist in _groupProperties, write them there, else write them to COMMON. Only write if they exist and have changed.
_commonPropertiesUpdate = [];
_combinedPropertiesUpdate = [];
{
	_key = _x select 0;
	_value = _x select 1;
	call {
		_currentValue = [_groupProperties,_key] call cTab_fnc_getFromPairs;
		if (!isNil "_currentValue") exitWith {
			call {
				if !(_currentValue isEqualTo _value) exitWith {
					[_combinedPropertiesUpdate,_key,_value] call BIS_fnc_setToPairs;
					[_groupProperties,_key,_value] call BIS_fnc_setToPairs;
				};
				if (_forceInterfaceUpdate) then {
					[_combinedPropertiesUpdate,_key,_value] call BIS_fnc_setToPairs;
				};
			};
		};
		_currentValue = [_commonProperties,_key] call cTab_fnc_getFromPairs;
		if (!isNil "_currentValue") then {
			call {
				if !(_currentValue isEqualTo _value) then {
					[_commonPropertiesUpdate,_key,_value] call BIS_fnc_setToPairs;
					[_commonProperties,_key,_value] call BIS_fnc_setToPairs;
				};
				if (_forceInterfaceUpdate) then {
					[_commonPropertiesUpdate,_key,_value] call BIS_fnc_setToPairs;
				};
			};
		};
	};
} forEach _properties;
[cTabSettings,_propertyGroupName,_groupProperties] call BIS_fnc_setToPairs;
[cTabSettings,"COMMON",_commonProperties] call BIS_fnc_setToPairs;

// Finally, call an interface update for the updated properties, but only if the currently interface uses the same property group, if not, pass changed common properties only.
if (!isNil "cTabIfOpen") then {
	call {
		if (!_updateInterface) exitWith {};
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