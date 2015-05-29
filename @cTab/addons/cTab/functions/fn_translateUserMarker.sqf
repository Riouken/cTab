/*
	Name: cTab_fnc_translateUserMarker
	
	Author(s):
		Gundy

	Description:
		Take the condensed user marker data and translate it so that it can be drawn much quicker
		
		Received marker data format:
			Index 0: ARRAY   - 2D marker position
			Index 1: INTEGER - number of icon
			Index 2: INTEGER - size type
			Index 3: INTEGER - octant of reported movement
			Index 4: STRING  - marker time
			Index 5: OBJECT  - marker creator
			
		Translated marker data format:
			Index 0: ARRAY  - marker position
			Index 1: STRING - path to marker icon
			Index 2: STRING - path to marker size icon
			Index 3: STRING - direction of reported movement
			Index 4: ARRAY  - marker color
			Index 5: STRING - marker time
			Index 6: STRING - text alignment
	
	Parameters:
		0: ARRAY - Marker data
	
	Returns:
		ARRAY - Translated marker data
	
	Example:
		[[1714.35,5716.82],0,0,0,"12:00"] call cTab_fnc_translateUserMarker;
*/

private ["_pos","_markerIcon","_texture1","_markerSize","_texture2","_markerDir","_dir","_text","_align"];

_pos = _this select 0;

_color = cTabColorRed;
_markerIcon = _this select 1;
_texture1 = call {
	if (_markerIcon == 0) exitWith {"\A3\ui_f\data\map\markers\nato\o_inf.paa"};
	if (_markerIcon == 1) exitWith {"\A3\ui_f\data\map\markers\nato\o_mech_inf.paa"};
	if (_markerIcon == 2) exitWith {"\A3\ui_f\data\map\markers\nato\o_motor_inf.paa"};
	if (_markerIcon == 3) exitWith {"\A3\ui_f\data\map\markers\nato\o_armor.paa"};
	if (_markerIcon == 4) exitWith {"\A3\ui_f\data\map\markers\nato\o_air.paa";};
	if (_markerIcon == 5) exitWith {"\A3\ui_f\data\map\markers\nato\o_plane.paa"};
	if (_markerIcon == 6) exitWith {"\A3\ui_f\data\map\markers\nato\o_unknown.paa"};
	if (_markerIcon == 7) exitWith {"\cTab\img\o_inf_rifle.paa"};
	if (_markerIcon == 8) exitWith {"\cTab\img\o_inf_mg.paa"};
	if (_markerIcon == 9) exitWith {"\cTab\img\o_inf_at.paa"};
	if (_markerIcon == 10) exitWith {"\cTab\img\o_inf_mmg.paa"};
	if (_markerIcon == 11) exitWith {"\cTab\img\o_inf_mat.paa"};
	if (_markerIcon == 12) exitWith {"\cTab\img\o_inf_mmortar.paa"};
	if (_markerIcon == 13) exitWith {"\cTab\img\o_inf_aa.paa"};
	_color = cTabColorGreen;
	if (_markerIcon == 20) exitWith {"\A3\ui_f\data\map\markers\military\join_CA.paa"};
	if (_markerIcon == 21) exitWith {"\A3\ui_f\data\map\markers\military\circle_CA.paa"};
	if (_markerIcon == 22) exitWith {"\A3\ui_f\data\map\mapcontrol\Hospital_CA.paa"};
	if (_markerIcon == 23) exitWith {"\A3\ui_f\data\map\markers\military\warning_CA.paa"};
	_color = cTabColorBlue;
	if (_markerIcon == 30) exitWith {"\A3\ui_f\data\map\markers\nato\b_hq.paa"};
	if (_markerIcon == 31) exitWith {"\A3\ui_f\data\map\markers\military\end_CA.paa"};
	""
};

_markerSize = _this select 2;
_texture2 = call {
	if (_markerSize == 0) exitWith {""};
	if (_markerSize == 1) exitWith {"\A3\ui_f\data\map\markers\nato\group_0.paa"};
	if (_markerSize == 2) exitWith {"\A3\ui_f\data\map\markers\nato\group_1.paa"};
	if (_markerSize == 3) exitWith {"\A3\ui_f\data\map\markers\nato\group_2.paa"};
	if (_markerSize == 4) exitWith {"\A3\ui_f\data\map\markers\nato\group_3.paa"};
	""
};

_markerDir = _this select 3;
_dir = call {
	if (_markerDir == 0) exitWith {400};
	if (_markerDir == 1) exitWith {0};
	if (_markerDir == 2) exitWith {45};
	if (_markerDir == 3) exitWith {90};
	if (_markerDir == 4) exitWith {135};
	if (_markerDir == 5) exitWith {180};
	if (_markerDir == 6) exitWith {225};
	if (_markerDir == 7) exitWith {270};
	if (_markerDir == 8) exitWith {315};
	700
};

_text = _this select 4;
_align = if ((_dir > 0) && (_dir < 180)) then {"left"} else {"right"};

[_pos,_texture1,_texture2,_dir,_color,_text,_align]