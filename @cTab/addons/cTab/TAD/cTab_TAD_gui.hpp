#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.04)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)

#define GUI_MARGIN_X	(0.05)
#define GUI_MARGIN_Y	(0.2)
#define GUI_MAP_W	(0.55)
#define GUI_MAP_H	(0.55)
#define GUI_SCREEN_Y_OFFSET	(0.007)
#define GUI_TAD_W	(0.82)
#define GUI_TAD_H	(0.82)

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
		class screen: cTab_RscMapControl
		{
			idc = 1201;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = safeZoneX + (GUI_MARGIN_X + ((GUI_TAD_W - GUI_MAP_W) / 2)) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MARGIN_Y - ((GUI_TAD_H - GUI_MAP_H) / 2) - GUI_MAP_H + GUI_SCREEN_Y_OFFSET;
			w = GUI_MAP_W * 3/4;
			h = GUI_MAP_H;
			// set initial map scale
			scaleDefault = "(missionNamespace getVariable 'cTabTADmapScale') / (missionNamespace getVariable 'cTabMapScaleFactor')";
			// allow to zoom out further (defines the maximum map scale, usually 1)
			scaleMax = 1000;
			// turn on satellite map information (defines the map scale of when to switch to topographical)
			maxSatelliteAlpha = 10000;
			alphaFadeStartScale = 10;
			alphaFadeEndScale = 10;
			colorBackground[] = {0.969,0.957,0.949,1.0};
			colorSea[] = {0.467,0.631,0.851,0.5};
			colorForest[] = {0.4,1,0.4,0.5};
			colorForestBorder[] = {0.2,1,0.2,1};
			colorRocks[] = {0.0,0.0,0.0,0.3};
			colorRocksBorder[] = {0.0,0.0,0.0,0.0};
			colorLevels[] = {0,0,0,1};
			colorMainCountlines[] = {0.78,0.44,0.22,1};
			colorCountlines[] = {0.9,0,0,1};
			colorMainCountlinesWater[] = {0.491,0.577,0.702,0.0};
			colorCountlinesWater[] = {0.491,0.577,0.702,0.0};
			colorPowerLines[] = {0.1,0.1,0.1,1.0};
			colorRailWay[] = {0.8,0.2,0.0,1.0};
			colorNames[] = {0,0,0,1};
			colorInactive[] = {1.0,1.0,1.0,0.5};
			colorOutside[] = {0.0,0.0,0.0,1.0};
			colorTracks[] = {0.84,0.76,0.65,1.0};
			colorTracksFill[] = {0.84,0.76,0.65,1.0};
			colorRoads[] = {1.0,0.8,0.0,1.0};
			colorRoadsFill[] = {1.0,0.8,0.0,1.0};
			colorMainRoads[] = {1.0,0.6,0.4,1.0};
			colorMainRoadsFill[] = {1.0,0.6,0.4,1.0};
			// hide grid lines
			colorGrid[] = {0.1,0.1,0.1,0};
			colorGridMap[] = {0.1,0.1,0.1,0};

			// Rendering density coefficients
			ptsPerSquareSea = 8;		// seas
			ptsPerSquareTxt = 8;		// textures
			ptsPerSquareCLn = 8;		// count-lines
			ptsPerSquareExp = 8;		// exposure
			ptsPerSquareCost = 8;		// cost

			// Rendering thresholds
			ptsPerSquareFor = 1;		// forests
			ptsPerSquareForEdge = 4.0;	// forest edges
			ptsPerSquareRoad = 0.5;		// roads
			ptsPerSquareObj = 4;		// other objects

			// Continuously call cTabOnDrawbftTAD to draw cTab's icons on map
			onDraw = "nop = [] call cTabOnDrawbftTAD;";
			/*
			// replace CustomMark with wedding cake icon
			class CustomMark
			{
				icon = "\cTab\img\icon_wedding_cake_ca.paa";
				size = 18;
				importance = 1;
				coefMin = 1;
				coefMax = 1;
				color[] = {1,1,1,1};
				shadow = 1;
			};
			*/
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
			x = safeZoneX + (GUI_MARGIN_X + GUI_MAP_W - 0.08 - 0.015 + ((GUI_TAD_W - GUI_MAP_W) / 2)) * 3/4;
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
			x = safeZoneX + (GUI_MARGIN_X + (GUI_MAP_W / 2) - 0.05 + ((GUI_TAD_W - GUI_MAP_W) / 2)) * 3/4;
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
			x = safeZoneX + (GUI_MARGIN_X + GUI_MAP_W - 0.06 - 0.015 + ((GUI_TAD_W - GUI_MAP_W) / 2)) * 3/4;
			y = safeZoneY + safeZoneH - GUI_MAP_H - ((GUI_TAD_H - GUI_MAP_H) / 2) - GUI_MARGIN_Y + 0.015 + GUI_SCREEN_Y_OFFSET;
			w = 0.06 * 3/4;
			h = 0.04;
			colorText[] = {57/255, 1, 20/255, 1};
			sizeEx = 0.04;
			colorBackground[] = {0,0,0,1};
			shadow = 0;
		};
	};
};
