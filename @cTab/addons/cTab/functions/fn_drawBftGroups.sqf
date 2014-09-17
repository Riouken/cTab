/*
 	Name: cTab_fnc_drawBftGroups
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Draw items contained in cTabBFTgroups to map control
		
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
		[_ctrlScreen] call cTab_fnc_drawBftGroups;
*/

private ["_ctrlScreen","_text","_pos"];

_ctrlScreen = _this select 0;

{
	_text = if (cTabBFTtxt) then {_x select 3} else {""};
	_pos = getPosASL (_x select 0);
	_ctrlScreen drawIcon [_x select 1,cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,_text,0,cTabTxtSize,"TahomaB"];
	_ctrlScreen drawIcon [_x select 2,cTabColorBlue,_pos,cTabGroupOverlayIconSize,cTabGroupOverlayIconSize,0,"",0,cTabTxtSize,"TahomaB"];
} count cTabBFTgroups;

true