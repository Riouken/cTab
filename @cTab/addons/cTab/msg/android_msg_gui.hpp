// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.




#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.025)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)



class cTab_Android_msg_dlg {
	idd = 177481;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_Android_msg_dlg', (_this select 0)];call cTab_android_msg_onload;nop = [] call cTab_android_msg_gui_load;";
	onUnload = "uiNamespace setVariable ['cTab_Android_msg_dlg', displayNull];call cTab_fnc_close;";
	objects[] = {};
	class controlsBackground {

			class androidBG: cTab_RscPicture
			{
				idc = 1200;
				moving = 1;
				text = "\cTab\img\15th_android_2.paa";
				x = -17 * GUI_GRID_W + GUI_GRID_X;
				y = 6 * GUI_GRID_H + GUI_GRID_Y;
				w = 41.5 * GUI_GRID_W;
				h = 33 * GUI_GRID_H;
			};
			
			/*
			class bftscreen: cTab_RscMapControl
			{
				idc = 17354;
				text = "#(argb,8,8,3)color(1,1,1,1)";
				x = -7.5 * GUI_GRID_W + GUI_GRID_X;
				y = 16 * GUI_GRID_H + GUI_GRID_Y;
				w = 21 * GUI_GRID_W;
				h = 11 * GUI_GRID_H;
				onDraw = "nop = [] call cTabOnDrawbftAndroid;";
				onMouseButtonDblClick = "_ok = ['cTab_Android_msg_dlg',3300,17354,_this] execVM 'cTab\bft\userload.sqf';";
				onMouseButtonDown = "_ok = ['cTab_Android_msg_dlg',3300,17354,_this] spawn cTabDeleteUsrMkr;";
			};
			*/
			
			
	};
	
	class controls {
	
	
			class menueBack: cTab_RscButtonInv
			{
				idc = 2400;
				x = 15.4 * GUI_GRID_W + GUI_GRID_X;
				y = 17.62 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
				tooltip = "Delete last user placed icon";
			};
			class menueMain: cTab_RscButtonInv
			{
				idc = 2401;
				x = 15.48 * GUI_GRID_W + GUI_GRID_X;
				y = 20.67 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				tooltip = "Main Menu ** Coming Soon";
			};
			class menueSub: cTab_RscButtonInv
			{
				idc = 2402;
				x = 15.56 * GUI_GRID_W + GUI_GRID_X;
				y = 23.71 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "ctrlShow [3357, True];";
				tooltip = "Main Options";
			};
			
			// Main Menue
			
			class MainOptMenu: cTab_RscControlsGroup
			{
				idc = 3357;
				x = 5 * GUI_GRID_W + GUI_GRID_X;
				y = 19 * GUI_GRID_H + GUI_GRID_Y;
				w = 8 * GUI_GRID_W;
				h = 7.5 * GUI_GRID_H;
				class controls
				{
					class mainbg: cTab_IGUIBack
					{
						idc = 187452;
						x = 0;
						y = 0;
						w = 7.3 * GUI_GRID_W;
						h = 3 * GUI_GRID_H;
					};

