// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


_test = player getVariable ["cTabHcams",[]];

if (count _test != 0) then {

	_nop = [] call cTabHcamDelCam;
	waitUntil {_nop};
};

_Hcam = cTabHcamlist select (_this select 1);
cTabActHcam = _Hcam;
_camOffSet = [.12,0,.15];
_targOffset1 = [0,8,1];

_target = "Sign_Sphere10cm_F" createVehicleLocal position player;
hideObject _target; 

_target attachTo [_Hcam,_targOffset1];


_cam = "camera" camCreate getPosATL _Hcam;
_cam camPrepareFov 0.700;
_cam camPrepareTarget _target;
_cam camCommitPrepared 0;
_cam cameraEffect ["INTERNAL", "BACK", "rendertarget12"];

_cam attachTo [_Hcam,_camOffSet,"Head"];

player setVariable ["cTabHcams",[_cam,_target]];