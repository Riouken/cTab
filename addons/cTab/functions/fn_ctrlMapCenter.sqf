/*
 	Name: cTab_fnc_ctrlMapCenter
 	
 	Author(s):
		Gundy

 	Description:
		Determine map center position of given map control
	
	Parameters:
		0: OBJECT  - Map control to return map center coordinates for
 	
 	Returns:
		ARRAY - 2D world coordinates of map control center 
 	
 	Example:
		[_ctrlScreen] call cTab_fnc_ctrlMapCenter;
*/

private ["_ctrlScreen","_ctrlPos","_ctrlPosCenter"];

_ctrlScreen = _this select 0;
_ctrlPos = ctrlPosition _ctrlScreen;
_ctrlPosCenter = [(_ctrlPos select 0) + ((_ctrlPos select 2) / 2),(_ctrlPos select 1) + ((_ctrlPos select 3) / 2)];

_ctrlScreen ctrlMapScreenToWorld _ctrlPosCenter