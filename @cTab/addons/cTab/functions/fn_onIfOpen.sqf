/*
	Name: cTab_fnc_onIfOpen
	
	Author(s):
		Gundy
	
	Description:
		Handles dialog / display startup and registering of event handlers
		
		This function will define cTabIfOpen, using the following format:
			Parameter 0: Interface type, 0 = Main, 1 = Secondary, 2 = Tertiary
			Parameter 1: Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
			Parameter 2: Unit we registered the killed eventhandler for
			Parameter 3: ID of registered eventhandler for killed event
			Parameter 4: Vehicle we registered the GetOut eventhandler for (even if no EH is registered)
			Parameter 5: ID of registered eventhandler for GetOut event (nil if no EH is registered)
	
	Parameters:
		0: INTEGER - Interface type, 0 = Main, 1 = Secondary
		1: STRING  - Name of uiNameSpace variable for display / dialog (i.e. "cTab_Tablet_dlg")
		2: OBJECT  - Unit to register killed eventhandler for
		3: OBJECT  - Vehicle to register GetOut eventhandler for
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		// open TAD display as main interface type
		cTabOnIfOpenScriptHandler = [0,"cTab_TAD_dsp",player,vehicle player] spawn cTab_fnc_onIfOpen;
*/

private ["_interfaceType","_displayName","_player","_vehicle","_playerKilledEhId","_vehicleGetOutEhId"];

if (cTabIfOpenStart || (!isNil "cTabIfOpen")) exitWith {false};
cTabIfOpenStart = true;

_interfaceType = _this select 0;
_displayName = _this select 1;
_player = _this select 2;
_vehicle = _this select 3;

if ([_displayName] call cTab_fnc_isDialog) then {
	closeDialog 0;
	waitUntil {!dialog};
	createDialog _displayName;
	waitUntil {dialog};
} else {
	cTabRscLayer cutRsc [_displayName,"PLAIN",0, false];
	waitUntil {!isNull (uiNamespace getVariable _displayName)};
};

_playerKilledEhId = _player addEventHandler ["killed",{call cTab_fnc_close}];
if (_vehicle != _player) then {
	_vehicleGetOutEhId = _vehicle addEventHandler ["GetOut",{if (_this select 2 == cTab_player) then {call cTab_fnc_close}}];
	cTabIfOpen = [_interfaceType,_displayName,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId];
} else {
	cTabIfOpen = [_interfaceType,_displayName,_player,_playerKilledEhId,_vehicle,nil];
};

call cTab_fnc_updateInterface;
cTabIfOpenStart = false;

true