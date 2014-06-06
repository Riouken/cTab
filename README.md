cTab
====
**Commander's Tablet - FBCB2, Blue Force Tracker, UAV, and Helmet Cam Interface**

Thanks to
---------
+ SpectreRSG - Graphic Design
+ Capt Drumheller / Jester814 - Technical advisor / Ideas / Media
+ LCpl C. Johnston - Technical advisor
+ LCpl Schwanke - Technical advisor
+ Knobee - Documentation
+ Everyone else in the 15th MEU SOC for help with support and testing.

+ BI - for ArmA 3 and all the opportunities to mod for this game.

Features
--------
+ Commander's tablet
+ Working FBCB2 Blue Force Tracker system
+ User placed makers - place markers for enemy, medical and general purpose
+ Tracks all crewed Bluefor Military vehicles
+ Tracks any dismounted troops with the proper equipment
+ Android based BFT interface
+ Commanders Tablet can view live UAV streams
+ Commanders Tablet can view live Helmet Cam streams
+ Vehicle mounted FBCB2 interface, Blue Force Tracking
+ This system is available to only one side at a time, there is a mission configurable parameter to choose sides
+ None of the markers or icons show on maps, need one of the devices to view

Known Issues
------------
+ Switching to or from the full screen views while in a vehicle can cause issues (fixed by exiting vehicle)
  [*BIS issue with command, please vote for a fix*](http://feedback.arma3.com/view.php?id=11577)
+ If your are viewing yourself from the UAV or Helmet Cam in PiP screen, your textures can bug on your unit
+ Even though items go into the GPS and radio slot they are not required to be there for cTab to operate, they can go anywhere in your inventory, i.e. your vest or uniform

Required
--------
+ [CBA_A3](http://www.armaholic.com/page.php?id=18767)

Media
-----
![Tablet UAV screen](http://imagizer.imageshack.us/a/img802/7273/uhhi.jpg)
![Vehicle FBCB2](http://imagizer.imageshack.us/a/img28/5193/cauf.jpg)
[![cTab release overview](http://img.youtube.com/vi/2fFSOej_GPk/0.jpg)](http://youtu.be/2fFSOej_GPk)

Install
-------
Place the `@cTab` folder in your ArmA 3 folder.

Place the folder `cTab_Testing.Stratis` in your ArmA 3 profile's mission folder:

    Documents\Arma 3 Other Profiles\*Your User Name*\missions\

This will make the test mission available in the editor.

The keys folder is for the server key.

How to configure
----------------
You will need to assign user action 12 in your custom controls. This will be the key that opens up cTab in game. This key is used to open and close whatever cTab device you is available to you.

*This is also the key you will need to use to exit from the full screen UAV and Helmet Cam views.*

For mission Makers
------------------
### Class Names ###

    ItemcTab // Commander Tablet
    ItemAndroid // Android based Blue Force Tracker
    ItemcTabHCam // Helmet Cam

### Add items to a box ###
Place this in the initialisation of an Ammo box to add 10 of each item:

    this addItemCargo ["ItemcTab",10];this addItemCargo ["ItemcTabHCam",10];this addItemCargo ["ItemAndroid",10];

### Add item to a player directly ###
Place this in the initialisation of a soldier:

    this addItem "ItemcTab";

### Set cTab side ###
If you wish to use cTab on a different side than Bluefore, put this at the **TOP** of your `init.sqf`:

    cTabSide = east;

Change `east` to what ever side you wish to have cTab available on (i.e. `guer`).
You can only have cTab available for one side. If you want cTab available on the west side or NATO then you do not need to include this.
