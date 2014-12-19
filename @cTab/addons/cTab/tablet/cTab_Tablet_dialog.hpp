// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


//--- cTab
#define GUI_GRID_W	(safezoneW * 0.8)
#define GUI_GRID_H	(GUI_GRID_W * 4/3)
#define GUI_GRID_X	(safezoneX + (safezoneW - GUI_GRID_W) / 2)
#define GUI_GRID_Y	(safezoneY + (safezoneH - GUI_GRID_H) / 2)

#include <\cTab\tablet\cTab_Tablet_controls.hpp>

#define MENU_sizeEx pxToScreen_H(cTab_GUI_tablet_OSD_TEXT_STD_SIZE)
#include "\cTab\shared\cTab_markerMenu_macros.hpp"

class cTab_Tablet_dlg {
	idd = 1775154;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_Tablet_dlg', (_this select 0)];";
	onUnload = "uiNamespace setVariable ['cTab_Tablet_dlg', displayNull];call cTab_fnc_close;";
	onKeyDown = "_this call cTab_fnc_onIfKeyDown;";
	objects[] = {};
	class controlsBackground {
		class background: cTab_Tablet_background
		{
			moving = 1;
		};
		class windowsBG: cTab_RscPicture
		{
			idc = IDC_CTAB_WIN_BACK;
			text = "#(argb,8,8,3)color(0.2,0.431,0.647,1)";
			x = pxToScreen_X(cTab_GUI_tablet_MAP_X);
			y = pxToScreen_Y(cTab_GUI_tablet_MAP_Y);
			w = pxToScreen_W(cTab_GUI_tablet_MAP_W);
			h = pxToScreen_H(cTab_GUI_tablet_MAP_H);
		};
		class windowsBar: cTab_RscPicture
		{
			idc = IDC_CTAB_WIN_TASKBAR;
			text = "\cTab\img\Desktop_bar.jpg";
			x = pxToScreen_X(cTab_GUI_tablet_TASKBAR_X);
			y = pxToScreen_Y(cTab_GUI_tablet_TASKBAR_Y);
			w = pxToScreen_W(cTab_GUI_tablet_TASKBAR_W);
			h = pxToScreen_H(cTab_GUI_tablet_TASKBAR_H);
		};
		class MiniMapBG: cTab_Tablet_window_back_BL
		{
			idc = IDC_CTAB_MINIMAPBG;
		};
		class cTabUavMap: cTab_RscMapControl
		{
			idc = IDC_CTAB_CTABUAVMAP;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = pxToScreen_X(cTab_GUI_tablet_WINDOW_CONTENT_L_X);
			y = pxToScreen_Y(cTab_GUI_tablet_WINDOW_CONTENT_B_Y);
			w = pxToScreen_W(cTab_GUI_tablet_WINDOW_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_WINDOW_CONTENT_H);
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
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
			onDraw = "nop = _this call cTabOnDrawbft;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM '\cTab\shared\cTab_markerMenu_load.sqf';";
			onMouseMoving = "cTabCursorOnMap = _this select 3;cTabMapCursorPos = _this select 0 ctrlMapScreenToWorld [_this select 1,_this select 2];";
			maxSatelliteAlpha = 10000;
			alphaFadeStartScale = 10;
			alphaFadeEndScale = 10;

			// Rendering density coefficients
			ptsPerSquareSea = 8 / (0.86 / GUI_GRID_H);		// seas
			ptsPerSquareTxt = 8 / (0.86 / GUI_GRID_H);		// textures
			ptsPerSquareCLn = 8 / (0.86 / GUI_GRID_H);		// count-lines
			ptsPerSquareExp = 8 / (0.86 / GUI_GRID_H);		// exposure
			ptsPerSquareCost = 8 / (0.86 / GUI_GRID_H);		// cost

