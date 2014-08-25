#define GUI_MARGIN_X	(0.05)
#define GUI_MARGIN_Y	(0.2)
#define GUI_MAP_W	(0.55)
#define GUI_MAP_H	(0.5625)
#define GUI_SCREEN_Y_OFFSET	(0.0085)
#define GUI_TAD_W	(0.86)
#define GUI_TAD_H	(0.86)

#define cTab_TAD_DLGtoDSP_fctr (1)

#define GUI_GRID_X	(safeZoneX + GUI_MARGIN_X * 3/4)
#define GUI_GRID_Y	(safeZoneY + safeZoneH - GUI_TAD_H - GUI_MARGIN_Y)
#define GUI_GRID_W	(GUI_TAD_W * 3/4)
#define GUI_GRID_H	(GUI_TAD_H)

#include <cTab_TAD_dialog_controls.hpp>

class cTab_TAD_dsp
{
	idd = 1775134;
	movingEnable = true;
	duration = 10e10;
	fadeIn = 0;
	fadeOut = 0;
	onLoad = "uiNamespace setVariable ['cTab_TAD_dsp', (_this select 0)];";
	class controlsBackground
	{
		class mapBackground: cTab_TAD_Map_Background{};
		class screen: cTab_TAD_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			onDraw = "nop = [] call cTabOnDrawbftTAD;";
			// set initial map scale
			scaleDefault = "missionNamespace getVariable 'cTabTADmapScaleCtrl'";
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
			onDraw = "nop = [] call cTabOnDrawbftTAD;";
			// set initial map scale
			scaleDefault = "missionNamespace getVariable 'cTabTADmapScaleCtrl'";
			// hide grid lines
			colorGrid[] = {0.1,0.1,0.1,0};
			colorGridMap[] = {0.1,0.1,0.1,0};
		};
	};

	class controls
	{
		class background: cTab_TAD_Background{};
		class on_screen_mode: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_MAP_SCALE;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_T) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 2 / GUI_GRID_PX_W * GUI_GRID_W;
			h = cTab_GUI_TAD_OSD_ELEMENT_MODE_H / GUI_GRID_PX_H * GUI_GRID_H;
			sizeEx = cTab_GUI_TAD_OSD_TEXT_MODE_SIZE / GUI_GRID_PX_H * GUI_GRID_H;
		};
		class mode_TAD: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_OSB15_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / GUI_GRID_PX_W * GUI_GRID_W;
			colorText[] = COLOR_BLACK;
			colorBackground[] = COLOR_NEON_GREEN;
			text = "TAD";
		};
		class on_screen_delete: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB09_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / GUI_GRID_PX_W * GUI_GRID_W;
			text = "DEL";
		};
		class on_screen_toggleIconBackground: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
		};
		class on_screen_toggleIcon: cTab_TAD_upDownArrow
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ICON_H / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
		};
		class on_screen_toggleText1: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / GUI_GRID_PX_W * GUI_GRID_W;
			text = "TXT";
		};
		class on_screen_toggleText2: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_TXT_TGGL;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB10_Y) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / GUI_GRID_PX_W * GUI_GRID_W;
		};
		class on_screen_time: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_TIME;
			x = (cTab_GUI_TAD_OSD_EDGE_L) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 5 / GUI_GRID_PX_W * GUI_GRID_W;
		};
		class on_screen_current_grid: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_GRID;
			x = (cTab_GUI_TAD_OSD_OSB13_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6 / 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6 / GUI_GRID_PX_W * GUI_GRID_W;
		};
		class on_screen_toggleMapIconBackground: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
		};
		class on_screen_toggleMapIcon: cTab_TAD_upDownArrow
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ICON_H / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
		};
		class on_screen_toggleMapText1: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / GUI_GRID_PX_W * GUI_GRID_W;
			text = "MAP";
		};
		class on_screen_toggleMapText2: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_MAP_TGGL;
			x = (cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB20_Y) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4 / GUI_GRID_PX_W * GUI_GRID_W;
		};
	};
};
