/*
 * Author: Gundy
 *
 * Description:
 *   Process cached notifications
 *
 * Arguments:
 *   NONE
 *
 * Return Value:
 *   TRUE <BOOL>
 *
 * Example:
 *   [] call cTab_devices_processNotifications;
 *
 * Public: No
 */

#include "\cTab\shared\cTab_gui_macros.hpp"

private ["_displayName","_display","_ctrl","_currentTime","_text","_notification"];

// make sure there is no PFH already, the interface is open and notifications are available
if (isNil "cTabProcessNotificationsPFH" && !(isNil "cTabIfOpen") && count cTabNotificationCache != 0) then {
	_displayName = cTabIfOpen select 1;
	_display = uiNamespace getVariable _displayName;
	_ctrl = _display displayCtrl IDC_CTAB_NOTIFICATION;
	
	// only proceed if there is a notification control
	if (!isNull _ctrl) then {
		// run every 4 seconds
		cTabProcessNotificationsPFH = [{
			private ["_ctrl","_notification","_currentTime","_text"];
			
			if !(isNil "cTabIfOpen") then {
				if (count cTabNotificationCache != 0) then {
					// grab and delete the oldest notification
					_notification = cTabNotificationCache deleteAt 0;
					
					_currentTime = [] call cTab_fnc_currentTime;
					// see if notification was issued in the same minute, if so, omit showing the time
					if (_currentTime isEqualTo (_notification select 1)) then {
						_text = format ["%1",_notification select 2];
					} else {
						_text = format ["%1: %2",_notification select 1,_notification select 2];
					};
					// if the counter on the notification is greater than 1, append the counter to the notification text
					if ((_notification select 3) > 1) then {
						_text = format ["%1 (x%2)",_text,_notification select 3];
					};
					
					// show the notification
					_ctrl = _this select 0 select 0;
					_ctrl ctrlSetText _text;
					// make the control visible (it might have had its fade set to 1 before)
					_ctrl ctrlSetFade 0;
					_ctrl ctrlCommit 0;
					_ctrl ctrlShow true;
					
					// bring the control to the front. Enable is required before focus can be set
					_ctrl ctrlEnable true;
					ctrlSetFocus _ctrl;
					_ctrl ctrlEnable false;
					
					// make the control fade out
					_ctrl ctrlSetFade 1;
					_ctrl ctrlCommit 5;
				} else {
					[_this select 1] call CBA_fnc_removePerFrameHandler;
					_ctrl ctrlShow false;
					cTabProcessNotificationsPFH = nil;
				};
			} else {
				[_this select 1] call CBA_fnc_removePerFrameHandler;
				cTabProcessNotificationsPFH = nil;
			};
		},4,[_ctrl]] call CBA_fnc_addPerFrameHandler;
	};
};

true