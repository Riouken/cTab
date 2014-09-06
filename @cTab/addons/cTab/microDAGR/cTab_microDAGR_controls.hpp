// Background definition
#define GUI_GRID_PX_W 2048 // width in pixels
#define GUI_GRID_PX_H 2048 // hight in pixels

// Base bacros to convert pixel space to screen space
#define pxToScreen_X(PIXEL) (PIXEL) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X
#define pxToScreen_Y(PIXEL) (PIXEL) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y
#define pxToScreen_W(PIXEL) (PIXEL) / GUI_GRID_PX_W * GUI_GRID_W
#define pxToScreen_H(PIXEL) (PIXEL) / GUI_GRID_PX_H * GUI_GRID_H

// Map position within background, pixel based
#define cTab_GUI_microDAGR_MAP_X (573)
#define cTab_GUI_microDAGR_MAP_Y (317)
#define cTab_GUI_microDAGR_MAP_W (942)
#define cTab_GUI_microDAGR_MAP_H (1296)

// Height of header and footer OSD elements
#define cTab_GUI_microDAGR_OSD_HEADER_H (94)
#define cTab_GUI_microDAGR_OSD_FOOTER_H (cTab_GUI_microDAGR_OSD_HEADER_H)

// On-screen edge positions (left, right, top, bottom)
#define cTab_GUI_microDAGR_OSD_MARGIN (24)
#define cTab_GUI_microDAGR_OSD_EDGE_L (cTab_GUI_microDAGR_OSD_MARGIN + cTab_GUI_microDAGR_MAP_X)
#define cTab_GUI_microDAGR_OSD_EDGE_R (-cTab_GUI_microDAGR_OSD_MARGIN + cTab_GUI_microDAGR_MAP_X + cTab_GUI_microDAGR_MAP_W)
#define cTab_GUI_microDAGR_OSD_EDGE_T (cTab_GUI_microDAGR_OSD_MARGIN + cTab_GUI_microDAGR_MAP_Y)
#define cTab_GUI_microDAGR_OSD_EDGE_B (-cTab_GUI_microDAGR_OSD_FOOTER_H + cTab_GUI_microDAGR_MAP_Y + cTab_GUI_microDAGR_MAP_H)

// On-screen element base width and height
#define cTab_GUI_microDAGR_OSD_ELEMENT_STD_W ((cTab_GUI_microDAGR_MAP_W - cTab_GUI_microDAGR_OSD_MARGIN * 4) / 3)
#define cTab_GUI_microDAGR_OSD_ELEMENT_STD_H (cTab_GUI_microDAGR_OSD_HEADER_H - cTab_GUI_microDAGR_OSD_MARGIN)

// On-screen element X-coord for left, center and right elements
#define cTab_GUI_microDAGR_OSD_LEFT_X (cTab_GUI_microDAGR_OSD_EDGE_L)
#define cTab_GUI_microDAGR_OSD_CENTER_X (cTab_GUI_microDAGR_OSD_EDGE_L + cTab_GUI_microDAGR_OSD_MARGIN + cTab_GUI_microDAGR_OSD_ELEMENT_STD_W)
#define cTab_GUI_microDAGR_OSD_RIGHT_X (cTab_GUI_microDAGR_OSD_EDGE_R - cTab_GUI_microDAGR_OSD_ELEMENT_STD_W)

// On-screen text sizes, hight in pixels
// Standard text elements
#define cTab_GUI_microDAGR_OSD_TEXT_STD_SIZE (60)
#define cTab_GUI_microDAGR_OSD_ICON_STD_SIZE (50)

// On-screen map centre cursor
#define cTab_GUI_microDAGR_CURSOR (38)

// define colours
#define COLOR_NEON_GREEN {57/255,255/255,20/255,1}
#define COLOR_BLACK {0,0,0,1}
#define COLOR_WHITE {1,1,1,1}

