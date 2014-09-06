// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


//--- cTab
#include <cTab_gui_uav_macros.hpp>

#define GUI_GRID_X	(safezoneX)
#define GUI_GRID_Y	(safezoneY)
#define GUI_GRID_W	(safezoneW / 40)
#define GUI_GRID_H	(safezoneH / 25)
#define GUI_GRID_WAbs	(safezoneW)
#define GUI_GRID_HAbs	(safezoneH)


class cTab_hCam_dlg {
	idd = 1772;
	movingEnable = true;
	onLoad = "uiNamespace setVariable ['cTab_hCam_dlg', (_this select 0)];nul = [] execVM '\cTab\hcam\ctab_gui_hcam_onload.sqf';";
	onUnload = "_nop = [] call cTabHcamDelCam;uiNamespace setVariable ['cTab_main_dlg', displayNull];call cTab_fnc_close;";
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

			class HcamListBG: cTab_RscPicture
			{
				moving = 1;
				idc = 478594;
				text = "\cTab\img\window_2.jpg";
				x = 11.02 * GUI_GRID_W + GUI_GRID_X;
				y = 5.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 8.5 * GUI_GRID_W;
				h = 6 * GUI_GRID_H;
			};

			class HcamMapBG: cTab_RscPicture
			{
				moving = 1;
				idc = 478594;
				text = "\cTab\img\window_2.jpg";
				x = 11.02 * GUI_GRID_W + GUI_GRID_X;
				y = 11.69 * GUI_GRID_H + GUI_GRID_Y;
				w = 8.5 * GUI_GRID_W;
				h = 7 * GUI_GRID_H;
			};

			class HcamVidBG: cTab_RscPicture
			{
				moving = 1;
				idc = 478594;
				text = "\cTab\img\window_2.jpg";
				x = 20.44 * GUI_GRID_W + GUI_GRID_X;
				y = 7.95 * GUI_GRID_H + GUI_GRID_Y;
				w = 8.5 * GUI_GRID_W;
				h = 8.5 * GUI_GRID_H;
			};				
							
			class cTabuavmap: cTab_RscMapControl
			{
				idc = IDC_CTAB_CTABUAVMAP;
				text = "#(argb,8,8,3)color(1,1,1,1)";
				x = 11.27 * GUI_GRID_W + GUI_GRID_X;
				y = 12.47 * GUI_GRID_H + GUI_GRID_Y;
				w = 8 * GUI_GRID_W;
				h = 6 * GUI_GRID_H;
				onDraw = "nop = _this call cTabOnDrawHCam;";
				//onMouseButtonDblClick = "";
				
			};

			
			
		};


	class controls {

			class cTabuavlist: cTab_RscListbox
			{
				idc = IDC_CTAB_CTABUAVLIST;
				x = 11.31 * GUI_GRID_W + GUI_GRID_X;
				y = 6.23 * GUI_GRID_H + GUI_GRID_Y;
				w = 8 * GUI_GRID_W;
				h = 5 * GUI_GRID_H;
				onLBSelChanged = "_nop = _this execVM '\cTab\hcam\cTab_gui_hcam_cam.sqf';";
			};
			class cTabuavdisplay: cTab_RscPicture
			{
				idc = IDC_CTAB_CTABUAVDISPLAY;
				text = "#(argb,512,512,1)r2t(rendertarget12,1.0)";
				x = 20.71 * GUI_GRID_W + GUI_GRID_X;
				y = 8.92 * GUI_GRID_H + GUI_GRID_Y;
				w = 8 * GUI_GRID_W;
				h = 7.18056 * GUI_GRID_H;
			};

/*			
			class cTabuav2nddisplay: cTab_RscPicture
			{
				idc = IDC_CTAB_CTABUAV2NDDISPLAY;
				text = "#(argb,512,512,1)r2t(rendertarget13,1.0)";
				x = 20 * GUI_GRID_W + GUI_GRID_X;
				y = 12 * GUI_GRID_H + GUI_GRID_Y;
				w = 8 * GUI_GRID_W;
				h = 6 * GUI_GRID_H;
			};	
*/	
			class btnF1: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF1;
				x = 14.29 * GUI_GRID_W + GUI_GRID_X;
				y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Blue Force Tracker - Quick Key";
				action = "_nop = [0,player,vehicle player] spawn cTab_load_BFT;";
			};
			class btnF2: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF2;
				x = 15.19 * GUI_GRID_W + GUI_GRID_X;
				y = 19.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "UAV Intel Live Feed - Quick Key";
				action = "_ok = [0,player,vehicle player] execVM 'cTab\uav\cTab_gui_uav_start.sqf';";
			};
			class btnF3: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF3;
				x = 16.07 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Helmet Cam Live Feed - Quick Key";
				action = "_ok = [0,player,vehicle player] execVM 'cTab\hcam\cTab_gui_hcam_start.sqf';";
			};
			class btnF4: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNF4;
				x = 16.94 * GUI_GRID_W + GUI_GRID_X;
				y = 19.49 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				tooltip = "Text Message Application - Quick Key";
				action = "_ok = [0,player,vehicle player] spawn cTab_spawn_msg_dlg;";
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
				action = "_ok = [0,player,vehicle player] execVM 'cTab\cTab_gui_start.sqf';";
			};
			class btnFN: cTab_RscButtonInv
			{
				idc = IDC_CTAB_BTNFN;
				x = 20.63 * GUI_GRID_W + GUI_GRID_X;
				y = 19.51 * GUI_GRID_H + GUI_GRID_Y;
				w = 0.683335 * GUI_GRID_W;
				h = 0.731482 * GUI_GRID_H;
				action = "['cTab_hCam_dlg'] call cTab_fnc_iconText_toggle;";
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
				action = "call cTab_hCam_Full_View;";  // _ok = createDialog 'cTab_Hcam_View_Exit';
				tooltip = "View Optics";
			};
				
	};

};


class cTab_Hcam_View_Exit {
	idd = 13057;
	movingEnable = false;
	onLoad = "";
	onUnload = "";
	objects[] = {};
	class controlsBackground {};
	class controls {
			class actExitTxt: cTab_ActiveText
			{
				idc = 130471;
				text = "EXIT"; //--- ToDo: Localize;
				x = 0.1 * GUI_GRID_W + GUI_GRID_X;
				y = 3.5 * GUI_GRID_H + GUI_GRID_Y;
				w = 5 * GUI_GRID_W;
				h = 1.5 * GUI_GRID_H;
				action = "player switchCamera 'INTERNAL';closeDialog 0;";
			};
	};
	
};