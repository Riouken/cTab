// Background definition
#define GUI_GRID_PX_W 2048 // width in pixels
#define GUI_GRID_PX_H 2048 // hight in pixels

// Base macros to convert pixel space to screen space
#define pxToScreen_X(PIXEL) (PIXEL) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X
#define pxToScreen_Y(PIXEL) (PIXEL) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y
#define pxToScreen_W(PIXEL) (PIXEL) / GUI_GRID_PX_W * GUI_GRID_W
#define pxToScreen_H(PIXEL) (PIXEL) / GUI_GRID_PX_H * GUI_GRID_H

// Map position within background, pixel based
#define cTab_GUI_android_MAP_X (452)
#define cTab_GUI_android_MAP_Y (713)
#define cTab_GUI_android_MAP_W (1067)
#define cTab_GUI_android_MAP_H (622)

// Height of header and footer OSD elements
#define cTab_GUI_android_OSD_HEADER_H (60)
#define cTab_GUI_android_OSD_FOOTER_H (0)

// Screen content (the stuff that changes, so map area - header and footer)
#define cTab_GUI_android_SCREEN_CONTENT_X (cTab_GUI_android_MAP_X)
#define cTab_GUI_android_SCREEN_CONTENT_Y (cTab_GUI_android_MAP_Y + cTab_GUI_android_OSD_HEADER_H)
#define cTab_GUI_android_SCREEN_CONTENT_W (cTab_GUI_android_MAP_W)
#define cTab_GUI_android_SCREEN_CONTENT_H (cTab_GUI_android_MAP_H - cTab_GUI_android_OSD_HEADER_H - cTab_GUI_android_OSD_FOOTER_H)

// Base macros to convert pixel space to screen space, but for groups (same size as map)
#define pxToGroup_X(PIXEL) (((PIXEL) - cTab_GUI_android_SCREEN_CONTENT_X) / GUI_GRID_PX_W * GUI_GRID_W)
#define pxToGroup_Y(PIXEL) (((PIXEL) - cTab_GUI_android_SCREEN_CONTENT_Y) / GUI_GRID_PX_H * GUI_GRID_H)

// Message element positions in pixels
#define cTab_GUI_android_MESSAGE_MARGIN_OUTER (20)
#define cTab_GUI_android_MESSAGE_MARGIN_INNER (10)

#define cTab_GUI_android_MESSAGE_BUTTON_H (60)

#define cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_X (cTab_GUI_android_MAP_X + cTab_GUI_android_MESSAGE_MARGIN_OUTER)
#define cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_Y (cTab_GUI_android_MAP_Y + cTab_GUI_android_OSD_HEADER_H + cTab_GUI_android_MESSAGE_MARGIN_INNER)
#define cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_W (cTab_GUI_android_MAP_W - cTab_GUI_android_MESSAGE_MARGIN_OUTER * 2)
#define cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_H (cTab_GUI_android_MAP_H - cTab_GUI_android_OSD_HEADER_H - cTab_GUI_android_MESSAGE_MARGIN_INNER * 2)

#define cTab_GUI_android_MESSAGE_MESSAGELIST_X (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_X + cTab_GUI_android_MESSAGE_MARGIN_INNER)
#define cTab_GUI_android_MESSAGE_MESSAGELIST_Y (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_Y + cTab_GUI_android_MESSAGE_MARGIN_OUTER)
#define cTab_GUI_android_MESSAGE_MESSAGELIST_W ((cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_W - cTab_GUI_android_MESSAGE_MARGIN_INNER * 3) / 3)
#define cTab_GUI_android_MESSAGE_MESSAGELIST_H (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_H - cTab_GUI_android_MESSAGE_MARGIN_INNER * 3 - cTab_GUI_android_MESSAGE_MARGIN_OUTER - cTab_GUI_android_MESSAGE_BUTTON_H * 2)

