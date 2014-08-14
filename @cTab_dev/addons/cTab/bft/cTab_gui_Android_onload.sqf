// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.


disableSerialization;

_display = (uiNamespace getVariable "cTab_Android_dlg");
ctrlShow [3357, false];
_popup = [3300,3301,3302,3303,3304,3305,3306];

{
	ctrlShow [_x, false];
	
} forEach _popup;



