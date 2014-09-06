// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


//--- cTab
#include <usermenu_gui_macros.hpp>

#define GUI_GRID_X	(safezoneX)
#define GUI_GRID_Y	(safezoneY)
#define GUI_GRID_W	(safezoneW / 40)
#define GUI_GRID_H	(safezoneH / 25)
#define GUI_GRID_WAbs	(safezoneW)
#define GUI_GRID_HAbs	(safezoneH)

#define MENU_sizeEx (0.04)
#include <\cTab\cTab_markerMenu_macros.hpp>

class cTab_main_dlg {
	idd = 1775154;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_main_dlg', (_this select 0)];";
	onUnload = "uiNamespace setVariable ['cTab_main_dlg', displayNull];call cTab_fnc_close;";
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
		class screen: cTab_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = 10.92 * GUI_GRID_W + GUI_GRID_X;
			y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
			w = 18.2292 * GUI_GRID_W;
			h = 13.4444 * GUI_GRID_H;
			onDraw = "nop = _this call cTabOnDrawbft;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM 'cTab\bft\userload.sqf';";
			onMouseButtonDown = "_ok = _this spawn cTabDeleteUsrMkr;";
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
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
			action = "['cTab_main_dlg',[['mode','BFT']]] call cTab_fnc_settings;";
		};
		class btnF2: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNF2;
			x = 15.19 * GUI_GRID_W + GUI_GRID_X;
			y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			tooltip = "UAV Intel Live Feed - Quick Key";
			action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] execVM 'cTab\uav\cTab_gui_uav_start.sqf';";
		};
		class btnF3: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNF3;
			x = 16.07 * GUI_GRID_W + GUI_GRID_X;
			y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			tooltip = "Helmet Cam Live Feed - Quick Key";
			action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';";
		};
		class btnF4: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNF4;
			x = 16.94 * GUI_GRID_W + GUI_GRID_X;
			y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			tooltip = "Text Message Application - Quick Key";
			action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] spawn cTab_spawn_msg_dlg;";
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
			tooltip = "Toggle Map Textures";
			action = "['cTab_main_dlg'] call cTab_fnc_mapType_toggle;";
		};
		class btnMain: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNMAIN;
			x = 19.65 * GUI_GRID_W + GUI_GRID_X;
			y = 19.35 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			tooltip = "Main Menu";
			action = "['cTab_main_dlg',[['mode','DESKTOP']]] call cTab_fnc_settings;";
		};
		class btnFN: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNFN;
			x = 20.63 * GUI_GRID_W + GUI_GRID_X;
			y = 19.51 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			action = "['cTab_main_dlg'] call cTab_fnc_iconText_toggle;";
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
		class loadingtxt: cTab_RscText
		{
			idc = IDC_CTAB_LOADINGTXT;
			text = "Loading"; //--- ToDo: Localize;
			x = 11.5 * GUI_GRID_W + GUI_GRID_X;
			y = 5.5 * GUI_GRID_H + GUI_GRID_Y;
			w = 3 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class actBFTtxt: cTab_ActiveText
		{
			style = ST_PICTURE;
			idc = IDC_CTAB_ACTBFTTXT;
			text = "\cTab\img\cTab_BFT_ico.paa" ;//"Blue Force Tracker"; //--- ToDo: Localize;
			x = 11.5 * GUI_GRID_W + GUI_GRID_X;
			y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
			w = 1.5 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "['cTab_main_dlg',[['mode','BFT']]] call cTab_fnc_settings;";
			toolTip = "FBCB2 - Blue Force Tracker";
		};
		class actUAVtxt: cTab_ActiveText
		{
			style = ST_PICTURE;
			idc = IDC_CTAB_ACTUAVTXT;
			text = "\cTab\img\cTab_UAV_ico.paa" ;//"UAV Intelligence"; //--- ToDo: Localize;
			x = 11.5 * GUI_GRID_W + GUI_GRID_X;
			y = 9 * GUI_GRID_H + GUI_GRID_Y;
			w = 1.5 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] execVM 'cTab\uav\cTab_gui_uav_start.sqf';";
			toolTip = "UAV Video Feeds";
		};
		class actVIDtxt: cTab_ActiveText
		{
			style = ST_PICTURE;
			idc = IDC_CTAB_ACTVIDTXT;
			text = "\cTab\img\cTab_HMC_ico.paa" ;//"Live Video Feeds"; //--- ToDo: Localize;
			x = 11.5 * GUI_GRID_W + GUI_GRID_X;
			y = 10.5 * GUI_GRID_H + GUI_GRID_Y;
			w = 1.5 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';";
			toolTip = "Live Helmet Cam Video Feeds";
		};
		class actMSGtxt: cTab_ActiveText
		{
			style = ST_PICTURE;
			idc = IDC_CTAB_ACTMSGTXT;
			text = "\cTab\img\Mail_Main_Icon_ico.paa" ;
			x = 11.5 * GUI_GRID_W + GUI_GRID_X;
			y = 12.0 * GUI_GRID_H + GUI_GRID_Y;
			w = 1.5 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 2,cTabIfOpen select 4] spawn cTab_spawn_msg_dlg;";
			toolTip = "Text Messaging System";
		};
		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------
		#include <\cTab\cTab_markerMenu_controls.hpp>
	};
};