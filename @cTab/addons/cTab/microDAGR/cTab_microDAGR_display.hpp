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
			onDraw = "nop = [] call cTabOnDrawbftmicroDAGRdsp;";
			// set initial map scale
			scaleDefault = "missionNamespace getVariable 'cTabMicroDAGRmapScaleCtrl'";
		};
		class screenTopo: screen
		{
			idc = IDC_CTAB_SCREEN_TOPO;
			maxSatelliteAlpha = 0;
		};
	};

	class controls
	{
		class header: cTab_microDAGR_header {};
		class footer: cTab_microDAGR_footer {};
		class background: cTab_microDAGR_background {};
	};
};