					class mainMenBFT: cTab_RscText
					{
						idc = 123647;
						text = "FBCB2"; //--- ToDo: Localize;
						x = 0;
						y = (1.5 * GUI_GRID_H) * 4;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
					};						
					class BtnTxtOnOff: cTab_ActiveText
					{
						idc = 23478;
						text = "GoTo>>"; //--- ToDo: Localize;
						x = (3 * GUI_GRID_W) * 1.5;
						y = (1.5 * GUI_GRID_H) * .1;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "";
					};				
		
				};
			};

			
			// Msg gui elements 
			class inbox_Container: cTab_RscControlsGroup
			{
				idc = 23001;
				x = -7.5 * GUI_GRID_W + GUI_GRID_X;
				y = 16 * GUI_GRID_H + GUI_GRID_Y;
				w = 21 * GUI_GRID_W;
				h = 11.5 * GUI_GRID_H;
				colorText[] = {1,1,1,1};
				colorBackground[] = {1,-1,-1,1};
				class controls
				{
					class inbox_frame2: cTab_RscFrame
					{
						idc = 1801;
						text = "Message Text"; //--- ToDo: Localize;
						x = 8.5 * GUI_GRID_W;
						y = 1.5 * GUI_GRID_H;
						w = 11.3413 * GUI_GRID_W;
						h = 9.60979 * GUI_GRID_H;
					};
					class in_box_frame1: cTab_RscFrame
					{
						idc = 1800;
						text = "My Messages"; //--- ToDo: Localize;
						x = 0.38 * GUI_GRID_W;
						y = 0.17 * GUI_GRID_H;
						w = 7.84921 * GUI_GRID_W;
						h = 10.9325 * GUI_GRID_H;
					};
					class inbox_dlt_btn: cTab_RscButton
					{
						idc = 1601;
						text = "Delete Msgs"; //--- ToDo: Localize;
						x = 8.55 * GUI_GRID_W;
						y = 0.5 * GUI_GRID_H;
						w = 5 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .75 * GUI_GRID_H;
						action = "player setVariable ['ctab_messages',[]];_nop = [] call cTab_android_msg_gui_load;";
					};
					class inbox_compose_btn: cTab_RscButton
					{
						idc = 1600;
						text = "Compose >>"; //--- ToDo: Localize;
						x = 14.82 * GUI_GRID_W;
						y = 0.53 * GUI_GRID_H;
						w = 5 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .75 * GUI_GRID_H;
						action = "nop = [1] call cTab_android_msg_swi_scrn;";
					};
					class inbox_list: cTab_RscListbox
					{
						idc = 1500;
						x = 0.61 * GUI_GRID_W;
						y = 0.7 * GUI_GRID_H;
						w = 7.38095 * GUI_GRID_W;
						h = 10.1243 * GUI_GRID_H;
						onLBSelChanged = "_this call cTab_msg_get_android_mailTxt;";
					};
					class inbox_msg: cTab_RscStructuredText
					{
						idc = 1100;
						x = 8.82 * GUI_GRID_W;
						y = 1.98 * GUI_GRID_H;
						w = 10.6666 * GUI_GRID_W;
						h = 8.9008 * GUI_GRID_H;
						
					};
				};
			};
			class compose_container: cTab_RscControlsGroup
			{
				idc = 23012;
				x = -7.5 * GUI_GRID_W + GUI_GRID_X;
				y = 16 * GUI_GRID_H + GUI_GRID_Y;
				w = 20 * GUI_GRID_W;
				h = 11 * GUI_GRID_H;
				colorText[] = {1,1,1,1};
				colorBackground[] = {1,-1,-1,1};
				class controls
				{
					class compose_frame1: cTab_RscFrame
					{
						idc = 1802;
						text = "Players"; //--- ToDo: Localize;
						x = 0.22 * GUI_GRID_W;
						y = 0.01 * GUI_GRID_H;
						w = 7.96824 * GUI_GRID_W;
						h = 10.7672 * GUI_GRID_H;
					};
					class RscFrame_1803: cTab_RscFrame
					{
						idc = 1803;
						text = "Players"; //--- ToDo: Localize;
						x = 8.45 * GUI_GRID_W;
						y = 1.74 * GUI_GRID_H;
						w = 11.2222 * GUI_GRID_W;
						h = 9.01454 * GUI_GRID_H;
					};
					class compose_inbox_btn: cTab_RscButton
					{
						idc = 1602;
						text = "<< Inbox"; //--- ToDo: Localize;
						x = 8.56 * GUI_GRID_W;
						y = 0.4 * GUI_GRID_H;
						w = 5 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .75 * GUI_GRID_H;
						action = "nop = [2] call cTab_android_msg_swi_scrn;";
					};
					class compose_send_btn: cTab_RscButton
					{
						idc = 1603;
						text = "Send Msg"; //--- ToDo: Localize;
						x = 14.44 * GUI_GRID_W;
						y = 0.4 * GUI_GRID_H;
						w = 5 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .75 * GUI_GRID_H;
						action = "call cTab_android_msg_Send;";
					};

					class compose_edit_box: cTab_RscEdit
					{
						idc = 1402;
						htmlControl = true;
						style = ST_MULTI;
						x = 8.7 * GUI_GRID_W;
						y = 2.24 * GUI_GRID_H;
						w = 10.7857 * GUI_GRID_W;
						h = 8.38624 * GUI_GRID_H;
					};
					class RscListbox_1501: cTab_RscListbox
					{
						idc = 1501;
						x = 0.63 * GUI_GRID_W;
						y = 0.57 * GUI_GRID_H;
						w = 7.1746 * GUI_GRID_W;
						h = 9.97354 * GUI_GRID_H;
					};
				};
			};

		
			
	};
	
};			