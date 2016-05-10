// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Gundy
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

class cTab_mapSize_dsp {
	idd = 13673;
	onLoad = "uiNamespace setVariable ['cTab_mapSize_dsp',_this select 0]";
	fadein = 0;
	fadeout = 0;
	duration = 10e10;
	controlsBackground[] = {};
	objects[] = {};
	class controls
	{
		class mapSize: cTab_RscMapControl
		{
			idc = 1110;
			type = CT_MAP; // better than map_main, markers are not required and it starts positioned in map center
			x = safeZoneXAbs + safeZoneWAbs; // positioned outside of view
			y = safeZoneY + safeZoneH; // positioned outside of view
			w = 0.01; // width is not important as we don't use it
			h = 10; // height is important to be large as it should be more precise when reading back world coordinates
			scaleMin = 0.001;
			scaleDefault = 0.001; // 0.001 is the correct scale to figure out the scaling factor
			maxSatelliteAlpha = 0; // make the map topographical

			// basically prevent that anything gets rendered as its not required
			ptsPerSquareSea = 10000;
			ptsPerSquareTxt = 10000;
			ptsPerSquareCLn = 10000;
			ptsPerSquareExp = 10000;
			ptsPerSquareCost = 10000;
			ptsPerSquareFor = 10000;
			ptsPerSquareForEdge = 10000;
			ptsPerSquareRoad = 10000;
			ptsPerSquareObj = 10000;
		};
	};
};