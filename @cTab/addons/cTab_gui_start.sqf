// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

closeDialog 0;

ShowDialog = {
	sleep 0.01;
	_ok = createDialog "cTab_main_dlg";
	waitUntil { !dialog };
};
 
_void = [] call ShowDialog;