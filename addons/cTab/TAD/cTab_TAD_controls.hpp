// Background definition
#define GUI_GRID_PX_W 2048 // width in pixels
#define GUI_GRID_PX_H 2048 // hight in pixels

// Base bacros to convert pixel space to screen space
#define pxToScreen_X(PIXEL) ((PIXEL) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X)
#define pxToScreen_Y(PIXEL) ((PIXEL) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y)
#define pxToScreen_W(PIXEL) ((PIXEL) / GUI_GRID_PX_W * GUI_GRID_W)
#define pxToScreen_H(PIXEL) ((PIXEL) / GUI_GRID_PX_H * GUI_GRID_H)

// Map position within background, pixel based
#define cTab_GUI_TAD_MAP_X (359)
#define cTab_GUI_TAD_MAP_Y (371)
#define cTab_GUI_TAD_MAP_W (1330)
#define cTab_GUI_TAD_MAP_H (1345)

// On-screen edge positions (left, right, top, bottom)
#define cTab_GUI_TAD_OSD_MARGIN (24)
#define cTab_GUI_TAD_OSD_EDGE_L (cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_X)
#define cTab_GUI_TAD_OSD_EDGE_R (-cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_X + cTab_GUI_TAD_MAP_W)
#define cTab_GUI_TAD_OSD_EDGE_T (cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_Y)
#define cTab_GUI_TAD_OSD_EDGE_B (-cTab_GUI_TAD_OSD_MARGIN + cTab_GUI_TAD_MAP_Y + cTab_GUI_TAD_MAP_H)

// On-screen element base width and height
#define cTab_GUI_TAD_OSD_ELEMENT_STD_W (26)
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

// set IDC counter to 0
__EXEC(cTab_IDC = 0);
#define IDC_COUNTER __EXEC(cTab_IDC = cTab_IDC + 1); idc = __EVAL(cTab_IDC);

