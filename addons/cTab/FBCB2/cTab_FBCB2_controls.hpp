// Background definition
#define GUI_GRID_PX_W 2048 // width in pixels
#define GUI_GRID_PX_H 2048 // hight in pixels

// Base macros to convert pixel space to screen space
#define pxToScreen_X(PIXEL) (PIXEL) / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X
#define pxToScreen_Y(PIXEL) (PIXEL) / GUI_GRID_PX_H * GUI_GRID_H + GUI_GRID_Y
#define pxToScreen_W(PIXEL) (PIXEL) / GUI_GRID_PX_W * GUI_GRID_W
#define pxToScreen_H(PIXEL) (PIXEL) / GUI_GRID_PX_H * GUI_GRID_H

// Map position within background, pixel based
#define cTab_GUI_FBCB2_MAP_X (685)
#define cTab_GUI_FBCB2_MAP_Y (608)
#define cTab_GUI_FBCB2_MAP_W (810)
#define cTab_GUI_FBCB2_MAP_H (810)

// Height of header and footer OSD elements
#define cTab_GUI_FBCB2_OSD_HEADER_H (44)
#define cTab_GUI_FBCB2_OSD_FOOTER_H (0)

// Screen content (the stuff that changes, so map area - header and footer)
#define cTab_GUI_FBCB2_SCREEN_CONTENT_X (cTab_GUI_FBCB2_MAP_X)
#define cTab_GUI_FBCB2_SCREEN_CONTENT_Y (cTab_GUI_FBCB2_MAP_Y + cTab_GUI_FBCB2_OSD_HEADER_H)
#define cTab_GUI_FBCB2_SCREEN_CONTENT_W (cTab_GUI_FBCB2_MAP_W)
#define cTab_GUI_FBCB2_SCREEN_CONTENT_H (cTab_GUI_FBCB2_MAP_H - cTab_GUI_FBCB2_OSD_HEADER_H - cTab_GUI_FBCB2_OSD_FOOTER_H)

// Base macros to convert pixel space to screen space, but for groups (same size as map)
#define pxToGroup_X(PIXEL) (((PIXEL) - cTab_GUI_FBCB2_SCREEN_CONTENT_X) / GUI_GRID_PX_W * GUI_GRID_W)
#define pxToGroup_Y(PIXEL) (((PIXEL) - cTab_GUI_FBCB2_SCREEN_CONTENT_Y) / GUI_GRID_PX_H * GUI_GRID_H)

// Message element positions in pixels
#define cTab_GUI_FBCB2_MESSAGE_MARGIN_OUTER (10)
#define cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER (5)

#define cTab_GUI_FBCB2_MESSAGE_BUTTON_W (90)
#define cTab_GUI_FBCB2_MESSAGE_BUTTON_H (30)

#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_X (cTab_GUI_FBCB2_SCREEN_CONTENT_X + cTab_GUI_FBCB2_MESSAGE_MARGIN_OUTER)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_Y (cTab_GUI_FBCB2_SCREEN_CONTENT_Y + cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_W (cTab_GUI_FBCB2_SCREEN_CONTENT_W - cTab_GUI_FBCB2_MESSAGE_MARGIN_OUTER * 2)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_H ((cTab_GUI_FBCB2_SCREEN_CONTENT_H - cTab_GUI_FBCB2_TASKBAR_H - cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER * 3) / 2)

#define cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_X (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_X + cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_Y (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_Y + cTab_GUI_FBCB2_MESSAGE_MARGIN_OUTER)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_W ((cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_W - cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER * 3) / 3)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_H (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_H - cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER - cTab_GUI_FBCB2_MESSAGE_MARGIN_OUTER)

#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_X (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_X + cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_W + cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_Y (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_Y)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_W (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_W * 2)
#define cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_H (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_H - cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER - cTab_GUI_FBCB2_MESSAGE_BUTTON_H)

#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_X (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_X)
#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_Y (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_Y + cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_H + cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER)
#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_W (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_W)
#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_H (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_FRAME_H)

#define cTab_GUI_FBCB2_MESSAGE_PLAYERLIST_X (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_X)
#define cTab_GUI_FBCB2_MESSAGE_PLAYERLIST_Y (cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_Y + cTab_GUI_FBCB2_MESSAGE_MARGIN_OUTER)
#define cTab_GUI_FBCB2_MESSAGE_PLAYERLIST_W (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_W)
#define cTab_GUI_FBCB2_MESSAGE_PLAYERLIST_H (cTab_GUI_FBCB2_MESSAGE_MESSAGELIST_H)

