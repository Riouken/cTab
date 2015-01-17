/*
Required defines:
MENU_sizeEx - Menu text size (height)
*/

// place the menu outside of the visible area
#define MENU_X safeZoneXAbs + safeZoneWAbs
#define MENU_Y safeZoneY + safeZoneH

#define MENU_maxChars 12 // used to determine the necessary width of the menu
#define MENU_wPerChar MENU_sizeEx * 3/4 * 0.5 // assume characters 50% width relative to height
#define MENU_W (MENU_maxChars + 1.5) * MENU_wPerChar // add 1.5 characters for padding
#define MENU_elementH MENU_sizeEx / 0.8
#define MENU_elementY(item) MENU_elementH * (item - 1)
#define MENU_H(noOfElements) (noOfElements + 0.5) * MENU_elementH