class cTab_RscButton_TAD_OSB: cTab_RscButtonInv
{
	w = pxToScreen_W(134);
	h = pxToScreen_H(134);
};
class cTab_RscButton_TAD_OSB01: cTab_RscButton_TAD_OSB
{
	x = pxToScreen_X(577);
	y = pxToScreen_Y(146);
};
class cTab_RscButton_TAD_OSB02: cTab_RscButton_TAD_OSB01
{
	x = pxToScreen_X(767);
};
class cTab_RscButton_TAD_OSB03: cTab_RscButton_TAD_OSB01
{
	x = pxToScreen_X(957);
};
class cTab_RscButton_TAD_OSB04: cTab_RscButton_TAD_OSB01
{
	x = pxToScreen_X(1147);
};
class cTab_RscButton_TAD_OSB05: cTab_RscButton_TAD_OSB01
{
	x = pxToScreen_X(1337);
};
class cTab_RscButton_TAD_OSB06: cTab_RscButton_TAD_OSB
{
	x = pxToScreen_X(1782);
	y = pxToScreen_Y(563);
};
class cTab_RscButton_TAD_OSB07: cTab_RscButton_TAD_OSB06
{
	y = pxToScreen_Y(760);
};
class cTab_RscButton_TAD_OSB08: cTab_RscButton_TAD_OSB06
{
	y = pxToScreen_Y(957);
};
class cTab_RscButton_TAD_OSB09: cTab_RscButton_TAD_OSB06
{
	y = pxToScreen_Y(1155);
};
class cTab_RscButton_TAD_OSB10: cTab_RscButton_TAD_OSB06
{
	y = pxToScreen_Y(1352);
};
class cTab_RscButton_TAD_OSB11: cTab_RscButton_TAD_OSB
{
	x = pxToScreen_X(1337);
	y = pxToScreen_Y(1811);
};
class cTab_RscButton_TAD_OSB12: cTab_RscButton_TAD_OSB11
{
	x = pxToScreen_X(1147);
};
class cTab_RscButton_TAD_OSB13: cTab_RscButton_TAD_OSB11
{
	x = pxToScreen_X(957);
};
class cTab_RscButton_TAD_OSB14: cTab_RscButton_TAD_OSB11
{
	x = pxToScreen_X(767);
};
class cTab_RscButton_TAD_OSB15: cTab_RscButton_TAD_OSB11
{
	x = pxToScreen_X(577);
};
class cTab_RscButton_TAD_OSB16: cTab_RscButton_TAD_OSB
{
	x = pxToScreen_X(132);
	y = pxToScreen_Y(1352);
};
class cTab_RscButton_TAD_OSB17: cTab_RscButton_TAD_OSB16
{
	y = pxToScreen_Y(1155);
};
class cTab_RscButton_TAD_OSB18: cTab_RscButton_TAD_OSB16
{
	y = pxToScreen_Y(957);
};
class cTab_RscButton_TAD_OSB19: cTab_RscButton_TAD_OSB16
{
	y = pxToScreen_Y(760);
};
class cTab_RscButton_TAD_OSB20: cTab_RscButton_TAD_OSB16
{
	y = pxToScreen_Y(563);
};
class cTab_RscButton_TAD_ADJ_INC: cTab_RscButtonInv
{
	x = pxToScreen_X(124);
	y = pxToScreen_Y(257);
	w = pxToScreen_W(142);
	h = pxToScreen_H(119);
};
class cTab_RscButton_TAD_ADJ_DEC: cTab_RscButton_TAD_ADJ_INC
{
	y = pxToScreen_Y(376);
};
class cTab_RscButton_TAD_DSP_INC: cTab_RscButton_TAD_ADJ_INC
{
	x = pxToScreen_X(1782);
};
class cTab_RscButton_TAD_DSP_DEC: cTab_RscButton_TAD_DSP_INC
{
	y = pxToScreen_Y(376);
};
class cTab_RscButton_TAD_CON_INC: cTab_RscButton_TAD_ADJ_INC
{
	y = pxToScreen_Y(1539);
};
class cTab_RscButton_TAD_CON_DEC: cTab_RscButton_TAD_CON_INC
{
	y = pxToScreen_Y(1658);
};
class cTab_RscButton_TAD_BRT_INC: cTab_RscButton_TAD_CON_INC
{
	x = pxToScreen_X(1782);
};
class cTab_RscButton_TAD_BRT_DEC: cTab_RscButton_TAD_BRT_INC
{
	y = pxToScreen_Y(1658);
};
class cTab_RscButton_TAD_SYM_INC: cTab_RscButtonInv
{
	x = pxToScreen_X(1663);
	y = pxToScreen_Y(1811);
	w = pxToScreen_W(119);
	h = pxToScreen_H(142);
};
class cTab_RscButton_TAD_SYM_DEC: cTab_RscButton_TAD_SYM_INC
{
	x = pxToScreen_X(1544);
};
class cTab_RscButton_TAD_DNO: cTab_RscButtonInv
{
	x = pxToScreen_X(234);
	y = pxToScreen_Y(1894);
	w = pxToScreen_W(142);
	h = pxToScreen_H(142);
};

class cTab_RscText_TAD: cTab_RscText
{
	style = ST_CENTER;
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W);
	h = pxToScreen_H(cTab_GUI_TAD_OSD_ELEMENT_STD_H);
	font = GUI_FONT_MONO;
	colorText[] = COLOR_NEON_GREEN;
	sizeEx = pxToScreen_H(cTab_GUI_TAD_OSD_TEXT_STD_SIZE);
	colorBackground[] = COLOR_BLACK;
	shadow = 0;
};
class cTab_TAD_upDownArrow: cTab_RscPicture
{
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W);
	h = pxToScreen_H(cTab_GUI_TAD_OSD_ICON_H);
	colorText[] = COLOR_NEON_GREEN;
	colorBackground[] = COLOR_BLACK;
	text = "\a3\ui_f\data\IGUI\Cfg\Actions\autohover_ca.paa";
};
class cTab_TAD_RscMapControl: cTab_RscMapControl
{
	text = "#(argb,8,8,3)color(1,1,1,1)";
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X);
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y);
	w = pxToScreen_W(cTab_GUI_TAD_MAP_W);
	h = pxToScreen_H(cTab_GUI_TAD_MAP_H);
	//type = CT_MAP;
	// allow to zoom out further (defines the maximum map scale, usually 1)
	scaleMax = 1000;
	// set initial map scale
	scaleDefault = "(missionNamespace getVariable 'cTabMapScale') * 0.86 / (safezoneH * 0.8)";
	// turn on satellite map information (defines the map scale of when to switch to topographical)
	maxSatelliteAlpha = 10000;
	alphaFadeStartScale = 10;
	alphaFadeEndScale = 10;

	// Rendering density coefficients
	ptsPerSquareSea = 8 / cTab_TAD_DLGtoDSP_fctr;		// seas
	ptsPerSquareTxt = 8 / cTab_TAD_DLGtoDSP_fctr;		// textures
	ptsPerSquareCLn = 8 / cTab_TAD_DLGtoDSP_fctr;		// count-lines
	ptsPerSquareExp = 8 / cTab_TAD_DLGtoDSP_fctr;		// exposure
	ptsPerSquareCost = 8 / cTab_TAD_DLGtoDSP_fctr;		// cost

	// Rendering thresholds
	ptsPerSquareFor = 3 / cTab_TAD_DLGtoDSP_fctr;		// forests
	ptsPerSquareForEdge = 100 / cTab_TAD_DLGtoDSP_fctr;	// forest edges
	ptsPerSquareRoad = 1.5 / cTab_TAD_DLGtoDSP_fctr;		// roads
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
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X);
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y);
	w = pxToScreen_W(cTab_GUI_TAD_MAP_W);
	h = pxToScreen_H(cTab_GUI_TAD_MAP_H);
	colorBackground[] = COLOR_BLACK;
};

