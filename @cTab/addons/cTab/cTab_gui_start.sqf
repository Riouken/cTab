// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

closeDialog 0;
waitUntil {!dialog};

createDialog "cTab_main_dlg";
waitUntil {dialog};
_this + [1775154,nil] call cTab_fnc_onIfOpen;
