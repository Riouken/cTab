// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


#include <\cTab\cTab_gui_macros.hpp>
#include <\cTab\usermenu_gui_macros.hpp>

#define GUI_GRID_X	(safezoneX)
#define GUI_GRID_Y	(safezoneY)
#define GUI_GRID_W	(safezoneW / 40)
#define GUI_GRID_H	(safezoneH / 25)
#define GUI_GRID_WAbs	(safezoneW)
#define GUI_GRID_HAbs	(safezoneH)


class cTab_msg_main_dlg {
	idd = 19457;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_msg_main_dlg', (_this select 0)];call cTab_msg_gui_load;";
	onUnload = "uiNamespace setVariable ['cTab_msg_main_dlg', displayNull];call cTab_fnc_close;";
	onKeyDown = "call cTab_keyDownShortcut";
	objects[] = {};
	class controlsBackground {


			class background: cTab_RscPicture
			{
				moving = 1;
				idc = IDC_CTAB_BACKGROUND;
				text = "\cTab\img\15th_rugged_tab.paa";
				x = 5.71 * GUI_GRID_W + GUI_GRID_X;
				y = -0.74 * GUI_GRID_H + GUI_GRID_Y;
				w = 27.5 * GUI_GRID_W;
				h = 26.5 * GUI_GRID_H;
			};
			
			
			class windowsBG: cTab_RscPicture
			{

				idc = 1247854;
				text = "#(argb,8,8,3)color(0.2,0.431,0.647,1)";
				x = 10.92 * GUI_GRID_W + GUI_GRID_X;
				y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
				w = 18.2292 * GUI_GRID_W;
				h = 13.4444 * GUI_GRID_H;
			};
			
			class windowsBar: cTab_RscPicture
			{

				idc = 1247858;
				text = "\cTab\img\Desktop_bar.jpg";
				x = 10.96 * GUI_GRID_W + GUI_GRID_X;
				y = 18.3 * GUI_GRID_H + GUI_GRID_Y;
				w = 18.1875 * GUI_GRID_W;
				h = 0.52315 * GUI_GRID_H;
			};			
			
			
				
			
		};


