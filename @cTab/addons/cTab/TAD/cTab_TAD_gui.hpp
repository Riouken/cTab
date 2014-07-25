#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.04)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)

#define GUI_MARGIN_X	(0.05)
#define GUI_MARGIN_Y	(0.2)
#define GUI_MAP_W	(0.55)
#define GUI_MAP_H	(0.5625)
#define GUI_SCREEN_Y_OFFSET	(0.0085)
#define GUI_TAD_W	(0.86)
#define GUI_TAD_H	(0.86)

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
		/*
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
		*/
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
};
