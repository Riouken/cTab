// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

#define GUI_GRID_W	(safezoneW * 0.8)
#define GUI_GRID_H	(GUI_GRID_W * 4/3)
#define GUI_GRID_X	(safezoneX + (safezoneW - GUI_GRID_W) / 2)
#define GUI_GRID_Y	(safezoneY + (safezoneH - GUI_GRID_H) / 2)

#define cTab_android_DLGtoDSP_fctr (0.86 / GUI_GRID_H)

#include <\cTab\android\cTab_android_controls.hpp>

#define MENU_sizeEx pxToScreen_H(27)
#include "\cTab\shared\cTab_markerMenu_macros.hpp"

class cTab_Android_dlg {
	idd = 177382;
	movingEnable = true;
	onLoad = "_this call cTab_fnc_onIfOpen;";
	onUnload = "[] call cTab_fnc_onIfclose;";
	onKeyDown = "_this call cTab_fnc_onIfKeyDown;";
	objects[] = {};
	class controlsBackground
	{
		class windowsBG: cTab_android_windowsBG {};
		class screen: cTab_android_RscMapControl
		{
			onDraw = "nop = _this call cTabOnDrawbftAndroid;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM '\cTab\shared\cTab_markerMenu_load.sqf';";
			onMouseMoving = "cTabCursorOnMap = _this select 3;cTabMapCursorPos = _this select 0 ctrlMapScreenToWorld [_this select 1,_this select 2];";
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
	};

	class controls
	{
		/*
			### OSD GUI controls ###
		*/
		class header: cTab_android_header {};
		class battery: cTab_android_on_screen_battery {};
		class time: cTab_android_on_screen_time {};
		class signalStrength: cTab_android_on_screen_signalStrength {};
		class satellite: cTab_android_on_screen_satellite {};
		class dirDegree: cTab_android_on_screen_dirDegree {};
		class grid: cTab_android_on_screen_grid {};
		class dirOctant: cTab_android_on_screen_dirOctant {};
		class hookGrid: cTab_android_on_screen_hookGrid {};
		class hookElevation: cTab_android_on_screen_hookElevation {};
		class hookDst: cTab_android_on_screen_hookDst {};
		class hookDir: cTab_android_on_screen_hookDir {};