	class controls {

	
			class btnF1: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF1;
				x = 14.29 * GUI_GRID_W + GUI_GRID_X;
				y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Blue Force Tracker - Quick Key";
				action = "_nop = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] spawn cTab_load_BFT;";
			};
			class btnF2: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF2;
				x = 15.19 * GUI_GRID_W + GUI_GRID_X;
				y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "UAV Intel Live Feed - Quick Key";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\uav\cTab_gui_uav_start.sqf';";
			};
			class btnF3: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF3;
				x = 16.07 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Helmet Cam Live Feed - Quick Key";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';";
			};
			class btnF4: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF4;
				x = 16.94 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Text Message Application - Quick Key";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] spawn cTab_spawn_msg_dlg;";
			};
			class btnF5: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF5;
				x = 17.84 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Not used yet*";
			};
			class btnF6: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF6;
				x = 18.71 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Not used yet*";
			};
			class btnMain: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNMAIN;
				x = 19.65 * GUI_GRID_W + GUI_GRID_X;
				y = 19.35 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Main Menu";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\cTab_gui_start.sqf';";
			};
			class btnFN: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNFN;
				x = 20.63 * GUI_GRID_W + GUI_GRID_X;
				y = 19.51 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "if (cTabBFTtxt) then {cTabBFTtxt = false;}else{cTabBFTtxt = true;};";
				tooltip = "Toggle Text on/off";
			};
			class btnOFF: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNOFF;
				x = 21.48 * GUI_GRID_W + GUI_GRID_X;
				y = 19.52 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "closeDialog 0;";
				tooltip = "Close Interface";
			};
			class btnUP: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNUP;
				x = 22.35 * GUI_GRID_W + GUI_GRID_X;
				y = 19.51 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "call cTab_fnc_txt_size_dec;";
				tooltip = "Decrease Font";
			};
			class btnDWN: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNDWN;
				x = 23.23 * GUI_GRID_W + GUI_GRID_X;
				y = 19.53 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "call cTab_fnc_txt_size_inc;";
				tooltip = "Increase Font";
			};
			class btnACT: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNACT;
				x = 26.56 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.1625 * GUI_GRID_W;
				h = 0.824071 * GUI_GRID_H;
				action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
				tooltip = "Delete last user placed icon";
			};


			class msgListbox: cTab_RscListbox
			{
				idc = 15000;
				style = LB_MULTI;
				x = 11.17 * GUI_GRID_W + GUI_GRID_X;
				y = 5.64 * GUI_GRID_H + GUI_GRID_Y;
				w = 7.04167 * GUI_GRID_W;
				h = 6.38426 * GUI_GRID_H;
				onLBSelChanged = "_this call cTab_msg_get_mailTxt;";
			};
			class msgframe: cTab_RscFrame
			{
				idc = 18000;
				text = "Message Text Box"; //--- ToDo: Localize;
				x = 18.61 * GUI_GRID_W + GUI_GRID_X;
				y = 5.52 * GUI_GRID_H + GUI_GRID_Y;
				w = 10 * GUI_GRID_W;
				h = 6.5 * GUI_GRID_H;
			};
			class msgTxt: cTab_RscStructuredText
			{
				idc = 18510;
				style = ST_LEFT+ST_UP;
				text = "Message Text Box"; //--- ToDo: Localize;
				x = 18.71 * GUI_GRID_W + GUI_GRID_X;
				y = 5.82 * GUI_GRID_H + GUI_GRID_Y;
				w = 9.90 * GUI_GRID_W;
				h = 6.3 * GUI_GRID_H;
			};			
			class composeFrame: cTab_RscFrame
			{
				idc = 18010;
				text = "Compose Message"; //--- ToDo: Localize;
				x = 11.09 * GUI_GRID_W + GUI_GRID_X;
				y = 12.01 * GUI_GRID_H + GUI_GRID_Y;
				w = 17.8542 * GUI_GRID_W;
				h = 6.37037 * GUI_GRID_H;
			};
			class playerlistbox: cTab_RscListbox
			{
				idc = 15010;
				style = LB_MULTI;
				x = 11.19 * GUI_GRID_W + GUI_GRID_X;
				y = 12.41 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 5.7176 * GUI_GRID_H;
			};
			class deletebtn: cTab_RscButton
			{
				idc = 16120;
				text = "Delete"; //--- ToDo: Localize;
				x = 21.98 * GUI_GRID_W + GUI_GRID_X;
				y = 17.08 * GUI_GRID_H + GUI_GRID_Y;
				w = 3 * GUI_GRID_W;
				h = 1 * GUI_GRID_H;
				action = "player setVariable ['ctab_messages',[]];_nop = [] call cTab_msg_gui_load;";
			};
			class sendbtn: cTab_RscButton
			{
				idc = 16130;
				text = "Send"; //--- ToDo: Localize;
				x = 25.54 * GUI_GRID_W + GUI_GRID_X;
				y = 17.07 * GUI_GRID_H + GUI_GRID_Y;
				w = 3 * GUI_GRID_W;
				h = 1 * GUI_GRID_H;
				action = "call cTab_msg_Send;";
			};
			class edittxtbox: cTab_RscEdit
			{
				idc = 14000;
				htmlControl = true;
				style = ST_MULTI;
				lineSpacing = 0.2;
				text = "Enter Text Here"; //--- ToDo: Localize;
				x = 16.31 * GUI_GRID_W + GUI_GRID_X;
				y = 12.44 * GUI_GRID_H + GUI_GRID_Y;
				w = 12.3958 * GUI_GRID_W;
				h = 4.48611 * GUI_GRID_H;
			};

	};
};
