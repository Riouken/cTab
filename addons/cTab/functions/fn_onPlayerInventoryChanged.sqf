/*
	Name: cTab_fnc_onPlayerInventoryChanged
	
	Author(s):
		Gundy
	
	Description:
		Handles ACE3 event that triggers upon player's inventory changed event. It will check to see if there is currently a cTab device that requires a an inventory item open and if that is the case, close that device.
	
	Parameters:
		0: OBJECT - player object that an inventory change was detected for
		1: ARRAY  - list of the new player inventory as returned by ace_common_fnc_getAllGear
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		[ACE_player,[player] call ace_common_fnc_getAllGear] call cTab_fnc_onPlayerInventoryChanged;
*/

private ["_displayName","_newPlayerInventory","_playerLostDevice","_itemsToCheck"];

// is cTab oben? if not exit
if (isNil "cTabIfOpen") exitWith {true};

// are we looking at the same player object? if not exit
if (_this select 0 != cTab_player) exitWith {true};

// get the currently open cTab device
_displayName = cTabIfOpen select 1;

// get the current inventory state
_newPlayerInventory = _this select 1;
// add all the item areas we need to look through to one big array
// index 17 of _newPlayerInventory is assignedItems, 3 is uniformItems, 5 is vestItems, 7 is backpackItems
_itemsToCheck = (_newPlayerInventory select 17) + (_newPlayerInventory select 3) + (_newPlayerInventory select 5) + (_newPlayerInventory select 7);

// see if we still have the correct device on us
_playerLostDevice = call {
	if (_displayName == "cTab_Tablet_dlg") exitWith {
		!("ItemcTab" in _itemsToCheck)
	};
	if (_displayName in ["cTab_Android_dlg","cTab_Android_dsp"]) exitWith {
		!("ItemAndroid" in _itemsToCheck)
	};
	if (_displayName in ["cTab_microDAGR_dsp","cTab_microDAGR_dlg"]) exitWith {
		!("ItemMicroDAGR" in _itemsToCheck)
	};
	false
};

if (_playerLostDevice) then {[] call cTab_fnc_close};

true