#define cTab_GUI_android_MESSAGE_MESSAGETEXT_X (cTab_GUI_android_MESSAGE_MESSAGELIST_X + cTab_GUI_android_MESSAGE_MESSAGELIST_W + cTab_GUI_android_MESSAGE_MARGIN_INNER)
#define cTab_GUI_android_MESSAGE_MESSAGETEXT_Y (cTab_GUI_android_MESSAGE_MESSAGELIST_Y)
#define cTab_GUI_android_MESSAGE_MESSAGETEXT_W (cTab_GUI_android_MESSAGE_MESSAGELIST_W * 2)
#define cTab_GUI_android_MESSAGE_MESSAGETEXT_H (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_H - cTab_GUI_android_MESSAGE_MARGIN_OUTER -cTab_GUI_android_MESSAGE_MARGIN_INNER)

#define cTab_GUI_android_MESSAGE_COMPOSE_FRAME_X (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_X)
#define cTab_GUI_android_MESSAGE_COMPOSE_FRAME_Y (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_Y)
#define cTab_GUI_android_MESSAGE_COMPOSE_FRAME_W (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_W)
#define cTab_GUI_android_MESSAGE_COMPOSE_FRAME_H (cTab_GUI_android_MESSAGE_MESSAGETEXT_FRAME_H)

#define cTab_GUI_android_MESSAGE_PLAYERLIST_X (cTab_GUI_android_MESSAGE_MESSAGELIST_X)
#define cTab_GUI_android_MESSAGE_PLAYERLIST_Y (cTab_GUI_android_MESSAGE_COMPOSE_FRAME_Y + cTab_GUI_android_MESSAGE_MARGIN_OUTER)
#define cTab_GUI_android_MESSAGE_PLAYERLIST_W (cTab_GUI_android_MESSAGE_MESSAGELIST_W)
#define cTab_GUI_android_MESSAGE_PLAYERLIST_H (cTab_GUI_android_MESSAGE_MESSAGELIST_H)

#define cTab_GUI_android_MESSAGE_COMPOSE_TEXT_X (cTab_GUI_android_MESSAGE_MESSAGETEXT_X)
#define cTab_GUI_android_MESSAGE_COMPOSE_TEXT_Y (cTab_GUI_android_MESSAGE_PLAYERLIST_Y)
#define cTab_GUI_android_MESSAGE_COMPOSE_TEXT_W (cTab_GUI_android_MESSAGE_MESSAGETEXT_W)
#define cTab_GUI_android_MESSAGE_COMPOSE_TEXT_H (cTab_GUI_android_MESSAGE_MESSAGETEXT_H)

#define cTab_GUI_android_MESSAGE_BUTTON_W (cTab_GUI_android_MESSAGE_MESSAGELIST_W)

#define cTab_GUI_android_MESSAGE_BUTTON_SEND_X (cTab_GUI_android_MESSAGE_COMPOSE_FRAME_X + cTab_GUI_android_MESSAGE_MARGIN_INNER)
#define cTab_GUI_android_MESSAGE_BUTTON_SEND_Y (cTab_GUI_android_MESSAGE_PLAYERLIST_Y + cTab_GUI_android_MESSAGE_PLAYERLIST_H + cTab_GUI_android_MESSAGE_MARGIN_INNER)

#define cTab_GUI_android_MESSAGE_BUTTON_DELETE_X (cTab_GUI_android_MESSAGE_BUTTON_SEND_X)
#define cTab_GUI_android_MESSAGE_BUTTON_DELETE_Y (cTab_GUI_android_MESSAGE_BUTTON_SEND_Y)

#define cTab_GUI_android_MESSAGE_BUTTON_MODE_X (cTab_GUI_android_MESSAGE_BUTTON_SEND_X)
#define cTab_GUI_android_MESSAGE_BUTTON_MODE_Y (cTab_GUI_android_MESSAGE_BUTTON_SEND_Y + cTab_GUI_android_MESSAGE_MARGIN_INNER + cTab_GUI_android_MESSAGE_BUTTON_H)

