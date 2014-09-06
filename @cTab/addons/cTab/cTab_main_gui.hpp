// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


//--- cTab
#include <\cTab\usermenu_gui_macros.hpp>
#include <\cTab\cTab_gui_uav_macros.hpp>

#define GUI_GRID_X	(safezoneX)
#define GUI_GRID_Y	(safezoneY)
#define GUI_GRID_W	(safezoneW / 40)
#define GUI_GRID_H	(safezoneH / 25)
#define GUI_GRID_WAbs	(safezoneW)
#define GUI_GRID_HAbs	(safezoneH)

#define GUI_ToGroup_X(COORD) (COORD) - (10.92 * GUI_GRID_W + GUI_GRID_X)
#define GUI_ToGroup_Y(COORD) (COORD) - (5.4 * GUI_GRID_H + GUI_GRID_Y)

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
		class MiniMapBG: cTab_RscPicture
		{
			moving = 1;
			idc = IDC_CTAB_CTABUAVMAPBG;
			text = "\cTab\img\window_2.jpg";
			x = 11.02 * GUI_GRID_W + GUI_GRID_X;
			y = 11.69 * GUI_GRID_H + GUI_GRID_Y;
			w = 8.5 * GUI_GRID_W;
			h = 7 * GUI_GRID_H;
		};
		class cTabUavMap: cTab_RscMapControl
		{
			idc = IDC_CTAB_CTABUAVMAP;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = 11.27 * GUI_GRID_W + GUI_GRID_X;
			y = 12.47 * GUI_GRID_H + GUI_GRID_Y;
			w = 8 * GUI_GRID_W;
			h = 6 * GUI_GRID_H;
			onDraw = "nop = _this call cTabOnDrawUAV;";
			onMouseButtonDblClick = "";
		};
		class cTabHcamMap: cTabUavMap
		{
			idc = IDC_CTAB_CTABHCAMMAP;
			onDraw = "nop = _this call cTabOnDrawHCam;";
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
			action = "['cTab_main_dlg',[['mode','UAV']]] call cTab_fnc_settings;";
		};
		class btnF3: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNF3;
			x = 16.07 * GUI_GRID_W + GUI_GRID_X;
			y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			tooltip = "Helmet Cam Live Feed - Quick Key";
			action = "['cTab_main_dlg',[['mode','HCAM']]] call cTab_fnc_settings;";
		};
		class btnF4: cTab_RscButtonInv
		{
			idc = IDC_CTAB_BTNF4;
			x = 16.94 * GUI_GRID_W + GUI_GRID_X;
			y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
			w = 0.683335 * GUI_GRID_W;
			h = 0.731482 * GUI_GRID_H;
			tooltip = "Text Message Application - Quick Key";
			action = "['cTab_main_dlg',[['mode','MESSAGE']]] call cTab_fnc_settings;";
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
			x = GUI_ToGroup_X(26.56 * GUI_GRID_W + GUI_GRID_X);
			y = GUI_ToGroup_Y(19.49 * GUI_GRID_H + GUI_GRID_Y);
			w = 1.1625 * GUI_GRID_W;
			h = 0.824071 * GUI_GRID_H;
			action = "_null = [] call cTab_Tablet_btnACT;";
			tooltip = "";
		};
		// ---------- DESKTOP -----------
		class Desktop: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_DESKTOP;
			x = 10.92 * GUI_GRID_W + GUI_GRID_X;
			y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
			w = 18.2292 * GUI_GRID_W;
			h = 13.4444 * GUI_GRID_H;
			class controls
			{
				class actBFTtxt: cTab_ActiveText
				{
					style = ST_PICTURE;
					idc = IDC_CTAB_ACTBFTTXT;
					text = "\cTab\img\cTab_BFT_ico.paa" ;//"Blue Force Tracker"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(11.5 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(7.5 * GUI_GRID_H + GUI_GRID_Y);
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
					x = GUI_ToGroup_X(11.5 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(9 * GUI_GRID_H + GUI_GRID_Y);
					w = 1.5 * GUI_GRID_W;
					h = 1.5 * GUI_GRID_H;
					action = "['cTab_main_dlg',[['mode','UAV']]] call cTab_fnc_settings;";
					toolTip = "UAV Video Feeds";
				};
				class actVIDtxt: cTab_ActiveText
				{
					style = ST_PICTURE;
					idc = IDC_CTAB_ACTVIDTXT;
					text = "\cTab\img\cTab_HMC_ico.paa" ;//"Live Video Feeds"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(11.5 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(10.5 * GUI_GRID_H + GUI_GRID_Y);
					w = 1.5 * GUI_GRID_W;
					h = 1.5 * GUI_GRID_H;
					action = "['cTab_main_dlg',[['mode','HCAM']]] call cTab_fnc_settings;";
					toolTip = "Live Helmet Cam Video Feeds";
				};
				class actMSGtxt: cTab_ActiveText
				{
					style = ST_PICTURE;
					idc = IDC_CTAB_ACTMSGTXT;
					text = "\cTab\img\Mail_Main_Icon_ico.paa" ;
					x = GUI_ToGroup_X(11.5 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(12.0 * GUI_GRID_H + GUI_GRID_Y);
					w = 1.5 * GUI_GRID_W;
					h = 1.5 * GUI_GRID_H;
					action = "['cTab_main_dlg',[['mode','MESSAGE']]] call cTab_fnc_settings;";
					toolTip = "Text Messaging System";
				};
			};
		};
		// ---------- UAV -----------
		class UAV: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_UAV;
			x = 10.92 * GUI_GRID_W + GUI_GRID_X;
			y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
			w = 18.2292 * GUI_GRID_W;
			h = 13.4444 * GUI_GRID_H;
			class controls
			{
				class UAVListBG: cTab_RscPicture
				{
					moving = 1;
					idc = 478594;
					text = "\cTab\img\window_2.jpg";
					x = GUI_ToGroup_X(11.02 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.5 * GUI_GRID_H + GUI_GRID_Y);
					w = 8.5 * GUI_GRID_W;
					h = 6 * GUI_GRID_H;
				};
				class UAVVidBG1: cTab_RscPicture
				{
					moving = 1;
					idc = 478594;
					text = "\cTab\img\window_2.jpg";
					x = GUI_ToGroup_X(20 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.5 * GUI_GRID_H + GUI_GRID_Y);
					w = 8.5 * GUI_GRID_W;
					h = 6.5 * GUI_GRID_H;
				};
				class UAVVidBG2: cTab_RscPicture
				{
					moving = 1;
					idc = 478594;
					text = "\cTab\img\window_2.jpg";
					x = GUI_ToGroup_X(20 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(12.15 * GUI_GRID_H + GUI_GRID_Y);
					w = 8.5 * GUI_GRID_W;
					h = 6.5 * GUI_GRID_H;
				};
				class cTabuavlist: cTab_RscListbox
				{
					idc = IDC_CTAB_CTABUAVLIST;
					x = GUI_ToGroup_X(11.31 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(6.23 * GUI_GRID_H + GUI_GRID_Y);
					w = 8 * GUI_GRID_W;
					h = 5 * GUI_GRID_H;
					onLBSelChanged = "_nop = _this execVM '\cTab\uav\cTab_gui_uav_cam.sqf';";
				};
				class cTabuavdisplay: cTab_RscPicture
				{
					idc = IDC_CTAB_CTABUAVDISPLAY;
					text = "#(argb,512,512,1)r2t(rendertarget9,1.0)";
					x = GUI_ToGroup_X(20.27 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(6.23 * GUI_GRID_H + GUI_GRID_Y);
					w = 8 * GUI_GRID_W;
					h = 5.5 * GUI_GRID_H;
				};
				class cTabuav2nddisplay: cTab_RscPicture
				{
					idc = IDC_CTAB_CTABUAV2NDDISPLAY;
					text = "#(argb,512,512,1)r2t(rendertarget8,1.0)";
					x = GUI_ToGroup_X(20.27 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(12.87 * GUI_GRID_H + GUI_GRID_Y);
					w = 8 * GUI_GRID_W;
					h = 5.5 * GUI_GRID_H;
				};
			};
		};
		// ---------- HELMET CAM -----------
		class HCAM: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_HCAM;
			x = 10.92 * GUI_GRID_W + GUI_GRID_X;
			y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
			w = 18.2292 * GUI_GRID_W;
			h = 13.4444 * GUI_GRID_H;
			class controls
			{
				class HcamListBG: cTab_RscPicture
				{
					moving = 1;
					idc = 478594;
					text = "\cTab\img\window_2.jpg";
					x = GUI_ToGroup_X(11.02 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.5 * GUI_GRID_H + GUI_GRID_Y);
					w = 8.5 * GUI_GRID_W;
					h = 6 * GUI_GRID_H;
				};
				class HcamVidBG: cTab_RscPicture
				{
					moving = 1;
					idc = 478594;
					text = "\cTab\img\window_2.jpg";
					x = GUI_ToGroup_X(20.44 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(7.95 * GUI_GRID_H + GUI_GRID_Y);
					w = 8.5 * GUI_GRID_W;
					h = 8.5 * GUI_GRID_H;
				};
				class cTabuavlist: cTab_RscListbox
				{
					idc = IDC_CTAB_CTABHCAMLIST;
					x = GUI_ToGroup_X(11.31 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(6.23 * GUI_GRID_H + GUI_GRID_Y);
					w = 8 * GUI_GRID_W;
					h = 5 * GUI_GRID_H;
					onLBSelChanged = "_nop = _this execVM '\cTab\hcam\cTab_gui_hcam_cam.sqf';";
				};
				class cTabuavdisplay: cTab_RscPicture
				{
					idc = IDC_CTAB_CTABUAVDISPLAY;
					text = "#(argb,512,512,1)r2t(rendertarget12,1.0)";
					x = GUI_ToGroup_X(20.71 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(8.92 * GUI_GRID_H + GUI_GRID_Y);
					w = 8 * GUI_GRID_W;
					h = 7.18056 * GUI_GRID_H;
				};
			};
		};
		// ---------- MESSAGING -----------
		class MESSAGE: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_MESSAGE;
			x = 10.92 * GUI_GRID_W + GUI_GRID_X;
			y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
			w = 18.2292 * GUI_GRID_W;
			h = 13.4444 * GUI_GRID_H;
			class controls
			{
				class windowsBG: cTab_RscPicture
				{
					idc = 1247854;
					text = "#(argb,8,8,3)color(0.2,0.431,0.647,1)";
					x = GUI_ToGroup_X(10.92 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.4 * GUI_GRID_H + GUI_GRID_Y);
					w = 18.2292 * GUI_GRID_W;
					h = 13.4444 * GUI_GRID_H;
				};
				class windowsBar: cTab_RscPicture
				{
					idc = 1247858;
					text = "\cTab\img\Desktop_bar.jpg";
					x = GUI_ToGroup_X(10.96 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(18.3 * GUI_GRID_H + GUI_GRID_Y);
					w = 18.1875 * GUI_GRID_W;
					h = 0.52315 * GUI_GRID_H;
				};
				class msgListbox: cTab_RscListbox
				{
					idc = 15000;
					style = LB_MULTI;
					x = GUI_ToGroup_X(11.17 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.64 * GUI_GRID_H + GUI_GRID_Y);
					w = 7.04167 * GUI_GRID_W;
					h = 6.38426 * GUI_GRID_H;
					onLBSelChanged = "_this call cTab_msg_get_mailTxt;";
				};
				class msgframe: cTab_RscFrame
				{
					idc = 18000;
					text = "Message Text Box"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(18.61 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.52 * GUI_GRID_H + GUI_GRID_Y);
					w = 10 * GUI_GRID_W;
					h = 6.5 * GUI_GRID_H;
				};
				class msgTxt: cTab_RscStructuredText
				{
					idc = 18510;
					style = ST_LEFT+ST_UP;
					text = "Message Text Box"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(18.71 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(5.82 * GUI_GRID_H + GUI_GRID_Y);
					w = 9.90 * GUI_GRID_W;
					h = 6.3 * GUI_GRID_H;
				};			
				class composeFrame: cTab_RscFrame
				{
					idc = 18010;
					text = "Compose Message"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(11.09 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(12.01 * GUI_GRID_H + GUI_GRID_Y);
					w = 17.8542 * GUI_GRID_W;
					h = 6.37037 * GUI_GRID_H;
				};
				class playerlistbox: cTab_RscListbox
				{
					idc = 15010;
					style = LB_MULTI;
					x = GUI_ToGroup_X(11.19 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(12.41 * GUI_GRID_H + GUI_GRID_Y);
					w = 5 * GUI_GRID_W;
					h = 5.7176 * GUI_GRID_H;
				};
				class deletebtn: cTab_RscButton
				{
					idc = 16120;
					text = "Delete"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(21.98 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(17.08 * GUI_GRID_H + GUI_GRID_Y);
					w = 3 * GUI_GRID_W;
					h = 1 * GUI_GRID_H;
					action = "player setVariable ['ctab_messages',[]];_nop = [] call cTab_msg_gui_load;";
				};
				class sendbtn: cTab_RscButton
				{
					idc = 16130;
					text = "Send"; //--- ToDo: Localize;
					x = GUI_ToGroup_X(25.54 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(17.07 * GUI_GRID_H + GUI_GRID_Y);
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
					x = GUI_ToGroup_X(16.31 * GUI_GRID_W + GUI_GRID_X);
					y = GUI_ToGroup_Y(12.44 * GUI_GRID_H + GUI_GRID_Y);
					w = 12.3958 * GUI_GRID_W;
					h = 4.48611 * GUI_GRID_H;
				};
			};
		};
		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------
		#include <\cTab\cTab_markerMenu_controls.hpp>

		// ---------- LOADING ------------
		class loadingtxt: cTab_RscText
		{
			idc = IDC_CTAB_LOADINGTXT;
			style = ST_CENTER;
			text = "Loading"; //--- ToDo: Localize;
			x = 10.92 * GUI_GRID_W + GUI_GRID_X;
			y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
			w = 18.2292 * GUI_GRID_W;
			h = 13.4444 * GUI_GRID_H;
			colorBackground[] = {0.2,0.431,0.647,1};
		};
	};
};