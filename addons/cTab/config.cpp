// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


#define PREFIX cTab
#define MAJOR 2
#define MINOR 2
#define PATCHLVL 2
#define BUILD 5
#define VERSION MAJOR.MINOR.PATCHLVL.BUILD
#define VERSION_AR MAJOR,MINOR,PATCHLVL,BUILD
#define REQUIRED_VERSION 1.32
#include "\x\cba\addons\main\script_macros_common.hpp"
#define AUTHOR "Gundy, Riouken, Raspu"


class CfgPatches
{
	class PREFIX  // cTab
		{
			units[] = {Box_cTab_items};
			weapons[] = {ItemcTab,ItemAndroid,ItemMicroDAGR,ItemcTabHCam};
			requiredVersion = REQUIRED_VERSION;
			requiredAddons[] = {"CBA_MAIN"};
			versionDesc = "cTab";
			VERSION_CONFIG;
			author[] = {"Gundy","Riouken","Raspu"};
			authorUrl = "https://github.com/Riouken/cTab";
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
				main_addon = PREFIX;
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
		name = "cTab - Blue Force Tracking";
		picture = "\cTab\img\cTab_BFT_ico.paa";
		hidePicture = "True";
		hideName = "True";
		actionName = "Website";
		action = "https://github.com/Riouken/cTab";
		overview = "Commander's Tablet / FBCB2 - Blue Force Tracking\nBattlefield tablet to access real time intel and blue force tracker.";
		tooltip = "Commander's Tablet / FBCB2 - Blue Force Tracking";
		author = AUTHOR;
	};
};

#include "\cTab\CfgFunctions.h"

class Extended_PostInit_EventHandlers
{
	class PREFIX
	{
		clientInit = QUOTE(call COMPILE_FILE2(\cTab\player_init.sqf));

		serverInit = QUOTE(call COMPILE_FILE2(\cTab\server_init.sqf));
	};
};

#include "\cTab\shared\cTab_gui_macros.hpp"
#include "\cTab\shared\cTab_base_gui_classes.hpp"

#include <\cTab\tablet\cTab_Tablet_dialog.hpp>
#include <\cTab\android\cTab_android_dialog.hpp>
#include <\cTab\FBCB2\cTab_FBCB2_dialog.hpp>
#include <\cTab\TAD\cTab_TAD_dialog.hpp>
#include <\cTab\microDAGR\cTab_microDAGR_dialog.hpp>

class CfgWeapons
{
	class ItemCore;
 	class InventoryItem_Base_F;
	class ItemcTab: ItemCore {
		descriptionshort = "DK10 Rugged Tablet PC";
		descriptionuse = "<t color='#9cf953'>Use: </t>Show Commander's Tablet";
		displayname = "Rugged Tablet";
		picture = "\cTab\img\icon_dk10.paa";
		model = "\ctab\data\itemDK10.p3d";
		scope = 2;
		simulation = "ItemGPS";
		class ItemInfo {
			mass = 56;
		};
		author = AUTHOR;
	};
	
	class ItemAndroid: ItemcTab {
		descriptionshort = "GD300 Rugged Wearable Computer";
		descriptionuse = "<t color='#9cf953'>Use: </t>Show Android Based BFT";
		displayname = "GD300 Android";
		picture = "\cTab\img\icon_Android.paa";
		model = "\ctab\data\itemAndroid.p3d";
		class ItemInfo {
			mass = 5;
		};
		author = AUTHOR;
	};

	class ItemMicroDAGR: ItemcTab {
		descriptionshort = "HNV-2930 Micro Defense Advanced GPS Receiver";
		descriptionuse = "<t color='#9cf953'>Use: </t>Show Android Based BFT";
		displayname = "MicroDAGR";
		picture = "\cTab\img\icon_MicroDAGR.paa";
		model = "\ctab\data\itemMicroDAGR.p3d";
		class ItemInfo {
			mass = 6;
		};
		author = AUTHOR;
	};
	
	class ItemcTabHCam: ItemCore {
		descriptionshort = "HD Helmet Mounted Camera";
		descriptionuse = "<t color='#9cf953'>Use: </t>Used to record and stream video";
		displayname = "Helmet Camera";
		picture = "\cTab\img\cTab_helmetCam_ico.paa";
		scope = 2;
		simulation = "ItemMineDetector";
		detectRange = -1;
		type = 0;
		class ItemInfo: InventoryItem_Base_F {
			mass = 4;
		};
		author = AUTHOR;
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
	#include "\cTab\shared\cTab_mapSize_title.hpp"
	#include "\cTab\shared\cTab_mail_title.hpp"
	#include <\cTab\TAD\cTab_TAD_display.hpp>
	#include <\cTab\microDAGR\cTab_microDAGR_display.hpp>
	#include <\cTab\android\cTab_android_display.hpp>
};


class CfgVehicles
{

	class Box_NATO_WpsSpecial_F;
	class Box_cTab_items : Box_NATO_WpsSpecial_F {
		displayname = "[cTab] Computer Gear";
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
			class _xx_ItemMicroDAGR {
				count = 25;
				name = "ItemMicroDAGR";
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

class CfgSounds
{
	sounds[] = {};
	class cTab_phoneVibrate
	{
		// filename, volume, pitch
		sound[] = {"\cTab\sounds\phoneVibrate.wss",1,1};
		// subtitle delay in seconds, subtitle text 
		titles[] = {};
	};
	class cTab_mailSent
	{
		sound[] = {"\cTab\sounds\mailSent.wss",1,1};
		titles[] = {};
	};
};
