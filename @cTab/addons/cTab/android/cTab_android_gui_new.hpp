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

#define MENU_sizeEx GUI_GRID_H * 0.75
#include <\cTab\cTab_markerMenu_macros.hpp>

class cTab_Android_dlg {
	idd = 177382;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_Android_dlg', (_this select 0)];nul = [] execVM '\cTab\bft\ctab_gui_Android_onload.sqf';";
	onUnload = "uiNamespace setVariable ['cTab_Android_dlg', displayNull];call cTab_fnc_close;";
	objects[] = {};
	class controlsBackground {

				class bftscreen: cTab_RscMapControl
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
				onDraw = "nop = _this call cTabOnDrawbftAndroid;";
				onMouseButtonDblClick = "_ok = [3300,_this] execVM 'cTab\bft\userload.sqf';";
				onMouseButtonDown = "_ok = _this spawn cTabDeleteUsrMkr;";				
			};
	
			class background: cTab_RscPicture
			{
				idc = 1200;
				text = "\cTab\img\itemAndroid_display.paa";
				x = -1.5 * GUI_GRID_W + GUI_GRID_X;
				y = 1 * GUI_GRID_H + GUI_GRID_Y;
				w = 44 * GUI_GRID_W;
				h = 35 * GUI_GRID_H;
			};

			
	};



	class controls {
	
			class btnBack: cTab_RscButtonInv
			{
				idc = 1600;
				x = 33.18 * GUI_GRID_W + GUI_GRID_X;
				y = 14.9 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
				tooltip = "Delete last user placed icon";				
			};
			class btnHome: cTab_RscButtonInv
			{
				idc = 1601;
				x = 33.26 * GUI_GRID_W + GUI_GRID_X;
				y = 17.77 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				tooltip = "** Coming Soon";
			};
			class btnMenu: cTab_RscButtonInv
			{
				idc = 1602;
				x = 33.16 * GUI_GRID_W + GUI_GRID_X;
				y = 20.65 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "ctrlShow [3357, True];";
				tooltip = "Main Options";				
			};
			
			
// Main Menu			
			class menuContainer: cTab_RscControlsGroup
			{
				idc = 3357;
				x = 24.4 * GUI_GRID_W + GUI_GRID_X;
				y = 13.64 * GUI_GRID_H + GUI_GRID_Y;
				w = 6.5 * GUI_GRID_W;
				h = 9.5 * GUI_GRID_H;
				class controls
				{
					class menuBackground: cTab_IGUIBack
					{
						idc = 2200;
						x = -0.01 * GUI_GRID_W;
						y = -0.04 * GUI_GRID_H;
						w = 6.5 * GUI_GRID_W;
						h = 9.5 * GUI_GRID_H;
					};
					class btnTextonoff: cTab_RscButton
					{
						idc = 2800;
						text = "Text On/Off"; //--- ToDo: Localize;
						x = 0.3 * GUI_GRID_W;
						y = 0.3 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						tooltip = "Change Icon/Text Size"; //--- ToDo: Localize;
						action = "['cTab_Android_dlg'] call cTab_fnc_iconText_toggle;";
					};
					
					/*
					class RscText_1001: RscText
					{
						idc = 1001;
						text = "Text"; //--- ToDo: Localize;
						x = 0.8 * GUI_GRID_W;
						y = -0.54 * GUI_GRID_H;
						w = 4 * GUI_GRID_W;
						h = 2.5 * GUI_GRID_H;
						sizeEx = .75 * GUI_GRID_H;
					};
					*/
					
					class btnIcnSizeup: cTab_RscButton
					{
						idc = 1603;
						text = "Icon Size +"; //--- ToDo: Localize;
						x = 0.3 * GUI_GRID_W;
						y = 1.3 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						tooltip = "Increase Icon/Text Size"; //--- ToDo: Localize;
						action = "call cTab_fnc_txt_size_inc;";						
					};
					class btnIconSizedwn: cTab_RscButton
					{
						idc = 1604;
						text = "Icon Size -"; //--- ToDo: Localize;
						x = 0.29 * GUI_GRID_W;
						y = 2.6 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						tooltip = "Decrease Icon/Text Size"; //--- ToDo: Localize;
						action = "call cTab_fnc_txt_size_dec;";						
					};
					class btnDeleteIcon: cTab_RscButton
					{
						idc = 1605;
						text = "Delete Icon"; //--- ToDo: Localize;
						x = 0.32 * GUI_GRID_W;
						y = 3.96 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
						tooltip = "Delete last user placed icon";
					};
					class RscButton_1606: cTab_RscButton
					{
						idc = 1606;
						text = "Messages >>"; //--- ToDo: Localize;
						x = 0.33 * GUI_GRID_W;
						y = 5.25 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						tooltip = "Goto Messages"; //--- ToDo: Localize;
						action = "nop =  [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] spawn cTab_open_android_msg;";						
					};
					class btnExitmenu: cTab_RscButton
					{
						idc = 1607;
						text = "Exit Menu"; //--- ToDo: Localize;
						x = 0.28 * GUI_GRID_W;
						y = 6.7 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						tooltip = "Exit Current Menu"; //--- ToDo: Localize;
						action = "ctrlShow [3357, False];";
					};
					class btnExit: cTab_RscButton
					{
						idc = 1608;
						text = "Exit Android"; //--- ToDo: Localize;
						x = 0.29 * GUI_GRID_W;
						y = 8.15 * GUI_GRID_H;
						w = 6 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						tooltip = "Exit Android GUI"; //--- ToDo: Localize;
						action = "closeDialog 0;";
					};
				};
			};

			// User Placed markers
			#include <\cTab\cTab_markerMenu_controls.hpp>
	};

};
