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

private ["_ctrlScreen","_obj","_text"];

_ctrlScreen = _this select 0;

{
	_text = if (cTabBFTtxt) then {_x select 4} else {""};
	_obj = _x select 0;
	_ctrlScreen drawIcon [_x select 1,cTabColorBlue,getPosASL _obj,cTabIconManSize,cTabIconManSize,direction _obj,_text,0,cTabTxtSize,"TahomaB"];
} count cTabBFTmembers;

true