class cTab_microDAGR_header: cTab_RscText
{
	idc = -1;
	x = pxToScreen_X(cTab_GUI_microDAGR_MAP_X);
	y = pxToScreen_Y(cTab_GUI_microDAGR_MAP_Y);
	w = pxToScreen_W(cTab_GUI_microDAGR_MAP_W);
	h = pxToScreen_H(cTab_GUI_microDAGR_OSD_HEADER_H);
	colorBackground[] = COLOR_BLACK;
};
class cTab_microDAGR_footer: cTab_microDAGR_header
{
	y = pxToScreen_Y(cTab_GUI_microDAGR_MAP_Y + cTab_GUI_microDAGR_MAP_H - cTab_GUI_microDAGR_OSD_FOOTER_H);
	h = pxToScreen_H(cTab_GUI_microDAGR_OSD_FOOTER_H);
};
class cTab_RscButton_microDAGR_LeftUp: cTab_RscButtonInv
{
	x = pxToScreen_X(373);
	y = pxToScreen_Y(400);
	w = pxToScreen_W(26);
	h = pxToScreen_H(171);
};
class cTab_RscButton_microDAGR_LeftDown: cTab_RscButton_microDAGR_LeftUp
{
	y = pxToScreen_Y(571);
};
class cTab_RscButton_microDAGR_LeftBtn: cTab_RscButtonInv
{
	x = pxToScreen_X(368);
	y = pxToScreen_Y(829);
	w = pxToScreen_W(31);
	h = pxToScreen_H(184);
};
class cTab_RscButton_microDAGR_RightUp: cTab_RscButton_microDAGR_LeftUp
{
	x = pxToScreen_X(1689);
};
class cTab_RscButton_microDAGR_RightDown: cTab_RscButton_microDAGR_LeftDown
{
	x = pxToScreen_X(1689);
};
class cTab_RscButton_microDAGR_RightBtn: cTab_RscButton_microDAGR_LeftBtn
{
	x = pxToScreen_X(1689);
};

class cTab_RscText_microDAGR: cTab_RscText
{
	style = ST_CENTER;
	w = pxToScreen_W(cTab_GUI_microDAGR_OSD_ELEMENT_STD_W);
	h = pxToScreen_H(cTab_GUI_microDAGR_OSD_ELEMENT_STD_H);
	font = GUI_FONT_MONO;
	colorText[] = COLOR_WHITE;
	sizeEx = pxToScreen_H(cTab_GUI_microDAGR_OSD_TEXT_STD_SIZE);
	colorBackground[] = COLOR_BLACK;
	shadow = 0;
};
class cTab_microDAGR_RscMapControl: cTab_RscMapControl
{
	idc = IDC_CTAB_SCREEN;
	text = "#(argb,8,8,3)color(1,1,1,1)";
	x = pxToScreen_X(cTab_GUI_microDAGR_MAP_X);
	y = pxToScreen_Y(cTab_GUI_microDAGR_MAP_Y + cTab_GUI_microDAGR_OSD_HEADER_H);
	w = pxToScreen_W(cTab_GUI_microDAGR_MAP_W);
	h = pxToScreen_H(cTab_GUI_microDAGR_MAP_H - cTab_GUI_microDAGR_OSD_HEADER_H - cTab_GUI_microDAGR_OSD_FOOTER_H);
	//type = CT_MAP;
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

	// Rendering density coefficients
	ptsPerSquareSea = 8 / cTab_microDAGR_DLGtoDSP_fctr;		// seas
	ptsPerSquareTxt = 8 / cTab_microDAGR_DLGtoDSP_fctr;		// textures
	ptsPerSquareCLn = 8 / cTab_microDAGR_DLGtoDSP_fctr;		// count-lines
	ptsPerSquareExp = 8 / cTab_microDAGR_DLGtoDSP_fctr;		// exposure
	ptsPerSquareCost = 8 / cTab_microDAGR_DLGtoDSP_fctr;		// cost

