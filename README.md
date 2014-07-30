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
+ Raspu - TAD screen model
+ Killzone_Kid - for his many excellent tutorials
+ Everyone else in the 15th MEU SOC and C-L-F for help with support and testing.

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

Changelog
---------
### 2.0.0 ###
* Reduced network traffic by moving the list generation of tracked elements from the server to the clients
  The server now sends an update pulse to all clients every 30 seconds (previous update interval was 20), instead of sending the whole list to every client. The clients then generate the list locally. This lessens the server load a little (shifting it to the clients), greatly reduces cTab related network traffic, while hopefully keeping the list content the same across clients since they update (almost) at the same time.
* Addition of messaging system (currently on Tablet only)
  Send text messages between team members equipped with tablets.
* Addition of cTab equipment box to be used in editor
  A simple box filled with your favourite cTab equipment. Includes 5 Tablets, 15 Android devices and 25 helmet cameras. The box is also available to Zeus.
* Addition of TAD (Tactical Awareness Display) for use in air vehicles.
  There are two variants, one is small and can be kept visible while operating your aircraft, similar to the GPS but populated with information from your cTab network. The map will be kept centred on your current position. In the upper right hand corner of the screen you can see the current scale represented by the radius of the outer circle. The inner circle is exactly half of that.
  The other variant is a larger representation of the same TAD, but in an interactive mode and *you will lose your vehicle controls* while open.
  Overall the TAD has been modelled to have a similar look to the TAD found in the DCS A-10C module.
  All friendly aircraft icons are replaced with a little circle attached symbol that has a small line attached to it, representing the current orientation of that vehicle.
  When in one of the pilot seats of an aircraft, press 'IF_Main' to open or close the small TAD. Use the new `Zoom_In` and `Zoom_Out` keys to zoom the small TAD. `IF_Secondary` opens the large TAD.
* Addition of userconfig for key bindings
  This frees up the previously used `UserAction12`.
* Addition of vehicle arrays to userconfig (server side) to define vehicles equipped with on-board FBCB2 or TAD
  The lists will be read by the server and distributed to all clients. It can also be overridden by mission makers.
* cTab now closes when exiting a vehicle or when the player is killed
* Performance improvements and bug fixes
