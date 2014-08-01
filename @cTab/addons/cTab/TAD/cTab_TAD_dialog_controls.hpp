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
class cTab_RscHTML_TAD_upDownArrow: cTab_RscPicture
{
	w = cTab_GUI_TAD_OSD_ELEMENT_STD_W / GUI_GRID_PX_W * GUI_GRID_W;
	h = cTab_GUI_TAD_OSD_ICON_H / GUI_GRID_PX_H * GUI_GRID_H;
	colorText[] = COLOR_NEON_GREEN;
	colorBackground[] = COLOR_BLACK;
	text = "\a3\ui_f\data\IGUI\Cfg\Actions\autohover_ca.paa"
};