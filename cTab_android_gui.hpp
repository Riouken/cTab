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



class cTab_Android_dlg {
	idd = 177382;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_Android_dlg', (_this select 0)];nul = [] execVM '\cTab\bft\ctab_gui_Android_onload.sqf';";
	onUnload = "";
	objects[] = {};
	class controlsBackground {

			class androidBG: cTab_RscPicture
			{
				idc = 1200;
				moving = 1;
				text = "\cTab\img\15th_android_2.paa";
				x = -17 * GUI_GRID_W + GUI_GRID_X;
				y = 6 * GUI_GRID_H + GUI_GRID_Y;
				w = 41.5 * GUI_GRID_W;
				h = 33 * GUI_GRID_H;
			};
			class bftscreen: cTab_RscMapControl
			{
				idc = 17354;
				text = "#(argb,8,8,3)color(1,1,1,1)";
				x = -7.5 * GUI_GRID_W + GUI_GRID_X;
				y = 16 * GUI_GRID_H + GUI_GRID_Y;
				w = 21 * GUI_GRID_W;
				h = 11 * GUI_GRID_H;
				onDraw = "nop = [] call cTabOnDrawbftAndroid;";
				onMouseButtonDblClick = "_ok = ['cTab_Android_dlg',3300,17354,_this] execVM 'cTab\bft\userload.sqf';";
			};
			
	};
	
	class controls {
	

			class menueBack: cTab_RscButtonInv
			{
				idc = 2400;
				x = 15.4 * GUI_GRID_W + GUI_GRID_X;
				y = 17.62 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
				tooltip = "Delete last user placed icon";
			};
			class menueMain: cTab_RscButtonInv
			{
				idc = 2401;
				x = 15.48 * GUI_GRID_W + GUI_GRID_X;
				y = 20.67 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				tooltip = "Main Menu ** Coming Soon";
			};
			class menueSub: cTab_RscButtonInv
			{
				idc = 2402;
				x = 15.56 * GUI_GRID_W + GUI_GRID_X;
				y = 23.71 * GUI_GRID_H + GUI_GRID_Y;
				w = 2 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "ctrlShow [3357, True];";
				tooltip = "Main Options";
			};
			
			// Main Menue
			
			class MainOptMenu: cTab_RscControlsGroup
			{
				idc = 3357;
				x = 5 * GUI_GRID_W + GUI_GRID_X;
				y = 20 * GUI_GRID_H + GUI_GRID_Y;
				w = 8 * GUI_GRID_W;
				h = 6.5 * GUI_GRID_H;
				class controls
				{
					class mainbg: cTab_IGUIBack
					{
						idc = 187452;
						x = 0;
						y = 0;
						w = 7.3 * GUI_GRID_W;
						h = 6.3 * GUI_GRID_H;
					};
					class mainMenTxtOnOff: cTab_RscText
					{
						idc = 124752;
						text = "Text on/off:"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 1.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
					};
					class mainMenIconUp: cTab_RscText
					{
						idc = 125781;
						text = "Icon Size Up:"; //--- ToDo: Localize;
						x = 0;
						y = (1.5 * GUI_GRID_H) * 1;
						w = 3.5 * GUI_GRID_W;
						h = 1.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
					};
					class mainMenIconDwn: cTab_RscText
					{
						idc = 124984;
						text = "Icon Size Dwn:"; //--- ToDo: Localize;
						x = 0;
						y = (1.5 * GUI_GRID_H) * 2;
						w = 3.5 * GUI_GRID_W;
						h = 1.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
					};
					class mainMenExit: cTab_RscText
					{
						idc = 123647;
						text = "Exit"; //--- ToDo: Localize;
						x = 0;
						y = (1.5 * GUI_GRID_H) * 3;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
					};
					class BtnTxtOnOff: cTab_ActiveText
					{
						idc = 23478;
						text = "On/Off"; //--- ToDo: Localize;
						x = (3 * GUI_GRID_W) * 1.5;
						y = (1.5 * GUI_GRID_H) * .1;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "if (cTabBFTtxt) then {cTabBFTtxt = false;}else{cTabBFTtxt = true;};";
					};
					class BtnTxtUp: cTab_ActiveText
					{
						idc = 214587;
						text = "Up"; //--- ToDo: Localize;
						x = (3 * GUI_GRID_W) * 1.5;
						y = (1.5 * GUI_GRID_H) * 1.1;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabTxtFctr = cTabTxtFctr + 1;";
					};
					class BtnTxtDwn: cTab_ActiveText
					{
						idc = 2345789;
						text = "Down"; //--- ToDo: Localize;
						x = (3 * GUI_GRID_W) * 1.5;
						y = (1.5 * GUI_GRID_H) * 2.1;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabTxtFctr = cTabTxtFctr - 1;";
					};
					class BtnTxtExit: cTab_ActiveText
					{
						idc = 2152471;
						text = "Close"; //--- ToDo: Localize;
						x = (3 * GUI_GRID_W) * 1.5;
						y = (1.5 * GUI_GRID_H) * 3.1;
						w = 3 * GUI_GRID_W;
						h = 1 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "ctrlShow [3357, False];";
					};		
				
				
				};
			};

// User Placed markers

			
			class MainSubmenu: cTab_RscControlsGroup
			{
				idc = 3300;
				x = 12.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 5 * GUI_GRID_H;
				class controls
				{
					class mainbg: cTab_IGUIBack
					{
						idc = IDC_USRMN_MAINBG;
						x = 0;
						y = 0 ;
						w = 3 * GUI_GRID_W;
						h = 2 * GUI_GRID_H;
					};
					
