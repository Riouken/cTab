// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

//prep the arrays that will hold ctab data
cTabBFTlist = [];
cTabHcamlist = [];

if (isnil ("cTabSide")) then {cTabSide = west;}; 


// fnc to check players gear for ctab.
cTabCheckGear = {
		
		_unit = _this select 0;
		_return = false;
		_chk_items = (items _unit);
		_chk_asgnItems = (assignedItems _unit);
	
		_chk_all_items = _chk_items + _chk_asgnItems;
		
		if (("ItemcTab" in _chk_all_items)) then
		{
			_return = true;
		} else
		{
			_return = false;
		};
		
		if (("ItemAndroid" in _chk_all_items)) then
		{
			_return = true;
		};

		
_return;
};

// fnc to check if unit has helmet cam.
hCamCheckGear = {
		
		_unit = _this select 0;
		_return = false;
		_chk_items = (items _unit);
		_chk_asgnItems = (assignedItems _unit);
	
		_chk_all_items = _chk_items + _chk_asgnItems;
		
		if (("ItemcTabHCam" in _chk_all_items)) then
		{
			_return = true;
		} else
		{
			_return = false;
		};
		
_return;
};


// Main loop to manage lists of people and veh that are shown in FBCB2
[] spawn {

	waituntil {time > 0};
	sleep .1;
	
	while {true} do 
	{
		cTabBFTlist = [];
		cTabHcamlist = [];
		
		{
			
			if (side _x == cTabSide) then
			{
				_gearTestTab = [_x] call cTabCheckGear;
				_gearTestHcam = [_x] call hCamCheckGear;
				if (_gearTestTab) then
				{
					_name = groupID (group _x);
					_tmpArray = [_x,"\A3\ui_f\data\map\markers\nato\b_inf.paa",_name];
					cTabBFTlist set [count cTabBFTlist,_tmpArray];
				};
				
				if (_gearTestHcam) then
				{
					cTabHcamlist set [count cTabHcamlist,_x];
				};
			};
			
		} forEach allUnits;
		
		
		{
			if ((count (crew _x) > 0) && (side _x == cTabSide)) then
			{
				_name = groupID (group _x);
				_txture = "\A3\ui_f\data\map\markers\nato\b_unknown.paa";
				
				call {
					if (_x isKindOf "Car_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_motor_inf.paa";};
					if (_x isKindOf "Wheeled_APC_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
					if (_x isKindOf "Truck_F") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_service.paa";};
					if (_x isKindOf "Helicopter") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_air.paa";};
					if (_x isKindOf "Plane") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_plane.paa";};
					if (_x isKindOf "Tank") exitWith {_txture = "\A3\ui_f\data\map\markers\nato\b_armor.paa";};
				};
				
				_tmpArray = [_x,_txture,_name];
				cTabBFTlist set [count cTabBFTlist,_tmpArray];
			};
			
		} forEach vehicles;
		


		publicVariable "cTabBFTlist";
		publicVariable "cTabHcamlist";
		sleep 20;
	};
		
	
	
	


};


	
	
	
	
	