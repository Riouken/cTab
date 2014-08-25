// Background definition
#define GUI_GRID_PX_W 2048 // width in pixels
#define GUI_GRID_PX_H 2048 // hight in pixels

// Map position within background, pixel based
#define cTab_GUI_TAD_MAP_X (371)
#define cTab_GUI_TAD_MAP_Y (378)
#define cTab_GUI_TAD_MAP_W (1306)
#define cTab_GUI_TAD_MAP_H (1328)

// On-screen edge positions (left, right, top, bottom)
#define cTab_GUI_TAD_OSD_MARGIN (24)
#define cTab_GUI_TAD_OSD_EDGE_L (cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_X)
#define cTab_GUI_TAD_OSD_EDGE_R (-cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_X + cTab_GUI_TAD_MAP_W)
#define cTab_GUI_TAD_OSD_EDGE_T (cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_Y)
#define cTab_GUI_TAD_OSD_EDGE_B (-cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_Y + cTab_GUI_TAD_MAP_H)

// On-screen element base width and height
#define cTab_GUI_TAD_OSD_ELEMENT_STD_W (25)
#define cTab_GUI_TAD_OSD_ELEMENT_STD_H (53)
#define cTab_GUI_TAD_OSD_ELEMENT_MODE_W (38)
#define cTab_GUI_TAD_OSD_ELEMENT_MODE_H (82)
#define cTab_GUI_TAD_OSD_ELEMENT_ROLL_W (146)
#define cTab_GUI_TAD_OSD_ELEMENT_ROLL_H (146)

// On-screen OSB element offsets horizontally from the edge
#define cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET (36)

// On-screen text sizes, hight in pixels
// Standard text elements
#define cTab_GUI_TAD_OSD_TEXT_STD_SIZE (42)
// Mode / scale element (top right corner)
#define cTab_GUI_TAD_OSD_TEXT_MODE_SIZE (66)
// Icon height
#define cTab_GUI_TAD_OSD_ICON_H (32)

// On-screen map centre cursor
#define cTab_GUI_TAD_CURSOR (48)

// SOI selection box, defining the # of pixels between map edge and box
#define cTab_GUI_TAD_SOI_MARGIN (66)

// On-screen OSB positions (where the line meets the screen), all values absolute pixels values
// OSB01 to OSB05 along the top, values along the x-axis
#define cTab_GUI_TAD_OSD_OSB01_X (661)
#define cTab_GUI_TAD_OSD_OSB02_X (844)
#define cTab_GUI_TAD_OSD_OSB03_X (1023)
#define cTab_GUI_TAD_OSD_OSB04_X (1202)
#define cTab_GUI_TAD_OSD_OSB05_X (1384)
// OSB06 to OSB10 along the right side, values along the y-axis
#define cTab_GUI_TAD_OSD_OSB06_Y (647)
#define cTab_GUI_TAD_OSD_OSB07_Y (836)
#define cTab_GUI_TAD_OSD_OSB08_Y (1023)
#define cTab_GUI_TAD_OSD_OSB09_Y (1209)
#define cTab_GUI_TAD_OSD_OSB10_Y (1398)
// OSB11 to OSB15 along the bottom, values along the x-axis
#define cTab_GUI_TAD_OSD_OSB11_X (cTab_GUI_TAD_OSD_OSB05_X)
#define cTab_GUI_TAD_OSD_OSB12_X (cTab_GUI_TAD_OSD_OSB04_X)
#define cTab_GUI_TAD_OSD_OSB13_X (cTab_GUI_TAD_OSD_OSB03_X)
#define cTab_GUI_TAD_OSD_OSB14_X (cTab_GUI_TAD_OSD_OSB02_X)
#define cTab_GUI_TAD_OSD_OSB15_X (cTab_GUI_TAD_OSD_OSB01_X)
// OSB16 to OSB20 along the left, values along the y-axis
#define cTab_GUI_TAD_OSD_OSB16_Y (cTab_GUI_TAD_OSD_OSB10_Y)
#define cTab_GUI_TAD_OSD_OSB17_Y (cTab_GUI_TAD_OSD_OSB09_Y)
#define cTab_GUI_TAD_OSD_OSB18_Y (cTab_GUI_TAD_OSD_OSB08_Y)
#define cTab_GUI_TAD_OSD_OSB19_Y (cTab_GUI_TAD_OSD_OSB07_Y)
#define cTab_GUI_TAD_OSD_OSB20_Y (cTab_GUI_TAD_OSD_OSB06_Y)

