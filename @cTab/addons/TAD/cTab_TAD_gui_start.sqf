// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.
// Edited by Gundy to add TAD functionality

ShowDisplay = {
	sleep 0.01;
	//layerNumber cutRsc [resourceClass, behaviour, durationMultiplier, showOverMap];
	cTabTADrscLayer cutRsc ["cTab_TAD_dsp","PLAIN",0, false];
	// not sure why I would need these, seems to work without
	//((uiNamespace getVariable "cTab_TAD_dsp") displayCtrl 1201)  ctrlSetPosition [0, 0];
	//((uiNamespace getVariable "cTab_TAD_dsp") displayCtrl 1201)  ctrlCommit 0;
};
_void = [] call ShowDisplay;