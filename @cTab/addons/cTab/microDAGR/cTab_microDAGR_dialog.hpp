#define GUI_GRID_X	(safezoneX + (safezoneW - safezoneH * 0.8 * 3/4) / 2)
#define GUI_GRID_Y	(safezoneY + 0.1 * safezoneH)
#define GUI_GRID_W	(safezoneH * 0.8 * 3/4)
#define GUI_GRID_H	(safezoneH * 0.8)

#define cTab_microDAGR_DLGtoDSP_fctr (0.86 / GUI_GRID_H)

#include <cTab_microDAGR_controls.hpp>

#define MENU_GRID_X	(0)
#define MENU_GRID_Y	(0)
#define MENU_GRID_W	(0.025)
#define MENU_GRID_H	(0.04)

class cTab_microDAGR_dlg
{
	idd = 1776134;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_microDAGR_dlg', (_this select 0)];nul = [] execVM '\cTab\microDAGR\cTab_microDAGR_dialog_onload.sqf';";
	onUnload = "uiNamespace setVariable ['cTab_microDAGR_dlg', displayNull];call cTab_fnc_close;";
	objects[] = {};
	class controlsBackground
	{
			class screen: cTab_microDAGR_RscMapControl
			{
				idc = IDC_CTAB_SCREEN;
				onDraw = "nop = [] call cTabOnDrawbftMicroDAGRdlg;";
				// set initial map scale
				scaleDefault = "(missionNamespace getVariable 'cTabMicroDAGRmapScaleCtrl') * 0.86 / (safezoneH * 0.8)";
			};
			class screenTopo: screen
			{
				idc = IDC_CTAB_SCREEN_TOPO;
				maxSatelliteAlpha = 0;
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
		class cursor: cTab_RscPicture
		{
			idc = -1;
			text = "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa";
				// "\a3\ui_f\data\map\Markers\Military\destroy_ca.paa";
				// "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa"
				// "\a3\ui_f\data\map\MarkerBrushes\cross_ca.paa"
			x = pxToScreen_X(cTab_GUI_microDAGR_MAP_X + cTab_GUI_microDAGR_MAP_W / 2 - 128 / 33 * cTab_GUI_microDAGR_CURSOR / 2);
			y = pxToScreen_Y(cTab_GUI_microDAGR_MAP_Y + cTab_GUI_microDAGR_MAP_H / 2 - 128 / 33 * cTab_GUI_microDAGR_CURSOR / 2);
			w = pxToScreen_W(128 / 33 * cTab_GUI_microDAGR_CURSOR);
			h = pxToScreen_H(128 / 33 * cTab_GUI_microDAGR_CURSOR);
			colorText[] = COLOR_NEON_GREEN;
		};
		*/
		class pwrbtn: cTab_RscButton_microDAGR_LeftBtn
		{
			idc = IDC_CTAB_BTNMAIN;
			action = "closeDialog 0;";
			tooltip = "Close Interface";
		};
		class btnbrtpls: cTab_RscButton_microDAGR_RightUp
		{
			idc = IDC_CTAB_BTNUP;
			action = "call cTab_fnc_txt_size_inc;";
			tooltip = "Increase Font";
		};
		class btnbrtmns: cTab_RscButton_microDAGR_RightDown
		{
			idc = IDC_CTAB_BTNDWN;
			action = "call cTab_fnc_txt_size_dec;";
			tooltip = "Decrease Font";
		};
		class btnfunction: cTab_RscButton_microDAGR_RightBtn
		{
			idc = IDC_CTAB_BTNFN;
			action = "call cTab_fnc_txt_tggl;";
			tooltip = "Toggle Text on/off";
		};
		class btnMapType: cTab_RscButton_microDAGR_LeftUp
		{
			idc = -1;
			action = "call cTab_fnc_map_tggl;";
			tooltip = "Toggle Map Type";
		};
		/*
		class on_screen_time: cTab_RscText_microDAGR
		{
			idc = IDC_CTAB_OSD_TIME;
			x = pxToScreen_X(cTab_GUI_microDAGR_OSD_EDGE_L);
			y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H);
			w = pxToScreen_W(cTab_GUI_microDAGR_OSD_ELEMENT_STD_W * 5);
		};
		class on_screen_current_grid: cTab_RscText_microDAGR
		{
			idc = IDC_CTAB_OSD_GRID;
			x = pxToScreen_X(cTab_GUI_microDAGR_OSD_OSB13_X - cTab_GUI_microDAGR_OSD_ELEMENT_STD_W * 6 / 2);
			y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H * 2);
			w = pxToScreen_W(cTab_GUI_microDAGR_OSD_ELEMENT_STD_W * 6);
		};
		*/
	};
};
