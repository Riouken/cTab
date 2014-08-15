#define GUI_GRID_X	(safezoneX + (safezoneW - safezoneH * 0.8 * 3/4) / 2)
#define GUI_GRID_Y	(safezoneY + 0.1 * safezoneH)
#define GUI_GRID_W	(safezoneH * 0.8 * 3/4)
#define GUI_GRID_H	(safezoneH * 0.8)

#define cTab_TAD_DLGtoDSP_fctr (0.86 / GUI_GRID_H)

#include <cTab_TAD_dialog_controls.hpp>

#define MENU_GRID_X	(0)
#define MENU_GRID_Y	(0)
#define MENU_GRID_W	(0.025)
#define MENU_GRID_H	(0.04)

class cTab_TAD_dialog
{
	idd = 1755424;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_TAD_dialog', (_this select 0)];nul = [] execVM '\cTab\TAD\cTab_TAD_dialog_onload.sqf';";
	onUnload = "uiNamespace setVariable ['cTab_TAD_dialog', displayNull];call cTab_fnc_close;";
	objects[] = {};
	class controlsBackground
	{
		class mapBackground: cTab_TAD_Map_Background{};
		class screen: cTab_TAD_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			onDraw = "nop = [] call cTabOnDrawbftTADdialog;";
			onMouseButtonDblClick = "_ok = ['cTab_TAD_dialog',3300,1201,_this] execVM 'cTab\bft\userload.sqf';";
			onMouseButtonDown = "_ok = ['cTab_TAD_dialog',3300,1201,_this] spawn cTabDeleteUsrMkr;";
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
		class screenBlack: cTab_TAD_RscMapControl_BLACK
		{
			idc = IDC_CTAB_SCREEN_BLACK;
			onDraw = "nop = [] call cTabOnDrawbftTADdialog;";
			onMouseButtonDblClick = "_ok = ['cTab_TAD_dialog',3300,1201,_this] execVM 'cTab\bft\userload.sqf';";
			onMouseButtonDown = "_ok = ['cTab_TAD_dialog',3300,1201,_this] spawn cTabDeleteUsrMkr;";
		};
	};

	class controls
	{
		class background: cTab_TAD_Background{};
		class cursor: cTab_RscPicture
		{
			idc = -1;
			text = "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa";
				// "\a3\ui_f\data\map\Markers\Military\destroy_ca.paa";
				// "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa"
				// "\a3\ui_f\data\map\MarkerBrushes\cross_ca.paa"
			x = (cTab_GUI_TAD_MAP_X + cTab_GUI_TAD_MAP_W / 2 - 128 / 33 * cTab_GUI_TAD_CURSOR / 2) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_MAP_Y + cTab_GUI_TAD_MAP_H / 2 - 128 / 33 * cTab_GUI_TAD_CURSOR / 2) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = 128 / 33 * cTab_GUI_TAD_CURSOR / GUI_GRID_PX_W * GUI_GRID_W;
			h = 128 / 33 * cTab_GUI_TAD_CURSOR / GUI_GRID_PX_H * GUI_GRID_H;
			colorText[] = COLOR_NEON_GREEN;
		};
		class on_screen_mode: cTab_RscText_TAD
		{
			idc = 1204;
			x = (cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 4) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_EDGE_T) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 4 / GUI_GRID_PX_W * GUI_GRID_W;
			h = cTab_GUI_TAD_OSD_ELEMENT_MODE_H / GUI_GRID_PX_H * GUI_GRID_H;
			sizeEx = cTab_GUI_TAD_OSD_TEXT_MODE_SIZE / GUI_GRID_PX_H * GUI_GRID_H;
			text = "EXT1";
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
		class btnMapType: cTab_RscButton_TAD_OSB20
		{
			idc = -1;
			action = "call cTab_fnc_TAD_map_tggl;";
			tooltip = "Toggle Map Type";
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
		class on_screen_toggleIconText2: cTab_RscText_TAD
		{
			idc = IDC_CTAB_OSD_MAP_TGGL;
			x = (cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
			y = (cTab_GUI_TAD_OSD_OSB20_Y) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
			w = cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4 / GUI_GRID_PX_W * GUI_GRID_W;
		};


		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------

