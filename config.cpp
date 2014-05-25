// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


#define PREFIX cTab
#define COMPONENT main
#define MAJOR 2
#define MINOR 0
#define PATCHLVL 0
#define BUILD 1
#define VERSION MAJOR.MINOR.PATCHLVL.BUILD
#define VERSION_AR MAJOR,MINOR,PATCHLVL,BUILD
#define REQUIRED_VERSION 1.0
#include "\x\cba\addons\main\script_macros_common.hpp"


class CfgPatches
{
	class PREFIX  // cTab
		{
			units[] = {};
			weapons[] = {};
			requiredVersion = REQUIRED_VERSION;
			requiredAddons[] = {"CBA_MAIN"};
			versionDesc = "cTab";
			versionAct = "";
			VERSION_CONFIG;
			author[] = {"Riouken"};
			authorUrl = "http://forums.bistudio.com/member.php?64032-Riouken";
		};
};

class CfgSettings 
{
	class CBA 
	{
		class Versioning 
		{
			class PREFIX 
			{
				class Dependencies 
				{
					CBA[] = {"cba_main", { 1,0,0 },"true"};
				};
			};
		};
	};
};

class CfgMods {
	class PREFIX {
		dir = "@cTab";
		name = "Commander's Tablet / FBCB2 - Blue Force Tracking";
		picture = "\cTab\img\cTab_BFT_ico.paa";
		hidePicture = "True";
		hideName = "True";
		actionName = "Website";
		action = "http://dev-heaven.net/projects/cca";
		description = "Battlefield tablet to access real time intel and blue force tracker.";
	};
};
class Extended_PostInit_EventHandlers
{
	class PREFIX
	{
		clientInit = QUOTE(call COMPILE_FILE2(\cTab\player_init.sqf));

		//serverInit = QUOTE(call COMPILE_FILE2(\cTab\server_init.sqf));
	};
};

#include <cTab_base_gui_classes.hpp>

#include <cTab_main_gui.hpp>
#include <cTab_Uav_gui.hpp>
#include <cTab_Hcam_gui.hpp>
#include <cTab_android_gui.hpp>
#include <cTab_veh_gui.hpp>
#include <\cTab\msg\msg_ctab_gui.hpp>

class CfgWeapons
{
    class ItemCore;
	class ItemcTab: ItemCore {
		descriptionshort = "8 inch Rugged Tablet";
		descriptionuse = "<t color='#9cf953'>Use: </t>Show Commander's Tablet";
		displayname = "Rugged Tablet";
		picture = "\cTab\img\15th_rugged_tab_ico.paa";
		scope = 2;
		simulation = "ItemGPS";
		class ItemInfo {
			mass = 1;
		};	
	};
	
	class ItemAndroid: ItemcTab {
		descriptionshort = "GL 300 Android";
		descriptionuse = "<t color='#9cf953'>Use: </t>Show Android Based BFT";
		displayname = "Android Device";
		picture = "\cTab\img\15th_android_2_ico.paa";
		scope = 2;
		simulation = "ItemGPS";
		class ItemInfo {
			mass = 1;
		};	
	};
	
	class ItemcTabHCam: ItemCore {
		descriptionshort = "HD Helmet Mounted Camera";
		descriptionuse = "<t color='#9cf953'>Use: </t>Used to record and stream video";
		displayname = "Helmet Camera";
		picture = "\cTab\img\cTab_helmet_cam_ico.paa";
		scope = 2;
		simulation = "ItemRadio";
		class ItemInfo {
			mass = 1;
		};	
	};	
};

class CfgNotifications
{
	
	class cTabUavNotAval
	{
		title = "cTab";
		iconPicture = "\cTab\img\15th_rugged_tab_ico.paa";
		iconText = "";
		color[] = {1,1,1,1};
		description = "%1";
		duration = 5;
		priority = 7;
		difficulty[] = {};
	};
	
	class cTabNewMsg
	{
		title = "cTab";
		iconPicture = "\cTab\img\icoUnopenedmail.paa";
		iconText = "";
		color[] = {1,1,1,1};
		description = "%1";
		duration = 4;
		priority = 7;
		difficulty[] = {};
	};

	class cTabMsgSent
	{
		title = "cTab";
		iconPicture = "\cTab\img\icoUnopenedmail.paa";
		iconText = "";
		color[] = {1,1,1,1};
		description = "Your message has been sent.";
		duration = 4;
		priority = 7;
		difficulty[] = {};
	};	

};

class RscTitles
{
	titles[]={};
	#include <\cTab\msg\msg_mail_title.hpp>


};


class CfgVehicles
{

	class Box_NATO_WpsSpecial_F;
	class Box_cTab_items : Box_NATO_WpsSpecial_F {
		displayname = "cTab Computer Gear";
		icon = "iconCrateLarge";
		model = "\A3\weapons_F\AmmoBoxes\WpnsBox_large_F";
		scope = 2;
		transportmaxmagazines = 64;
		transportmaxweapons = 12;

		class TransportItems {
			class _xx_ItemcTab {
				count = 5;
				name = "ItemcTab";
			};
			class _xx_ItemAndroid {
				count = 15;
				name = "ItemAndroid";
			};
			class _xx_ItemcTabHCam {
				count = 25;
				name = "ItemcTabHCam";
			};	
		};
	
	
		class TransportMagazines {};
		class TransportWeapons {};
	
	};
	
};




