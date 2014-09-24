/*
 	Name: cTab_fnc_drawUserMarkers
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Draw userMarkers held in cTabUserIconList to map control
		
		List format:
			Index 0: Position
			Index 1: Icon
			Index 2: Group size icon
			Index 3: Direction
			Index 4: Color

	
	Parameters:
		0: OBJECT  - Map control to draw BFT icons on
		1: BOOLEAN - Highlight marker under cursor
 	
 	Returns:
		BOOLEAN - Always TRUE
 	
 	Example:
		[_ctrlScreen] call cTab_fnc_drawUserMarkers;
*/

private ["_ctrlScreen","_arrowLength","_pos","_secondPos","_texture1","_texture2","_dir","_color","_text","_align","_cursorMarkerIndex"];

_ctrlScreen = _this select 0;
_arrowLength = cTabUserMarkerArrowSize * ctrlMapScale _ctrlScreen;
_cursorMarkerIndex = if (_this select 1) then {[_ctrlScreen,cTabMapCursorPos] call cTab_fnc_findUserMarker} else {-1};
{
	_pos = _x select 0;
	_texture1 = _x select 1;
	_texture2 = _x select 2;
	_dir = _x select 3;
	_color = if (_forEachIndex != _cursorMarkerIndex) then {_x select 4} else {cTabTADhighlightColour};
	_text = "";
	_align = "right";
	if ((_dir > 0) && (_dir < 180)) then {_align = "left"};
	if (_dir < 360) then {
		_secondPos = [_pos,_arrowLength,_dir] call BIS_fnc_relPos;
		_ctrlScreen drawArrow [_pos, _secondPos, _color];
	};
	if (cTabBFTtxt) then {_text = _x select 5;};
	_ctrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB",_align];
	if (_texture2 != "") then {
		_ctrlScreen drawIcon [_texture2,_color,_pos, cTabGroupOverlayIconSize, cTabGroupOverlayIconSize, 0, "", 0, cTabTxtSize,"TahomaB"];
	};
} forEach cTabUserIconList;

true