		class MainSubmenu: cTab_RscControlsGroup
		{
			idc = 3300;
			x = 12.5 * MENU_GRID_W + MENU_GRID_X;
			y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
			w = 5 * MENU_GRID_W;
			h = 5 * MENU_GRID_H;
			class controls
			{
				class mainbg: cTab_IGUIBack
				{
					idc = IDC_USRMN_MAINBG;
					x = 0;
					y = 0;
					w = 3 * MENU_GRID_W;
					h = 2 * MENU_GRID_H;
				};

				class op4btn: cTab_ActiveText
				{
					idc = IDC_USRMN_OP4BTN;
					text = "Enemy SALUTE"; //--- ToDo: Localize;
					x = 0;
					y = 0;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [4,cTabColorRed];Nop = [11,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};

				class medbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_MEDBTN;
					text = "Medical"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 1;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [4,cTabColorGreen];Nop = [21,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};

				class genbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_GENBTN;
					text = "General"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 2;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [4,cTabColorBlue];Nop = [31,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
			};
		};

		class EnemySub1: cTab_RscControlsGroup
		{
			idc = 3301;
			x = 12.5 * MENU_GRID_W + MENU_GRID_X;
			y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
			w = 5 * MENU_GRID_W;
			h = 5 * MENU_GRID_H;
			class controls
			{
				class IGUIBack_2201: cTab_IGUIBack
				{
					idc = IDC_USRMN_IGUIBACK_2202;
					x = 0;
					y = 0;
					w = 3.5 * MENU_GRID_W;
					h = 4.01389 * MENU_GRID_H;
				};

				class infbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_INFBTN;
					text = "Infantry"; //--- ToDo: Localize;
					x = 0;
					y = 0;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_inf.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";

				};
				class mecinfbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_MECINFBTN;
					text = "Mec Inf"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 1;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_mech_inf.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};

				class motrinfbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_MOTRINFBTN;
					text = "Motr Inf"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 2;
					w = 2.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_motor_inf.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class amrbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_AMRBTN;
					text = "Armor"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 3;
					w = 2.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_armor.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class helibtn: cTab_ActiveText
				{
					idc = IDC_USRMN_HELIBTN;
					text = "Helicopter"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 4;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_air.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class plnbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_PLNBTN;
					text = "Plane"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 5;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_plane.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class uknbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_UKNBTN;
					text = "Unknown"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 6;
					w = 3.45833 * MENU_GRID_W;
					h = 0.430556 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_unknown.paa'];Nop = [12,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
			};
		};


		class EnemySub2: cTab_RscControlsGroup
		{
			idc = 3303;
			x = 12.5 * MENU_GRID_W + MENU_GRID_X;
			y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
			w = 5 * MENU_GRID_W;
			h = 5 * MENU_GRID_H;
			class controls
			{

				class IGUIBack_2202: cTab_IGUIBack
				{
					idc = IDC_USRMN_IGUIBACK_2202;
					x = 0;
					y = 0;
					w = 2.9375 * MENU_GRID_W;
					h = 4.01389 * MENU_GRID_H;
				};
				class ftbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_FTBTN;
					text = "Fire Team"; //--- ToDo: Localize;
					x = 0;
					y = 0;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class patbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_PATBTN;
					text = "Patrol"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 1;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class sqdbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_SQDBTN;
					text = "Squad"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 2;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_1.paa'];Nop = [13,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class sctbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_SCTBTN;
					text = "Section"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 3;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_2.paa'];Nop = [13,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class pltnbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_PLTNBTN;
					text = "Platoon"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 4;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_3.paa'];Nop = [13,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class cpnybtn: cTab_ActiveText
				{
					idc = IDC_USRMN_CPNYBTN;
					text = "Company"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 5;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_4.paa'];Nop = [13,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
			};
		};


		class EnemySub3: cTab_RscControlsGroup
		{
			idc = 3304;
			x = 12.5 * MENU_GRID_W + MENU_GRID_X;
			y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
			w = 5 * MENU_GRID_W;
			h = 7 * MENU_GRID_H;
			class controls
			{

