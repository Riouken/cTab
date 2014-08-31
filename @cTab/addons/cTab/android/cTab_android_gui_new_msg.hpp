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

			class background: cTab_RscPicture
			{
				idc = 1200;
				text = "\cTab\img\itemAndroid_display.paa";
				x = -1.5 * GUI_GRID_W + GUI_GRID_X;
				y = 1 * GUI_GRID_H + GUI_GRID_Y;
				w = 44 * GUI_GRID_W;
				h = 35 * GUI_GRID_H;
			};
			class screen: cTab_RscPicture
			{
				idc = 1201;
				text = "#(argb,8,8,3)color(1,1,1,1)";
				x = 8.06 * GUI_GRID_W + GUI_GRID_X;
				y = 13.17 * GUI_GRID_H + GUI_GRID_Y;
				w = 23.0714 * GUI_GRID_W;
				h = 10.8386 * GUI_GRID_H;
				colorText[] = {-1,-1,-1,0};
				colorBackground[] = {-1,-1,-1,0};
				colorActive[] = {-1,-1,-1,0};
			};
			class btnBack: cTab_RscButton
			{
				idc = 1600;
				x = 33.18 * GUI_GRID_W + GUI_GRID_X;
				y = 14.9 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnHome: cTab_RscButton
			{
				idc = 1601;
				x = 33.26 * GUI_GRID_W + GUI_GRID_X;
				y = 17.77 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnMenu: cTab_RscButton
			{
				idc = 1602;
				x = 33.16 * GUI_GRID_W + GUI_GRID_X;
				y = 20.65 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class controlGroupInbox: cTab_RscControlsGroup
			{
				idc = 23001;
				x = 8.26 * GUI_GRID_W + GUI_GRID_X;
				y = 13.23 * GUI_GRID_H + GUI_GRID_Y;
				w = 22.7937 * GUI_GRID_W;
				h = 10.5556 * GUI_GRID_H;
				class controls
				{
					class RscFrame_1800: cTab_RscFrame
					{
						idc = 1800;
						text = "Inbox"; //--- ToDo: Localize;
						x = 0.12 * GUI_GRID_W;
						y = -0.14 * GUI_GRID_H;
						w = 8.39683 * GUI_GRID_W;
						h = 10.5542 * GUI_GRID_H;
					};
					class RscFrame_1801: cTab_RscFrame
					{
						idc = 1801;
						text = "Navigation"; //--- ToDo: Localize;
						x = 8.73 * GUI_GRID_W;
						y = -0.15 * GUI_GRID_H;
						w = 13.7857 * GUI_GRID_W;
						h = 2.04894 * GUI_GRID_H;
					};
					class RscFrame_1802: cTab_RscFrame
					{
						idc = 1802;
						text = "Message"; //--- ToDo: Localize;
						x = 8.75 * GUI_GRID_W;
						y = 1.89 * GUI_GRID_H;
						w = 13.7778 * GUI_GRID_W;
						h = 8.46296 * GUI_GRID_H;
					};
					class RscListbox_1500: cTab_RscListbox
					{
						idc = 1500;
						x = 0.34 * GUI_GRID_W;
						y = 0.29 * GUI_GRID_H;
						w = 7.9127 * GUI_GRID_W;
						h = 9.83862 * GUI_GRID_H;
						onLBSelChanged = "_this call cTab_msg_get_android_mailTxt;";
					};
					class RscButton_1603: cTab_RscButton
					{
						idc = 1603;
						text = "Delete"; //--- ToDo: Localize;
						x = 9.14 * GUI_GRID_W;
						y = 0.47 * GUI_GRID_H;
						w = 5.84126 * GUI_GRID_W;
						h = 1.16931 * GUI_GRID_H;
						action = "player setVariable ['ctab_messages',[]];_nop = [] call cTab_android_msg_gui_load;";						
					};
					class RscButton_1604: cTab_RscButton
					{
						idc = 1604;
						text = "Compose >"; //--- ToDo: Localize;
						x = 15.78 * GUI_GRID_W;
						y = 0.46 * GUI_GRID_H;
						w = 5.84126 * GUI_GRID_W;
						h = 1.16931 * GUI_GRID_H;
						action = "nop = [1] call cTab_android_msg_swi_scrn;";
					};
					class RscStructuredText_1100: cTab_RscStructuredText
					{
						idc = 1100;
						x = 9.05 * GUI_GRID_W;
						y = 2.41 * GUI_GRID_H;
						w = 13.1905 * GUI_GRID_W;
						h = 7.74471 * GUI_GRID_H;
					};
				};
			};
			
			
			class controlGroupCompose: cTab_RscControlsGroup
			{
				idc = 23012;
				x = 8.26 * GUI_GRID_W + GUI_GRID_X;
				y = 13.23 * GUI_GRID_H + GUI_GRID_Y;
				w = 22.7937 * GUI_GRID_W;
				h = 10.5556 * GUI_GRID_H;
				class controls
				{
					class RscFrame_1800: cTab_RscFrame
					{
						idc = 1800;
						text = "Players"; //--- ToDo: Localize;
						x = 0.12 * GUI_GRID_W;
						y = -0.14 * GUI_GRID_H;
						w = 8.39683 * GUI_GRID_W;
						h = 10.5542 * GUI_GRID_H;
					};
					class RscFrame_1801: cTab_RscFrame
					{
						idc = 1801;
						text = "Navigation"; //--- ToDo: Localize;
						x = 8.73 * GUI_GRID_W;
						y = -0.15 * GUI_GRID_H;
						w = 13.7857 * GUI_GRID_W;
						h = 2.04894 * GUI_GRID_H;
					};
					class RscFrame_1802: cTab_RscFrame
					{
						idc = 1802;
						text = "Compose Message"; //--- ToDo: Localize;
						x = 8.75 * GUI_GRID_W;
						y = 1.89 * GUI_GRID_H;
						w = 13.7778 * GUI_GRID_W;
						h = 8.46296 * GUI_GRID_H;
					};
					class RscListbox_1500: cTab_RscListbox
					{
						idc = 1500;
						x = 0.34 * GUI_GRID_W;
						y = 0.29 * GUI_GRID_H;
						w = 7.9127 * GUI_GRID_W;
						h = 9.83862 * GUI_GRID_H;
						//onLBSelChanged = "_this call cTab_msg_get_android_mailTxt;";
					};
					class RscButton_1603: cTab_RscButton
					{
						idc = 1603;
						text = "Send MSG"; //--- ToDo: Localize;
						x = 9.14 * GUI_GRID_W;
						y = 0.47 * GUI_GRID_H;
						w = 5.84126 * GUI_GRID_W;
						h = 1.16931 * GUI_GRID_H;
						action = "call cTab_android_msg_Send;";						
					};
					class RscButton_1604: cTab_RscButton
					{
						idc = 1604;
						text = "< Inbox"; //--- ToDo: Localize;
						x = 15.78 * GUI_GRID_W;
						y = 0.46 * GUI_GRID_H;
						w = 5.84126 * GUI_GRID_W;
						h = 1.16931 * GUI_GRID_H;
						action = "nop = [1] call cTab_android_msg_swi_scrn;";
					};
					class compose_edit_box: cTab_RscEdit
					{
						idc = 1402;
						htmlControl = true;
						style = ST_MULTI;
						x = 9.05 * GUI_GRID_W;
						y = 2.41 * GUI_GRID_H;
						w = 13.1905 * GUI_GRID_W;
						h = 7.74471 * GUI_GRID_H;
					};
				};
			};			
			

	};
	
};