/*
 	Name: cTab_fnc_drawMarkers
 	
 	Author(s):
		Gundy

 	Description:
		Draw map markers provided by allMapMarkers. 

	Parameters:
		0: OBJECT  - Map control to draw BFT icons on
 	
 	Returns:
		BOOLEAN - Always TRUE
 	
 	Example:
		[_ctrlScreen] call cTab_fnc_drawMarkers;
*/

private ["_ctrlScreen","_marker","_pos","_type","_size","_icon","_colorType","_color","_brush","_brushType","_shape","_alpha","_dir","_text"];

_ctrlScreen = _this select 0;
{
	
	_marker = _x;
	
	_pos = getMarkerPos _marker;
	_type = getMarkerType _marker;
	_size = getMarkerSize _marker;
	_icon = getText(configFile/"CfgMarkers"/_type/"Icon");
	_colorType = getMarkerColor _marker;  
	if (_icon != "" && {_colorType == "Default"}) then {
		_color = getArray(configFile/"CfgMarkers"/_type/"color");
	} else {
		_color = getArray(configFile/"CfgMarkerColors"/_colorType/"color");
	};
	if (typeName (_color select 0) == "STRING") then {
		_color = [
			call compile (_color select 0),
			call compile (_color select 1),
			call compile (_color select 2),
			call compile (_color select 3)
		];
	};
	_brushType = markerBrush _marker;
	_brush = getText(configFile/"CfgMarkerBrushes"/_brushType/"texture");
	_shape = markerShape _marker;
	_alpha = markerAlpha _marker;
	_dir = markerDir _marker;
	_text = markerText _marker;
	
	switch (_shape) do {
	    case "ICON": {
	    	_ctrlScreen drawIcon [_icon,_color,_pos,(_size select 0) * cTabIconSize,(_size select 1) * cTabIconSize,_dir,_text,0,cTabTxtSize,"TahomaB","right"];
	    };
	    case "RECTANGLE": {
	    	_ctrlScreen drawRectangle [_pos,_size select 0,_size select 1,_dir,_color,_brush];
		};
		case "ELLIPSE": {
	    	_ctrlScreen drawEllipse [_pos,_size select 0,_size select 1,_dir,_color,_brush];
		};
	};
} forEach allMapMarkers;

true