#define GUI_MARGIN_X	(0.05)
#define GUI_MARGIN_Y	(0.2)
#define GUI_TAD_W	(0.86)
#define GUI_TAD_H	(0.86)

#define cTab_TAD_DLGtoDSP_fctr (1)

#define GUI_GRID_X	(safeZoneX + GUI_MARGIN_X * 3/4)
#define GUI_GRID_Y	(safeZoneY + safeZoneH - GUI_TAD_H - GUI_MARGIN_Y)
#define GUI_GRID_W	(GUI_TAD_W * 3/4)
#define GUI_GRID_H	(GUI_TAD_H)

#include <cTab_TAD_controls.hpp>

class cTab_TAD_dsp
{
	idd = 1775134;
	movingEnable = true;
	duration = 10e10;
	fadeIn = 0;
	fadeOut = 0;
	onLoad = "((_this select 0) displayCtrl 1200) ctrlSetText ('cTab_TAD_dsp' call cTab_fnc_getBackground);uiNamespace setVariable ['cTab_TAD_dsp', (_this select 0)];";
	class controlsBackground
	{
		class mapBackground: cTab_TAD_Map_Background{};
		class screen: cTab_TAD_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			onDraw = "nop = _this call cTabOnDrawbftTAD;";
			// set initial map scale
			scaleDefault = "missionNamespace getVariable 'cTabMapScale'";
			// hide grid lines
			colorGrid[] = {0.1,0.1,0.1,0};
			colorGridMap[] = {0.1,0.1,0.1,0};
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
		class screenBlack: cTab_TAD_RscMapControl_BLACK
		{
			idc = IDC_CTAB_SCREEN_BLACK;
			onDraw = "nop = _this call cTabOnDrawbftTAD;";
			// set initial map scale
			scaleDefault = "missionNamespace getVariable 'cTabMapScale'";
			// hide grid lines
			colorGrid[] = {0.1,0.1,0.1,0};
			colorGridMap[] = {0.1,0.1,0.1,0};
		};
	};

	class controls
	{
		/*
			### OSD GUI controls ###
		*/
		class on_screen_mode: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_MAP_SCALE;
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 2);
			y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_T);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 2);
			h = pxToScreen_H(cTab_GUI_TAD_OSD_ELEMENT_MODE_H);
			sizeEx = pxToScreen_H(cTab_GUI_TAD_OSD_TEXT_MODE_SIZE);
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
		class hookToggleIconBackground: cTab_TAD_on_screen_hookToggleIconBackground {};
		class hookToggleIcon: cTab_TAD_on_screen_hookToggleIcon {};
		class hookToggleText1: cTab_TAD_on_screen_hookToggleText1 {};
		class hookToggleText2: cTab_TAD_on_screen_hookToggleText2 {};
		class on_screen_currentDirection: cTab_TAD_on_screen_currentDirection {};
		class on_screen_currentElevation: cTab_TAD_on_screen_currentElevation {};
		class on_screen_centerMapText: cTab_TAD_on_screen_centerMapText {};

		/*
			### Overlays ###
		*/
		// ---------- LOADING ------------
		class loadingtxt: cTab_TAD_loadingtxt {};
		// ---------- BRIGHTNESS ------------
		class brightness: cTab_TAD_brightness {};
		// ---------- BACKGROUND ------------
		class background: cTab_TAD_background{};
	};
};