			// Rendering thresholds
			ptsPerSquareFor = 3 / (0.86 / GUI_GRID_H);		// forests
			ptsPerSquareForEdge = 100 / (0.86 / GUI_GRID_H);	// forest edges
			ptsPerSquareRoad = 1.5 / (0.86 / GUI_GRID_H);		// roads
			ptsPerSquareObj = 4 / (0.86 / GUI_GRID_H);		// other objects
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
	};
	class controls {
		class header: cTab_tablet_header {};
		class battery: cTab_tablet_on_screen_battery {};
		class time: cTab_tablet_on_screen_time {};
		class signalStrength: cTab_tablet_on_screen_signalStrength {};
		class satellite: cTab_tablet_on_screen_satellite {};
		class dirDegree: cTab_tablet_on_screen_dirDegree {};
		class grid: cTab_tablet_on_screen_grid {};
		class dirOctant: cTab_tablet_on_screen_dirOctant {};
		class btnF1: cTab_Tablet_btnF1
		{
			idc = IDC_CTAB_BTNF1;
			tooltip = "Blue Force Tracker - Quick Key";
			action = "['cTab_Tablet_dlg',[['mode','BFT']]] call cTab_fnc_setSettings;";
		};
		class btnF2: cTab_Tablet_btnF2
		{
			idc = IDC_CTAB_BTNF2;
			tooltip = "UAV Intel Live Feed - Quick Key";
			action = "['cTab_Tablet_dlg',[['mode','UAV']]] call cTab_fnc_setSettings;";
		};
		class btnF3: cTab_Tablet_btnF3
		{
			idc = IDC_CTAB_BTNF3;
			tooltip = "Helmet Cam Live Feed - Quick Key";
			action = "['cTab_Tablet_dlg',[['mode','HCAM']]] call cTab_fnc_setSettings;";
		};
		class btnF4: cTab_Tablet_btnF4
		{
			idc = IDC_CTAB_BTNF4;
			tooltip = "Text Message Application - Quick Key";
			action = "['cTab_Tablet_dlg',[['mode','MESSAGE']]] call cTab_fnc_setSettings;";
		};
		class btnF5: cTab_Tablet_btnF5
		{
			idc = IDC_CTAB_BTNF5;
			tooltip = "Toggle Map Tools (F5)";
			action = "['cTab_Tablet_dlg'] call cTab_fnc_toggleMapTools;";
		};
		class btnF6: cTab_Tablet_btnF6
		{
			idc = IDC_CTAB_BTNF6;
			tooltip = "Toggle Map Textures (F6)";
			action = "['cTab_Tablet_dlg'] call cTab_fnc_mapType_toggle;";
		};
		class btnF7: cTab_Tablet_btnTrackpad
		{
			idc = -1;
			action = "['cTab_Tablet_dlg'] call cTab_fnc_centerMapOnPlayerPosition;";
			tooltip = "Center Map On Current Position (F7)";
		};
		class btnMain: cTab_Tablet_btnHome
		{
			idc = IDC_CTAB_BTNMAIN;
			tooltip = "Main Menu";
			action = "['cTab_Tablet_dlg',[['mode','DESKTOP']]] call cTab_fnc_setSettings;";
		};
		class btnFN: cTab_Tablet_btnFn
		{
			idc = IDC_CTAB_BTNFN;
			action = "['cTab_Tablet_dlg'] call cTab_fnc_iconText_toggle;";
			tooltip = "Toggle Text on/off";
		};
		class btnOFF: cTab_Tablet_btnPower
		{
			idc = IDC_CTAB_BTNOFF;
			action = "closeDialog 0;";
			tooltip = "Close Interface";
		};
		class btnUP: cTab_Tablet_btnBrtUp
		{
			idc = IDC_CTAB_BTNUP;
			action = "call cTab_fnc_txt_size_dec;";
			tooltip = "Decrease Font";
		};
		class btnDWN: cTab_Tablet_btnBrtDn
		{
			idc = IDC_CTAB_BTNDWN;
			action = "call cTab_fnc_txt_size_inc;";
			tooltip = "Increase Font";
		};
		class btnACT: cTab_Tablet_btnMouse
		{
			idc = IDC_CTAB_BTNACT;
			action = "_null = [] call cTab_Tablet_btnACT;";
			tooltip = "";
		};
		class hookGrid: cTab_Tablet_on_screen_hookGrid {};
		class hookElevation: cTab_Tablet_on_screen_hookElevation {};
		class hookDst: cTab_Tablet_on_screen_hookDst {};
		class hookDir: cTab_Tablet_on_screen_hookDir {};
		// ---------- DESKTOP -----------
		class Desktop: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_DESKTOP;
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class actBFTtxt: cTab_ActiveText
				{
					style = ST_PICTURE;
					idc = IDC_CTAB_ACTBFTTXT;
					text = "\cTab\img\cTab_BFT_ico.paa" ;//"Blue Force Tracker"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_tablet_SCREEN_CONTENT_X + cTab_GUI_tablet_DESKTOP_ICON_OFFSET_X);
					y = pxToGroup_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y + cTab_GUI_tablet_DESKTOP_ICON_OFFSET_Y);
					w = pxToScreen_W(cTab_GUI_tablet_DESKTOP_ICON_W);
					h = pxToScreen_H(cTab_GUI_tablet_DESKTOP_ICON_H);
					action = "['cTab_Tablet_dlg',[['mode','BFT']]] call cTab_fnc_setSettings;";
					toolTip = "FBCB2 - Blue Force Tracker";
				};
				class actUAVtxt: actBFTtxt
				{
					idc = IDC_CTAB_ACTUAVTXT;
					text = "\cTab\img\cTab_UAV_ico.paa" ;//"UAV Intelligence"; //--- ToDo: Localize;
					y = pxToGroup_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y + cTab_GUI_tablet_DESKTOP_ICON_OFFSET_Y * 2 + cTab_GUI_tablet_DESKTOP_ICON_H);
					action = "['cTab_Tablet_dlg',[['mode','UAV']]] call cTab_fnc_setSettings;";
					toolTip = "UAV Video Feeds";
				};
				class actVIDtxt: actBFTtxt
				{
					idc = IDC_CTAB_ACTVIDTXT;
					text = "\cTab\img\cTab_HMC_ico.paa" ;//"Live Video Feeds"; //--- ToDo: Localize;
					y = pxToGroup_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y + cTab_GUI_tablet_DESKTOP_ICON_OFFSET_Y * 3 + cTab_GUI_tablet_DESKTOP_ICON_H * 2);
					action = "['cTab_Tablet_dlg',[['mode','HCAM']]] call cTab_fnc_setSettings;";
					toolTip = "Live Helmet Cam Video Feeds";
				};
				class actMSGtxt: actBFTtxt
				{
					idc = IDC_CTAB_ACTMSGTXT;
					text = "\cTab\img\Mail_Main_Icon_ico.paa" ;
					y = pxToGroup_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y + cTab_GUI_tablet_DESKTOP_ICON_OFFSET_Y * 4 + cTab_GUI_tablet_DESKTOP_ICON_H * 3);
					action = "['cTab_Tablet_dlg',[['mode','MESSAGE']]] call cTab_fnc_setSettings;";
					toolTip = "Text Messaging System";
				};
			};
		};
		// ---------- UAV -----------
		class UAV: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_UAV;
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class UAVListBG: cTab_Tablet_window_back_TL
				{
					idc = -1;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_BACK_L_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_BACK_T_Y);
				};
				class UAVVidBG1: cTab_Tablet_window_back_TR
				{
					idc = -1;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_BACK_R_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_BACK_T_Y);
				};
				class UAVVidBG2: cTab_Tablet_window_back_BR
				{
					idc = -1;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_BACK_R_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_BACK_B_Y);
				};
				class cTabUAVlist: cTab_RscListbox
				{
					idc = IDC_CTAB_CTABUAVLIST;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_CONTENT_L_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_CONTENT_T_Y);
					w = pxToScreen_W(cTab_GUI_tablet_WINDOW_CONTENT_W);
					h = pxToScreen_H(cTab_GUI_tablet_WINDOW_CONTENT_H);
					onLBSelChanged = "['cTab_Tablet_dlg',[['uavCam',(_this select 0) lbData (_this select 1)]]] call cTab_fnc_setSettings;";
				};
				class cTabUAVdisplay: cTab_RscPicture
				{
					idc = IDC_CTAB_CTABUAVDISPLAY;
					text = "#(argb,512,512,1)r2t(rendertarget8,1.1896551724)";
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_CONTENT_R_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_CONTENT_T_Y);
					w = pxToScreen_W(cTab_GUI_tablet_WINDOW_CONTENT_W);
					h = pxToScreen_H(cTab_GUI_tablet_WINDOW_CONTENT_H);
				};
				class cTabUAV2nddisplay: cTab_RscPicture
				{
					idc = IDC_CTAB_CTABUAV2NDDISPLAY;
					text = "#(argb,512,512,1)r2t(rendertarget9,1.1896551724)";
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_CONTENT_R_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_CONTENT_B_Y);
					w = pxToScreen_W(cTab_GUI_tablet_WINDOW_CONTENT_W);
					h = pxToScreen_H(cTab_GUI_tablet_WINDOW_CONTENT_H);
				};
			};
		};
		// ---------- HELMET CAM -----------
		class HCAM: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_HCAM;
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class HcamListBG: cTab_Tablet_window_back_TL
				{
					idc = -1;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_BACK_L_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_BACK_T_Y);
				};
				class HcamVidBG: cTab_Tablet_window_back_TR
				{
					idc = -1;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_BACK_R_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_BACK_T_Y);
				};
				class cTabHcamList: cTab_RscListbox
				{
					idc = IDC_CTAB_CTABHCAMLIST;
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_CONTENT_L_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_CONTENT_T_Y);
					w = pxToScreen_W(cTab_GUI_tablet_WINDOW_CONTENT_W);
					h = pxToScreen_H(cTab_GUI_tablet_WINDOW_CONTENT_H);
					onLBSelChanged = "['cTab_Tablet_dlg',[['hCam',(_this select 0) lbData (_this select 1)]]] call cTab_fnc_setSettings;";
				};
				class cTabHcamDisplay: cTab_RscPicture
				{
					idc = IDC_CTAB_CTABHCAMDISPLAY;
					text = "#(argb,512,512,1)r2t(rendertarget12,1.1896551724)";
					x = pxToGroup_X(cTab_GUI_tablet_WINDOW_CONTENT_R_X);
					y = pxToGroup_Y(cTab_GUI_tablet_WINDOW_CONTENT_T_Y);
					w = pxToScreen_W(cTab_GUI_tablet_WINDOW_CONTENT_W);
					h = pxToScreen_H(cTab_GUI_tablet_WINDOW_CONTENT_H);
				};
			};
		};
		// ---------- MESSAGING -----------
		class MESSAGE: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_MESSAGE;
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class msgListbox: cTab_RscListbox
				{
					idc = IDC_CTAB_MSG_LIST;
					style = LB_MULTI;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_MESSAGELIST_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_MESSAGELIST_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_MESSAGELIST_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_MESSAGELIST_H);
					onLBSelChanged = "_this call cTab_msg_get_mailTxt;";
				};
				class msgframe: cTab_RscFrame
				{
					idc = -1;
					text = "Read Message"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_FRAME_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_FRAME_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_FRAME_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_FRAME_H);
				};
				class msgTxt: cTab_RscEdit
				{
					idc = IDC_CTAB_MSG_CONTENT;
					htmlControl = true;
					style = ST_MULTI;
					lineSpacing = 0.2;
					text = "No Message Selected"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_MESSAGETEXT_H);
					canModify = 0;
				};
				class composeFrame: cTab_RscFrame
				{
					idc = -1;
					text = "Compose Message"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_COMPOSE_FRAME_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_COMPOSE_FRAME_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_COMPOSE_FRAME_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_COMPOSE_FRAME_H);
				};
				class playerlistbox: cTab_RscListbox
				{
					idc = IDC_CTAB_MSG_RECIPIENTS;
					style = LB_MULTI;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_PLAYERLIST_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_PLAYERLIST_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_PLAYERLIST_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_PLAYERLIST_H);
				};
				class deletebtn: cTab_RscButton
				{
					idc = IDS_CTAB_MSG_BTNDELETE;
					text = "Delete"; //--- ToDo: Localize;
					tooltip = "Delete Selected Message(s)";
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_BUTTON_DELETE_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_BUTTON_DELETE_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_BUTTON_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_BUTTON_H);
					action = "['cTab_Tablet_dlg'] call cTab_fnc_onMsgBtnDelete;";
				};
				class sendbtn: cTab_RscButton
				{
					idc = IDS_CTAB_MSG_BTNSEND;
					text = "Send"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_BUTTON_SEND_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_BUTTON_SEND_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_BUTTON_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_BUTTON_H);
					action = "call cTab_msg_Send;";
				};
				class edittxtbox: cTab_RscEdit
				{
					idc = IDC_CTAB_MSG_COMPOSE;
					htmlControl = true;
					style = ST_MULTI;
					lineSpacing = 0.2;
					text = ""; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_tablet_MESSAGE_COMPOSE_TEXT_X);
					y = pxToGroup_Y(cTab_GUI_tablet_MESSAGE_COMPOSE_TEXT_Y);
					w = pxToScreen_W(cTab_GUI_tablet_MESSAGE_COMPOSE_TEXT_W);
					h = pxToScreen_H(cTab_GUI_tablet_MESSAGE_COMPOSE_TEXT_H);
				};
			};
		};
		// ---------- FULLSCREEN HCAM -----------
		class cTabHcamFull: cTab_RscPicture
		{
			idc = IDC_CTAB_HCAM_FULL;
			text = "#(argb,512,512,1)r2t(rendertarget13,1.3096153846)";
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
		};
		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------
		#include "\cTab\shared\cTab_markerMenu_controls.hpp"

		// ---------- LOADING ------------
		class loadingtxt: cTab_RscText
		{
			idc = IDC_CTAB_LOADINGTXT;
			style = ST_CENTER;
			text = "Loading"; //--- ToDo: Localize;
			x = pxToScreen_X(cTab_GUI_tablet_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_tablet_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_tablet_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_tablet_SCREEN_CONTENT_H);
			colorBackground[] = {0.2,0.431,0.647,1};
		};
	};
};