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
				text = "#(argb,8,8,3)color(1,1,1,1)";
				x = cTab_GUI_microDAGR_MAP_X / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
				y = cTab_GUI_microDAGR_MAP_Y / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
				w = cTab_GUI_microDAGR_MAP_W / GUI_GRID_PX_W * GUI_GRID_W;
				h = cTab_GUI_microDAGR_MAP_H / GUI_GRID_PX_H * GUI_GRID_H;
				onDraw = "nop = [] call cTabOnDrawbftMicroDAGRdlg;";
				//onMouseButtonDblClick = "_ok = ['cTab_microDAGR_dialog',3300,1201,_this] execVM 'cTab\bft\userload.sqf';";
				//onMouseButtonDown = "_ok = ['cTab_microDAGR_dialog',3300,1201,_this] spawn cTabDeleteUsrMkr;";
				// set initial map scale
				//scaleDefault = "(missionNamespace getVariable 'cTabmicroDAGRmapScale') / (missionNamespace getVariable 'cTabMapScaleFactor') * 0.86 / (safezoneH * 0.8)";
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
			x = (cTab_GUI_microDAGR_MAP_X + cTab_GUI_microDAGR_MAP_W / 2 - 128 / 33 * cTab_GUI_microDAGR_CURSOR / 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_microDAGR_MAP_Y + cTab_GUI_microDAGR_MAP_H / 2 - 128 / 33 * cTab_GUI_microDAGR_CURSOR / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = 128 / 33 * cTab_GUI_microDAGR_CURSOR / GUI_GRID_PX_W * GUI_GRID_W;
			h = 128 / 33 * cTab_GUI_microDAGR_CURSOR / GUI_GRID_PX_H * GUI_GRID_H;
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
