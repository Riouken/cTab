/*
	Name: cTab_fnc_onIfclose
	
	Author(s):
		Gundy
	
	Description:
		Closes the currently open interface and remove any previously registered eventhandlers.
	
	Parameters:
		No Parameters
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		[] call cTab_fnc_onIfclose;
*/

private ["_displayName","_mapScale","_ifType","_player","_playerKilledEhId","_vehicle","_vehicleGetOutEhId","_draw3dEhId","_aceUnconciousEhId","_acePlayerInventoryChangedEhId","_backgroundPosition","_backgroundPositionX","_backgroundPositionY","_backgroundConfigPositionX","_backgroundConfigPositionY","_xOffset","_yOffset","_backgroundOffset"];

// remove helmet and UAV cameras
[] call cTab_fnc_deleteHelmetCam;
[] call cTab_fnc_deleteUAVcam;

if !(isNil "cTabIfOpen") then {
	// [_ifType,_displayName,_player,_playerKilledEhId,_vehicle,_vehicleGetOutEhId]
	_ifType = cTabIfOpen select 0;
	_displayName = cTabIfOpen select 1;
	_player = cTabIfOpen select 2;
	_playerKilledEhId = cTabIfOpen select 3;
	_vehicle = cTabIfOpen select 4;
	_vehicleGetOutEhId = cTabIfOpen select 5;
	_draw3dEhId = cTabIfOpen select 6;
	_aceUnconciousEhId = cTabIfOpen select 7;
	_acePlayerInventoryChangedEhId = cTabIfOpen select 8;
	
	if (!isNil "_playerKilledEhId") then {_player removeEventHandler ["killed",_playerKilledEhId]};
	if (!isNil "_vehicleGetOutEhId") then {_vehicle removeEventHandler ["GetOut",_vehicleGetOutEhId]};
	if (!isNil "_draw3dEhId") then {removeMissionEventHandler ["Draw3D",_draw3dEhId]};
	if (!isNil "_aceUnconciousEhId") then {["medical_onUnconscious",_aceUnconciousEhId] call ace_common_fnc_removeEventHandler};
	if (!isNil "_acePlayerInventoryChangedEhId") then {["playerInventoryChanged",_acePlayerInventoryChangedEhId] call ace_common_fnc_removeEventHandler};
	
	// remove notification system related PFH
	if !(isNil "cTabProcessNotificationsPFH") then {
		[cTabProcessNotificationsPFH] call CBA_fnc_removePerFrameHandler;
		cTabProcessNotificationsPFH = nil;
	};
	
	// don't call this part if we are closing down before setup has finished
	if (!cTabIfOpenStart) then {
		if ([_displayName] call cTab_fnc_isDialog) then {
			// convert mapscale to km
			_mapScale = cTabMapScale * cTabMapScaleFactor / 0.86 * (safezoneH * 0.8);
			
			// get the current position of the background control
			_backgroundPosition = [_displayName] call cTab_fnc_getBackgroundPosition;
			_backgroundPositionX = _backgroundPosition select 0 select 0;
			_backgroundPositionY = _backgroundPosition select 0 select 1;
			
			// get the original position of the background control
			_backgroundConfigPositionX = _backgroundPosition select 1 select 0;
			_backgroundConfigPositionY = _backgroundPosition select 1 select 1;
			
			// calculate x and y as offsets to the original
			_xOffset = _backgroundPositionX - _backgroundConfigPositionX;
			_yOffset = _backgroundPositionY - _backgroundConfigPositionY;
			
			// figure out if the interface position has changed
			_backgroundOffset = if (_xOffset != 0 || _yOffset != 0) then {
				[_xOffset,_yOffset]
			} else {
				[]
			};
			
			// Save mapWorldPos and mapScaleDlg of current dialog so it can be restored later
			[_displayName,[["mapWorldPos",cTabMapWorldPos],["mapScaleDlg",_mapScale],["dlgIfPosition",_backgroundOffset]],false] call cTab_fnc_setSettings;
		};
	};
	
	uiNamespace setVariable [_displayName, displayNull];
	cTabIfOpen = nil;
};

cTabCursorOnMap = false;
cTabIfOpenStart = false;

true