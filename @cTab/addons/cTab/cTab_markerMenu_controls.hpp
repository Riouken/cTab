class MainSubmenu: cTab_RscControlsGroup
{
	idc = 3300;
	x = MENU_X;
	y = MENU_Y;
	w = MENU_W;
	h = MENU_H(3);
	class controls
	{
		class mainbg: cTab_IGUIBack
		{
			idc = IDC_USRMN_MAINBG;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_H(3);
		};
		class op4btn: cTab_ActiveText
		{
			idc = IDC_USRMN_OP4BTN;
			text = "Enemy SALUTE"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [4,cTabColorRed];Nop = [11] call cTabUsrMenuSelect;";
		};
		class medbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MEDBTN;
			text = "Medical"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 1;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [4,cTabColorGreen];Nop = [21] call cTabUsrMenuSelect;";
		};
		class genbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_GENBTN;
			text = "General"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 2;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [4,cTabColorBlue];Nop = [31] call cTabUsrMenuSelect;";
		};
	};
};

class EnemySub1: cTab_RscControlsGroup
{
	idc = 3301;
	x = MENU_X;
	y = MENU_Y;
	w = MENU_W;
	h = MENU_H(7);
	class controls
	{
		class IGUIBack_2201: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2202;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_H(7);
		};
		class infbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_INFBTN;
			text = "Infantry"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_inf.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class mecinfbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MECINFBTN;
			text = "Mec Inf"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 1;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_mech_inf.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};

		class motrinfbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MOTRINFBTN;
			text = "Motr Inf"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 2;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_motor_inf.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class amrbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_AMRBTN;
			text = "Armor"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 3;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_armor.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class helibtn: cTab_ActiveText
		{
			idc = IDC_USRMN_HELIBTN;
			text = "Helicopter"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 4;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_air.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class plnbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_PLNBTN;
			text = "Plane"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 5;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_plane.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class uknbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_UKNBTN;
			text = "Unknown"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 6;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_unknown.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
	};
};

class EnemySub2: cTab_RscControlsGroup
{
	idc = 3303;
	x = MENU_X;
	y = MENU_Y;
	w = MENU_W;
	h = MENU_H(6);
	class controls
	{
		class IGUIBack_2202: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2202;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_H(6);
		};
		class ftbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_FTBTN;
			text = "Fire Team"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class patbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_PATBTN;
			text = "Patrol"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 1;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class sqdbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SQDBTN;
			text = "Squad"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 2;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_1.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class sctbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SCTBTN;
			text = "Section"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 3;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_2.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class pltnbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_PLTNBTN;
			text = "Platoon"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 4;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_3.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class cpnybtn: cTab_ActiveText
		{
			idc = IDC_USRMN_CPNYBTN;
			text = "Company"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 5;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_4.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
	};
};

class EnemySub3: cTab_RscControlsGroup
{
	idc = 3304;
	x = MENU_X;
	y = MENU_Y;
	w = MENU_W;
	h = MENU_H(10);
	class controls
	{
		class IGUIBack_2203: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2203;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_H(10);
		};

		class nthbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_NTHBTN;
			text = "N"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,0];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class nebtn: cTab_ActiveText
		{
			idc = IDC_USRMN_NEBTN;
			text = "NE"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 1;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,45];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class ebtn: cTab_ActiveText
		{
			idc = IDC_USRMN_EBTN;
			text = "E"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 2;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,90];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class sebtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SEBTN;
			text = "SE"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 3;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,135];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class sbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SBTN;
			text = "S"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 4;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,180];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class swbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SWBTN;
			text = "SW"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 5;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,225];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class wbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_WBTN;
			text = "W"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 6;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,270];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class RscText_1022: cTab_ActiveText
		{
			idc = IDC_USRMN_RSCTEXT_1022;
			text = "NW"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 7;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,315];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class RscText_1023: cTab_ActiveText
		{
			idc = IDC_USRMN_RSCTEXT_1023;
			text = "Unknown"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 8;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,500];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class stnbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_STNBTN;
			text = "Stationary"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 9;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [3,700];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
	};
};

class CasulSub1: cTab_RscControlsGroup
{
	idc = 3305;
	x = MENU_X;
	y = MENU_Y;
	w = MENU_W;
	h = MENU_H(4);
	class controls
	{
		class IGUIBack_2204: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2204;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_H(4);
		};
		class casltybtn: cTab_ActiveText
		{
			idc = IDC_USRMN_CASLTYBTN;
			text = "Casualty"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\join_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
		class ccpbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_CCPBTN;
			text = "CCP"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 1;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\circle_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
		class basbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_BASBTN;
			text = "BAS"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 2;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\mapcontrol\Hospital_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
		class mcibtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MCIBTN;
			text = "MCI"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 3;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\warning_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
	};
};

class GenSub1: cTab_RscControlsGroup
{
	idc = 3306;
	x = MENU_X;
	y = MENU_Y;
	w = MENU_W;
	h = MENU_H(2);
	class controls
	{
		class IGUIBack_2205: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2205;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_H(2);
		};
		class hqbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_HQBTN;
			text = "Headquarters"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\b_hq.paa'];nop = [] call cTabUserIconPush;Nop = [30] call cTabUsrMenuSelect;";
		};
		class lzbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_LZBTN;
			text = "LZ"; //--- ToDo: Localize;
			x = 0;
			y = MENU_elementH * 1;
			w = MENU_W;
			h = MENU_elementH;
			sizeEx = MENU_sizeEx;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\end_CA.paa'];nop = [] call cTabUserIconPush;Nop = [30] call cTabUsrMenuSelect;";
		};
	};
};