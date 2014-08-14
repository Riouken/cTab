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
		class screen: cTab_TAD_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = cTab_GUI_TAD_MAP_X / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = cTab_GUI_TAD_MAP_Y / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_MAP_W / GUI_GRID_PX_W * GUI_GRID_W;
			h = cTab_GUI_TAD_MAP_H / GUI_GRID_PX_H * GUI_GRID_H;
			onDraw = "nop = [] call cTabOnDrawbftTAD;";
			onMouseButtonDblClick = "_ok = ['cTab_TAD_dialog',3300,1201,_this] execVM 'cTab\bft\userload.sqf';";
			// set initial map scale
			scaleDefault = "(missionNamespace getVariable 'cTabTADmapScale') / (missionNamespace getVariable 'cTabMapScaleFactor')";
			// hide grid lines
			colorGrid[] = {0.1,0.1,0.1,0};
			colorGridMap[] = {0.1,0.1,0.1,0};
		};
	};

	class controls
	{
		class background: cTab_RscPicture
		{
			idc = IDC_CTAB_BACKGROUND;
			text = "\cTab\img\TAD_background_ca.paa";
			x = GUI_GRID_X;
			y = GUI_GRID_Y;
			w = GUI_GRID_W;
			h = GUI_GRID_H;
		};
		class on_screen_mode: cTab_RscText_TAD
		{
			idc = 1204;
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
		class btnesc: cTab_RscButton_TAD_OSB09
		{
			idc = IDC_CTAB_BTNACT;
			action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
			tooltip = "Delete last user placed icon";
		};
		class on_screen_delete: cTab_RscText_TAD
		{
			idc = -1;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB09_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / GUI_GRID_PX_W * GUI_GRID_W;
			text = "DEL";
		};
		class btnfunction: cTab_RscButton_TAD_OSB10
		{
			idc = IDC_CTAB_BTNFN;
			action = "call cTab_fnc_txt_tggl;";
			tooltip = "Toggle Text on/off";
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
			idc = 1202;
			x = (cTab_GUI_TAD_OSD_EDGE_L) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 5 / GUI_GRID_PX_W * GUI_GRID_W;
		};
		class on_screen_current_grid: cTab_RscText_TAD
		{
			idc = 1203;
			x = (cTab_GUI_TAD_OSD_OSB13_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6 / 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6 / GUI_GRID_PX_W * GUI_GRID_W;
		};
	};
};

	/*
	class controlsBackground
	{
		class screen: cTab_TAD_RscMapControl
		{
			idc = 1201;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = safeZoneX + (GUI_MARGIN_X + ((GUI_TAD_W - GUI_MAP_W) / 2)) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MARGIN_Y - ((GUI_TAD_H - GUI_MAP_H) / 2) - GUI_MAP_H + GUI_SCREEN_Y_OFFSET;
			w = GUI_MAP_W * 3/4;
			h = GUI_MAP_H;
			// set initial map scale
			scaleDefault = "(missionNamespace getVariable 'cTabTADmapScale') / (missionNamespace getVariable 'cTabMapScaleFactor')";
			// Continuously call cTabOnDrawbftTAD to draw cTab's icons on map
			onDraw = "nop = [] call cTabOnDrawbftTAD;";

			// hide grid lines
			colorGrid[] = {0.1,0.1,0.1,0};
			colorGridMap[] = {0.1,0.1,0.1,0};
		};
	};

	class controls
	{
		class background: cTab_RscPicture
		{
			idc = 1200;
			text = "\cTab\img\TAD_background_ca.paa";
			x = safeZoneX + GUI_MARGIN_X * 3/4;
			y = safeZoneY + safeZoneH - GUI_TAD_H - GUI_MARGIN_Y;
			w = GUI_TAD_W * 3/4;
			h = GUI_TAD_H;
		};

		// showing TAD as SOI (sensor of interest)
		class box: cTab_RscPicture {
			x = safeZoneX + (GUI_MARGIN_X + 0.015 + ((GUI_TAD_W - GUI_MAP_W) / 2)) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MAP_H - GUI_MARGIN_Y - ((GUI_TAD_H - GUI_MAP_H) / 2) + 0.015;
			w = (GUI_MAP_W - 0.015 * 2) * 3/4;
			h = GUI_MAP_H - 0.015 * 2;
			colorText[] = {57/255, 1, 20/255, 1};
			shadow = 1;
			text = "\cTab\img\TAD_soi_ca.paa";
		};

		class time: cTab_RscText {
			idc = 1202;
			style = "0x01"; // align right
			x = safeZoneX + (GUI_MARGIN_X + GUI_MAP_W + ((GUI_TAD_W - GUI_MAP_W) / 2) - 0.08 - 0.015) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MARGIN_Y - ((GUI_TAD_H - GUI_MAP_H) / 2) - 0.03 - 0.015 + GUI_SCREEN_Y_OFFSET;
			w = 0.08 * 3/4;
			h = 0.03;
			colorText[] = {57/255, 1, 20/255, 1};
			sizeEx = 0.025;
			colorBackground[] = {0,0,0,1};
			shadow = 0;
		};
		class grid: cTab_RscText {
			idc = 1203;
			style = "0x02"; // align centre
			x = safeZoneX + (GUI_MARGIN_X + ((GUI_TAD_W - 0.1) / 2)) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MARGIN_Y - ((GUI_TAD_H - GUI_MAP_H) / 2) - 0.03 - 0.015 + GUI_SCREEN_Y_OFFSET;
			w = 0.1 * 3/4;
			h = 0.03;
			colorText[] = {57/255, 1, 20/255, 1};
			sizeEx = 0.025;
			colorBackground[] = {0,0,0,1};
			shadow = 0;
		};
		class scale: cTab_RscText {
			idc = 1204;
			style = "0x01"; // align right
			x = safeZoneX + (GUI_MARGIN_X + GUI_MAP_W + ((GUI_TAD_W - GUI_MAP_W) / 2) - 0.06 - 0.015) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MARGIN_Y - ((GUI_TAD_H - GUI_MAP_H) / 2) - GUI_MAP_H + 0.015 + GUI_SCREEN_Y_OFFSET;
			w = 0.06 * 3/4;
			h = 0.04;
			colorText[] = {57/255, 1, 20/255, 1};
			sizeEx = 0.04;
			colorBackground[] = {0,0,0,1};
			shadow = 0;
		};
	};
	*/