				class IGUIBack_2203: cTab_IGUIBack
				{
					idc = IDC_USRMN_IGUIBACK_2203;
					x = 0;
					y = 0;
					w = 2.10417 * MENU_GRID_W;
					h = 6.72685 * MENU_GRID_H;
				};

				class nthbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_NTHBTN;
					text = "N"; //--- ToDo: Localize;
					x = 0;
					y = 0;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,0];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class nebtn: cTab_ActiveText
				{
					idc = IDC_USRMN_NEBTN;
					text = "NE"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 1;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,45];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class ebtn: cTab_ActiveText
				{
					idc = IDC_USRMN_EBTN;
					text = "E"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 2;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,90];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class sebtn: cTab_ActiveText
				{
					idc = IDC_USRMN_SEBTN;
					text = "SE"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 3;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,135];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class sbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_SBTN;
					text = "S"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 4;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,180];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class swbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_SWBTN;
					text = "SW"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 5;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,225];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class wbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_WBTN;
					text = "W"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 6;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,270];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class RscText_1022: cTab_ActiveText
				{
					idc = IDC_USRMN_RSCTEXT_1022;
					text = "NW"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 7;
					w = 1.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,315];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class RscText_1023: cTab_ActiveText
				{
					idc = IDC_USRMN_RSCTEXT_1023;
					text = "Unknown"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 8;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,500];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};

				class stnbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_STNBTN;
					text = "Stationary"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 9;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [3,700];nop = [] call cTabUserIconPush;Nop = [10,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};


			};
		};




		class CasulSub1: cTab_RscControlsGroup
		{
			idc = 3305;
			x = 12.5 * MENU_GRID_W + MENU_GRID_X;
			y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
			w = 5 * MENU_GRID_W;
			h = 5 * MENU_GRID_H;
			class controls
			{

				class IGUIBack_2204: cTab_IGUIBack
				{
					idc = IDC_USRMN_IGUIBACK_2204;
					x = 0;
					y = 0;
					w = 2.77083 * MENU_GRID_W;
					h = 2.70833 * MENU_GRID_H;
				};
				class casltybtn: cTab_ActiveText
				{
					idc = IDC_USRMN_CASLTYBTN;
					text = "Casualty"; //--- ToDo: Localize;
					x = 0;
					y = 0;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\join_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class ccpbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_CCPBTN;
					text = "CCP"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 1;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\circle_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class basbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_BASBTN;
					text = "BAS"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 2;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\mapcontrol\Hospital_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};

				class mcibtn: cTab_ActiveText
				{
					idc = IDC_USRMN_MCIBTN;
					text = "MCI"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 3;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\warning_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
			};
		};

		class GenSub1: cTab_RscControlsGroup
		{
			idc = 3306;
			x = 12.5 * MENU_GRID_W + MENU_GRID_X;
			y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
			w = 5 * MENU_GRID_W;
			h = 5 * MENU_GRID_H;
			class controls
			{

				class IGUIBack_2205: cTab_IGUIBack
				{
					idc = IDC_USRMN_IGUIBACK_2205;
					x = 0;
					y = 0;
					w = 2.5 * MENU_GRID_W;
					h = 1.5 * MENU_GRID_H;
				};


				class hqbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_HQBTN;
					text = "Headquarters"; //--- ToDo: Localize;
					x = 0;
					y = 0;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\b_hq.paa'];nop = [] call cTabUserIconPush;Nop = [30,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
				class lzbtn: cTab_ActiveText
				{
					idc = IDC_USRMN_LZBTN;
					text = "LZ"; //--- ToDo: Localize;
					x = 0;
					y = (0.5 * MENU_GRID_H) * 1;
					w = 3.5 * MENU_GRID_W;
					h = 0.5 * MENU_GRID_H;
					sizeEx = .5 * MENU_GRID_H;
					action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\end_CA.paa'];nop = [] call cTabUserIconPush;Nop = [30,'cTab_TAD_dialog'] call cTabUsrMenuSelect;";
				};
			};
		};
	};
};
