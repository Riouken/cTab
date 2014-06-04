
#define GUI_MARGIN_X	(0.05)
#define GUI_MARGIN_Y	(0.2)
#define GUI_MAP_W	(0.55)
#define GUI_MAP_H	(0.55)
#define GUI_TAD_W	(0.72)
#define GUI_TAD_H	(0.72)



#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.025)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)


class cTab_TAD_dialog
{
	idd = 1755424;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_TAD_dialog', (_this select 0)];";
	class controlsBackground
	{
		class background: cTab_RscPicture
		{
			idc = 1200;
			text = "\cTab\img\TAD_background_co.paa";
			x = 4.14 * GUI_GRID_W + GUI_GRID_X;
			y = 0.53 * GUI_GRID_H + GUI_GRID_Y;
			w = 32 * GUI_GRID_W;
			h = 24 * GUI_GRID_H;
		};
		class screen: cTab_RscMapControl
		{
			idc = 1201;
			text = "#(argb,8,8,3)color(1,1,1,1)";
			x = 8.03 * GUI_GRID_W + GUI_GRID_X;
			y = 3.41 * GUI_GRID_H + GUI_GRID_Y;
			w = 24.254 * GUI_GRID_W;
			h = 18.1944 * GUI_GRID_H;
			// allow to zoom out further (defines the maximum map scale, usually 1)
			scaleMax = 1000;
			// turn on satellite map information (defines the map scale of when to switch to topographical)
			maxSatelliteAlpha = 10000;
			alphaFadeStartScale = 0.1;
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
			
			//@{ coefficients which determine rendering density / threshold
			ptsPerSquareSea = 0.1; // seas
			ptsPerSquareTxt = 8;   // textures
			ptsPerSquareCLn = 8;   // count-lines
			ptsPerSquareExp = 8;   // exposure
			ptsPerSquareCost = 8;  // cost
			//@}
			
			//@{ coefficients which determine when rendering of given type is done
			ptsPerSquareFor = 1;           // forests
			ptsPerSquareForEdge = "5.0f"; // forest edges
			ptsPerSquareRoad = "0.5f";     // roads
			ptsPerSquareObj = 5;           // other objects
			//@}
			
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