// On-screen edge positions (left, right, top, bottom)
#define cTab_GUI_android_OSD_MARGIN (20)
#define cTab_GUI_android_OSD_EDGE_L (cTab_GUI_android_OSD_MARGIN + cTab_GUI_android_MAP_X)
#define cTab_GUI_android_OSD_EDGE_R (-cTab_GUI_android_OSD_MARGIN + cTab_GUI_android_MAP_X + cTab_GUI_android_MAP_W)
#define cTab_GUI_android_OSD_EDGE_T (cTab_GUI_android_OSD_MARGIN + cTab_GUI_android_MAP_Y)
#define cTab_GUI_android_OSD_EDGE_B (-cTab_GUI_android_OSD_FOOTER_H + cTab_GUI_android_MAP_Y + cTab_GUI_android_MAP_H)

// On-screen element base width and height
#define cTab_GUI_android_OSD_ELEMENT_STD_W ((cTab_GUI_android_MAP_W - cTab_GUI_android_OSD_MARGIN * 6) / 5)
#define cTab_GUI_android_OSD_ELEMENT_STD_H (cTab_GUI_android_OSD_HEADER_H - cTab_GUI_android_OSD_MARGIN)

// On-screen element X-coord for left, center and right elements
#define cTab_GUI_android_OSD_X(ITEM) (cTab_GUI_android_OSD_EDGE_L + (cTab_GUI_android_OSD_MARGIN + cTab_GUI_android_OSD_ELEMENT_STD_W) * (ITEM - 1))

// On-screen text sizes, hight in pixels
// Standard text elements
#define cTab_GUI_android_OSD_TEXT_STD_SIZE (38)
#define cTab_GUI_android_OSD_ICON_STD_SIZE (42)

// On-screen map centre cursor
#define cTab_GUI_android_CURSOR (48)

// On-screen menu frame
#define cTab_GUI_android_OSD_MENU_W (cTab_GUI_android_SCREEN_CONTENT_W / 4)
#define cTab_GUI_android_OSD_MENU_H (cTab_GUI_android_SCREEN_CONTENT_H)
#define cTab_GUI_android_OSD_MENU_X (cTab_GUI_android_SCREEN_CONTENT_X + cTab_GUI_android_SCREEN_CONTENT_W - cTab_GUI_android_OSD_MENU_W)
#define cTab_GUI_android_OSD_MENU_Y (cTab_GUI_android_SCREEN_CONTENT_Y)

// On-screen menu elelements
#define cTab_GUI_android_OSD_MENU_MARGIN_W (cTab_GUI_android_OSD_MENU_W * 0.05)
#define cTab_GUI_android_OSD_MENU_MARGIN_H (cTab_GUI_android_OSD_MENU_H * 0.05)
#define cTab_GUI_android_OSD_MENU_ELEMENT_X (cTab_GUI_android_OSD_MENU_X + cTab_GUI_android_OSD_MENU_MARGIN_W)
#define cTab_GUI_android_OSD_MENU_ELEMENT_W (cTab_GUI_android_OSD_MENU_W - (cTab_GUI_android_OSD_MENU_MARGIN_W * 2))
#define cTab_GUI_android_OSD_MENU_ELEMENT_H ((cTab_GUI_android_OSD_MENU_H - cTab_GUI_android_OSD_MENU_MARGIN_H * 8) / 7)
#define cTab_GUI_android_OSD_MENU_ELEMENT_Y(ITEM) (cTab_GUI_android_OSD_MENU_Y + cTab_GUI_android_OSD_MENU_MARGIN_H + (cTab_GUI_android_OSD_MENU_ELEMENT_H + cTab_GUI_android_OSD_MENU_MARGIN_H) * (ITEM - 1))

// like to pxToGrou, just for the menu
#define pxToMenu_X(PIXEL) (((PIXEL) - cTab_GUI_android_OSD_MENU_X) / GUI_GRID_PX_W * GUI_GRID_W)
#define pxToMenu_Y(PIXEL) (((PIXEL) - cTab_GUI_android_OSD_MENU_Y) / GUI_GRID_PX_H * GUI_GRID_H)

