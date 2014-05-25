// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


_test = player getVariable ["cTabUAVcams",[]];

if (count _test != 0) then {

	_nop = [] call cTabUavDelCam;
	waitUntil {_nop};
};

_uav = allUnitsUav select (_this select 1);
cTabActUav = _uav;
_camOffSet = [0,0,-.5];
_targOffset1 = [];
_targOffset2 = [];
_uavClassname = typeOf _uav;

switch (_uavClassname) do
{
    case "B_UAV_01_F":
    {
		_camOffSet = [0,0,-.5];
		_targOffset1 = [0,5,-25];
		_targOffset2 = [0,25,-5];
    };

    case "B_UAV_02_CAS_F":
    {
		_camOffSet = [0,.50,-1.0];
		_targOffset1 = [0,5,-25];
		_targOffset2 = [0,25,-5];	
    };
	
	case "B_UAV_02_F":
    {
		_camOffSet = [0,.50,-1.0];
		_targOffset1 = [0,5,-25];
		_targOffset2 = [0,25,-5];			
    };

    case "B_UGV_01_F":
    {
		_camOffSet = [0,0,1];
		_targOffset1 = [0,25,0];
		_targOffset2 = [0,25,-1];	
    };
	
	case "B_UGV_01_rcws_F":
    {
		_camOffSet = [0,0,1];
		_targOffset1 = [0,25,0];
		_targOffset2 = [0,25,-1];	
    };
	
    default
    {
        _camOffSet = [0,0,-.5];
		_targOffset1 = [0,5,-25];
		_targOffset2 = [0,25,-5];		
    };
};

_target = "Sign_Sphere10cm_F" createVehicleLocal position player;
hideObject _target; 
_target2 = "Sign_Sphere10cm_F" createVehicleLocal position player;
hideObject _target2; 

_target attachTo [_uav,_targOffset1];
_target2 attachTo [_uav,_targOffset2];

_cam = "camera" camCreate getPosATL _uav;
_cam camPrepareFov 0.700;
_cam camPrepareTarget _target;
_cam camCommitPrepared 0;
_cam cameraEffect ["INTERNAL", "BACK", "rendertarget9"];

_cam attachTo [_uav,_camOffSet];

_cam2 = "camera" camCreate getPosATL _uav;
_cam2 camPrepareFov 0.700;
_cam2 camPrepareTarget _target2;
_cam2 camCommitPrepared 0;
_cam2 cameraEffect ["INTERNAL", "BACK", "rendertarget8"];

_cam2 attachTo [_uav,_camOffSet];


player setVariable ["cTabUAVcams",[_cam,_cam2,[_target,_target2]]];