#define GUI_GRID_W	(safezoneW)
#define GUI_GRID_H	(GUI_GRID_W * 4/3)
#define GUI_GRID_X	(safezoneX + (safezoneW - GUI_GRID_W) / 2)
#define GUI_GRID_Y	(safezoneY + (safezoneH - GUI_GRID_H) / 2)

#include <\cTab\FBCB2\cTab_FBCB2_controls.hpp>

#define MENU_sizeEx pxToScreen_H(cTab_GUI_FBCB2_OSD_TEXT_STD_SIZE)
#include "\cTab\shared\cTab_markerMenu_macros.hpp"

class cTab_FBCB2_dlg {
	idd = 1775144;
	movingEnable = true;
	onLoad = "_this call cTab_fnc_onIfOpen;";
	onUnload = "[] call cTab_fnc_onIfclose;";
	onKeyDown = "_this call cTab_fnc_onIfKeyDown;";
	objects[] = {};
	class controlsBackground {
		class background: cTab_FBCB2_background
		{
			moving = 1;
		};
		class screen: cTab_RscMapControl
		{
			idc = IDC_CTAB_SCREEN;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = pxToScreen_X(cTab_GUI_FBCB2_SCREEN_CONTENT_X);
			y = pxToScreen_Y(cTab_GUI_FBCB2_SCREEN_CONTENT_Y);
			w = pxToScreen_W(cTab_GUI_FBCB2_SCREEN_CONTENT_W);
			h = pxToScreen_H(cTab_GUI_FBCB2_SCREEN_CONTENT_H);
			onDraw = "nop = _this call cTabOnDrawbftVeh;";
			onMouseButtonDblClick = "_ok = [3300,_this] execVM '\cTab\shared\cTab_markerMenu_load.sqf';";
			onMouseMoving = "cTabCursorOnMap = _this select 3;cTabMapCursorPos = _this select 0 ctrlMapScreenToWorld [_this select 1,_this select 2];";
			maxSatelliteAlpha = 10000;
			alphaFadeStartScale = 10;
			alphaFadeEndScale = 10;

			// Rendering density coefficients
			ptsPerSquareSea = 8 / (0.86 / GUI_GRID_H);		// seas
			ptsPerSquareTxt = 8 / (0.86 / GUI_GRID_H);		// textures
			ptsPerSquareCLn = 8 / (0.86 / GUI_GRID_H);		// count-lines
			ptsPerSquareExp = 8 / (0.86 / GUI_GRID_H);		// exposure
			ptsPerSquareCost = 8 / (0.86 / GUI_GRID_H);		// cost

			// Rendering thresholds
			ptsPerSquareFor = 3 / (0.86 / GUI_GRID_H);		// forests
			ptsPerSquareForEdge = 100 / (0.86 / GUI_GRID_H);	// forest edges
			ptsPerSquareRoad = 1.5 / (0.86 / GUI_GRID_H);		// roads
			ptsPerSquareObj = 4 / (0.86 / GUI_GRID_H);		// other objects
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
	};
	class controls {
		class header: cTab_FBCB2_header {};
		class battery: cTab_FBCB2_on_screen_battery {};
		class time: cTab_FBCB2_on_screen_time {};
		class signalStrength: cTab_FBCB2_on_screen_signalStrength {};
		class satellite: cTab_FBCB2_on_screen_satellite {};
		class dirDegree: cTab_FBCB2_on_screen_dirDegree {};
		class grid: cTab_FBCB2_on_screen_grid {};
		class dirOctant: cTab_FBCB2_on_screen_dirOctant {};
		class pwrbtn: cTab_FBCB2_btnPWR
		{
			idc = IDC_CTAB_BTNOFF;
			action = "closeDialog 0;";
			tooltip = "Close Interface";
		};
		class btnbrtpls: cTab_FBCB2_btnBRTplus
		{
			idc = IDC_CTAB_BTNUP;
			action = "call cTab_fnc_txt_size_inc;";
			tooltip = "Increase Font";
		};
		class btnbrtmns: cTab_FBCB2_btnBRTminus
		{
			idc = IDC_CTAB_BTNDWN;
			action = "call cTab_fnc_txt_size_dec;";
			tooltip = "Decrease Font";
		};
		class btnfunction: cTab_FBCB2_btnFCN
		{
			idc = IDC_CTAB_BTNFN;
			action = "['cTab_FBCB2_dlg'] call cTab_fnc_iconText_toggle;";
			tooltip = "Toggle Text on/off";
		};
		class btnF5: cTab_FBCB2_btnF5
		{
			idc = IDC_CTAB_BTNF5;
			tooltip = "Toggle Map Tools (F5)";
			action = "['cTab_FBCB2_dlg'] call cTab_fnc_toggleMapTools;";
		};
		class btnF6: cTab_FBCB2_btnF6
		{
			idc = IDC_CTAB_BTNF6;
			tooltip = "Toggle Map Textures";
			action = "['cTab_FBCB2_dlg'] call cTab_fnc_mapType_toggle;";
		};
		class btnF7: cTab_FBCB2_btnF7
		{
			IDC_COUNTER
			action = "['cTab_FBCB2_dlg'] call cTab_fnc_centerMapOnPlayerPosition;";
			tooltip = "Center Map On Current Position (F7)";
		};
		class hookGrid: cTab_FBCB2_on_screen_hookGrid {};
		class hookElevation: cTab_FBCB2_on_screen_hookElevation {};
		class hookDst: cTab_FBCB2_on_screen_hookDst {};
		class hookDir: cTab_FBCB2_on_screen_hookDir {};
		//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------
		#include "\cTab\shared\cTab_markerMenu_controls.hpp"

		// ---------- NOTIFICATION ------------
		class notification: cTab_FBCB2_notification {};
		// ---------- LOADING ------------
		class loadingtxt: cTab_FBCB2_loadingtxt {};
	};
};
