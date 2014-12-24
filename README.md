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
+ Raspu - TAD, Android and MicroDAGR background graphics and 3D models
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
+ MicroDAGR hand-held GPS with Blue Force Tracking
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
+ Even though items go into the GPS slot they are not required to be there for cTab to operate, they can go anywhere in your inventory, i.e. your vest or uniform
+ Players that are experiencing conflicts with help screens (uses `H`as a key as well) are advised to rebind cTab `IF_MAIN`, for example to `SHIFT`+ `H`. This seems to only happen sometimes, so far mostly for players playing Zeus.
+ Helicopter pilots (and co-pilots) that are using RAVEN's LIFTER mod are advised to rebind cTab `IF_MAIN` to something other than the default as `H` is used by that mod and cannot be changed (as of this writing).

Required
--------
+ [CBA_A3](http://www.armaholic.com/page.php?id=18767)

Media
-----
![Tablet UAV screen](http://imagizer.imageshack.us/a/img802/7273/uhhi.jpg)
![Vehicle FBCB2](http://imagizer.imageshack.us/a/img28/5193/cauf.jpg)
[![TAD small](http://imagizer.imageshack.us/v2/280x200q90/746/UTTp2B.jpg)](http://imageshack.com/f/kqUTTp2Bj)
[![TAD large](http://imagizer.imageshack.us/v2/280x200q90/909/P8FrUz.jpg)](http://imageshack.com/f/p9P8FrUzj)
[![cTab release overview](http://img.youtube.com/vi/2fFSOej_GPk/0.jpg)](http://youtu.be/2fFSOej_GPk)

Install
-------
Place the `@cTab` and `userconfig` folders in your ArmA 3 folder (*both on the server and the clients*). Then start the game with `@CBA_A3`and `@cTab`. It can be done either by enabling the necessary mods in the game settings (Settings -> Expansions), or by adding the mod names to the game shortcut after the EXE file, i.e. `...\arma3.exe -mod=@CBA_A3;@cTab`.

The keys folder is for the server key.

How to configure
----------------
### Key Bindings ###
Key Bindings can now be configured via the CBA Keybinding system available to you from the configure controls screen once you are in game.
You can reconfigure the default keys in the configuration file, which can be found in the ArmA 3 folder `...\Arma 3\userconfig\cTab\ctab_settings.hpp`. The file can be edited in Notepad or any other text editor. These are the default key bindings:

| Keys | Action |
| --- | --- |
| `H` | This key is used to open and close whatever cTab device is available to you, showing the "small" version where available. It can also be used to close UAV view. |
| `CTRL` + `H` | Opens and closes the secondary view mode of the cTab device available to you. This would usually be the "large" version. |
| `ALT` + `H` | Opens and closes an alternative cTab device that you may have available (i.e. when a pilot carrying a tablet, this will open the tablet). |
| `LEFT DOUBLE-CLICK` |  Opens dialog to place markers at mouse cursor location. Not available on MicroDAGR |
| `DEL` |  Deletes the highlighted user placed marker under your cursor. |
| `F1` |  Change to Blue Force Tracker on tablet. |
| `F2` |  Change to UAV cameras on tablet. |
| `F3` |  Change to helmet cameras on tablet. |
| `F4` |  Change to Message mode on tablet. |
| `F5` |  Toggles map tools (grid/elevation/range/direction to mouse cursor). |
| `F6` |  Toggles map mode (satellite/topographical/black). |
| `F7` |  Center map on current position. |
| `CTRL` + `SHIFT` `PAGE_UP` | Zoom in on the "small" TAD, MicroDAGR and Android. |
| `CTRL` + `SHIFT` `PAGE_DOWN` | Zoom out on the "small" TAD, MicroDAGR and Android. |
| `ESC` | Closes all interactive cTab devices (i.e. all but the "small" variants) as well as the UAV view. |

### Define vehicle types that have FBCB2 or TAD available ###
To configure the list of vehicle types that have FBCB2 or TAD available, edit the `cTab_vehicleClass_has_FBCB2` and `cTab_vehicleClass_has_TAD` arrays in the configuration file on the server, which can be found in the ArmA 3 folder `...\Arma 3\userconfig\cTab\ctab_settings.hpp`.

    class cTab_settings {
        cTab_vehicleClass_has_FBCB2[] = {"MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank","Truck_01_base_F","Truck_03_base_F"};
        cTab_vehicleClass_has_TAD[] = {"Helicopter","Plane"};
    };

### Define helmet classes with enabled helmet camera ###
To configure the list of helmet classes that enable helmet cameras, edit the `cTab_helmetClass_has_HCam` array in the configuration file on the server, which can be found in the ArmA 3 folder `...\Arma 3\userconfig\cTab\ctab_settings.hpp`. It needs to be within the class `cTab_settings` (same area as above).

    class cTab_settings {
        cTab_vehicleClass_has_FBCB2[] = {"MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank","Truck_01_base_F","Truck_03_base_F"};
        cTab_vehicleClass_has_TAD[] = {"Helicopter","Plane"};
        cTab_helmetClass_has_HCam = {"H_HelmetB_light","H_Helmet_Kerry","H_HelmetSpecB","H_HelmetO_ocamo","BWA3_OpsCore_Fleck_Camera","BWA3_OpsCore_Schwarz_Camera","BWA3_OpsCore_Tropen_Camera"};
    };

For Mission Makers
------------------
### Class Names ###

    ItemcTab // Commander Tablet
    ItemAndroid // Android based Blue Force Tracker
    ItemcTabHCam // Helmet Cam
    ItemMicroDAGR // MicroDAGR GPS

### Add items to a box ###
Place this in the initialisation of an Ammo box to add 10 of each item:

    this addItemCargo ["ItemcTab",10];this addItemCargo ["ItemcTabHCam",10];this addItemCargo ["ItemAndroid",10];this addItemCargo ["ItemMicroDAGR",10];

### Add item to a unit directly ###
Place this in the initialisation of a soldier:

    this addItem "ItemcTab";

Note: This will add the item to the actual inventory, but not assign it to the GPS slot. The unit will have to have enough space in its inventory to fit the item, otherwise it won't be assigned. `addItem` assigns the item to the next best inventory container that fits the item, in the order of uniform, vest and backpack. The Tablet (`itemcTab`) for example won't fit in most uniforms, so there has to be space in either the vest or backpack. Use `addItemToBackpack` to add the item directly to the unit's backpack and `addItemToVest` to directly assign it to the vest. To assign an item directly to the GPS slot (it has no space restrictions, but will still count towards the unit's total load), use ´linkItem´ instead.

This will for example assign the MicroDAGR to the GPS slot and place the Tablet into the unit's backpack:

    this linkItem "ItemMicroDAGR";this addItemToBackpack "ItemcTab";

### Set cTab side-specific encryption keys ###
If you whish multiple factions to share cTab data, you will have to set their encryption keys to be the same. These are the variables that hold the encryption keys with their default values:

    cTab_encryptionKey_west = "bluefor";
    cTab_encryptionKey_east = "opfor";
    cTab_encryptionKey_guer = "independent";
    cTab_encryptionKey_civ = "civilian";

So if you want to have for example OPFOR and GUER share cTab data, put this at the **TOP** of your `init.sqf`:

    // set GUER encryption key to be the same as the default BLUEFOR encryption key
    cTab_encryptionKey_guer = "bluefor";

Note: If GUER is set to be friendly with either WEST or EAST, GUER will by default have the same encryption key as the friendly faction. Set `cTab_encryptionKey_guer` to override.

### Override vehicle types that have FBCB2 or TAD available ###
If you wish to override the list of vehicles that have FBCB2 or TAD available, put this at the **TOP** of your `init.sqf`:

    // only make FBCB2 available to MRAPs, APCs and tanks
    cTab_vehicleClass_has_FBCB2 = ["MRAP_01_base_F","MRAP_02_base_F","MRAP_03_base_F","Wheeled_APC_F","Tank"];
    
    // make TAD available to all helicopters and planes with the exception of the MH-9 Hummingbird and AH-9 Pawnee
    cTab_vehicleClass_has_TAD = ["Heli_Attack_01_base_F","Heli_Attack_02_base_F","Heli_Light_02_base_F","Heli_Transport_01_base_F","Heli_Transport_02_base_F","I_Heli_light_03_base_F","Plane"];

### Override helmet classes with enabled helmet camera ###

    // Only have BWmod helmets with a camera simulate a helmet camera
    cTab_helmetClass_has_HCam = ["BWA3_OpsCore_Schwarz_Camera","BWA3_OpsCore_Tropen_Camera"];

### Change display name of a vehicle ###
By default all vehicles will be shown with their group names next to them. This can make it difficult to distinguish multiple vehicles of the same type when they are in the same group. To change that, use the following code in the unit's initialization:

    // Change this vehicle's identification displayed on all cTab Blue Force Trackers to "Fox"
    this setVariable ["cTab_groupId","Fox",true];

Changelog
---------
### 2.1.0 ###
* Added MicroDAGR hand-held GPS.
  It features a self-centring small view mode that can be kept visible while navigating and a large view mode that allows for user interaction. The small view mode can be zoomed in and out using the `Zoom_In` and `Zoom_Out` keys.
  Only units with a cTab device in your own group are displayed, unless you have "connected" it to a tablet (i.e. you are carrying one).
* Added configurable server-side list of helmets that define the presence of a helmet camera, defaulting to vanilla ArmA 3 and BWmod helmet models with a camera.
* Enabled support for CBA Keybinding system to make key bind changes more user friendly and changeable without a restart. Userconfig settings now define the default keybinds.
* Helmet Cam item no longer occupies the radio slot when added to inventory. This is to prevent complications with TFAR.
* Changed weight of all items to be close to their real-world equivalents (before everything did weight 45g)
* Updated Android background graphic and added 3D model (for when you drop it on the ground)
* Completely reworked Android user interface
* Added messaging to Android interface
* Sent messages are now kept with the list of received messages
* Message receive notification has been made a lot less intrusive, both visually (now a small white envelope icon on the right side of the screen) and audibly (a humming sound similar to that of a mobile phone vibrating)
* The "delete messages" function will now only delete selected messages (instead of all)
* Added "small" version to Android interface, so you can now keep it visible while navigating
* Reworked Tablet user interface, switching modes feels a lot more natural now
* Reworked UAV camera positions, gunner and driver camera will now reflect what the UAV gunner and driver actually sees. Gunner camera now uses FLIR (white/hot) mode.
* Lists of UAVs and helmet cameras are now alphabetically sorted
* Reworked helmet "full-screen" view to only occupy the whole screen of the Tablet instead of the whole screen
* Added ability to remove marker at mouse cursor position. The marker currently under the cursor will be highlighted and removed upon pressing DEL (delete on your keyboard).
* Players sitting in the back of the trucks (HMTT and Tempest by default) now no longer have access to the vehicle based FBCB2
* Workaround for left-door gunner having access to the TAD instead of the co-pilot in Konyo's Boeing/SOAR MH-47E
* All interfaces are now restored to last mode of operation operation (BFT,Messaging,...) on open
* All interfaces will now restore last map position and zoom level on open
* Added topographical map mode to all devices
* Added black map mode to TAD
* Added switch (F6) to toggle map modes (satellite, topographical, black) via the "large" versions of the devices (the "small" versions will use the same setting)
* Added switch (F7) to center map on current player position
* Added current in-game time to all interfaces
* Added current grid location as well as current heading in degrees and octant to all interfaces
* Greatly enhanced user placed map markers to properly scale when zooming the map (including the directional arrow and group size denominators) as well as making sure the directional arrow does not interfere with the time-stamps
* Added new marker types for infantry (AT and MG) and wheeled MRAPs/APCs
* Added an "Exit" menu entry to the map double-click dialog (the one you place map markers with)
* Added a "Copy Grid" entry to the map double-click dialog, copying the grid location of the clicked location to the clipboard
* Added map tools (can be toggled using F5) that show grid and elevation at mouse cursor as well as distance and direction from the current position to the mouse cursor position.
* Island sizes are now dynamically detected, no more waiting on islands being supported
* Tweaked map visuals to be easier to read
* General performance tweaks
* Added new keybinding (ALT + H) to allow access to alternative interface (i.e. to get access to the Tablet that is being carried while in one of the pilot seats of a helicopter)
* Infantry carrying a cTab device in your own group will now show with a smaller infantry icon that points in the direction of the unit as well as the index of that unit within the group (instead of a square infantry symbol with the full group ID). To anyone outside this group, there will only be a single icon shown for the group at the position of the group's leader (if equipped with a cTab device, otherwise the next unit in line).
* Infantry groups will now automatically show the group strength with dots above the icon
* Changed BFT list generation and display functions to help de-clutter everyone's view. For example transports will no longer show overlayed icons for other units with cTab equipment that are mounted. Instead, the names of groups and the group indices of units from your own group will be displayed to the left of the transport's icon.
* The arrow on the inner TAD range circle (that used to show north) will now rotate with the direction of the aircraft to help show the current direction of travel
* Excluded static weapons from showing up on BFT
* Added ability to define custom names for vehicles via the mission or scripts

### 2.0.1 ###
* Fixed "_chk_all_items" script error that could appear during Zeus (and probably other) missions

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

Download / Links
----------------
[Armaholic](http://www.armaholic.com/page.php?id=22992)
[GitHub](https://github.com/Riouken/cTab)
