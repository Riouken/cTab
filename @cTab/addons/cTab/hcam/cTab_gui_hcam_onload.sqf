// cTab - Commander's Tablet with FBCB2 Blue Force Tracking
// Battlefield tablet to access real time intel and blue force tracker.
// By - Riouken
// http://forums.bistudio.com/member.php?64032-Riouken
// You may re-use any of this work as long as you provide credit back to me.

#include <\cTab\cTab_gui_macros.hpp>
#include <\cTab\cTab_gui_uav_macros.hpp>

disableSerialization;


_display = (uiNamespace getVariable "cTab_hCam_dlg");
_hcamListctrl = _display displayCtrl IDC_CTAB_CTABUAVLIST;

{
	_index = _hcamListctrl lbAdd format ["%2 (%1)",groupId group _x,name _x];
} forEach cTabHcamlist;
