/*
 	Name: cTab_fnc_findUserMarker
 	
 	Author(s):
		Gundy, Riouken

 	Description:
		Find user placed marker at provided position

	Parameters:
		0: OBJECT - Map control we took the position from
		1: ARRAY  - Position to look for marker
 	
 	Returns:
		INTEGER - Index of user marker, if not found -1
 	
 	Example:
		_markerIndex = [_ctrlScreen,[0,0]] call cTab_fnc_findUserMarker;
*/

private["_return","_searchPos","_targetRadius","_maxDistance","_distance"];

_return = -1;
_searchPos = _this select 1;

// figure out radius around cursor box based on map zoom and scale
_targetRadius = cTabIconSize * 2 * (ctrlMapScale (_this select 0)) * cTabMapScaleFactor;
_maxDistance = _searchPos distanceSqr [(_searchPos select 0) + _targetRadius,(_searchPos select 1) + _targetRadius];

// find closest user marker within _maxDistance
{
	_distance = _searchPos distanceSqr (_x select 1 select 0);
	if (_distance <= _maxDistance) then {
		_maxDistance = _distance;
		_return = _x select 0;
	};
} count cTabUserMarkerList;

_return