class cTab_TAD_background: cTab_RscPicture
{
	idc = IDC_CTAB_BACKGROUND;
	text = ""; // will be set during onLoad event
	x = GUI_GRID_X;
	y = GUI_GRID_Y;
	w = GUI_GRID_W;
	h = GUI_GRID_H;
};
class cTab_TAD_OSD_hookGrid: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_HOOK_GRID;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB11_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 0.5 + cTab_GUI_TAD_OSD_ELEMENT_STD_H * 1);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6);
};
class cTab_TAD_OSD_hookElevation: cTab_TAD_OSD_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_ELEVATION;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB11_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 2);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 0.5 + cTab_GUI_TAD_OSD_ELEMENT_STD_H * 2);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4);
};
class cTab_TAD_OSD_hookDir: cTab_TAD_OSD_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DIR;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB11_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 0.5 + cTab_GUI_TAD_OSD_ELEMENT_STD_H * 0);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 8);
};
class cTab_TAD_OSD_hookToggleIconBackground: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB18_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H	 / 2);
};
class cTab_TAD_OSD_hookToggleIcon: cTab_TAD_upDownArrow
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB18_Y - cTab_GUI_TAD_OSD_ICON_H / 2);
};
class cTab_TAD_OSD_hookToggleText1: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_HOOK_TGGL1;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB18_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4);
};
class cTab_TAD_OSD_hookToggleText2: cTab_TAD_OSD_hookToggleText1
{
	idc = IDC_CTAB_OSD_HOOK_TGGL2;
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB18_Y);
};
class cTab_TAD_OSD_currentDirection: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_DIR_DEGREE;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB14_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4 / 2);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 2);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4);
};
class cTab_TAD_OSD_currentElevation: cTab_TAD_OSD_currentDirection
{
	idc = IDC_CTAB_OSD_ELEVATION;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB12_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 5 / 2);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 5);
};
class cTab_TAD_OSD_centerMapText: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB19_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
	text = "CTR";
};
class cTab_TAD_loadingtxt: cTab_RscText_TAD
{
	idc = IDC_CTAB_LOADINGTXT;
	style = ST_CENTER;
	text = "Loading"; //--- ToDo: Localize;
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X);
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y);
	w = pxToScreen_W(cTab_GUI_TAD_MAP_W);
	h = pxToScreen_H(cTab_GUI_TAD_MAP_H);
};
class cTab_TAD_OSD_cursor: cTab_RscPicture
{
	IDC_COUNTER
	text = "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa";
		// "\a3\ui_f\data\map\Markers\Military\destroy_ca.paa";
		// "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa"
		// "\a3\ui_f\data\map\MarkerBrushes\cross_ca.paa"
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X + cTab_GUI_TAD_MAP_W / 2 - 128 / 33 * cTab_GUI_TAD_CURSOR / 2);
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y + cTab_GUI_TAD_MAP_H / 2 - 128 / 33 * cTab_GUI_TAD_CURSOR / 2);
	w = pxToScreen_W(128 / 33 * cTab_GUI_TAD_CURSOR);
	h = pxToScreen_H(128 / 33 * cTab_GUI_TAD_CURSOR);
	colorText[] = COLOR_NEON_GREEN;
};
class cTab_TAD_OSD_navModeOrScale: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_MAP_SCALE;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 4);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_T);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_MODE_W * 4);
	h = pxToScreen_H(cTab_GUI_TAD_OSD_ELEMENT_MODE_H);
	sizeEx = pxToScreen_H(cTab_GUI_TAD_OSD_TEXT_MODE_SIZE);
};
class cTab_TAD_OSD_modeTAD: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB15_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3 / 2);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
	colorText[] = COLOR_BLACK;
	colorBackground[] = COLOR_NEON_GREEN;
	text = "TAD";
};
class cTab_TAD_OSD_txtToggleIconBg: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2);
};
class cTab_TAD_OSD_txtToggleIcon: cTab_TAD_upDownArrow
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ICON_H / 2);
};
class cTab_TAD_OSD_txtToggleText1: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
	text = "TXT";
};
class cTab_TAD_OSD_txtToggleText2: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_TXT_TGGL;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_R - cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB10_Y);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
};
class cTab_TAD_OSD_time: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_TIME;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 5);
};
class cTab_TAD_OSD_currentGrid: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_GRID;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_OSB13_X - cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6 / 2);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 2);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 6);
};
class cTab_TAD_OSD_mapToggleIconBg: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H / 2);
};
class cTab_TAD_OSD_mapToggleIcon: cTab_TAD_upDownArrow
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET - cTab_GUI_TAD_OSD_ELEMENT_STD_W);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ICON_H / 2);
};
class cTab_TAD_OSD_mapToggleText1: cTab_RscText_TAD
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y - cTab_GUI_TAD_OSD_ELEMENT_STD_H);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 3);
	text = "MAP";
};
class cTab_TAD_OSD_mapToggleText2: cTab_RscText_TAD
{
	idc = IDC_CTAB_OSD_MAP_TGGL;
	x = pxToScreen_X(cTab_GUI_TAD_OSD_EDGE_L + cTab_GUI_TAD_OSD_OSB_TEXT_OFFSET);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_OSB20_Y);
	w = pxToScreen_W(cTab_GUI_TAD_OSD_ELEMENT_STD_W * 4);
};

