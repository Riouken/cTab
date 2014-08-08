// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


//--- cTab
#include <cTab_gui_macros.hpp>
#include <usermenu_gui_macros.hpp>

#define GUI_GRID_X	(safezoneX)
#define GUI_GRID_Y	(safezoneY)
#define GUI_GRID_W	(safezoneW / 40)
#define GUI_GRID_H	(safezoneH / 25)
#define GUI_GRID_WAbs	(safezoneW)
#define GUI_GRID_HAbs	(safezoneH)


class cTab_main_dlg {
	idd = 1775154;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_main_dlg', (_this select 0)];nul = [] execVM '\cTab\main\onload.sqf';";
	onUnload = "uiNamespace setVariable ['cTab_main_dlg', displayNull];call cTab_fnc_close;";
	onKeyDown = "call cTab_keyDownShortcut";
	objects[] = {};
	class controlsBackground {


			class background: cTab_RscPicture
			{
				moving = 1;
				idc = IDC_CTAB_BACKGROUND;
				text = "\cTab\img\15th_rugged_tab.paa";
				x = 5.71 * GUI_GRID_W + GUI_GRID_X;
				y = -0.74 * GUI_GRID_H + GUI_GRID_Y;
				w = 27.5 * GUI_GRID_W;
				h = 26.5 * GUI_GRID_H;
			};
			
			
			class windowsBG: cTab_RscPicture
			{

				idc = 1247854;
				text = "#(argb,8,8,3)color(0.2,0.431,0.647,1)";
				x = 10.92 * GUI_GRID_W + GUI_GRID_X;
				y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
				w = 18.2292 * GUI_GRID_W;
				h = 13.4444 * GUI_GRID_H;
			};
			
			class windowsBar: cTab_RscPicture
			{

				idc = 1247858;
				text = "\cTab\img\Desktop_bar.jpg";
				x = 10.96 * GUI_GRID_W + GUI_GRID_X;
				y = 18.3 * GUI_GRID_H + GUI_GRID_Y;
				w = 18.1875 * GUI_GRID_W;
				h = 0.52315 * GUI_GRID_H;
			};			
			
			
			class screen: cTab_RscMapControl
			{
				idc = IDC_CTAB_SCREEN;
				text = "#(argb,8,8,3)color(1,1,1,1)";
				x = 10.92 * GUI_GRID_W + GUI_GRID_X;
				y = 5.4 * GUI_GRID_H + GUI_GRID_Y;
				w = 18.2292 * GUI_GRID_W;
				h = 13.4444 * GUI_GRID_H;
				onDraw = "nop = [] call cTabOnDrawbft;";
				onMouseButtonDblClick = "_ok = ['cTab_main_dlg',3300,1201,_this] execVM 'cTab\bft\userload.sqf';";
				onMouseButtonDown = "_ok = ['cTab_main_dlg',3300,1201,_this] spawn cTabDeleteUsrMkr;";
			};
				
			
		};


