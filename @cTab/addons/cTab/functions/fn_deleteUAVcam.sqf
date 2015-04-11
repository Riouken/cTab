/*
	Name: cTab_fnc_deleteUAVcam
	
	Author(s):
		Gundy

	Description:
		Delete UAV camera
	
	Parameters:
		0: BOOLEAN - Terminate, FALSE if camera direction update script should not be terminated
 	
	Returns:
		BOOLEAN - TRUE
	
	Example:
		// delete all UAV cameras
		[true] call cTab_fnc_deleteUAVcam;
		
		// delete UAV cameras, but keep update script running
		[false] call cTab_fnc_deleteUAVcam;
*/

private ["_cam","_terminate"];

_terminate = _this select 0;

// terminate camera direction update script
if (_terminate) then {
	if (!isNil "cTabUavEventHandle") then {
		removeMissionEventHandler ["Draw3D",cTabUavEventHandle];
		cTabUavEventHandle = nil;
	};
};

// remove cameras
{
	_cam = _x select 2;
	_cam cameraEffect ["TERMINATE","BACK"];
	camDestroy _cam;
} count cTabUAVcams;

cTabUAVcams = [];

true