#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_TEXT_X (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_X)
#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_TEXT_Y (cTab_GUI_FBCB2_MESSAGE_PLAYERLIST_Y)
#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_TEXT_W (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_W)
#define cTab_GUI_FBCB2_MESSAGE_COMPOSE_TEXT_H (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_H)

#define cTab_GUI_FBCB2_MESSAGE_BUTTON_SEND_X (cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_X + cTab_GUI_FBCB2_MESSAGE_COMPOSE_FRAME_W - cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER - cTab_GUI_FBCB2_MESSAGE_BUTTON_W)
#define cTab_GUI_FBCB2_MESSAGE_BUTTON_SEND_Y (cTab_GUI_FBCB2_MESSAGE_COMPOSE_TEXT_Y + cTab_GUI_FBCB2_MESSAGE_COMPOSE_TEXT_H + cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER)

#define cTab_GUI_FBCB2_MESSAGE_BUTTON_DELETE_X (cTab_GUI_FBCB2_MESSAGE_BUTTON_SEND_X)
#define cTab_GUI_FBCB2_MESSAGE_BUTTON_DELETE_Y (cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_Y + cTab_GUI_FBCB2_MESSAGE_MESSAGETEXT_H + cTab_GUI_FBCB2_MESSAGE_MARGIN_INNER)

// On-screen edge positions (left, right, top, bottom)
#define cTab_GUI_FBCB2_OSD_MARGIN (15)
#define cTab_GUI_FBCB2_OSD_EDGE_L (cTab_GUI_FBCB2_OSD_MARGIN + cTab_GUI_FBCB2_SCREEN_CONTENT_X)
#define cTab_GUI_FBCB2_OSD_EDGE_R (-cTab_GUI_FBCB2_OSD_MARGIN + cTab_GUI_FBCB2_SCREEN_CONTENT_X + cTab_GUI_FBCB2_SCREEN_CONTENT_W)
#define cTab_GUI_FBCB2_OSD_EDGE_T (cTab_GUI_FBCB2_OSD_MARGIN + cTab_GUI_FBCB2_SCREEN_CONTENT_Y)
#define cTab_GUI_FBCB2_OSD_EDGE_B (-cTab_GUI_FBCB2_OSD_FOOTER_H + cTab_GUI_FBCB2_MAP_Y + cTab_GUI_FBCB2_MAP_H)

// On-screen element base width and height
#define cTab_GUI_FBCB2_OSD_ELEMENT_STD_W ((cTab_GUI_FBCB2_SCREEN_CONTENT_W - cTab_GUI_FBCB2_OSD_MARGIN * 6) / 5)
#define cTab_GUI_FBCB2_OSD_ELEMENT_STD_H (cTab_GUI_FBCB2_OSD_HEADER_H - cTab_GUI_FBCB2_OSD_MARGIN)

// On-screen element X-coord for left, center and right elements
#define cTab_GUI_FBCB2_OSD_LEFT_X (cTab_GUI_FBCB2_OSD_EDGE_L)
#define cTab_GUI_FBCB2_OSD_CENTER_X (cTab_GUI_FBCB2_OSD_EDGE_L + cTab_GUI_FBCB2_OSD_MARGIN + cTab_GUI_FBCB2_OSD_ELEMENT_STD_W)
#define cTab_GUI_FBCB2_OSD_RIGHT_X (cTab_GUI_FBCB2_OSD_EDGE_R - cTab_GUI_FBCB2_OSD_ELEMENT_STD_W)

// On-screen element X-coord for left, center and right elements
#define cTab_GUI_FBCB2_OSD_X(ITEM) (cTab_GUI_FBCB2_OSD_EDGE_L + (cTab_GUI_FBCB2_OSD_MARGIN + cTab_GUI_FBCB2_OSD_ELEMENT_STD_W) * (ITEM - 1))

// On-screen text sizes, hight in pixels
// Standard text elements
#define cTab_GUI_FBCB2_OSD_TEXT_STD_SIZE (24)
#define cTab_GUI_FBCB2_OSD_ICON_STD_SIZE (28.5)

// On-screen map centre cursor
#define cTab_GUI_FBCB2_CURSOR (76)

// set IDC counter to 0
__EXEC(cTab_IDC = 0);
#define IDC_COUNTER __EXEC(cTab_IDC = cTab_IDC + 1); idc = __EVAL(cTab_IDC);