	class controls {

	
			class btnF1: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF1;
				x = 14.29 * GUI_GRID_W + GUI_GRID_X;
				y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Blue Force Tracker - Quick Key";
				action = "_nop = [] execVM '\cTab\main\loadBFT.sqf';";
			};
			class btnF2: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF2;
				x = 15.19 * GUI_GRID_W + GUI_GRID_X;
				y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "UAV Intel Live Feed - Quick Key";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\uav\cTab_gui_uav_start.sqf';";
			};
			class btnF3: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF3;
				x = 16.07 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Helmet Cam Live Feed - Quick Key";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';";
			};
			class btnF4: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF4;
				x = 16.94 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Text Message Application - Quick Key";
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] spawn cTab_spawn_msg_dlg;";
			};
			class btnF5: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF5;
				x = 17.84 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Not used yet*";
			};
			class btnF6: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF6;
				x = 18.71 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Not used yet*";
			};
			class btnMain: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNMAIN;
				x = 19.65 * GUI_GRID_W + GUI_GRID_X;
				y = 19.35 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Main Menu";
				action = "_ok = _this execVM 'cTab\main\onload.sqf';";
			};
			class btnFN: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNFN;
				x = 20.63 * GUI_GRID_W + GUI_GRID_X;
				y = 19.51 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "if (cTabBFTtxt) then {cTabBFTtxt = false;}else{cTabBFTtxt = true;};";
				tooltip = "Toggle Text on/off";
			};
			class btnOFF: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNOFF;
				x = 21.48 * GUI_GRID_W + GUI_GRID_X;
				y = 19.52 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "closeDialog 0;";
				tooltip = "Close Interface";
			};
			class btnUP: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNUP;
				x = 22.35 * GUI_GRID_W + GUI_GRID_X;
				y = 19.51 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "call cTab_fnc_txt_size_dec;";
				tooltip = "Decrease Font";
			};
			class btnDWN: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNDWN;
				x = 23.23 * GUI_GRID_W + GUI_GRID_X;
				y = 19.53 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "call cTab_fnc_txt_size_inc;";
				tooltip = "Increase Font";
			};
			class btnACT: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNACT;
				x = 26.56 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.1625 * GUI_GRID_W;
				h = 0.824071 * GUI_GRID_H;
				action = "if (count cTabUserIconList > 0) then { _nop = cTabUserIconList call BIS_fnc_arrayPop;};";
				tooltip = "Delete last user placed icon";
			};
			class loadingtxt: cTab_RscText
			{
				idc = IDC_CTAB_LOADINGTXT;
				text = "Loading"; //--- ToDo: Localize;
				x = 11.5 * GUI_GRID_W + GUI_GRID_X;
				y = 5.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 3 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
			};
			class actBFTtxt: cTab_ActiveText
			{
				style = ST_PICTURE;
				idc = IDC_CTAB_ACTBFTTXT;
				text = "\cTab\img\cTab_BFT_ico.paa" ;//"Blue Force Tracker"; //--- ToDo: Localize;
				x = 11.5 * GUI_GRID_W + GUI_GRID_X;
				y = 7.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.5 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "nul = [] execVM '\cTab\main\loadBFT.sqf';";
				toolTip = "FBCB2 - Blue Force Tracker";
			};
			class actUAVtxt: cTab_ActiveText
			{
				style = ST_PICTURE;
				idc = IDC_CTAB_ACTUAVTXT;
				text = "\cTab\img\cTab_UAV_ico.paa" ;//"UAV Intelligence"; //--- ToDo: Localize;
				x = 11.5 * GUI_GRID_W + GUI_GRID_X;
				y = 9 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.5 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\uav\cTab_gui_uav_start.sqf';";
				toolTip = "UAV Video Feeds";
			};
			class actVIDtxt: cTab_ActiveText
			{
				style = ST_PICTURE;
				idc = IDC_CTAB_ACTVIDTXT;
				text = "\cTab\img\cTab_HMC_ico.paa" ;//"Live Video Feeds"; //--- ToDo: Localize;
				x = 11.5 * GUI_GRID_W + GUI_GRID_X;
				y = 10.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.5 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';";
				toolTip = "Live Helmet Cam Video Feeds";
			};
			class actMSGtxt: cTab_ActiveText
			{
				style = ST_PICTURE;
				idc = IDC_CTAB_ACTMSGTXT;
				text = "\cTab\img\Mail_Main_Icon_ico.paa" ;
				x = 11.5 * GUI_GRID_W + GUI_GRID_X;
				y = 12.0 * GUI_GRID_H + GUI_GRID_Y;
				w = 1.5 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "_ok = [cTabIfOpen select 0,cTabIfOpen select 3,cTabIfOpen select 5] spawn cTab_spawn_msg_dlg;";
				toolTip = "Text Messaging System";
			};		

			
			//### Secondary Map Pop up	------------------------------------------------------------------------------------------------------	
			
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
						action = "cTabUserSelIcon set [4,cTabColorRed];Nop = [11,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [4,cTabColorGreen];Nop = [21,'cTab_main_dlg'] call cTabUsrMenuSelect;";						
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
						action = "cTabUserSelIcon set [4,cTabColorBlue];Nop = [31,'cTab_main_dlg'] call cTabUsrMenuSelect;";						
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_inf.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
						
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_mech_inf.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_motor_inf.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_armor.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_air.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_plane.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\o_unknown.paa'];Nop = [12,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_0.paa'];Nop = [13,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_1.paa'];Nop = [13,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_2.paa'];Nop = [13,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_3.paa'];Nop = [13,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [2,'\A3\ui_f\data\map\markers\nato\group_4.paa'];Nop = [13,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,0];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,45];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,90];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,135];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,180];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,225];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,270];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,315];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,500];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [3,700];nop = [] call cTabUserIconPush;Nop = [10,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\join_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\circle_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\mapcontrol\Hospital_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\warning_CA.paa'];nop = [] call cTabUserIconPush;Nop = [20,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\nato\b_hq.paa'];nop = [] call cTabUserIconPush;Nop = [30,'cTab_main_dlg'] call cTabUsrMenuSelect;";
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
						action = "cTabUserSelIcon set [1,'\A3\ui_f\data\map\markers\military\end_CA.paa'];nop = [] call cTabUserIconPush;Nop = [30,'cTab_main_dlg'] call cTabUsrMenuSelect;";
					};
			
										
					
				};
			};				
			
			
	
				
	};

};