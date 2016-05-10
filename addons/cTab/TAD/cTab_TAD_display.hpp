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
	onLoad = "_this call cTab_fnc_onIfOpen;";
	class controlsBackground
	{
		class mapBackground: cTab_TAD_Map_Background {};
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
		class navModeOrScale: cTab_TAD_OSD_navModeOrScale
		{
			x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 2);
			w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 2);
		};
		class modeTAD: cTab_TAD_OSD_modeTAD {};
		class txtToggleIconBg: cTab_TAD_OSD_txtToggleIconBg {};
		class txtToggleIcon: cTab_TAD_OSD_txtToggleIcon {};
		class txtToggleText1: cTab_TAD_OSD_txtToggleText1 {};
		class txtToggleText2: cTab_TAD_OSD_txtToggleText2 {};
		class time: cTab_TAD_OSD_time {};
		class currentGrid: cTab_TAD_OSD_currentGrid {};
		class mapToggleIconBg: cTab_TAD_OSD_mapToggleIconBg {};
		class mapToggleIcon: cTab_TAD_OSD_mapToggleIcon {};
		class mapToggleText1: cTab_TAD_OSD_mapToggleText1 {};
		class mapToggleText2: cTab_TAD_OSD_mapToggleText2 {};
		class hookToggleIconBackground: cTab_TAD_OSD_hookToggleIconBackground {};
		class hookToggleIcon: cTab_TAD_OSD_hookToggleIcon {};
		class hookToggleText1: cTab_TAD_OSD_hookToggleText1 {};
		class hookToggleText2: cTab_TAD_OSD_hookToggleText2 {};
		class on_screen_currentDirection: cTab_TAD_OSD_currentDirection {};
		class on_screen_currentElevation: cTab_TAD_OSD_currentElevation {};
		class on_screen_centerMapText: cTab_TAD_OSD_centerMapText {};

		/*
			### Overlays ###
		*/
		// ---------- NOTIFICATION ------------
		class notification: cTab_TAD_notification {};
		// ---------- LOADING ------------
		class loadingtxt: cTab_TAD_loadingtxt {};
		// ---------- BRIGHTNESS ------------
		class brightness: cTab_TAD_brightness {};
		// ---------- BACKGROUND ------------
		class background: cTab_TAD_background {};
	};
};