		// ---------- MAIN MENU -----------
		class menuContainer: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_MENU;
			x = pxToScreen_X(cTab_GUI_android_OSD_MENU_X);
			y = pxToScreen_Y(cTab_GUI_android_OSD_MENU_Y);
			w = pxToScreen_W(cTab_GUI_android_OSD_MENU_W);
			h = pxToScreen_H(cTab_GUI_android_OSD_MENU_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class menuBackground: cTab_IGUIBack
				{
					IDC_COUNTER
					x = 0;
					y = 0;
					w = pxToScreen_W(cTab_GUI_android_OSD_MENU_W);
					h = pxToScreen_H(cTab_GUI_android_OSD_MENU_H);
				};
				class btnTextonoff: cTab_RscButton
				{
					IDC_COUNTER
					text = "Text On/Off"; //--- ToDo: Localize;
					sizeEx = pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE);
					x = pxToMenu_X(cTab_GUI_android_OSD_MENU_ELEMENT_X);
					y = pxToMenu_Y(cTab_GUI_android_OSD_MENU_ELEMENT_Y(1));
					w = pxToScreen_W(cTab_GUI_android_OSD_MENU_ELEMENT_W);
					h = pxToScreen_H(cTab_GUI_android_OSD_MENU_ELEMENT_H);
					tooltip = "Toggle Text on/off"; //--- ToDo: Localize;
					action = "['cTab_Android_dlg'] call cTab_fnc_iconText_toggle;";
				};
				class btnIcnSizeup: btnTextonoff
				{
					IDC_COUNTER
					text = "Icon Size +"; //--- ToDo: Localize;
					y = pxToMenu_Y(cTab_GUI_android_OSD_MENU_ELEMENT_Y(2));
					tooltip = "Increase Icon/Text Size"; //--- ToDo: Localize;
					action = "call cTab_fnc_txt_size_inc;";
				};
				class btnIconSizedwn: btnTextonoff
				{
					IDC_COUNTER
					text = "Icon Size -"; //--- ToDo: Localize;
					y = pxToMenu_Y(cTab_GUI_android_OSD_MENU_ELEMENT_Y(3));
					tooltip = "Decrease Icon/Text Size"; //--- ToDo: Localize;
					action = "call cTab_fnc_txt_size_dec;";
				};
				class btnF5: btnTextonoff
				{
					IDC_COUNTER
					y = pxToMenu_Y(cTab_GUI_android_OSD_MENU_ELEMENT_Y(7));
					text = "Map Tools";
					tooltip = "Toggle Map Tools (F5)";
					action = "['cTab_Android_dlg'] call cTab_fnc_toggleMapTools;";
				};
				class btnF6: btnTextonoff
				{
					IDC_COUNTER
					y = pxToMenu_Y(cTab_GUI_android_OSD_MENU_ELEMENT_Y(5));
					text = "Map Textures";
					tooltip = "Toggle Map Textures (F6)";
					action = "['cTab_Android_dlg'] call cTab_fnc_mapType_toggle;";
				};
				class btnF7: btnTextonoff
				{
					IDC_COUNTER
					y = pxToMenu_Y(cTab_GUI_android_OSD_MENU_ELEMENT_Y(6));
					text = "Center Map";
					action = "['cTab_Android_dlg'] call cTab_fnc_centerMapOnPlayerPosition;";
					tooltip = "Center Map On Current Position (F7)";
				};
			};
		};
		// ---------- MESSAGING READ -----------
		class MESSAGE: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_MESSAGE;
			x = pxToScreen_X(cTab_GUI_android_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_android_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_android_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_android_SCREEN_CONTENT_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class msgListbox: cTab_RscListbox
				{
					idc = IDC_CTAB_MSG_LIST;
					style = LB_MULTI;
					sizeEx = pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE * 0.8);
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_MESSAGELIST_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_MESSAGELIST_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_MESSAGELIST_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_MESSAGELIST_H);
					onLBSelChanged = "_this call cTab_msg_get_mailTxt;";
				};
				class msgframe: cTab_RscFrame
				{
					IDC_COUNTER
					text = "Read Message"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_H);
				};
				class msgTxt: cTab_RscEdit
				{
					idc = IDC_CTAB_MSG_CONTENT;
					htmlControl = true;
					style = ST_MULTI;
					lineSpacing = 0.2;
					text = "No Message Selected"; //--- ToDo: Localize;
					sizeEx = pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE);
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_MESSAGETEXT_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_MESSAGETEXT_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_MESSAGETEXT_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_MESSAGETEXT_H);
					canModify = 0;
				};
				class deletebtn: cTab_RscButton
				{
					idc = IDC_CTAB_MSG_BTNDELETE;
					text = "Delete"; //--- ToDo: Localize;
					tooltip = "Delete Selected Message(s)";
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_BUTTON_DELETE_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_BUTTON_DELETE_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_BUTTON_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_BUTTON_H);
					action = "['cTab_Android_dlg'] call cTab_fnc_onMsgBtnDelete;";
				};
				class toCompose: cTab_RscButton
				{
					IDC_COUNTER
					text = "Compose >>"; //--- ToDo: Localize;
					tooltip = "Compose Messages";
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_BUTTON_MODE_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_BUTTON_MODE_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_BUTTON_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_BUTTON_H);
					action = "['cTab_Android_dlg',[['mode','COMPOSE']]] call cTab_fnc_setSettings;";
				};
			};
		};
		// ---------- MESSAGING COMPOSE -----------
		class COMPOSE: cTab_RscControlsGroup
		{
			idc = IDC_CTAB_GROUP_COMPOSE;
			x = pxToScreen_X(cTab_GUI_android_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_android_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_android_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_android_SCREEN_CONTENT_H);
			class VScrollbar {};
			class HScrollbar {};
			class Scrollbar {};
			class controls
			{
				class composeFrame: cTab_RscFrame
				{
					IDC_COUNTER
					text = "Compose Message"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_COMPOSE_FRAME_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_COMPOSE_FRAME_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_COMPOSE_FRAME_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_COMPOSE_FRAME_H);
				};
				class playerlistbox: cTab_RscListbox
				{
					idc = IDC_CTAB_MSG_RECIPIENTS;
					style = LB_MULTI;
					sizeEx = pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE * 0.8);
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_PLAYERLIST_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_PLAYERLIST_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_PLAYERLIST_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_PLAYERLIST_H);
				};
				class sendbtn: cTab_RscButton
				{
					idc = IDC_CTAB_MSG_BTNSEND;
					text = "Send"; //--- ToDo: Localize;
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_BUTTON_SEND_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_BUTTON_SEND_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_BUTTON_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_BUTTON_H);
					action = "call cTab_msg_Send;";
				};
				class edittxtbox: cTab_RscEdit
				{
					idc = IDC_CTAB_MSG_COMPOSE;
					htmlControl = true;
					style = ST_MULTI;
					lineSpacing = 0.2;
					text = ""; //--- ToDo: Localize;
					sizeEx = pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE);
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_COMPOSE_TEXT_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_COMPOSE_TEXT_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_COMPOSE_TEXT_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_COMPOSE_TEXT_H);
				};
				class toRead: cTab_RscButton
				{
					IDC_COUNTER
					text = "Read >>"; //--- ToDo: Localize;
					tooltip = "Read Messages";
					x = pxToGroup_X(cTab_GUI_android_MESSAGE_BUTTON_MODE_X);
					y = pxToGroup_Y(cTab_GUI_android_MESSAGE_BUTTON_MODE_Y);
					w = pxToScreen_W(cTab_GUI_android_MESSAGE_BUTTON_W);
					h = pxToScreen_H(cTab_GUI_android_MESSAGE_BUTTON_H);
					action = "['cTab_Android_dlg',[['mode','MESSAGE']]] call cTab_fnc_setSettings;";
				};
			};
		};

		/*
			### Overlays ###
		*/
		// ---------- NOTIFICATION ------------
		class notification: cTab_android_notification {};
		// ---------- LOADING ------------
		class loadingtxt: cTab_android_loadingtxt {};
		// ---------- BRIGHTNESS ------------
		class brightness: cTab_android_brightness {};
		// ---------- USER MARKERS ------------
		#include "\cTab\shared\cTab_markerMenu_controls.hpp"
		// ---------- BACKGROUND ------------
		class background: cTab_android_background {};
		// ---------- MOVING HANDLEs ------------
		class movingHandle_T: cTab_android_movingHandle_T{};
		class movingHandle_B: cTab_android_movingHandle_B{};
		class movingHandle_L: cTab_android_movingHandle_L{};
		class movingHandle_R: cTab_android_movingHandle_R{};

		/*
			### PHYSICAL BUTTONS ###
		*/
		class btnMenu: cTab_android_btnMenu
		{
			idc = IDC_CTAB_BTNFN;
			action = "['cTab_Android_dlg'] call cTab_fnc_showMenu_toggle;";
			tooltip = "Map Options";
		};
		class btnPower: cTab_android_btnPower
		{
			idc = IDC_CTAB_BTNOFF;
			action = "closeDialog 0;";
			tooltip = "Close Interface";
		};
		class btnHome: cTab_android_btnHome
		{
			idc = IDC_CTAB_BTNF1;
			action = "['cTab_Android_dlg'] call cTab_fnc_mode_toggle;";
			tooltip = "Toggle Map (F1) / Messages (F4)";
		};
	};
};