					class op4btn: cTab_ActiveText
					{
						idc = IDC_USRMN_OP4BTN;
						text = "Enemy SALUTE"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [4,cTabColorRed];Nop = [11,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};					
					
					class medbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_MEDBTN;
						text = "Medical"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 1;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [4,cTabColorGreen];Nop = [21,'cTab_Android_dlg'] call cTabUsrMenuSelect;";						
					};
					
					class genbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_GENBTN;
						text = "General"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 2;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [4,cTabColorBlue];Nop = [31,'cTab_Android_dlg'] call cTabUsrMenuSelect;";						
					};
										
					
				};
			};
			
			class EnemySub1: cTab_RscControlsGroup
			{
				idc = 3301;
				x = 12.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 5 * GUI_GRID_H;
				class controls
				{
					class IGUIBack_2201: cTab_IGUIBack
					{
						idc = IDC_USRMN_IGUIBACK_2202;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 4.01389 * GUI_GRID_H;
					};
					
					class infbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_INFBTN;
						text = "Infantry"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_inf.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
						
					};
					class mecinfbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_MECINFBTN;
						text = "Mec Inf"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 1;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_mech_inf.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					
					class motrinfbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_MOTRINFBTN;
						text = "Motr Inf"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 2;
						w = 2.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_motor_inf.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class amrbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_AMRBTN;
						text = "Armor"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 3;
						w = 2.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_armor.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class helibtn: cTab_ActiveText
					{
						idc = IDC_USRMN_HELIBTN;
						text = "Helicopter"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 4;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_air.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class plnbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_PLNBTN;
						text = "Plane"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 5;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_plane.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class uknbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_UKNBTN;
						text = "Unknown"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 6;
						w = 3.45833 * GUI_GRID_W;
						h = 0.430556 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_unknown.paa'];Nop = [12,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					
					
				};
			};


			class EnemySub2: cTab_RscControlsGroup
			{
				idc = 3303;
				x = 12.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 5 * GUI_GRID_H;
				class controls
				{
				
					class IGUIBack_2202: cTab_IGUIBack
					{
						idc = IDC_USRMN_IGUIBACK_2202;
						x = 0;
						y = 0;
						w = 2.9375 * GUI_GRID_W;
						h = 4.01389 * GUI_GRID_H;
					};	
					class ftbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_FTBTN;
						text = "Fire Team"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class patbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_PATBTN;
						text = "Patrol"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 1;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class sqdbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_SQDBTN;
						text = "Squad"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 2;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_1.paa'];Nop = [13,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class sctbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_SCTBTN;
						text = "Section"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 3;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_2.paa'];Nop = [13,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class pltnbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_PLTNBTN;
						text = "Platoon"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 4;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_3.paa'];Nop = [13,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class cpnybtn: cTab_ActiveText
					{
						idc = IDC_USRMN_CPNYBTN;
						text = "Company"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 5;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_4.paa'];Nop = [13,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};										
					
				};
			};			


