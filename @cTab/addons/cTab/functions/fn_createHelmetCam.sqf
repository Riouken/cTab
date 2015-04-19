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

/*call {
	// should unit not be in a vehicle
	if (vehicle _newHost isKindOf "CAManBase") exitWith {
		_camOffSet = [0.12,0,0.15];
		_targetOffSet = [0,8,1];
	};
	// if unit is in a vehilce, see if 3rd person view is allowed
	if (difficultyEnabled "3rdPersonView") exitWith {
		_newHost = vehicle _newHost;
		// Might want to calculate offsets based on the actual vehicle dimensions in the future
		_camOffSet = [0,-8,4];
		_targetOffSet = [0,8,2];
	};
	// if unit is in a vehicle and 3rd person view is not allowed
	_newHost = objNull;
};*/

// if there is no valid unit or we are not allowed to set up a helmet cam in these conditions, drop out of full screen view
if (IsNull _newHost) exitWith {
	["cTab_Tablet_dlg",[["mode","HCAM"]]] call cTab_fnc_setSettings;
	false
};

// if there is already a camera, see if its the same one we are about to set up
// if true, render to given target (in case the target has changed), else delete the camera so we can create a new one
if (!isNil "cTabHcams") then {
	_oldCam = cTabHcams select 0;
	_oldHost = cTabHcams select 3;
	if (_oldHost isEqualTo _newHost) then {
		_oldCam cameraEffect ["INTERNAL","BACK",_renderTarget];
	} else {
		_nop = [] call cTab_fnc_deleteHelmetCam;
		waitUntil {_nop};
	};
};

// only continue if there is no helmet cam currently set up
if (!isNil "cTabHcams") exitWith {true};

/*_target = "Sign_Sphere10cm_F" createVehicleLocal position player;
hideObject _target;
_target attachTo [_newHost,_targetOffSet];

_cam = "camera" camCreate getPosATL _newHost;
_cam camPrepareFov 0.700;
_cam camPrepareTarget _target;
_cam camCommitPrepared 0;
if (vehicle _newHost == _newHost) then {
	_cam attachTo [_newHost,_camOffSet,"Head"];
} else {
	_cam attachTo [_newHost,_camOffSet];
};
_cam cameraEffect ["INTERNAL","BACK",_renderTarget];

cTabHcams = [_cam,_target,_newHost];*/

// cam init
_cameraTarget = "Sign_Sphere10cm_F" createVehicleLocal ((eyePos player) vectorAdd (eyeDirection player));
_leaningIndicator = "Sign_Sphere10cm_F" createVehicleLocal (getPos player);
hideObject _cameraTarget;
hideObject _leaningIndicator;

_camera = "camera" camCreate eyePos player;
_camera camSetFov 0.6;
_camera camSetTarget _cameraTarget;
_camera camCommit 0;

_renderTarget setPiPEffect [3, 1, 0.8, 1, 0.1, [0.3, 0.3, 0.3, -0.1], [1.0, 0.0, 1.0, 1.0], [0, 0, 0, 0]];

_camera cameraEffect ["INTERNAL", "BACK", _renderTarget];

//_screen setVariable ["AME_LiveFeed_Camera", _camera];
/*_screen setVariable ["AME_LiveFeed_CameraTarget", _cameraTarget];
_screen setVariable ["AME_LiveFeed_LeaningIndicator", _leaningIndicator];

_allScreens = player getVariable ["AME_LiveFeed_Screens", []];
_allScreens = _allScreens + [_screen];
player setVariable ["AME_LiveFeed_Screens", _allScreens];

waitUntil {!(_screen getVariable ["AME_LiveFeed_Running", false])}*/;

/*_allScreens = player getVariable "AME_LiveFeed_Screens";
_allScreens = _allScreens - [_screen];
player setVariable ["AME_LiveFeed_Screens", _allScreens];*/

cTabHcams = [_camera,_cameraTarget,_leaningIndicator,_newHost];

