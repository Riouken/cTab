// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

#define GUI_GRID_X	(0)
#define GUI_GRID_Y	(0)
#define GUI_GRID_W	(0.025)
#define GUI_GRID_H	(0.04)
#define GUI_GRID_WAbs	(1)
#define GUI_GRID_HAbs	(1)


class cTab_Mail_ico_disp {
	idd = 13672;
	name=__cTabMailico;
	onLoad = "uiNamespace setVariable ['cTab_Mail_ico_disp', _this select 0]";
	fadein = 0;
	fadeout = 0;
	duration = 10e10;
	controlsBackground[] = {};
	objects[] = {};
	 class controls {
		class trin_image {
			idc = 1110;
			type = CT_STATIC;
			style = ST_PICTURE;
			colorBackground[] = { };
			colorText[] = { };
			font = puristaLight;
			sizeEx = 0.053;
			x = 38.5 * GUI_GRID_W + GUI_GRID_X;
			y = -4.5 * GUI_GRID_H + GUI_GRID_Y;
			w = 1.5 * GUI_GRID_W;
			h = 1.2 * GUI_GRID_H;
			text = "\cTab\img\icoUnopenedmail.paa";
		};
		
	};
};
