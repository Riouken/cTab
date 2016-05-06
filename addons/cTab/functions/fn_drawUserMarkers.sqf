/*
	Name: cTab_fnc_drawUserMarkers
	
	Author(s):
		Gundy, Riouken

	Description:
		Draw userMarkers held in cTabUserMarkerList to map control
		
		List format:
			Index 0: ARRAY  - marker position
			Index 1: STRING - path to marker icon
			Index 2: STRING - path to marker size icon
			Index 3: STRING - direction of reported movement
			Index 4: ARRAY  - marker color
			Index 5: STRING - marker time
			Index 6: STRING - text alignment
	
	Parameters:
		0: OBJECT  - Map control to draw BFT icons on
		1: BOOLEAN - Highlight marker under cursor
	
	Returns:
		BOOLEAN - Always TRUE
	
	Example:
		[_ctrlScreen] call cTab_fnc_drawUserMarkers;
*/

private ["_ctrlScreen","_arrowLength","_pos","_secondPos","_texture1","_texture2","_dir","_color","_text","_align","_cursorMarkerIndex","_markerData"];

_ctrlScreen = _this select 0;
_arrowLength = cTabUserMarkerArrowSize * ctrlMapScale _ctrlScreen;
_cursorMarkerIndex = if (_this select 1) then {[_ctrlScreen,cTabMapCursorPos] call cTab_fnc_findUserMarker} else {-1};
{
	_markerData = _x select 1;
	_pos = _markerData select 0;
	_texture1 = _markerData select 1;
	_texture2 = _markerData select 2;
	_dir = _markerData select 3;
	_color = if (_x select 0 != _cursorMarkerIndex) then {_markerData select 4} else {cTabTADhighlightColour};
	_text = "";
	if (_dir < 360) then {
		_secondPos = [_pos,_arrowLength,_dir] call BIS_fnc_relPos;
		_ctrlScreen drawArrow [_pos, _secondPos, _color];
	};
	if (cTabBFTtxt) then {_text = _markerData select 5;};
	_ctrlScreen drawIcon [_texture1,_color,_pos, cTabIconSize, cTabIconSize, 0, _text, 0, cTabTxtSize,"TahomaB",_markerData select 6];
	if (_texture2 != "") then {
		_ctrlScreen drawIcon [_texture2,_color,_pos, cTabGroupOverlayIconSize, cTabGroupOverlayIconSize, 0, "", 0, cTabTxtSize,"TahomaB","right"];
	};
} count cTabUserMarkerList;

true