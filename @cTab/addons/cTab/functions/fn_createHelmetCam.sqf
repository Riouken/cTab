/*
 	Name: cTab_fnc_createHelmetCam
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Set up helmet camera and display on supplied render target
	
	Parameters:
		0: STRING - Render target
		1: STRING - Name of unit with helmet camera (format used from `str unitObject`)
 	
 	Returns:
		BOOLEAN - If helmet cam could be set up or not
 	
 	Example:
		["rendertarget12",str player] spawn cTab_fnc_createHelmetCam;
*/

private ["_renderTarget","_data","_newHost","_camOffSet","_targetOffSet","_oldCam","_oldHost","_nop","_target","_cam"];

_renderTarget = _this select 0;
_data = _this select 1;

_newHost = objNull;
_camOffSet = [];
_targetOffSet = [];

// see if given unit name is still in the list of units with valid helmet cams
{
	if (_data == str _x) exitWith {_newHost = _x;};
} count cTabHcamlist;

// if there is no valid unit or we are not allowed to set up a helmet cam in these conditions, drop out of full screen view
if (IsNull _newHost) exitWith {
	["cTab_Tablet_dlg",[["mode","HCAM"]]] call cTab_fnc_setSettings;
	false
};

_camHost = vehicle _newHost;

/*call {
	// should unit not be in a vehicle
	if (vehicle _newHost isKindOf "CAManBase") exitWith {
		
	};
	// if unit is in a vehilce, see if 3rd person view is allowed
	if (difficultyEnabled "3rdPersonView") exitWith {
		// Might want to calculate offsets based on the actual vehicle dimensions in the future
		_camOffSet = (vehicle _newHost) worldToModel (_newHost modelToWorld (_newHost selectionPosition "head"));
		//_camOffSet = [0,-8,4];
		_targetOffSet = [0,8,2];
		_newHost = vehicle _newHost;
	};
	// if unit is in a vehicle and 3rd person view is not allowed
	_newHost = objNull;
};*/

// if there is already a camera, see if its the same one we are about to set up
// if true, render to given target (in case the target has changed), else delete the camera so we can create a new one
if (!isNil "cTabHcams") then {
	_oldCam = cTabHcams select 0;
	_oldHost = cTabHcams select 3;
	if (_oldHost isEqualTo _newHost) then {
		_oldCam cameraEffect ["INTERNAL","BACK",_renderTarget];
	} else {
		[false] call cTab_fnc_deleteHelmetCam;
	};
};

// only continue if there is no helmet cam currently set up
if (!isNil "cTabHcams") exitWith {true};

_camOffSet = [0.15,0.05,0];
_targetOffSet = [0,8,1];

// check if host is in a vehicle
if (_newHost != _camHost) then {
	_headOffSet = _camHost worldToModel (_newHost modelToWorld (_newHost selectionPosition "pilot"));
	_rotation = ((eyeDirection _newHost select 0) atan2 (eyeDirection _newHost select 1) + direction _camHost - 360);
	_camOffSet = [((_camOffSet select 0) * cos _rotation) + ((_camOffSet select 1) * sin _rotation), ((_camOffSet select 0) * sin _rotation) * -1 + ((_camOffSet select 1) * cos _rotation), _camOffSet select 2];
	_targetOffSet = [((_targetOffSet select 0) * cos _rotation) + ((_targetOffSet select 1) * sin _rotation), ((_targetOffSet select 0) * sin _rotation) * -1 + ((_targetOffSet select 1) * cos _rotation), _targetOffSet select 2];
	_camOffSet = _camOffSet vectorAdd _headOffSet;
	_targetOffSet = _targetOffSet vectorAdd _headOffSet;
	systemChat str _rotation;
};

_target = "Sign_Sphere10cm_F" createVehicleLocal position player;
hideObject _target;
_target attachTo [_camHost,_targetOffSet];

_cam = "camera" camCreate getPosATL _camHost;
_cam camPrepareFov 0.700;
_cam camPrepareTarget _target;
_cam camCommitPrepared 0;
if (_newHost == _camHost) then {
	systemChat str ["head"];
	_cam attachTo [_camHost,_camOffSet,"pilot"];
} else {
	systemChat str ["vehicle"];
	_cam attachTo [_camHost,_camOffSet];
};
_cam cameraEffect ["INTERNAL","BACK",_renderTarget];

cTabHcams = [_cam,_target,_camHost,_newHost];

// set up event handler
if !(cTabHcams isEqualTo []) exitWith {
	if (scriptDone cTabHcamScriptHandle) then {
		// use spawn instead of addMissionEventHandler until http://feedback.arma3.com/view.php?id=21737 gets fixed
		cTabHcamScriptHandle = [] spawn {
			while {true} do {
				if !(isNil "cTabHcams") then {
					_camHost = cTabHcams select 2;
					_newHost = cTabHcams select 3;
					if (_camHost != vehicle _newHost) then {
						_camHost = vehicle _newHost;
						_cam = cTabHcams select 0;
						_target = cTabHcams select 1;
						_camOffSet = [0.15,0.05,0];
						_targetOffSet = [0,8,1];
						// check if host is in a vehicle
						if (_newHost != _camHost) then {
							// get the eye direction as a vector (relative to north)
							_eyeDirection = eyeDirection _newHost;
							// calculate the angle from _eyeDirection and make it relative to the vehicle
							_rotation = (_eyeDirection select 0) atan2 (_eyeDirection select 1) + direction _camHost - 360;
							_cosRotation = cos _rotation;
							_sinRotation = sin _rotation;
							// rotate both _camOffSet and _targetOffSet by the _rotation angle in clock-wise direction
							_camOffSet = [((_camOffSet select 0) * _cosRotation) + ((_camOffSet select 1) * _sinRotation), ((_camOffSet select 0) * _sinRotation) * -1 + ((_camOffSet select 1) * _cosRotation), _camOffSet select 2];
							_targetOffSet = [((_targetOffSet select 0) * _cosRotation) + ((_targetOffSet select 1) * _sinRotation), ((_targetOffSet select 0) * _sinRotation) * -1 + ((_targetOffSet select 1) * _cosRotation), _targetOffSet select 2];
							// get the memory point for the head (model coordinates), transplant that to world coordinates and then transplant these back to model coordinates relative to the vehicle
							_headOffSet = _camHost worldToModel (_newHost modelToWorld (_newHost selectionPosition "pilot"));
							// combine the _headOffSet with both the _camOffSet and _targetOffSet to correctly place camera and target within the vehicle model
							_camOffSet = _camOffSet vectorAdd _headOffSet;
							_targetOffSet = _targetOffSet vectorAdd _headOffSet;
							
							systemChat str _rotation;
						};
						_target attachTo [_camHost,_targetOffSet];
						
						if (_newHost == _camHost) then {
							systemChat str ["head"];
							_cam attachTo [_camHost,_camOffSet,"pilot"];
						} else {
							systemChat str ["vehicle"];
							_cam attachTo [_camHost,_camOffSet];
						};
						
						cTabHcams = [_cam,_target,_camHost,_newHost];
					};
				};
			};
		};
	};
	
	true
};

false