// set IDC counter to 0
__EXEC(cTab_IDC = 0);
#define IDC_COUNTER __EXEC(cTab_IDC = cTab_IDC + 1); idc = __EVAL(cTab_IDC);

class cTab_RscText_Android: cTab_RscText
{
	style = ST_CENTER;
	w = pxToScreen_W(cTab_GUI_android_OSD_ELEMENT_STD_W);
	h = pxToScreen_H(cTab_GUI_android_OSD_ELEMENT_STD_H);
	font = GUI_FONT_MONO;
	colorText[] = COLOR_WHITE;
	sizeEx = pxToScreen_H(cTab_GUI_android_OSD_TEXT_STD_SIZE);
	colorBackground[] = COLOR_TRANSPARENT;
	shadow = 0;
};
class cTab_android_RscMapControl: cTab_RscMapControl
{
	idc = IDC_CTAB_SCREEN;
	text = "#(argb,8,8,3)color(1,1,1,1)";
	x = pxToScreen_X(cTab_GUI_android_SCREEN_CONTENT_X);
	y = pxToScreen_Y(cTab_GUI_android_SCREEN_CONTENT_Y);
	w = pxToScreen_W(cTab_GUI_android_SCREEN_CONTENT_W);
	h = pxToScreen_H(cTab_GUI_android_SCREEN_CONTENT_H);
	//type = CT_MAP;
	// allow to zoom out further (defines the maximum map scale, usually 1)
	scaleMax = 1000;
	// set initial map scale
	scaleDefault = "(missionNamespace getVariable 'cTabMapScale') * 0.86 / safezoneH";
	// turn on satellite map information (defines the map scale of when to switch to topographical)
	maxSatelliteAlpha = 10000;
	alphaFadeStartScale = 10;
	alphaFadeEndScale = 10;

	// Rendering density coefficients
	ptsPerSquareSea = 8 / cTab_android_DLGtoDSP_fctr;		// seas
	ptsPerSquareTxt = 8 / cTab_android_DLGtoDSP_fctr;		// textures
	ptsPerSquareCLn = 8 / cTab_android_DLGtoDSP_fctr;		// count-lines
	ptsPerSquareExp = 8 / cTab_android_DLGtoDSP_fctr;		// exposure
	ptsPerSquareCost = 8 / cTab_android_DLGtoDSP_fctr;		// cost

