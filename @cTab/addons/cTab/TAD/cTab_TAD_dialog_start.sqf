// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.
// Edited by Gundy to add TAD functionality

closeDialog 0;
waitUntil {!dialog};

createDialog "cTab_TAD_dlg";
waitUntil {dialog};
_this + ["cTab_TAD_dlg"] call cTab_fnc_onIfOpen;
