cTab_key_if_main_scancode = getNumber (configFile >> "cTab_keys" >>  "if_main"  >> "key");
cTab_key_if_main_modifiers = [
	getNumber (configFile >> "cTab_keys" >>  "if_main"  >> "shift") == 1,
	getNumber (configFile >> "cTab_keys" >>  "if_main"  >> "ctrl") == 1,
	getNumber (configFile >> "cTab_keys" >>  "if_main"  >> "alt") == 1
];

cTab_key_if_secondary_scancode = getNumber (configFile >> "cTab_keys" >>  "if_secondary"  >> "key");
cTab_key_if_secondary_modifiers = [
	getNumber (configFile >> "cTab_keys" >>  "if_secondary"  >> "shift") == 1,
	getNumber (configFile >> "cTab_keys" >>  "if_secondary"  >> "ctrl") == 1,
	getNumber (configFile >> "cTab_keys" >>  "if_secondary"  >> "alt") == 1
];

cTab_key_if_tertiary_scancode = getNumber (configFile >> "cTab_keys" >>  "if_tertiary"  >> "key");
cTab_key_if_tertiary_modifiers = [
	getNumber (configFile >> "cTab_keys" >>  "if_tertiary"  >> "shift") == 1,
	getNumber (configFile >> "cTab_keys" >>  "if_tertiary"  >> "ctrl") == 1,
	getNumber (configFile >> "cTab_keys" >>  "if_tertiary"  >> "alt") == 1
];

cTab_key_zoom_in_scancode = getNumber (configFile >> "cTab_keys" >>  "zoom_in"  >> "key");
cTab_key_zoom_in_modifiers = [
	getNumber (configFile >> "cTab_keys" >>  "zoom_in"  >> "shift") == 1,
	getNumber (configFile >> "cTab_keys" >>  "zoom_in"  >> "ctrl") == 1,
	getNumber (configFile >> "cTab_keys" >>  "zoom_in"  >> "alt") == 1
];

cTab_key_zoom_out_scancode = getNumber (configFile >> "cTab_keys" >>  "zoom_out"  >> "key");
cTab_key_zoom_out_modifiers = [
	getNumber (configFile >> "cTab_keys" >>  "zoom_out"  >> "shift") == 1,
	getNumber (configFile >> "cTab_keys" >>  "zoom_out"  >> "ctrl") == 1,
	getNumber (configFile >> "cTab_keys" >>  "zoom_out"  >> "alt") == 1
];
