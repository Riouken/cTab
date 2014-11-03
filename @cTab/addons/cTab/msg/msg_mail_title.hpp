// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

#define GUI_GRID_H	(0.048)
#define GUI_GRID_W	(GUI_GRID_H * 3/4)
#define GUI_GRID_X	(safezoneX + safezoneW * (1 - 0.00675) - GUI_GRID_W)
#define GUI_GRID_Y	(safezoneY + safezoneH * 0.25)

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
			x = GUI_GRID_X;
			y = GUI_GRID_Y;
			w = GUI_GRID_W;
			h = GUI_GRID_H;
			text = "\cTab\img\icon_mail_ca.paa";
		};
	};
};