	// Rendering thresholds
	ptsPerSquareFor = 3 / cTab_android_DLGtoDSP_fctr;		// forests
	ptsPerSquareForEdge = 100 / cTab_android_DLGtoDSP_fctr;	// forest edges
	ptsPerSquareRoad = 1.5 / cTab_android_DLGtoDSP_fctr;		// roads
	ptsPerSquareObj = 4 / cTab_android_DLGtoDSP_fctr;		// other objects

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
class cTab_android_background: cTab_RscPicture
{
	idc = IDC_CTAB_BACKGROUND;
	text = ""; // will be set during onLoad event
	x = GUI_GRID_X;
	y = GUI_GRID_Y;
	w = GUI_GRID_W;
	h = GUI_GRID_H;
};
class cTab_android_btnBack: cTab_RscButtonInv
{
	x = pxToScreen_X(1609);
	y = pxToScreen_Y(806);
	w = pxToScreen_W(102);
	h = pxToScreen_H(102);
};
class cTab_android_btnMenu: cTab_android_btnBack
{
	y = pxToScreen_Y(1140);
};
class cTab_android_btnHome: cTab_android_btnBack
{
	x = pxToScreen_X(1613);
	y = pxToScreen_Y(972);
};
class cTab_android_btnPower: cTab_RscButtonInv
{
	x = pxToScreen_X(1583);
	y = pxToScreen_Y(1407);
	w = pxToScreen_W(107);
	h = pxToScreen_H(48);
};
class cTab_android_notificationLight
{
	x = pxToScreen_X(1793);
	y = pxToScreen_Y(768);
	w = pxToScreen_W(61);
	h = pxToScreen_H(61);
};
class cTab_android_header: cTab_RscPicture
{
	IDC_COUNTER
	text = "#(argb,8,8,3)color(0,0,0,1)";
	x = pxToScreen_X(cTab_GUI_android_MAP_X);
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y);
	w = pxToScreen_W(cTab_GUI_android_MAP_W);
	h = pxToScreen_H(cTab_GUI_android_OSD_HEADER_H);
};
class cTab_android_on_screen_battery: cTab_RscPicture
{
	IDC_COUNTER
	text = "\cTab\img\icon_battery_ca.paa";
	x = pxToScreen_X(cTab_GUI_android_OSD_X(1));
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y + (cTab_GUI_android_OSD_HEADER_H - cTab_GUI_android_OSD_ICON_STD_SIZE) / 2);
	w = pxToScreen_W(cTab_GUI_android_OSD_ICON_STD_SIZE);
	h = pxToScreen_H(cTab_GUI_android_OSD_ICON_STD_SIZE);
	colorText[] = COLOR_WHITE;
};
class cTab_android_on_screen_time: cTab_RscText_android
{
	idc = IDC_CTAB_OSD_TIME;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_android_OSD_X(3));
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y + (cTab_GUI_android_OSD_HEADER_H - cTab_GUI_android_OSD_TEXT_STD_SIZE) / 2);
};
class cTab_android_on_screen_signalStrength: cTab_android_on_screen_battery
{
	IDC_COUNTER
	text = "\cTab\img\icon_signalStrength_ca.paa";
	x = pxToScreen_X(cTab_GUI_android_OSD_X(5) + cTab_GUI_android_OSD_ELEMENT_STD_W - cTab_GUI_android_OSD_ICON_STD_SIZE * 2);
	colorText[] = COLOR_WHITE;
};
class cTab_android_on_screen_satellite: cTab_android_on_screen_battery
{
	IDC_COUNTER
	text = "\a3\ui_f\data\map\Diary\signal_ca.paa";
	x = pxToScreen_X(cTab_GUI_android_OSD_X(5) + cTab_GUI_android_OSD_ELEMENT_STD_W - cTab_GUI_android_OSD_ICON_STD_SIZE);
	colorText[] = COLOR_WHITE;
};
class cTab_android_on_screen_dirDegree: cTab_android_on_screen_time
{
	idc = IDC_CTAB_OSD_DIR_DEGREE;
	style = ST_LEFT;
	x = pxToScreen_X(cTab_GUI_android_OSD_X(2));
};
class cTab_android_on_screen_grid: cTab_android_on_screen_dirDegree
{
	idc = IDC_CTAB_OSD_GRID;
	style = ST_RIGHT;
	x = pxToScreen_X(cTab_GUI_android_OSD_X(4));
};
class cTab_android_on_screen_dirOctant: cTab_android_on_screen_dirDegree
{
	idc = IDC_CTAB_OSD_DIR_OCTANT;
	style = ST_RIGHT;
	x = pxToScreen_X(cTab_GUI_android_OSD_X(1));
};
class cTab_android_on_screen_hookGrid: cTab_RscText_Android
{
	idc = IDC_CTAB_OSD_HOOK_GRID;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_android_OSD_X(1));
	y = pxToScreen_Y(cTab_GUI_android_OSD_EDGE_B - cTab_GUI_android_OSD_MARGIN - cTab_GUI_android_OSD_ELEMENT_STD_H * 4);
	colorText[] = {1,1,1,0.5};
	colorBackground[] = {0,0,0,0.25};
};
class cTab_android_on_screen_hookElevation: cTab_android_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_ELEVATION;
	y = pxToScreen_Y(cTab_GUI_android_OSD_EDGE_B - cTab_GUI_android_OSD_MARGIN - cTab_GUI_android_OSD_ELEMENT_STD_H * 3);
};
class cTab_android_on_screen_hookDst: cTab_android_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DST;
	y = pxToScreen_Y(cTab_GUI_android_OSD_EDGE_B - cTab_GUI_android_OSD_MARGIN - cTab_GUI_android_OSD_ELEMENT_STD_H * 2);
};
class cTab_android_on_screen_hookDir: cTab_android_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DIR;
	y = pxToScreen_Y(cTab_GUI_android_OSD_EDGE_B - cTab_GUI_android_OSD_MARGIN - cTab_GUI_android_OSD_ELEMENT_STD_H);
};
class cTab_android_loadingtxt: cTab_RscText_android
{
	idc = IDC_CTAB_LOADINGTXT;
	style = ST_CENTER;
	text = "Loading"; //--- ToDo: Localize;
	x = pxToScreen_X(cTab_GUI_android_SCREEN_CONTENT_X);
	y = pxToScreen_Y(cTab_GUI_android_SCREEN_CONTENT_Y);
	w = pxToScreen_W(cTab_GUI_android_SCREEN_CONTENT_W);
	h = pxToScreen_H(cTab_GUI_android_SCREEN_CONTENT_H);
	colorBackground[] = COLOR_LIGHT_BLUE;
};
class cTab_android_windowsBG: cTab_RscPicture
{
	idc = IDC_CTAB_WIN_BACK;
	text = "#(argb,8,8,3)color(0.2,0.431,0.647,1)";
	x = pxToScreen_X(cTab_GUI_android_MAP_X);
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y);
	w = pxToScreen_W(cTab_GUI_android_MAP_W);
	h = pxToScreen_H(cTab_GUI_android_MAP_H);
};