			class btnF1: cTab_RscButton
			{
				idc = 1600;
				x = 4.8 * GUI_GRID_W + GUI_GRID_X;
				y = 6.55 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF2: cTab_RscButton
			{
				idc = 1601;
				x = 4.8 * GUI_GRID_W + GUI_GRID_X;
				y = 9.1 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF3: cTab_RscButton
			{
				idc = 1602;
				x = 4.81 * GUI_GRID_W + GUI_GRID_X;
				y = 11.74 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF4: cTab_RscButton
			{
				idc = 1603;
				x = 4.84 * GUI_GRID_W + GUI_GRID_X;
				y = 14.39 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF5: cTab_RscButton
			{
				idc = 1604;
				x = 4.81 * GUI_GRID_W + GUI_GRID_X;
				y = 16.9 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF6: cTab_RscButton
			{
				idc = 1605;
				x = 11.5 * GUI_GRID_W + GUI_GRID_X;
				y = 22.46 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF7: cTab_RscButton
			{
				idc = 1606;
				x = 15.4 * GUI_GRID_W + GUI_GRID_X;
				y = 22.46 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF8: cTab_RscButton
			{
				idc = 1607;
				x = 19.21 * GUI_GRID_W + GUI_GRID_X;
				y = 22.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF9: cTab_RscButton
			{
				idc = 1608;
				x = 23.01 * GUI_GRID_W + GUI_GRID_X;
				y = 22.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF10: cTab_RscButton
			{
				idc = 1609;
				x = 26.79 * GUI_GRID_W + GUI_GRID_X;
				y = 22.48 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF11: cTab_RscButton
			{
				idc = 1610;
				x = 33.25 * GUI_GRID_W + GUI_GRID_X;
				y = 16.97 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF12: cTab_RscButton
			{
				idc = 1611;
				x = 33.25 * GUI_GRID_W + GUI_GRID_X;
				y = 14.38 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF13: cTab_RscButton
			{
				idc = 1612;
				x = 33.25 * GUI_GRID_W + GUI_GRID_X;
				y = 11.71 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF14: cTab_RscButton
			{
				idc = 1613;
				x = 33.26 * GUI_GRID_W + GUI_GRID_X;
				y = 9.09 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF15: cTab_RscButton
			{
				idc = 1614;
				x = 33.25 * GUI_GRID_W + GUI_GRID_X;
				y = 6.52 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF16: cTab_RscButton
			{
				idc = 1615;
				x = 26.82 * GUI_GRID_W + GUI_GRID_X;
				y = 1.09 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF17: cTab_RscButton
			{
				idc = 1616;
				x = 22.98 * GUI_GRID_W + GUI_GRID_X;
				y = 1.12 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF18: cTab_RscButton
			{
				idc = 1617;
				x = 19.24 * GUI_GRID_W + GUI_GRID_X;
				y = 1.09 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF19: cTab_RscButton
			{
				idc = 1618;
				x = 15.44 * GUI_GRID_W + GUI_GRID_X;
				y = 1.09 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class btnF20: cTab_RscButton
			{
				idc = 1619;
				x = 11.51 * GUI_GRID_W + GUI_GRID_X;
				y = 1.09 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class adjbtnPlus: cTab_RscButton
			{
				idc = 1620;
				x = 4.5 * GUI_GRID_W + GUI_GRID_X;
				y = 2.83 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class adjbtnmin: cTab_RscButton
			{
				idc = 1621;
				x = 4.49 * GUI_GRID_W + GUI_GRID_X;
				y = 4.63 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class conbtnplus: cTab_RscButton
			{
				idc = 1622;
				x = 4.56 * GUI_GRID_W + GUI_GRID_X;
				y = 19.08 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class conbtnmin: cTab_RscButton
			{
				idc = 1623;
				x = 4.57 * GUI_GRID_W + GUI_GRID_X;
				y = 20.93 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class brtbtnmin: cTab_RscButton
			{
				idc = 1624;
				x = 32.86 * GUI_GRID_W + GUI_GRID_X;
				y = 20.83 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class brtbtnplus: cTab_RscButton
			{
				idc = 1625;
				x = 32.86 * GUI_GRID_W + GUI_GRID_X;
				y = 19.12 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class dspbtnmin: cTab_RscButton
			{
				idc = 1626;
				x = 32.98 * GUI_GRID_W + GUI_GRID_X;
				y = 4.63 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class dspbtnplus: cTab_RscButton
			{
				idc = 1627;
				x = 32.94 * GUI_GRID_W + GUI_GRID_X;
				y = 2.88 * GUI_GRID_H + GUI_GRID_Y;
				w = 2.63492 * GUI_GRID_W;
				h = 1.16534 * GUI_GRID_H;
			};
			class daynteknob: cTab_RscButton
			{
				idc = 1628;
				x = 7.14 * GUI_GRID_W + GUI_GRID_X;
				y = 22.22 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class symbtnmin: cTab_RscButton
			{
				idc = 1629;
				x = 29.66 * GUI_GRID_W + GUI_GRID_X;
				y = 22 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.52381 * GUI_GRID_W;
				h = 2.32672 * GUI_GRID_H;
			};
			class simbtnplus: cTab_RscButton
			{
				idc = 1630;
				x = 32.23 * GUI_GRID_W + GUI_GRID_X;
				y = 22.06 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.52381 * GUI_GRID_W;
				h = 2.32672 * GUI_GRID_H;
			};




			class RscText_1000: RscText
			{
				idc = 1000;
				text = "1247859"; //--- ToDo: Localize;
				x = 18.1 * GUI_GRID_W + GUI_GRID_X;
				y = 19.84 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class RscText_1001: RscText
			{
				idc = 1001;
				text = "12:00"; //--- ToDo: Localize;
				x = 28.77 * GUI_GRID_W + GUI_GRID_X;
				y = 19.45 * GUI_GRID_H + GUI_GRID_Y;
				w = 3 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class RscText_1002: RscText
			{
				idc = 1002;
				text = "12"; //--- ToDo: Localize;
				x = 29.5 * GUI_GRID_W + GUI_GRID_X;
				y = 4 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};




	};
};