// Define areas around the screen as interaction areas to allow screen movement
class cTab_TAD_movingHandle_T: cTab_RscText_TAD
{
	IDC_COUNTER
	moving = 1;
	colorBackground[] = COLOR_TRANSPARENT;
	x = pxToScreen_X(0);
	y = pxToScreen_Y(0);
	w = pxToScreen_W(GUI_GRID_PX_W);
	h = pxToScreen_H(cTab_GUI_TAD_MAP_Y);
};
class cTab_TAD_movingHandle_B: cTab_TAD_movingHandle_T
{
	IDC_COUNTER
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y + cTab_GUI_TAD_MAP_H);
	h = pxToScreen_H(GUI_GRID_PX_H - (cTab_GUI_TAD_MAP_Y + cTab_GUI_TAD_MAP_H));
};
class cTab_TAD_movingHandle_L: cTab_TAD_movingHandle_T
{
	IDC_COUNTER
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y);
	w = pxToScreen_W(cTab_GUI_TAD_MAP_X);
	h = pxToScreen_H(cTab_GUI_TAD_MAP_H);
};
class cTab_TAD_movingHandle_R: cTab_TAD_movingHandle_L
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X + cTab_GUI_TAD_MAP_W);
	w = pxToScreen_W(GUI_GRID_PX_W - (cTab_GUI_TAD_MAP_X + cTab_GUI_TAD_MAP_W));
};

// transparent control that gets placed on top of the GUI to adjust brightness
class cTab_TAD_brightness: cTab_RscText_TAD
{
	idc = IDC_CTAB_BRIGHTNESS;
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X);
	y = pxToScreen_Y(cTab_GUI_TAD_MAP_Y);
	w = pxToScreen_W(cTab_GUI_TAD_MAP_W);
	h = pxToScreen_H(cTab_GUI_TAD_MAP_H);
	colorBackground[] = COLOR_TRANSPARENT;
};
class cTab_TAD_notification: cTab_RscText_TAD {
	idc = IDC_CTAB_NOTIFICATION;
	x = pxToScreen_X(cTab_GUI_TAD_MAP_X + (cTab_GUI_TAD_MAP_W * 0.2) / 2);
	y = pxToScreen_Y(cTab_GUI_TAD_OSD_EDGE_B - cTab_GUI_TAD_OSD_ELEMENT_STD_H * 3);
	w = pxToScreen_W(cTab_GUI_TAD_MAP_W * 0.8);
	colorText[] = COLOR_NAVYBLUE;
	colorBackground[] = COLOR_WHITE;
};