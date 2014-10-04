/*
 	Name: cTab_fnc_drawBftMembers
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Draw items contained in cTabBFTmembers to map control
		
		List format:
			Index 0: Unit object
			Index 1: Path to icon A
			Index 2: Path to icon B (either group size or wingmen)
			Index 3: Text to display
			Index 4: String of group index
	
	Parameters:
		0: OBJECT - Map control to draw BFT icons on
 	
 	Returns:
		BOOLEAN - Always TRUE
 	
 	Example:
		[_ctrlScreen] call cTab_fnc_drawBftMembers;
*/

private ["_ctrlScreen","_obj","_pos","_veh","_vehicles","_vehicleIndex"];

_ctrlScreen = _this select 0;
_vehicles = [];

{
	_obj = _x select 0;
	_veh = vehicle _obj;
	
	call {
		if !(_veh isEqualTo _obj) exitWith {
			_vehicleIndex = _vehicles find _veh;
			if (_vehicleIndex != -1) then {
				_vehicles set [_vehicleIndex + 1,(_vehicles select (_vehicleIndex + 1)) + "/" + (_x select 4)];
			} else {
				_vehicles pushBack _veh;
				_vehicles pushBack (_x select 4);
			};
		};
		_pos = getPosASL _veh;
		_ctrlScreen drawIcon [_x select 1,cTabColorBlue,_pos,cTabIconManSize,cTabIconManSize,direction _veh,"",0,cTabTxtSize,"TahomaB"];
		if (cTabBFTtxt) then {
			_ctrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabColorBlue,_pos,cTabIconManSize,cTabIconManSize,0,_x select 4,0,cTabTxtSize,"TahomaB"];
		};
	};
} count cTabBFTmembers;

if !(_vehicles isEqualTo []) then {
	for "_i" from 0 to (count _vehicles - 2) step 2 do {
		_veh = _vehicles select _i;
		_pos = getPosASL _veh;
		if (_veh != vehicle player) then {
			_ctrlScreen drawIcon ["\A3\ui_f\data\map\VehicleIcons\iconmanvirtual_ca.paa",cTabColorBlue,_pos,cTabIconSize,cTabIconSize,direction _veh,"",0,cTabTxtSize,"TahomaB"];
		};
		if (cTabBFTtxt) then {
			_ctrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,_vehicles select (_i + 1),0,cTabTxtSize,"TahomaB","left"];
		};
	} count _vehicles;
};	

true