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
+ Android based Blue Force Tracker
+ Commanders Tablet can view live UAV streams
+ Commanders Tablet can view live Helmet Cam streams
+ Vehicle mounted FBCB2 interface, Blue Force Tracking
+ Tactical Awareness Display (TAD) for air vehicles, Blue Force Tracking
+ This system is available to only one side at a time, there is a mission configurable parameter to choose sides
+ None of the markers or icons show on maps, need one of the devices to view

Known Issues
------------
+ Switching to or from the full screen views while in a vehicle can cause issues (fixed by exiting vehicle)
  [*BIS issue with command, please vote for a fix*](http://feedback.arma3.com/view.php?id=11577)
+ If your are viewing yourself from the UAV or Helmet Cam in PiP screen, your textures can bug on your unit
+ Even though items go into the GPS and radio slot they are not required to be there for cTab to operate, they can go anywhere in your inventory, i.e. your vest or uniform
+ Players that are experiencing conflicts with help screens (uses `H`as a key as well) are advised to rebind cTab `IF_MAIN`, for example to `SHIFT`+ `H` in the userconfig. This seems to only happen sometimes, sofar mostly for players playing Zeus.

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
Place the `@cTab` and `userconfig` folders in your ArmA 3 folder (both on the server and the clients). Then start the game with `@CBA_A3`and `@cTab`. It can be done either by enabling the necessary mods in the game settings (Settings -> Expansions), or by adding the mod names to the game shortcut after the EXE file, i.e. `…\arma3.exe -mod=@CBA_A3;@cTab`.

The keys folder is for the server key.

How to configure
----------------
### Key Bindings ###
You can reconfigure the keys in the configuration file, which can be found in the ArmA 3 folder `...\Arma 3\userconfig\cTab\ctab_settings.hpp`. The file can be edited in Notepad or any other text editor. These are the default key binding:

| Keys | Action |
| --- | --- |
| `H` | This key is used to open and close whatever cTab device is available to you. It can also be used to close UAV and Helmet Cam views. |
| `CTRL` + `H` | Opens and closes the secondary view mode of the cTab device available to you, currently only available when in one of the pilot seats of an aircraft. |
| `CTRL` + `SHIFT` `PAGE_UP` | Zoom in on the "small" TAD. |
| `CTRL` + `SHIFT` `PAGE_DOWN` | Zoom out on the "small" TAD. |
| `ESC` | Closes all interactive cTab devices (i.e. all but the "small" TAD) as well as the UAV and Helmet Cam views. |

### Define vehicle types that have FBCB2 or TAD available ###
To configure the list of vehicle types that have FBCB2 or TAD available, edit the `cTab_vehicleClass_has_FBCB2` and `cTab_vehicleClass_has_TAD` arrays in the configuration file on the server, wich can be found in the ArmA 3 folder `...\Arma 3\userconfig\cTab\ctab_settings.hpp`.

    class cTab_settings {
        cTab_vehicleClass_has_FBCB2[] = {"MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank","Truck_01_base_F","Truck_03_base_F"};
        cTab_vehicleClass_has_TAD[] = {"Helicopter","Plane"};
    };

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

### Override vehicle types that have FBCB2 or TAD available ###
If you wish to override the list of vehicles that have FBCB2 or TAD available, put this at the **TOP** of your `init.sqf`:

    // only make FBCB2 available to MRAPs, APCs and tanks
    cTab_vehicleClass_has_FBCB2 = ["MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank"];
    
    // make TAD available to all helicopters and planes with the exception of the MH-9 Hummingbird and AH-9 Pawnee
    cTab_vehicleClass_has_TAD = ["Heli_Attack_01_base_F","Heli_Attack_02_base_F","Heli_Light_02_base_F","Heli_Transport_01_base_F","Heli_Transport_02_base_F","I_Heli_light_03_base_F","Plane"];

Changelog
---------
### 2.0.0 ###
* Reduced network traffic by moving the list generation of tracked elements from the server to the clients
  The server now sends an update pulse to all clients every 30 seconds (previous update interval was 20), instead of sending the whole list to every client. The clients then generate the list locally. This lessens the server load a little (shifting it to the clients), greatly reduces cTab related network traffic, while hopefully keeping the list content the same across clients since they update (almost) at the same time.
* Addition of messaging system (currently on Tablet only)
  Send text messages between team members equipped with tablets.
* Addition of cTab equipment box to be used in editor
  A simple box filled with your favourite cTab equipment. Includes 5 Tablets, 15 Android devices and 25 helmet cameras. The box is also available to Zeus.
* Tablet, Android and helmet camera are now available in Zeus when editing the contents of boxes
* Addition of TAD (Tactical Awareness Display) for use in air vehicles.
  There are two variants, one is small and can be kept visible while operating your aircraft, similar to the GPS but populated with information from your cTab network. The map will be kept centred on your current position. In the upper right hand corner of the screen you can see the current scale represented by the radius of the outer circle. The inner circle is exactly half of that.
  The other variant is a larger representation of the same TAD, but in an interactive mode and *you will lose your vehicle controls* while open.
  Overall the TAD has been modelled to have a similar look to the TAD found in the DCS A-10C module.
  All friendly aircraft icons are replaced with a little circle that has a small line attached to it, representing the current orientation of that vehicle.
  When in one of the pilot seats of an aircraft, press `IF_Main` to open or close the small TAD. Use the new `Zoom_In` and `Zoom_Out` keys to zoom the small TAD. `IF_Secondary` opens the large TAD.
* Addition of userconfig for key bindings
  This frees up the previously used `UserAction12`.
* Addition of vehicle arrays to userconfig (server side) to define vehicles equipped with on-board FBCB2 or TAD
  The lists will be read by the server and distributed to all clients. It can also be overridden by mission makers.
* cTab now closes when exiting a vehicle or when the player is killed
* Added Ifrit, Strider and Tempest to the default list of FBCB2 enabled vehicles.
* Players sitting in the cargo area of an FBCB2 enabled vehicle will no longer have access to the vehicle based FBCB2. The currently known exceptions are the trucks (HMTT and Tempest), they are working as before. We are waiting on a new command in ArmA3 release 1.26 to hopefully be able to address this.
* Fixed error appearing when helmet cam screen was selected on the tablet for the first time
* Added artillery and mortar symbols
* The increase / decrease font function now actually resizes the fonts (in addition to the symbols as before)
* General performance improvements and bug fixes
