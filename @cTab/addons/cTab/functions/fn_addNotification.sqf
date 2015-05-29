/*
 * Author: Gundy
 *
 * Description:
 *   Add a notification
 *
 * Arguments:
 *   0: App ID <STRING>
 *   1: Notification <STRING>
 *
 * Return Value:
 *   TRUE <BOOL>
 *
 * Example:
 *   [_appID,"This is a notification"] call cTab_fnc_addNotification;
 *
 * Public: No
 */

private ["_appID","_notification","_time","_done"];

_appID = _this select 0;
_notification = _this select 1;
_time = [] call cTab_fnc_currentTime;
_done = false;

// search for other _appID notifications
{
	// if we find one, override it and increase the counter
	if ((_x select 0) isEqualTo _appID) exitWith {
		cTabNotificationCache set [_forEachIndex,[_appID,_time,_notification,(_x select 3) + 1]];
		_done = true;
	};
} forEach cTabNotificationCache;

// if we haven't added the notification to the cache above, do it now
if !(_done) then {
	cTabNotificationCache pushBack [_appID,_time,_notification,1];
};

[] call cTab_fnc_processNotifications;

true