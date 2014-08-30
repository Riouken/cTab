// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

cTab_open_android_msg = {
	
	closedialog 0;
	waitUntil {!dialog};
	
	createDialog "cTab_Android_msg_dlg";
	waitUntil {dialog};
	_this + [177481,nil] call cTab_fnc_onIfOpen;
};

cTab_android_msg_onload = {
	disableSerialization;
	_display = (uiNamespace getVariable "cTab_Android_dlg");
	ctrlShow [23012, false];
	ctrlShow [3357, false];

};

cTab_android_msg_swi_scrn = {

	_screen = _this select 0;
	
	switch (_screen) do
	{
		case 1:
		{
			disableSerialization;
			_display = (uiNamespace getVariable "cTab_Android_dlg");
			ctrlShow [23001, false];
			ctrlShow [23012, true];
		};

		case 2:
		{
			disableSerialization;
			_display = (uiNamespace getVariable "cTab_Android_dlg");
			ctrlShow [23012, false];
			ctrlShow [23001, true];
		};

	};
	
};

cTab_android_msg_gui_load = 
{
	disableSerialization;
	_return = true;
	_display = (uiNamespace getVariable "cTab_Android_msg_dlg");
	_msgarry = player getVariable ["ctab_messages",[]];
	_msgControl = _display displayCtrl 1500;
	_plrlistControl = _display displayCtrl 1501;
	lbClear 1500;
	lbClear 1501;
	_plrList = playableUnits;
	
	if (count _plrList < 1) then { _plrList = switchableUnits;};
	
	uiNamespace setVariable ['cTab_msg_playerList', _plrList];
	// Messages
	if ((count _msgarry) > 0) then 
	{
		{		
			_title =  _x select 0;
			_msgIsRead = _x select 2;
			_img = "";
			if (_msgIsRead) then 
			{
				_img = "\cTab\img\icoOpenmail.paa";
			}
			else
			{
				_img = "\cTab\img\icoUnopenedmail.paa";
			};
		
			_index = _msgControl lbAdd _title;
			_index = _msgControl lbSetPicture [_forEachIndex,_img];
		
		} forEach _msgarry;
	};
	
	{
		_index = _plrlistControl lbAdd name _x;
		if (!([_x] call cTabCheckGear)) then { _plrlistControl lbSetColor [_forEachIndex, [1,0,0,1]];};
		
	} forEach _plrList;
	
	367 cutText ["", "PLAIN"];
	_return;
};

cTab_msg_get_android_mailTxt = 
{
	disableSerialization;
	_return = true;
	_index = _this select 1;
	_display = (uiNamespace getVariable "cTab_Android_msg_dlg");
	_msgArray = player getVariable ["ctab_messages",[]];
	_msgName = (_msgArray select _index) select 0;
	_msgtxt = (_msgArray select _index) select 1;
	_msgArray set [_index,[_msgName,_msgtxt,true]];
	   
	player setVariable ["ctab_messages",_msgArray];
	
	_nop = [] call cTab_msg_gui_load;
	
	_txtControl = _display displayCtrl 1100;

	_nul = _txtControl ctrlSetText  _msgtxt;
	
	_return;
};

cTab_android_msg_Send = 
{
	disableSerialization;
	_return = true;
	_display = (uiNamespace getVariable "cTab_Android_msg_dlg");
	_plrLBctrl = _display displayCtrl 1501;
	_msgBodyctrl = _display displayCtrl 1402;
	_plrList = (uiNamespace getVariable "cTab_msg_playerList");
	
	_indices = lbSelection _plrLBctrl;
	_hr = date select 3;
	_min = date select 4;
	_msgTitle = str _hr + ":"+ str _min + " - " + name player;
	_msgBody = ctrlText _msgBodyctrl;
	
	{
		_recip = _plrList select _x;
		
		["cTab_msg_receive", [_recip,_msgTitle,_msgBody]] call CBA_fnc_whereLocalEvent;
		
	} forEach _indices;
	
	_nop = ["cTabMsgSent",[]] call bis_fnc_showNotification;
	_return;
};