// Define areas around the screen as interaction areas to allow screen movement
class cTab_android_movingHandle_T: cTab_RscText_android
{
	IDC_COUNTER
	moving = 1;
	colorBackground[] = COLOR_TRANSPARENT;
	x = pxToScreen_X(0);
	y = pxToScreen_Y(0);
	w = pxToScreen_W(GUI_GRID_PX_W);
	h = pxToScreen_H(cTab_GUI_android_MAP_Y);
};
class cTab_android_movingHandle_B: cTab_android_movingHandle_T
{
	IDC_COUNTER
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y + cTab_GUI_android_MAP_H);
	h = pxToScreen_H(GUI_GRID_PX_H - (cTab_GUI_android_MAP_Y + cTab_GUI_android_MAP_H));
};
class cTab_android_movingHandle_L: cTab_android_movingHandle_T
{
	IDC_COUNTER
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y);
	w = pxToScreen_W(cTab_GUI_android_MAP_X);
	h = pxToScreen_H(cTab_GUI_android_MAP_H);
};
class cTab_android_movingHandle_R: cTab_android_movingHandle_L
{
	IDC_COUNTER
	x = pxToScreen_X(cTab_GUI_android_MAP_X + cTab_GUI_android_MAP_W);
	w = pxToScreen_W(GUI_GRID_PX_W - (cTab_GUI_android_MAP_X + cTab_GUI_android_MAP_W));
};

// transparent control that gets placed on top of the GUI to adjust brightness
class cTab_android_brightness: cTab_RscText_Android
{
	idc = IDC_CTAB_BRIGHTNESS;
	x = pxToScreen_X(cTab_GUI_android_MAP_X);
	y = pxToScreen_Y(cTab_GUI_android_MAP_Y);
	w = pxToScreen_W(cTab_GUI_android_MAP_W);
	h = pxToScreen_H(cTab_GUI_android_MAP_H);
	colorBackground[] = COLOR_TRANSPARENT;
};
class cTab_android_notification: cTab_RscText_Android {
	idc = IDC_CTAB_NOTIFICATION;
	x = pxToScreen_X(cTab_GUI_android_SCREEN_CONTENT_X + (cTab_GUI_android_SCREEN_CONTENT_W * 0.2) / 2);
	y = pxToScreen_Y(cTab_GUI_android_SCREEN_CONTENT_Y + cTab_GUI_android_SCREEN_CONTENT_H - 2 * cTab_GUI_android_OSD_TEXT_STD_SIZE);
	w = pxToScreen_W(cTab_GUI_android_SCREEN_CONTENT_W * 0.8);
	colorBackground[] = COLOR_BLACK;
};