			class EnemySub3: cTab_RscControlsGroup
			{
				idc = 3304;
				x = 12.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 7 * GUI_GRID_H;
				class controls
				{
				
					class IGUIBack_2203: cTab_IGUIBack
					{
						idc = IDC_USRMN_IGUIBACK_2203;
						x = 0;
						y = 0;
						w = 2.10417 * GUI_GRID_W;
						h = 6.72685 * GUI_GRID_H;
					};	
				
					class nthbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_NTHBTN;
						text = "N"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,0];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class nebtn: cTab_ActiveText
					{
						idc = IDC_USRMN_NEBTN;
						text = "NE"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 1;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,45];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class ebtn: cTab_ActiveText
					{
						idc = IDC_USRMN_EBTN;
						text = "E"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 2;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,90];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class sebtn: cTab_ActiveText
					{
						idc = IDC_USRMN_SEBTN;
						text = "SE"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 3;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,135];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class sbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_SBTN;
						text = "S"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 4;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,180];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class swbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_SWBTN;
						text = "SW"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 5;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,225];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class wbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_WBTN;
						text = "W"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 6;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,270];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class RscText_1022: cTab_ActiveText
					{
						idc = IDC_USRMN_RSCTEXT_1022;
						text = "NW"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 7;
						w = 1.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,315];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class RscText_1023: cTab_ActiveText
					{
						idc = IDC_USRMN_RSCTEXT_1023;
						text = "Unknown"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 8;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,500];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					
					class stnbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_STNBTN;
						text = "Stationary"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 9;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [3,700];nop = [] call cTabUserIconPush;Nop = [10,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
									
					
				};
			};	

			
			
			
			class CasulSub1: cTab_RscControlsGroup
			{
				idc = 3305;
				x = 12.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 5 * GUI_GRID_H;
				class controls
				{

					class IGUIBack_2204: cTab_IGUIBack
					{
						idc = IDC_USRMN_IGUIBACK_2204;
						x = 0;
						y = 0;
						w = 2.77083 * GUI_GRID_W;
						h = 2.70833 * GUI_GRID_H;
					};				
					class casltybtn: cTab_ActiveText
					{
						idc = IDC_USRMN_CASLTYBTN;
						text = "Casualty"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\join_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class ccpbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_CCPBTN;
						text = "CCP"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 1;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\circle_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class basbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_BASBTN;
						text = "BAS"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 2;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\mapcontrol\Hospital_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};				
				
					class mcibtn: cTab_ActiveText
					{
						idc = IDC_USRMN_MCIBTN;
						text = "MCI"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 3;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\warning_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};				
										
					
				};
			};			
			
			
			
			
			
			class GenSub1: cTab_RscControlsGroup
			{
				idc = 3306;
				x = 12.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 5 * GUI_GRID_H;
				class controls
				{
				
					class IGUIBack_2205: cTab_IGUIBack
					{
						idc = IDC_USRMN_IGUIBACK_2205;
						x = 0;
						y = 0;
						w = 2.5 * GUI_GRID_W;
						h = 1.5 * GUI_GRID_H;
					};
				
				
					class hqbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_HQBTN;
						text = "Headquarters"; //--- ToDo: Localize;
						x = 0;
						y = 0;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\b_hq.paa'];nop = [] call cTabUserIconPush;Nop = [30,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
					class lzbtn: cTab_ActiveText
					{
						idc = IDC_USRMN_LZBTN;
						text = "LZ"; //--- ToDo: Localize;
						x = 0;
						y = (0.5 * GUI_GRID_H) * 1;
						w = 3.5 * GUI_GRID_W;
						h = 0.5 * GUI_GRID_H;
						sizeEx = .5 * GUI_GRID_H;
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\end_CA.paa'];nop = [] call cTabUserIconPush;Nop = [30,'cTab_Android_dlg'] call cTabUsrMenuSelect;";
					};
			
										
					
				};
			};	





















			
			
	};
	
};
			