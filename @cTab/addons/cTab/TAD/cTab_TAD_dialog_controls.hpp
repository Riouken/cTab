#define GUI_GRID_X	(safezoneX + (safezoneW - safezoneH * 0.8 * 3/4) / 2)
#define GUI_GRID_Y	(safezoneY + 0.1 * safezoneH)
#define GUI_GRID_W	(safezoneH * 0.8 * 3/4)
#define GUI_GRID_H	(safezoneH * 0.8)
#define GUI_GRID_WAbs	(GUI_GRID_W)
#define GUI_GRID_HAbs	(GUI_GRID_H)
#define GUI_GRID_PX_W 2048 // width in pixels
#define GUI_GRID_PX_H 2048 // hight in pixels

#define COLOR_NEON_GREEN {57/255,255/255,20/255,1}
#define COLOR_BLACK {0,0,0,1}
#define COLOR_WHITE {1,1,1,1}

class cTab_RscButton_TAD_OSB: cTab_RscButtonInv
{
	w = 134 / GUI_GRID_PX_H * GUI_GRID_W;
	h = 134 / GUI_GRID_PX_H * GUI_GRID_H;
};
class cTab_RscButton_TAD_OSB01: cTab_RscButton_TAD_OSB
{
	x = 577 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 146 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
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
	y = 563 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB07: cTab_RscButton_TAD_OSB06
{
	y = 760 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB08: cTab_RscButton_TAD_OSB06
{
	y = 957 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB09: cTab_RscButton_TAD_OSB06
{
	y = 1155 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB10: cTab_RscButton_TAD_OSB06
{
	y = 1352 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB11: cTab_RscButton_TAD_OSB
{
	x = 1337 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1811 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
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
	y = 1352 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB17: cTab_RscButton_TAD_OSB16
{
	y = 1155 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB18: cTab_RscButton_TAD_OSB16
{
	y = 957 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB19: cTab_RscButton_TAD_OSB16
{
	y = 760 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_OSB20: cTab_RscButton_TAD_OSB16
{
	y = 563 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_ADJ_INC: cTab_RscButtonInv
{
	x = 124 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 257 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
	w = 142 / GUI_GRID_PX_H * GUI_GRID_W;
	h = 119 / GUI_GRID_PX_H * GUI_GRID_H;
};
class cTab_RscButton_TAD_ADJ_DEC: cTab_RscButton_TAD_ADJ_INC
{
	y = 376 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_DSP_INC: cTab_RscButton_TAD_ADJ_INC
{
	x = 1782 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_DSP_DEC: cTab_RscButton_TAD_DSP_INC
{
	y = 376 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_CON_INC: cTab_RscButton_TAD_ADJ_INC
{
	y = 1539 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_CON_DEC: cTab_RscButton_TAD_CON_INC
{
	y = 1658 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_BRT_INC: cTab_RscButton_TAD_CON_INC
{
	x = 1782 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_BRT_DEC: cTab_RscButton_TAD_BRT_INC
{
	y = 1658 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
};
class cTab_RscButton_TAD_SYM_INC: cTab_RscButtonInv
{
	x = 1663 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1811 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
	w = 119 / GUI_GRID_PX_H * GUI_GRID_W;
	h = 142 / GUI_GRID_PX_H * GUI_GRID_H;
};
class cTab_RscButton_TAD_SYM_DEC: cTab_RscButton_TAD_SYM_INC
{
	x = 1544 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
};
class cTab_RscButton_TAD_DNO: cTab_RscButtonInv
{
	x = 234 / GUI_GRID_PX_W * GUI_GRID_W + GUI_GRID_X;
	y = 1894 / GUI_GRID_PX_W * GUI_GRID_H + GUI_GRID_Y;
	w = 142 / GUI_GRID_PX_H * GUI_GRID_W;
	h = 142 / GUI_GRID_PX_H * GUI_GRID_H;
};