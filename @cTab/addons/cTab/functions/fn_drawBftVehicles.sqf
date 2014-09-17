/*
 	Name: cTab_fnc_drawBftVehicles
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Draw items contained in cTabBFTvehicles to map control
		
		List format:
			Index 0: Unit object
			Index 1: Path to icon A
			Index 2: Path to icon B (either group size or wingmen)
			Index 3: Text to display
			Index 4: String of group index

	
	Parameters:
		0: OBJECT - Map control to draw BFT icons on
		1: BOOLEAN - Mode, FALSE = Ground, TRUE = Air (for TAD)
 	
 	Returns:
		BOOLEAN - Always TRUE
 	
 	Example:
		[_ctrlScreen] call cTab_fnc_drawBftVehicles;
*/

private ["_ctrlScreen","_modeTAD","_obj","_iconB","_text","_groupID","_pos"];

_ctrlScreen = _this select 0;
_modeTAD = _this select 1;

{
	_obj = _x select 0;
	_iconB = _x select 2;
	_text = if (cTabBFTtxt) then {_x select 3} else {""};
	_groupID = _x select 4;
	_pos = getPosASL _obj;
	
	if (_modeTAD && {_iconB != ""}) then {
		// draw air contact icon and dummy icon for the text to have a better alignment
		if (_groupID != "") then {
			_ctrlScreen drawIcon [_iconB,cTabTADgroupColour,_pos,cTabAirContactSize,cTabAirContactSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
			_ctrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabTADgroupColour,_pos,0,0,0,_groupID,0,cTabAirContactGroupTxtSize * 0.8,"TahomaB","center"];
		} else {
			_ctrlScreen drawIcon [_iconB,cTabTADfontColour,_pos,cTabAirContactSize,cTabAirContactSize,direction _obj,"",0,cTabTxtSize,"TahomaB"];
			_ctrlScreen drawIcon ["\A3\ui_f\data\map\Markers\System\dummy_ca.paa",cTabTADfontColour,_pos,cTabAirContactDummySize,cTabAirContactDummySize,0,_text,0,cTabTxtSize,"TahomaB"];
		};
	} else {
		_ctrlScreen drawIcon [_x select 1,cTabColorBlue,_pos,cTabIconSize,cTabIconSize,0,_text,0,cTabTxtSize,"TahomaB"];
	};
} count cTabBFTvehicles;

true