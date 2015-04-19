/*
	Name: cTab_fnc_deleteHelmetCam
	
	Author(s):
		Gundy

	Description:
		Delete helmet camera
	
	Parameters:
		0: BOOLEAN (optional) - Terminate, FALSE if camera update script should not be terminated
	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		call cTab_fnc_deleteHelmetCam;

*/

private ["_cam"];

_terminate = if (count _this == 1) then {_this select 0} else {true};

// terminate camera update script
if (_terminate) then {
	if (!scriptDone cTabHcamScriptHandle) then {
		terminate cTabHcamScriptHandle;
		waitUntil {scriptDone cTabHcamScriptHandle};
		systemChat str ["terminated"];
	};
};

if (!isNil "cTabHcams") then {
	_cam = cTabHcams select 0;
	_cameraTarget = cTabHcams select 1;
	_leaningIndicator = cTabHcams select 2;
	cTabHcams = nil;
	_cam cameraEffect ["TERMINATE","BACK"];
	camDestroy _cam;
    deleteVehicle _leaningIndicator;
    deleteVehicle _cameraTarget;
};

if (!isNil "cTabHcamEventHandle") then {
	removeMissionEventHandler ["Draw3D",cTabHcamEventHandle];
	cTabHcamEventHandle = nil;
};

true