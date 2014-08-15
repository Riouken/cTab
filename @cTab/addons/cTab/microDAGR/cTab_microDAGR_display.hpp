#define GUI_MARGIN_X	(0.05)
#define GUI_MARGIN_Y	(0.2)
#define GUI_MAP_W	(0.55)
#define GUI_MAP_H	(0.5625)
#define GUI_SCREEN_Y_OFFSET	(0.0085)
#define GUI_microDAGR_W	(0.86)
#define GUI_microDAGR_H	(0.86)

#define cTab_microDAGR_DLGtoDSP_fctr (1)

#define GUI_GRID_X	(safeZoneX + GUI_MARGIN_X * 3/4)
#define GUI_GRID_Y	(safeZoneY + safeZoneH - GUI_microDAGR_H - GUI_MARGIN_Y)
#define GUI_GRID_W	(GUI_microDAGR_W * 3/4)
#define GUI_GRID_H	(GUI_microDAGR_H)

#include <cTab_microDAGR_controls.hpp>

class cTab_microDAGR_dsp
{
	idd = 1776134;
	movingEnable = true;
	duration = 10e10;
	fadeIn = 0;
	fadeOut = 0;
	onLoad = "uiNamespace setVariable ['cTab_microDAGR_dsp', (_this select 0)];";
	class controlsBackground
	{
		class screen: cTab_microDAGR_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = cTab_GUI_microDAGR_MAP_X / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = cTab_GUI_microDAGR_MAP_Y / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_microDAGR_MAP_W / GUI_GRID_PX_W * GUI_GRID_W;
			h = cTab_GUI_microDAGR_MAP_H / GUI_GRID_PX_H * GUI_GRID_H;
			onDraw = "nop = [] call cTabOnDrawbftmicroDAGRdsp;";
			// set initial map scale
			//scaleDefault = "(missionNamespace getVariable 'cTabmicroDAGRmapScale') / (missionNamespace getVariable 'cTabMapScaleFactor')";
			// hide grid lines
			//colorGrid[] = {0.1,0.1,0.1,0};
			//colorGridMap[] = {0.1,0.1,0.1,0};
		};
	};

	class controls
	{
		class background: cTab_RscPicture
		{
			idc = IDC_CTAB_BACKGROUND;
			text = "\cTab\img\microDAGR_background_ca.paa";
			x = GUI_GRID_X;
			y = GUI_GRID_Y;
			w = GUI_GRID_W;
			h = GUI_GRID_H;
		};
		/*
		class on_screen_time: cTab_RscText_microDAGR
		{
			idc = 1202;
			x = (cTab_GUI_microDAGR_OSD_EDGE_L) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_microDAGR_OSD_ELEMENT_STD_W * 5 / GUI_GRID_PX_W * GUI_GRID_W;
		};
		class on_screen_current_grid: cTab_RscText_microDAGR
		{
			idc = 1203;
			x = (cTab_GUI_microDAGR_OSD_OSB13_X - cTab_GUI_microDAGR_OSD_ELEMENT_STD_W * 6 / 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H * 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_microDAGR_OSD_ELEMENT_STD_W * 6 / GUI_GRID_PX_W * GUI_GRID_W;
		};
		*/
	};
};