class cTab_RscText_FBCB2: cTab_RscText
{
	style = ST_CENTER;
	w = pxToScreen_W(cTab_GUI_FBCB2_OSD_ELEMENT_STD_W);
	h = pxToScreen_H(cTab_GUI_FBCB2_OSD_ELEMENT_STD_H);
	font = GUI_FONT_MONO;
	colorText[] = COLOR_WHITE;
	sizeEx = pxToScreen_H(cTab_GUI_FBCB2_OSD_TEXT_STD_SIZE);
	colorBackground[] = COLOR_TRANSPARENT;
	shadow = 0;
};
class cTab_FBCB2_background: cTab_RscPicture
{
	idc = IDC_CTAB_BACKGROUND;
	text = "\cTab\img\FBCB2.paa";
	x = GUI_GRID_X;
	y = GUI_GRID_Y;
	w = GUI_GRID_W;
	h = GUI_GRID_H;
};
class cTab_FBCB2_header: cTab_RscPicture
{
	IDC_COUNTER
	text = "#(argb,8,8,3)color(0,0,0,1)";
	x = pxToScreen_X(cTab_GUI_FBCB2_MAP_X);
	y = pxToScreen_Y(cTab_GUI_FBCB2_MAP_Y);
	w = pxToScreen_W(cTab_GUI_FBCB2_MAP_W);
	h = pxToScreen_H(cTab_GUI_FBCB2_OSD_HEADER_H);
};
class cTab_FBCB2_on_screen_battery: cTab_RscPicture
{
	IDC_COUNTER
	text = "\cTab\img\icon_battery_ca.paa";
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(1));
	y = pxToScreen_Y(cTab_GUI_FBCB2_MAP_Y + (cTab_GUI_FBCB2_OSD_HEADER_H - cTab_GUI_FBCB2_OSD_ICON_STD_SIZE) / 2);
	w = pxToScreen_W(cTab_GUI_FBCB2_OSD_ICON_STD_SIZE);
	h = pxToScreen_H(cTab_GUI_FBCB2_OSD_ICON_STD_SIZE);
	colorText[] = COLOR_WHITE;
};
class cTab_FBCB2_on_screen_time: cTab_RscText_FBCB2
{
	idc = IDC_CTAB_OSD_TIME;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(3));
	y = pxToScreen_Y(cTab_GUI_FBCB2_MAP_Y + (cTab_GUI_FBCB2_OSD_HEADER_H - cTab_GUI_FBCB2_OSD_TEXT_STD_SIZE) / 2);
};
class cTab_FBCB2_on_screen_signalStrength: cTab_FBCB2_on_screen_battery
{
	IDC_COUNTER
	text = "\cTab\img\icon_signalStrength_ca.paa";
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(5) + cTab_GUI_FBCB2_OSD_ELEMENT_STD_W - cTab_GUI_FBCB2_OSD_ICON_STD_SIZE * 2);
	colorText[] = COLOR_WHITE;
};
class cTab_FBCB2_on_screen_satellite: cTab_FBCB2_on_screen_battery
{
	IDC_COUNTER
	text = "\a3\ui_f\data\map\Diary\signal_ca.paa";
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(5) + cTab_GUI_FBCB2_OSD_ELEMENT_STD_W - cTab_GUI_FBCB2_OSD_ICON_STD_SIZE);
	colorText[] = COLOR_WHITE;
};
class cTab_FBCB2_on_screen_dirDegree: cTab_FBCB2_on_screen_time
{
	idc = IDC_CTAB_OSD_DIR_DEGREE;
	style = ST_LEFT;
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(2));
};
class cTab_FBCB2_on_screen_grid: cTab_FBCB2_on_screen_dirDegree
{
	idc = IDC_CTAB_OSD_GRID;
	style = ST_RIGHT;
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(4));
};
class cTab_FBCB2_on_screen_dirOctant: cTab_FBCB2_on_screen_dirDegree
{
	idc = IDC_CTAB_OSD_DIR_OCTANT;
	style = ST_RIGHT;
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_X(1));
};
class cTab_FBCB2_btnF1: cTab_RscButtonInv
{
	x = pxToScreen_X(762);
	y = pxToScreen_Y(1452);
	w = pxToScreen_W(70);
	h = pxToScreen_H(40);
};
class cTab_FBCB2_btnF2: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(846);
};
class cTab_FBCB2_btnF3: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(929);
};
class cTab_FBCB2_btnF4: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(1013);
};
class cTab_FBCB2_btnF5: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(1097);
};
class cTab_FBCB2_btnF6: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(1180);
};
class cTab_FBCB2_btnF7: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(1264);
};
class cTab_FBCB2_btnF8: cTab_FBCB2_btnF1
{
	x = pxToScreen_X(1349);
};
class cTab_FBCB2_btnPWR: cTab_RscButtonInv
{
	x = pxToScreen_X(592);
	y = pxToScreen_Y(603);
	w = pxToScreen_W(40);
	h = pxToScreen_H(70);
};
class cTab_FBCB2_btnBRTplus: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(680);
};
class cTab_FBCB2_btnBRTminus: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(759);
};
class cTab_FBCB2_btnBLKOUT: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(839);
};
class cTab_FBCB2_btnESC: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(918);
};
class cTab_FBCB2_btnRight: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(998);
};
class cTab_FBCB2_btnUp: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(1079);
};
class cTab_FBCB2_btnDown: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(1161);
};
class cTab_FBCB2_btnENT: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(1241);
};
class cTab_FBCB2_btnFCN: cTab_FBCB2_btnPWR
{
	y = pxToScreen_Y(1322);
};
class cTab_FBCB2_on_screen_hookGrid: cTab_RscText_FBCB2
{
	idc = IDC_CTAB_OSD_HOOK_GRID;
	style = ST_CENTER;
	x = pxToScreen_X(cTab_GUI_FBCB2_OSD_RIGHT_X);
	y = pxToScreen_Y(cTab_GUI_FBCB2_OSD_EDGE_B - cTab_GUI_FBCB2_OSD_MARGIN - cTab_GUI_FBCB2_OSD_ELEMENT_STD_H * 4);
	colorText[] = {1,1,1,0.5};
	colorBackground[] = {0,0,0,0.25};
};
class cTab_FBCB2_on_screen_hookElevation: cTab_FBCB2_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_ELEVATION;
	y = pxToScreen_Y(cTab_GUI_FBCB2_OSD_EDGE_B - cTab_GUI_FBCB2_OSD_MARGIN - cTab_GUI_FBCB2_OSD_ELEMENT_STD_H * 3);
};
class cTab_FBCB2_on_screen_hookDst: cTab_FBCB2_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DST;
	y = pxToScreen_Y(cTab_GUI_FBCB2_OSD_EDGE_B - cTab_GUI_FBCB2_OSD_MARGIN - cTab_GUI_FBCB2_OSD_ELEMENT_STD_H * 2);
};
class cTab_FBCB2_on_screen_hookDir: cTab_FBCB2_on_screen_hookGrid
{
	idc = IDC_CTAB_OSD_HOOK_DIR;
	y = pxToScreen_Y(cTab_GUI_FBCB2_OSD_EDGE_B - cTab_GUI_FBCB2_OSD_MARGIN - cTab_GUI_FBCB2_OSD_ELEMENT_STD_H);
};
class cTab_FBCB2_loadingtxt: cTab_RscText_FBCB2
{
	idc = IDC_CTAB_LOADINGTXT;
	style = ST_CENTER;
	text = "Loading"; //--- ToDo: Localize;
	x = pxToScreen_X(cTab_GUI_FBCB2_SCREEN_CONTENT_X);
	y = pxToScreen_Y(cTab_GUI_FBCB2_SCREEN_CONTENT_Y);
	w = pxToScreen_W(cTab_GUI_FBCB2_SCREEN_CONTENT_W);
	h = pxToScreen_H(cTab_GUI_FBCB2_SCREEN_CONTENT_H);
	colorBackground[] = COLOR_BLACK;
};
class cTab_FBCB2_notification: cTab_RscText_FBCB2 {
	idc = IDC_CTAB_NOTIFICATION;
	x = pxToScreen_X(cTab_GUI_FBCB2_SCREEN_CONTENT_X + (cTab_GUI_FBCB2_SCREEN_CONTENT_W * 0.2) / 2);
	y = pxToScreen_Y(cTab_GUI_FBCB2_SCREEN_CONTENT_Y + cTab_GUI_FBCB2_SCREEN_CONTENT_H - 2 * cTab_GUI_FBCB2_OSD_TEXT_STD_SIZE);
	w = pxToScreen_W(cTab_GUI_FBCB2_SCREEN_CONTENT_W * 0.8);
	colorBackground[] = COLOR_BLACK;
};