// Set up cam direction update event handler
if (isNil "cTabHcamEventHandle") then {
	cTabHcamEventHandle = addMissionEventHandler ["Draw3D", {
		if (!isNil "cTabHcams") then {
			_camera = cTabHcams select 0;
			_cameraTarget = cTabHcams select 1;
			_leaningIndicator = cTabHcams select 2;
			_viewablePlayer = cTabHcams select 3;

			_d = "_viewablePlayer: " + (name _viewablePlayer) + "\n";

			_inVehicle = vehicle _viewablePlayer != _viewablePlayer;
			_d = _d + "_inVehicle: " + (str _inVehicle) + "\n";

			_isDriver = if (_inVehicle) then {driver vehicle _viewablePlayer == _viewablePlayer} else {false};
			_d = _d + "_isDriver: " + (str _isDriver) + "\n";
			
			// todo: check what if unit is cargo, what does assignedVehicleRole return?
			_inTurret = if (_inVehicle) then {(count assignedVehicleRole _viewablePlayer) > 1} else {false};
			_d = _d + "_inTurret: " + (str _inTurret) + "\n";

			_allTurretConfigs = [];
			_turretConfig = if (_inTurret) then {
				// pretty sure this only returns a single turret, riht?
				_turretIndex = assignedVehicleRole _viewablePlayer select 1;
				_turretConfig = (configFile >> "CfgVehicles" >> typeOf (vehicle _viewablePlayer));
				// a) why are we looping through turret index
				// b) just selecting the turret index from _turretConfig is problematic, as not all turrets from the config are actually turrets that are counted, a check for class is reuired, see coPilot function
				{
					_turretConfig = (_turretConfig >> "Turrets") select _x;
					_allTurretConfigs pushBack _turretConfig;
				} forEach _turretIndex;
				_d = _d + "_turretConfig: " + (configName _turretConfig) + "\n";
				_turretConfig
			} else {objNull};

			_inGunTurret = if (_inTurret) then {getText (_turretConfig >> "body") != ""} else {false};
			_d = _d + "_inGunTurret: " + (str _inGunTurret) + "\n";

			_ownGunVisible = if (_inTurret) then {getNumber (_turretConfig >> "hideWeaponsGunner") == 0} else {true};
			_d = _d + "_ownGunVisible: " + (str _ownGunVisible) + "\n";

			_cameraAttachPoint = if (!_inVehicle) then {"eye"} else {
				if (_inGunTurret) then {
					getText (_turretConfig >> "memoryPointGunnerOptics")
				} else {
					if (_isDriver && getNumber (configFile >> "CfgVehicles" >> typeOf (vehicle _viewablePlayer) >> "driverForceOptics") == 1) then {
						getText (configFile >> "CfgVehicles" >> typeOf (vehicle _viewablePlayer) >> "memoryPointDriverOptics")
					} else {
						"eye"
					}
				}
			};
			_d = _d + "_cameraAttachPoint: " + (str _cameraAttachPoint) + "\n";

			_eyePos = if (surfaceIsWater [getPos _viewablePlayer select 0, getPos _viewablePlayer select 1]) then {eyePos _viewablePlayer} else {ASLToATL eyePos _viewablePlayer};
			_eyeAttachPoint = (vehicle _viewablePlayer) worldToModel _eyePos;
			_eyeDirection = ((vehicle _viewablePlayer) worldToModel (_eyePos vectorAdd eyeDirection _viewablePlayer)) vectorDiff _eyeAttachPoint;

			_aimingVector = if (!_inTurret) then {
				// todo: check if use of isTouchingGround is solid as it probablz won't return true if in water
				if (!_inVehicle && isTouchingGround _viewablePlayer) then {
					_leaningIndicator attachTo [_viewablePlayer, [0, 0, 0], "leaning_axis"];
					_leaningAxisAttachPoint = (getPos _leaningIndicator) vectorDiff (getPos _viewablePlayer);
					_frontLeaningVector = vectorNormalized (_eyeAttachPoint vectorDiff _leaningAxisAttachPoint) vectorCrossProduct [1, 1, 0];
					_sideLeaningVector = vectorNormalized (_eyeAttachPoint vectorDiff _leaningAxisAttachPoint) vectorCrossProduct [0, 0, 1];

					_frontLeaningAngle = (-1 * aCos (_frontLeaningVector select 1)) + ([31.5, 35, 70] select (["STAND", "CROUCH", "PRONE"] find stance _viewablePlayer));

					_a = _eyeDirection vectorMultiply (cos _frontLeaningAngle);
					_b = vectorNormalized _eyeDirection vectorCrossProduct [0, 0, 1];
					_c = _eyeDirection vectorMultiply (sin _frontLeaningAngle);
					_a vectorAdd (_b vectorCrossProduct _c)
				} else {
					_eyeDirection
				};
			} else {
				if (_inGunTurret) then {
					_turretBodyDir = 0;
					{
						_turretBodyAnimationName = getText (_x >> "animationSourceBody");
						_turretBodyDir = _turretBodyDir + (deg ((vehicle _viewablePlayer) animationPhase _turretBodyAnimationName));
					} forEach _allTurretConfigs;
					_turretBodyDir = _turretBodyDir + 90;

					_turretGunAnimationName = getText (_turretConfig >> "animationSourceGun");
					_turretGunDir = deg ((vehicle _viewablePlayer) animationPhase _turretGunAnimationName);

					[cos _turretBodyDir, sin _turretBodyDir, sin _turretGunDir];
				} else {
					if (_ownGunVisible) then {
						((vehicle _viewablePlayer) worldToModel (_eyePos vectorAdd (_viewablePlayer weaponDirection currentWeapon _viewablePlayer))) vectorDiff _eyeAttachPoint;
					} else {
						_eyeDirection;
					};
				};
			};

			if (_cameraAttachPoint == "eye") then {
				_camera attachTo [vehicle _viewablePlayer, _eyeAttachPoint];
				_cameraTarget attachTo [vehicle _viewablePlayer, _eyeAttachPoint vectorAdd _aimingVector];
			} else {
				_camera attachTo [vehicle _viewablePlayer, [0, 0, 0], _cameraAttachPoint];
				_cameraTarget attachTo [vehicle _viewablePlayer, _aimingVector, _cameraAttachPoint];
			};

			hint _d;
		};
	};
};

true