	// Rendering thresholds
	ptsPerSquareFor = 2 / cTab_microDAGR_DLGtoDSP_fctr;		// forests
	ptsPerSquareForEdge = 4 / cTab_microDAGR_DLGtoDSP_fctr;	// forest edges
	ptsPerSquareRoad = 2 / cTab_microDAGR_DLGtoDSP_fctr;		// roads
	ptsPerSquareObj = 4 / cTab_microDAGR_DLGtoDSP_fctr;		// other objects

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
class cTab_microDAGR_background: cTab_RscPicture
{
	idc = IDC_CTAB_BACKGROUND;
	text = "\cTab\img\microDAGR_background_ca.paa";
	x = GUI_GRID_X;
	y = GUI_GRID_Y;
	w = GUI_GRID_W;
	h = GUI_GRID_H;
};
class cTab_microDAGR_cursor: cTab_RscPicture
{
	idc = -1;
	text = "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa";
		// "\a3\ui_f\data\map\Markers\Military\destroy_ca.paa";
		// "\a3\ui_f\data\IGUI\Cfg\WeaponCursors\cursoraimon_gs.paa"
		// "\a3\ui_f\data\map\MarkerBrushes\cross_ca.paa"
	x = pxToScreen_X(cTab_GUI_microDAGR_MAP_X + cTab_GUI_microDAGR_MAP_W / 2 - 128 / 33 * cTab_GUI_microDAGR_CURSOR / 2);
	y = pxToScreen_Y(cTab_GUI_microDAGR_MAP_Y + cTab_GUI_microDAGR_MAP_H / 2 - 128 / 33 * cTab_GUI_microDAGR_CURSOR / 2);
	w = pxToScreen_W(128 / 33 * cTab_GUI_microDAGR_CURSOR);
	h = pxToScreen_H(128 / 33 * cTab_GUI_microDAGR_CURSOR);
	colorText[] = COLOR_NEON_GREEN;
};
class cTab_microDAGR_pwrbtn: cTab_RscButton_microDAGR_LeftBtn
{
	idc = IDC_CTAB_BTNMAIN;
	action = "closeDialog 0;";
	tooltip = "Close Interface";
};
class cTab_microDAGR_btnbrtpls: cTab_RscButton_microDAGR_RightUp
{
	idc = IDC_CTAB_BTNUP;
	action = "call cTab_fnc_txt_size_inc;";
	tooltip = "Increase Font";
};
class cTab_microDAGR_btnbrtmns: cTab_RscButton_microDAGR_RightDown
{
	idc = IDC_CTAB_BTNDWN;
	action = "call cTab_fnc_txt_size_dec;";
	tooltip = "Decrease Font";
};
class cTab_microDAGR_btnfunction: cTab_RscButton_microDAGR_RightBtn
{
	idc = IDC_CTAB_BTNFN;
	tooltip = "Toggle Text on/off";
};
class cTab_microDAGR_btnMapType: cTab_RscButton_microDAGR_LeftUp
{
	idc = -1;
	tooltip = "Toggle Map Type";
};
class cTab_microDAGR_on_screen_battery: cTab_RscPicture
{
	idc = -1;
	text = "\cTab\img\icon_battery_ca.paa";
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_LEFT_X);
	y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_T + (cTab_GUI_microDAGR_OSD_ELEMENT_STD_H - cTab_GUI_microDAGR_OSD_ICON_STD_SIZE) / 2);
	w = pxToScreen_W(cTab_GUI_microDAGR_OSD_ICON_STD_SIZE);
	h = pxToScreen_H(cTab_GUI_microDAGR_OSD_ICON_STD_SIZE);
	colorText[] = COLOR_WHITE;
};
class cTab_microDAGR_on_screen_time: cTab_RscText_microDAGR
{
	idc = IDC_CTAB_OSD_TIME;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_CENTER_X);
	y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_T);
};
class cTab_microDAGR_on_screen_signalStrength: cTab_microDAGR_on_screen_battery
{
	idc = -1;
	text = "\cTab\img\icon_signalStrength_ca.paa";
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_RIGHT_X + cTab_GUI_microDAGR_OSD_ELEMENT_STD_W - cTab_GUI_microDAGR_OSD_ICON_STD_SIZE * 2);
	colorText[] = COLOR_WHITE;
};
class cTab_microDAGR_on_screen_satellite: cTab_microDAGR_on_screen_battery
{
	idc = -1;
	text = "\a3\ui_f\data\map\Diary\signal_ca.paa";
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_RIGHT_X + cTab_GUI_microDAGR_OSD_ELEMENT_STD_W - cTab_GUI_microDAGR_OSD_ICON_STD_SIZE);
	colorText[] = COLOR_WHITE;
};
class cTab_microDAGR_on_screen_dirDegree: cTab_RscText_microDAGR
{
	idc = IDC_CTAB_OSD_DIR_DEGREE;
	style = ST_LEFT;
	y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_B);
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_LEFT_X);
};
class cTab_microDAGR_on_screen_grid: cTab_microDAGR_on_screen_dirDegree
{
	idc = IDC_CTAB_OSD_GRID;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_CENTER_X);
};
class cTab_microDAGR_on_screen_dirOctant: cTab_microDAGR_on_screen_dirDegree
{
	idc = IDC_CTAB_OSD_DIR_OCTANT;
	style = ST_RIGHT;
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_RIGHT_X);
};
class cTab_microDAGR_on_screen_hookGrid: cTab_RscText_microDAGR
{
	idc = IDC_CTAB_OSD_HOOK_GRID;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_microDAGR_OSD_RIGHT_X);
	y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_MARGIN - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H * 3);
	colorText[] = {1,1,1,0.5};
	colorBackground[] = {0,0,0,0.25};
};
class cTab_microDAGR_on_screen_hookDst: cTab_microDAGR_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DST;
	y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_MARGIN - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H * 2);
};
class cTab_microDAGR_on_screen_hookDir: cTab_microDAGR_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DIR;
	y = pxToScreen_Y(cTab_GUI_microDAGR_OSD_EDGE_B - cTab_GUI_microDAGR_OSD_MARGIN - cTab_GUI_microDAGR_OSD_ELEMENT_STD_H);
};