// define colours
#define COLOR_NEON_GREEN {57/255,255/255,20/255,1}
#define COLOR_BLACK {0,0,0,1}
#define COLOR_WHITE {1,1,1,1}

class cTab_RscButton_TAD_OSB: cTab_RscButtonInv
{
	w = 134 / GUI_GRID_PX_W * GUI_GRID_W;
	h = 134 / GUI_GRID_PX_H * GUI_GRID_H;
};
class cTab_RscButton_TAD_OSB01: cTab_RscButton_TAD_OSB
{
	x = 577 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 146 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB02: cTab_RscButton_TAD_OSB01
{
	x = 767 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB03: cTab_RscButton_TAD_OSB01
{
	x = 957 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB04: cTab_RscButton_TAD_OSB01
{
	x = 1147 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB05: cTab_RscButton_TAD_OSB01
{
	x = 1337 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB06: cTab_RscButton_TAD_OSB
{
	x = 1782 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 563 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB07: cTab_RscButton_TAD_OSB06
{
	y = 760 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB08: cTab_RscButton_TAD_OSB06
{
	y = 957 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB09: cTab_RscButton_TAD_OSB06
{
	y = 1155 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB10: cTab_RscButton_TAD_OSB06
{
	y = 1352 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB11: cTab_RscButton_TAD_OSB
{
	x = 1337 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1811 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB12: cTab_RscButton_TAD_OSB11
{
	x = 1147 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB13: cTab_RscButton_TAD_OSB11
{
	x = 957 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB14: cTab_RscButton_TAD_OSB11
{
	x = 767 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB15: cTab_RscButton_TAD_OSB11
{
	x = 577 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_OSB16: cTab_RscButton_TAD_OSB
{
	x = 132 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1352 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB17: cTab_RscButton_TAD_OSB16
{
	y = 1155 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB18: cTab_RscButton_TAD_OSB16
{
	y = 957 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB19: cTab_RscButton_TAD_OSB16
{
	y = 760 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB20: cTab_RscButton_TAD_OSB16
{
	y = 563 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_ADJ_INC: cTab_RscButtonInv
{
	x = 124 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 257 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
	w = 142 / GUI_GRID_PX_W * GUI_GRID_W;
	h = 119 / GUI_GRID_PX_H * GUI_GRID_H;
};
class cTab_RscButton_TAD_ADJ_DEC: cTab_RscButton_TAD_ADJ_INC
{
	y = 376 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_DSP_INC: cTab_RscButton_TAD_ADJ_INC
{
	x = 1782 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_DSP_DEC: cTab_RscButton_TAD_DSP_INC
{
	y = 376 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_CON_INC: cTab_RscButton_TAD_ADJ_INC
{
	y = 1539 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_CON_DEC: cTab_RscButton_TAD_CON_INC
{
	y = 1658 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_BRT_INC: cTab_RscButton_TAD_CON_INC
{
	x = 1782 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_BRT_DEC: cTab_RscButton_TAD_BRT_INC
{
	y = 1658 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_SYM_INC: cTab_RscButtonInv
{
	x = 1663 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1811 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
	w = 119 / GUI_GRID_PX_W * GUI_GRID_W;
	h = 142 / GUI_GRID_PX_H * GUI_GRID_H;
};
class cTab_RscButton_TAD_SYM_DEC: cTab_RscButton_TAD_SYM_INC
{
	x = 1544 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_DNO: cTab_RscButtonInv
{
	x = 234 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1894 / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
	w = 142 / GUI_GRID_PX_W * GUI_GRID_W;
	h = 142 / GUI_GRID_PX_H * GUI_GRID_H;
};

class cTab_RscText_TAD: cTab_RscText
{
	style = ST_CENTER;
	w = cTab_GUI_TAD_OSD_ELEMENT_STD_W / GUI_GRID_PX_W * GUI_GRID_W;
	h = cTab_GUI_TAD_OSD_ELEMENT_STD_H / GUI_GRID_PX_H * GUI_GRID_H;
	font = GUI_FONT_MONO;
	colorText[] = COLOR_NEON_GREEN;
	sizeEx = cTab_GUI_TAD_OSD_TEXT_STD_SIZE / GUI_GRID_PX_H * GUI_GRID_H;
	colorBackground[] = COLOR_BLACK;
	shadow = 0;
};
class cTab_TAD_upDownArrow: cTab_RscPicture
{
	w = cTab_GUI_TAD_OSD_ELEMENT_STD_W / GUI_GRID_PX_W * GUI_GRID_W;
	h = cTab_GUI_TAD_OSD_ICON_H / GUI_GRID_PX_H * GUI_GRID_H;
	colorText[] = COLOR_NEON_GREEN;
	colorBackground[] = COLOR_BLACK;
	text = "\a3\ui_f\data\IGUI\Cfg\Actions\autohover_ca.paa";
};
class cTab_TAD_RscMapControl: cTab_RscMapControl
{
	text = "#(argb,8,8,3)color(1,1,1,1)";
	x = cTab_GUI_TAD_MAP_X / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = cTab_GUI_TAD_MAP_Y / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
	w = cTab_GUI_TAD_MAP_W / GUI_GRID_PX_W * GUI_GRID_W;
	h = cTab_GUI_TAD_MAP_H / GUI_GRID_PX_H * GUI_GRID_H;
	//type = CT_MAP;
	// allow to zoom out further (defines the maximum map scale, usually 1)
	scaleMax = 1000;
	// set initial map scale
	scaleDefault = "(missionNamespace getVariable 'cTabTADmapScaleCtrl') * 0.86 / (safezoneH * 0.8)";
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

	// Rendering density coefficients
	ptsPerSquareSea = 8 / cTab_TAD_DLGtoDSP_fctr;		// seas
	ptsPerSquareTxt = 8 / cTab_TAD_DLGtoDSP_fctr;		// textures
	ptsPerSquareCLn = 8 / cTab_TAD_DLGtoDSP_fctr;		// count-lines
	ptsPerSquareExp = 8 / cTab_TAD_DLGtoDSP_fctr;		// exposure
	ptsPerSquareCost = 8 / cTab_TAD_DLGtoDSP_fctr;		// cost

	// Rendering thresholds
	ptsPerSquareFor = 2 / cTab_TAD_DLGtoDSP_fctr;		// forests
	ptsPerSquareForEdge = 4 / cTab_TAD_DLGtoDSP_fctr;	// forest edges
	ptsPerSquareRoad = 2 / cTab_TAD_DLGtoDSP_fctr;		// roads
	ptsPerSquareObj = 4 / cTab_TAD_DLGtoDSP_fctr;		// other objects

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
class cTab_TAD_RscMapControl_BLACK: cTab_TAD_RscMapControl
{
	font = "TahomaB";
	sizeEx = 0.0;
	maxSatelliteAlpha = 0.0;
	colorBackground[] = {0,0,0,0};
	colorLevels[] = {0,0,0,0};
	colorSea[] = {0,0,0,0};
	colorForest[] = {0,0,0,0};
	colorRocks[] = {0,0,0,0};
	colorCountlines[] = {0,0,0,0};
	colorMainCountlines[] = {0,0,0,0};
	colorCountlinesWater[] = {0,0,0,0};
	colorMainCountlinesWater[] = {0,0,0,0};
	colorPowerLines[] = {0,0,0,0};
	colorRailWay[] = {0,0,0,0};
	colorForestBorder[] = {0,0,0,0};
	colorRocksBorder[] = {0,0,0,0};
	colorNames[] = {0,0,0,0};
	colorInactive[] = {0,0,0,0};
	colorOutside[] = {0,0,0,0};
	colorText[] = {0,0,0,0};
	colorGrid[] = {0,0,0,0};
	colorGridMap[] = {0,0,0,0};
	colorTracks[] = {0,0,0,0};
	colorTracksFill[] = {0,0,0,0};
	colorRoads[] = {0,0,0,0};
	colorRoadsFill[] = {0,0,0,0};
	colorMainRoads[] = {0,0,0,0};
	colorMainRoadsFill[] = {0,0,0,0};
	ShowCountourInterval = 0;
	shadow = 0;
	text = "";
	alphaFadeStartScale = 0.0;
	alphaFadeEndScale = 0.0;
	fontLabel = "TahomaB";
	sizeExLabel = 0.0;
	fontGrid = "TahomaB";
	sizeExGrid = 0.0;
	fontUnits = "TahomaB";
	sizeExUnits = 0.0;
	fontNames = "TahomaB";
	sizeExNames = 0.0;
	fontInfo = "TahomaB";
	sizeExInfo = 0.0;
	fontLevel = "TahomaB";
	sizeExLevel = 0.0;
	stickX[] = {0.0,{ "Gamma",0,0.0 }};
	stickY[] = {0.0,{ "Gamma",0,0.0 }};
	ptsPerSquareSea = 10000;
	ptsPerSquareTxt = 10000;
	ptsPerSquareCLn = 10000;
	ptsPerSquareExp = 10000;
	ptsPerSquareCost = 10000;
	ptsPerSquareFor = 10000;
	ptsPerSquareForEdge = 10000;
	ptsPerSquareRoad = 10000;
	ptsPerSquareObj = 10000;
	class Task
	{
		icon = "";
		color[] = {0,0,0,0};
		iconCreated = "";
		colorCreated[] = {0,0,0,0};
		iconCanceled = "";
		colorCanceled[] = {0,0,0,0};
		iconDone = "";
		colorDone[] = {0,0,0,0};
		iconFailed = "";
		colorFailed[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class CustomMark
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Bunker
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Bush
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class BusStop
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Command
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Cross
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Fortress
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Fuelstation
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Fountain
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Hospital
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Chapel
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Church
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Lighthouse
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Quay
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Rock
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Ruin
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class SmallTree
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Stack
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Tree
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Tourism
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Transmitter
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class ViewTower
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Watertower
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Waypoint
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class WaypointCompleted
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class ActiveMarker
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class PowerSolar
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class PowerWave
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class PowerWind
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
	class Shipwreck
	{
		icon = "";
		color[] = {0,0,0,0};
		size = 0;
		importance = 0;
		coefMin = 0;
		coefMax = 0;
	};
};

class cTab_TAD_Map_Background: cTab_RscText
{
	x = cTab_GUI_TAD_MAP_X / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = cTab_GUI_TAD_MAP_Y / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y;
	w = cTab_GUI_TAD_MAP_W / GUI_GRID_PX_W * GUI_GRID_W;
	h = cTab_GUI_TAD_MAP_H / GUI_GRID_PX_H * GUI_GRID_H;
	colorBackground[] = COLOR_BLACK;
};

class cTab_TAD_background: cTab_RscPicture
{
	idc = IDC_CTAB_BACKGROUND;
	text = "\cTab\img\TAD_background_ca.paa";
	x = GUI_GRID_X;
	y = GUI_GRID_Y;
	w = GUI_GRID_W;
	h = GUI_GRID_H;
};