cTab
====
*Commander's Tablet - FBCB2, Bluforce Tracker, UAV, and Helmetcam Interface*

Thanks to:
----------
+ SpectreRSG - Graphic Design
+ Capt Drumheller / Jester814 - Technical advisor / Ideas / Media
+ LCpl C. Johnston - Technical advisor
+ LCpl Schwanke - Technical advisor
+ Knobee - Documentation
+ Everyone else in the 15th MEU SOC for help with support and testing.

+ BI - for Arma 3 and all the opportunities to mod for this game.

Features:
---------
+ Commander's tablet
+ Working FBCB2, Bluforce Tracker system
+ User placed makers - Place markers for enemy, medical and general purpose.
+ Tracks all crewed Bluefor Military vehicles
+ Tracks any dismounted troops with the proper equipment.
+ Android Based BFT Interface
+ Commanders Tablet can view live UAV streams
+ Commanders Tablet can view live helmet cam streams
+ Vehicle mounted Interface FBCB2, Blue Force Tracking
+ This system is available to only one side, but there is a mission configurable parameter to have it work for other sides.
+ None of the markers or icons show on maps, need one of the devices to view.

Known Issues
-------------
+ Switching to or from the full screen views while in a vehicle can cause issues (fixed by exiting vehicle. *BIS issue with command, please vote for a fix* http://feedback.arma3.com/view.php?id=11577)
+ If viewing yourself from UAV or Helmet Cam in pip screen your textures can bug on on your unit.
+ Even though items go into the GPS slot and Radio slot they are not required to be there for cTab to operate, they can go anywhere in your inv. ie.. your vest or uniform.

Required
--------
+ CBA_A3 - http://www.armaholic.com/page.php?id=18767

Media
-----
![Tablet UAV screen](http://imagizer.imageshack.us/a/img802/7273/uhhi.jpg)
![Vehicle FBCB2](http://imagizer.imageshack.us/a/img28/5193/cauf.jpg)
[![cTab release overview](http://img.youtube.com/vi/2fFSOej_GPk/0.jpg)](http://youtu.be/2fFSOej_GPk)

Install
-------
place the `@cTab` folder in your Arma 3 folder.

Place the `cTab_Testing.Stratis` in your Arma 3 Other Profiles mission folder.

    documents\Arma 3 Other Profiles\*Your User Name*\missions\

Then the test mission that I have will be availiable in your editor.

the keys folder is for the server key.

How to configure:
-----------------
You will need to assign user action 12 in your custom controls. This will be the key that opens up the ctab in game.
This key is a lot like a function key, it is a smart key, if you have an android device it will open that, if you have the table it will open that, if an interface is open then it will close it.

*this is also the key you will need to use to exit from the full screen UAV and Helmet Cam views.*

For Mission Makers:
-------------------
### Class Names ###

    "ItemcTab"
    "ItemAndroid"
    "ItemcTabHCam"

### Add items to a box ###
Put this next line in the init of a ammobox:

    this addItemCargo ["itemcTab", 10];this addItemCargo ["ItemcTabHCam", 10];this addItemCargo ["ItemAndroid", 10];

### Add item to a player directly ###

    this addItem "itemcTab";

### For mission makers ###
If you wish to use cTab on a diffrent side than bluefore then put this at the TOP(important) of your init.sqf

    cTabSide = west;

Change the west to what ever side you wish to have cTab availible on.
You can only have cTab availible for one side. If you want cTab availible on the west side or NATO then you do not need to include this.
