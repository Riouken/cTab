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

private ["_ctrlScreen","_obj","_pos"];

_ctrlScreen = _this select 0;

{
	_obj = _x select 0;
	_pos = getPosASL _obj;
	_ctrlScreen drawIcon [_x select 1,cTabColorBlue,_pos,cTabIconManSize,cTabIconManSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
	if (cTabBFTtxt) then {
		_ctrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabColorBlue,_pos,cTabIconManSize,cTabIconManSize,0,_x select 4,0,cTabTxtSize,"TahomaB"];
	};
} count cTabBFTmembers;

true