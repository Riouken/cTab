#define GUI_GRID_X	(safezoneX + (safezoneW - safezoneH * 0.8 * 3/4) / 2)
#define GUI_GRID_Y	(safezoneY + 0.1 * safezoneH)
#define GUI_GRID_W	(safezoneH * 0.8 * 3/4)
#define GUI_GRID_H	(safezoneH * 0.8)

#define cTab_TAD_DLGtoDSP_fctr (0.86 / GUI_GRID_H)

#include <cTab_TAD_controls.hpp>

#define MENU_sizeEx pxToScreen_H(cTab_GUI_TAD_OSD_TEXT_STD_SIZE)
#include "\cTab\shared\cTab_markerMenu_macros.hpp"

class cTab_TAD_dlg
{
	idd = 1755424;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_TAD_dlg', (_this select 0)];";
	onUnload = "uiNamespace setVariable ['cTab_TAD_dlg', displayNull];call cTab_fnc_close;";
	onKeyDown = "_this call cTab_fnc_onIfKeyDown;";
	objects[] = {};
	class controlsBackground
	{
		class mapBackground: cTab_TAD_Map_Background{};
		class screen: cTab_TAD_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			onDraw = "nop = _this call cTabOnDrawbftTADdialog;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM '\cTab\shared\cTab_markerMenu_load.sqf';";
			onMouseMoving = "cTabCursorOnMap = _this select 3;cTabMapCursorPos = _this select 0 ctrlMapScreenToWorld [_this select 1,_this select 2];";
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
		class screenBlack: cTab_TAD_RscMapControl_BLACK
		{
			idc = IDC_CTAB_SCREEN_BLACK;
			onDraw = "nop = _this call cTabOnDrawbftTADdialog;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM '\cTab\shared\cTab_markerMenu_load.sqf';";
			onMouseMoving = "cTabCursorOnMap = _this select 3;cTabMapCursorPos = _this select 0 ctrlMapScreenToWorld [_this select 1,_this select 2];";
		};
	};

	class controls
	{
		class background: cTab_TAD_Background{};
		class movingHandle_T: cTab_TAD_movingHandle_T{};
		class movingHandle_B: cTab_TAD_movingHandle_B{};
		class movingHandle_L: cTab_TAD_movingHandle_L{};
		class movingHandle_R: cTab_TAD_movingHandle_R{};
		class on_screen_mode: cTab_RscText_TAD
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 4);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_T);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 4);
			h = pxToScreen_H(cTab_GUI_TAD_OSD_ELEMENT_MODE_H);
			sizeEx = pxToScreen_H(cTab_GUI_TAD_OSD_TEXT_MODE_SIZE);
			text = "EXT1";
		};
		class mode_TAD: cTab_RscText_TAD
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB15_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / 2);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
			colorText[] = COLOR_BLACK;
			colorBackground[] = COLOR_NEON_GREEN;
			text = "TAD";
		};
		class pwrbtn: cTab_RscButton_TAD_DNO
		{
			idc = IDC_CTAB_BTNMAIN;
			action = "closeDialog 0;";
			tooltip = "Close Interface";
		};
		class btnbrtpls: cTab_RscButton_TAD_SYM_INC
		{
			idc = IDC_CTAB_BTNUP;
			action = "call cTab_fnc_txt_size_inc;";
			tooltip = "Increase Font";
		};
		class btnbrtmns: cTab_RscButton_TAD_SYM_DEC
		{
			idc = IDC_CTAB_BTNDWN;
			action = "call cTab_fnc_txt_size_dec;";
			tooltip = "Decrease Font";
		};
		class btnfunction: cTab_RscButton_TAD_OSB10
		{
			idc = IDC_CTAB_BTNFN;
			action = "['cTab_TAD_dlg'] call cTab_fnc_iconText_toggle;";
			tooltip = "Toggle Text on/off";
		};
		class on_screen_toggleIconBackground: cTab_RscText_TAD
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2);
		};
		class on_screen_toggleIcon: cTab_TAD_upDownArrow
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ICON_H / 2);
		};
		class on_screen_toggleText1: cTab_RscText_TAD
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
			text = "TXT";
		};
		class on_screen_toggleText2: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_TXT_TGGL;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
		};
		class on_screen_time: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_TIME;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 5);
		};
		class on_screen_current_grid: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_GRID;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB13_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6 / 2);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 2);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6);
		};
		class btnMapType: cTab_RscButton_TAD_OSB20
		{
			idc = -1;
			action = "['cTab_TAD_dlg'] call cTab_fnc_mapType_toggle;";
			tooltip = "Toggle Map Type (F6)";
		};
		class on_screen_toggleMapIconBackground: cTab_RscText_TAD
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2);
		};
		class on_screen_toggleMapIcon: cTab_TAD_upDownArrow
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ICON_H / 2);
		};
		class on_screen_toggleMapText1: cTab_RscText_TAD
		{
			idc = -1;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
			text = "MAP";
		};
		class on_screen_toggleMapText2: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_MAP_TGGL;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4);
		};
		class hookGrid: cTab_TAD_on_screen_hookGrid {};
		class hookElevation: cTab_TAD_on_screen_hookElevation {};
		class hookDir: cTab_TAD_on_screen_hookDir {};
		class hookToggleIconBackground: cTab_TAD_on_screen_hookToggleIconBackground {};
		class hookToggleIcon: cTab_TAD_on_screen_hookToggleIcon {};
		class hookToggleText1: cTab_TAD_on_screen_hookToggleText1 {};
		class hookToggleText2: cTab_TAD_on_screen_hookToggleText2 {};
		class btnMapTools: cTab_RscButton_TAD_OSB18
		{
			idc = -1;
			action = "['cTab_TAD_dlg'] call cTab_fnc_toggleMapTools;";
			tooltip = "Toggle Map Tools (F5)";
		};
		class on_screen_currentDirection: cTab_TAD_on_screen_currentDirection {};
		class on_screen_currentElevation: cTab_TAD_on_screen_currentElevation {};
		class btnF7: cTab_RscButton_TAD_OSB19
		{
			idc = -1;
			action = "['cTab_TAD_dlg'] call cTab_fnc_centerMapOnPlayerPosition;";
			tooltip = "Center Map On Current Position (F7)";
		};
		class on_screen_centerMapText: cTab_TAD_on_screen_centerMapText {};

		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------
		#include "\cTab\shared\cTab_markerMenu_controls.hpp"

		// ---------- LOADING ------------
		class loadingtxt: cTab_TAD_loadingtxt {};
	};
};
