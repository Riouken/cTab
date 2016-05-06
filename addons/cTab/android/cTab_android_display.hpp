// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

#define GUI_GRID_W	(0.86)
#define GUI_GRID_H	(GUI_GRID_W * 4/3)
#define GUI_GRID_X	(safezoneX - GUI_GRID_W * 0.17)
#define GUI_GRID_Y	(safezoneY + safezoneH * 0.88 - GUI_GRID_H * 0.72)

#define cTab_android_DLGtoDSP_fctr (1)

#include <\cTab\android\cTab_android_controls.hpp>

#define MENU_sizeEx pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE)
#include "\cTab\shared\cTab_markerMenu_macros.hpp"

class cTab_Android_dsp {
	idd = 177383;
	duration = 10e10;
	fadeIn = 0;
	fadeOut = 0;
	onLoad = "_this call cTab_fnc_onIfOpen;";
	objects[] = {};
	class controlsBackground
	{
		class windowsBG: cTab_android_windowsBG {};
		class screen: cTab_android_RscMapControl
		{
			onDraw = "nop = _this call cTabOnDrawbftAndroidDsp;";
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
	};

	class controls
	{
		/*
			### OSD GUI controls ###
		*/
		class header: cTab_android_header {};
		class battery: cTab_android_on_screen_battery {};
		class time: cTab_android_on_screen_time {};
		class signalStrength: cTab_android_on_screen_signalStrength {};
		class satellite: cTab_android_on_screen_satellite {};
		class dirDegree: cTab_android_on_screen_dirDegree {};
		class grid: cTab_android_on_screen_grid {};
		class dirOctant: cTab_android_on_screen_dirOctant {};

		/*
			### Overlays ###
		*/
		// ---------- NOTIFICATION ------------
		class notification: cTab_android_notification {};
		// ---------- LOADING ------------
		class loadingtxt: cTab_android_loadingtxt {};
		// ---------- BRIGHTNESS ------------
		class brightness: cTab_android_brightness {};
		// ---------- BACKGROUND ------------
		class background: cTab_android_background {};
	};
};
