// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.
// Edited by Gundy to add TAD functionality

cTabTADrscLayer cutRsc ["cTab_microDAGR_dsp","PLAIN",0, false];
waitUntil {!isNull (uiNamespace getVariable 'cTab_microDAGR_dsp')};
_this + [nil,'cTab_microDAGR_dsp'] call cTab_fnc_onIfOpen;
