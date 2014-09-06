#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.025)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)

#define MENU_sizeEx GUI_GRID_H
#include <\cTab\cTab_markerMenu_macros.hpp>

class cTab_Veh_dlg {
	idd = 1775144;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_Veh_dlg', (_this select 0)];nul = [] execVM '\cTab\bft\veh\onload.sqf';";
	onUnload = "uiNamespace setVariable ['cTab_Veh_dlg', displayNull];call cTab_fnc_close;";
	objects[] = {};
	class controlsBackground {
		class background: cTab_RscPicture
		{
			idc = 1200;
			text = "\cTab\img\FBCB2.paa";
			x = -27.04 * GUI_GRID_W + GUI_GRID_X;
			y = -21.03 * GUI_GRID_H + GUI_GRID_Y;
			w = 89 * GUI_GRID_W;
			h = 67.5 * GUI_GRID_H;
		};
		class screen: cTab_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = 2.04 * GUI_GRID_W + GUI_GRID_X;
			y = -1.89 * GUI_GRID_H + GUI_GRID_Y;
			w = 36.5 * GUI_GRID_W;
			h = 28 * GUI_GRID_H;
			onDraw = "nop = _this call cTabOnDrawbftVeh;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM 'cTab\bft\userload.sqf';";
			onMouseButtonDown = "_ok = _this spawn cTabDeleteUsrMkr;";
		};
	};

	class controls {
		class pwrbtn: cTab_RscButtonInv
		{
			idc = 2400;
			x = -1.3 * GUI_GRID_W + GUI_GRID_X;
			y = -0.7 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "closeDialog 0;";
			tooltip = "Close Interface";
		};
		class btnbrtpls: cTab_RscButtonInv
		{
			idc = 2401;
			x = -1.43 * GUI_GRID_W + GUI_GRID_X;
			y = 1.79 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "call cTab_fnc_txt_size_inc;";
			tooltip = "Increase Font";
		};
		class btnbrtmns: cTab_RscButtonInv
		{
			idc = 2402;
			x = -1.47 * GUI_GRID_W + GUI_GRID_X;
			y = 4.36 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "call cTab_fnc_txt_size_dec;";
			tooltip = "Decrease Font";
		};
		class btnblkout: cTab_RscButtonInv
		{
			idc = 2403;
			x = -1.43 * GUI_GRID_W + GUI_GRID_X;
			y = 7.05 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnesc: cTab_RscButtonInv
		{
			idc = 2404;
			x = -1.43 * GUI_GRID_W + GUI_GRID_X;
			y = 9.69 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
			tooltip = "Delete last user placed icon";
		};
		class btnright: cTab_RscButtonInv
		{
			idc = 2405;
			x = -1.39 * GUI_GRID_W + GUI_GRID_X;
			y = 12.3 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnup: cTab_RscButtonInv
		{
			idc = 2406;
			x = -1.39 * GUI_GRID_W + GUI_GRID_X;
			y = 14.98 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btndown: cTab_RscButtonInv
		{
			idc = 2407;
			x = -1.42 * GUI_GRID_W + GUI_GRID_X;
			y = 17.69 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnenter: cTab_RscButtonInv
		{
			idc = 2408;
			x = -1.38 * GUI_GRID_W + GUI_GRID_X;
			y = 20.37 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnfunction: cTab_RscButtonInv
		{
			idc = 2409;
			x = -1.35 * GUI_GRID_W + GUI_GRID_X;
			y = 23.08 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
			action = "['cTab_Veh_dlg'] call cTab_fnc_iconText_toggle;";
			tooltip = "Toggle Text on/off";
		};
		class btnf1: cTab_RscButtonInv
		{
			idc = 2410;
			x = 6.7 * GUI_GRID_W + GUI_GRID_X;
			y = 26.68 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf2: cTab_RscButtonInv
		{
			idc = 2411;
			x = 10.36 * GUI_GRID_W + GUI_GRID_X;
			y = 26.72 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf3: cTab_RscButtonInv
		{
			idc = 2412;
			x = 13.88 * GUI_GRID_W + GUI_GRID_X;
			y = 26.72 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf4: cTab_RscButtonInv
		{
			idc = 2413;
			x = 17.58 * GUI_GRID_W + GUI_GRID_X;
			y = 26.75 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf5: cTab_RscButtonInv
		{
			idc = 2414;
			x = 21.23 * GUI_GRID_W + GUI_GRID_X;
			y = 26.75 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf6: cTab_RscButtonInv
		{
			idc = 2415;
			x = 24.76 * GUI_GRID_W + GUI_GRID_X;
			y = 26.72 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf7: cTab_RscButtonInv
		{
			idc = 2416;
			x = 28.49 * GUI_GRID_W + GUI_GRID_X;
			y = 26.78 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		class btnf8: cTab_RscButtonInv
		{
			idc = 2417;
			x = 32.18 * GUI_GRID_W + GUI_GRID_X;
			y = 26.82 * GUI_GRID_H + GUI_GRID_Y;
			w = 2 * GUI_GRID_W;
			h = 1.5 * GUI_GRID_H;
		};
		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------
		#include <\cTab\cTab_markerMenu_controls.hpp>
	};
};
