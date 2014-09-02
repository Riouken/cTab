class MainSubmenu: cTab_RscControlsGroup
{
	idc = 3300;
	x = 12.5 * MENU_GRID_W + MENU_GRID_X;
	y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
	w = 5 * MENU_GRID_W;
	h = 5 * MENU_GRID_H;
	class controls
	{
		class mainbg: cTab_IGUIBack
		{
			idc = IDC_USRMN_MAINBG;
			x = 0;
			y = 0;
			w = 3 * MENU_GRID_W;
			h = 2 * MENU_GRID_H;
		};

		class op4btn: cTab_ActiveText
		{
			idc = IDC_USRMN_OP4BTN;
			text = "Enemy SALUTE"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [4,cTabColorRed];Nop = [11] call cTabUsrMenuSelect;";
		};

		class medbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MEDBTN;
			text = "Medical"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 1;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [4,cTabColorGreen];Nop = [21] call cTabUsrMenuSelect;";
		};

		class genbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_GENBTN;
			text = "General"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 2;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [4,cTabColorBlue];Nop = [31] call cTabUsrMenuSelect;";
		};
	};
};

class EnemySub1: cTab_RscControlsGroup
{
	idc = 3301;
	x = 12.5 * MENU_GRID_W + MENU_GRID_X;
	y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
	w = 5 * MENU_GRID_W;
	h = 5 * MENU_GRID_H;
	class controls
	{
		class IGUIBack_2201: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2202;
			x = 0;
			y = 0;
			w = 3.5 * MENU_GRID_W;
			h = 4.01389 * MENU_GRID_H;
		};

		class infbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_INFBTN;
			text = "Infantry"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_inf.paa'];Nop = [12] call cTabUsrMenuSelect;";

		};
		class mecinfbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MECINFBTN;
			text = "Mec Inf"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 1;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_mech_inf.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};

		class motrinfbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MOTRINFBTN;
			text = "Motr Inf"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 2;
			w = 2.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_motor_inf.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class amrbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_AMRBTN;
			text = "Armor"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 3;
			w = 2.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_armor.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class helibtn: cTab_ActiveText
		{
			idc = IDC_USRMN_HELIBTN;
			text = "Helicopter"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 4;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_air.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class plnbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_PLNBTN;
			text = "Plane"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 5;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_plane.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
		class uknbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_UKNBTN;
			text = "Unknown"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 6;
			w = 3.45833 * MENU_GRID_W;
			h = 0.430556 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_unknown.paa'];Nop = [12] call cTabUsrMenuSelect;";
		};
	};
};


class EnemySub2: cTab_RscControlsGroup
{
	idc = 3303;
	x = 12.5 * MENU_GRID_W + MENU_GRID_X;
	y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
	w = 5 * MENU_GRID_W;
	h = 5 * MENU_GRID_H;
	class controls
	{

		class IGUIBack_2202: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2202;
			x = 0;
			y = 0;
			w = 2.9375 * MENU_GRID_W;
			h = 4.01389 * MENU_GRID_H;
		};
		class ftbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_FTBTN;
			text = "Fire Team"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class patbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_PATBTN;
			text = "Patrol"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 1;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class sqdbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SQDBTN;
			text = "Squad"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 2;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_1.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class sctbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SCTBTN;
			text = "Section"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 3;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_2.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class pltnbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_PLTNBTN;
			text = "Platoon"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 4;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_3.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
		class cpnybtn: cTab_ActiveText
		{
			idc = IDC_USRMN_CPNYBTN;
			text = "Company"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 5;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_4.paa'];Nop = [13] call cTabUsrMenuSelect;";
		};
	};
};


class EnemySub3: cTab_RscControlsGroup
{
	idc = 3304;
	x = 12.5 * MENU_GRID_W + MENU_GRID_X;
	y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
	w = 5 * MENU_GRID_W;
	h = 7 * MENU_GRID_H;
	class controls
	{

		class IGUIBack_2203: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2203;
			x = 0;
			y = 0;
			w = 2.10417 * MENU_GRID_W;
			h = 6.72685 * MENU_GRID_H;
		};

		class nthbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_NTHBTN;
			text = "N"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,0];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class nebtn: cTab_ActiveText
		{
			idc = IDC_USRMN_NEBTN;
			text = "NE"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 1;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,45];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class ebtn: cTab_ActiveText
		{
			idc = IDC_USRMN_EBTN;
			text = "E"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 2;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,90];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class sebtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SEBTN;
			text = "SE"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 3;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,135];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class sbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SBTN;
			text = "S"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 4;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,180];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class swbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_SWBTN;
			text = "SW"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 5;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,225];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class wbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_WBTN;
			text = "W"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 6;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,270];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class RscText_1022: cTab_ActiveText
		{
			idc = IDC_USRMN_RSCTEXT_1022;
			text = "NW"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 7;
			w = 1.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,315];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};
		class RscText_1023: cTab_ActiveText
		{
			idc = IDC_USRMN_RSCTEXT_1023;
			text = "Unknown"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 8;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,500];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};

		class stnbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_STNBTN;
			text = "Stationary"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 9;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [3,700];nop = [] call cTabUserIconPush;Nop = [10] call cTabUsrMenuSelect;";
		};


	};
};




class CasulSub1: cTab_RscControlsGroup
{
	idc = 3305;
	x = 12.5 * MENU_GRID_W + MENU_GRID_X;
	y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
	w = 5 * MENU_GRID_W;
	h = 5 * MENU_GRID_H;
	class controls
	{

		class IGUIBack_2204: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2204;
			x = 0;
			y = 0;
			w = 2.77083 * MENU_GRID_W;
			h = 2.70833 * MENU_GRID_H;
		};
		class casltybtn: cTab_ActiveText
		{
			idc = IDC_USRMN_CASLTYBTN;
			text = "Casualty"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\join_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
		class ccpbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_CCPBTN;
			text = "CCP"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 1;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\circle_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
		class basbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_BASBTN;
			text = "BAS"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 2;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\mapcontrol\Hospital_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};

		class mcibtn: cTab_ActiveText
		{
			idc = IDC_USRMN_MCIBTN;
			text = "MCI"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 3;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\warning_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20] call cTabUsrMenuSelect;";
		};
	};
};

class GenSub1: cTab_RscControlsGroup
{
	idc = 3306;
	x = 12.5 * MENU_GRID_W + MENU_GRID_X;
	y = 7.5 * MENU_GRID_H + MENU_GRID_Y;
	w = 5 * MENU_GRID_W;
	h = 5 * MENU_GRID_H;
	class controls
	{

		class IGUIBack_2205: cTab_IGUIBack
		{
			idc = IDC_USRMN_IGUIBACK_2205;
			x = 0;
			y = 0;
			w = 2.5 * MENU_GRID_W;
			h = 1.5 * MENU_GRID_H;
		};


		class hqbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_HQBTN;
			text = "Headquarters"; //--- ToDo: Localize;
			x = 0;
			y = 0;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\b_hq.paa'];nop = [] call cTabUserIconPush;Nop = [30] call cTabUsrMenuSelect;";
		};
		class lzbtn: cTab_ActiveText
		{
			idc = IDC_USRMN_LZBTN;
			text = "LZ"; //--- ToDo: Localize;
			x = 0;
			y = (0.5 * MENU_GRID_H) * 1;
			w = 3.5 * MENU_GRID_W;
			h = 0.5 * MENU_GRID_H;
			sizeEx = .5 * MENU_GRID_H;
			action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\end_CA.paa'];nop = [] call cTabUserIconPush;Nop = [30] call cTabUsrMenuSelect;";
		};
	};
};