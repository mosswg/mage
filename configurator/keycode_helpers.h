#pragma once
#include <unordered_map>
#include <string>

//--------------------------------------------------------------------+
// HID KEYCODE
//--------------------------------------------------------------------+
#define HID_KEY_NONE                      0x00
#define HID_KEY_A                         0x04
#define HID_KEY_B                         0x05
#define HID_KEY_C                         0x06
#define HID_KEY_D                         0x07
#define HID_KEY_E                         0x08
#define HID_KEY_F                         0x09
#define HID_KEY_G                         0x0A
#define HID_KEY_H                         0x0B
#define HID_KEY_I                         0x0C
#define HID_KEY_J                         0x0D
#define HID_KEY_K                         0x0E
#define HID_KEY_L                         0x0F
#define HID_KEY_M                         0x10
#define HID_KEY_N                         0x11
#define HID_KEY_O                         0x12
#define HID_KEY_P                         0x13
#define HID_KEY_Q                         0x14
#define HID_KEY_R                         0x15
#define HID_KEY_S                         0x16
#define HID_KEY_T                         0x17
#define HID_KEY_U                         0x18
#define HID_KEY_V                         0x19
#define HID_KEY_W                         0x1A
#define HID_KEY_X                         0x1B
#define HID_KEY_Y                         0x1C
#define HID_KEY_Z                         0x1D
#define HID_KEY_1                         0x1E
#define HID_KEY_2                         0x1F
#define HID_KEY_3                         0x20
#define HID_KEY_4                         0x21
#define HID_KEY_5                         0x22
#define HID_KEY_6                         0x23
#define HID_KEY_7                         0x24
#define HID_KEY_8                         0x25
#define HID_KEY_9                         0x26
#define HID_KEY_0                         0x27
#define HID_KEY_ENTER                     0x28
#define HID_KEY_ESCAPE                    0x29
#define HID_KEY_BACKSPACE                 0x2A
#define HID_KEY_TAB                       0x2B
#define HID_KEY_SPACE                     0x2C
#define HID_KEY_MINUS                     0x2D
#define HID_KEY_EQUAL                     0x2E
#define HID_KEY_BRACKET_LEFT              0x2F
#define HID_KEY_BRACKET_RIGHT             0x30
#define HID_KEY_BACKSLASH                 0x31
#define HID_KEY_EUROPE_1                  0x32
#define HID_KEY_SEMICOLON                 0x33
#define HID_KEY_APOSTROPHE                0x34
#define HID_KEY_GRAVE                     0x35
#define HID_KEY_COMMA                     0x36
#define HID_KEY_PERIOD                    0x37
#define HID_KEY_SLASH                     0x38
#define HID_KEY_CAPS_LOCK                 0x39
#define HID_KEY_F1                        0x3A
#define HID_KEY_F2                        0x3B
#define HID_KEY_F3                        0x3C
#define HID_KEY_F4                        0x3D
#define HID_KEY_F5                        0x3E
#define HID_KEY_F6                        0x3F
#define HID_KEY_F7                        0x40
#define HID_KEY_F8                        0x41
#define HID_KEY_F9                        0x42
#define HID_KEY_F10                       0x43
#define HID_KEY_F11                       0x44
#define HID_KEY_F12                       0x45
#define HID_KEY_PRINT_SCREEN              0x46
#define HID_KEY_SCROLL_LOCK               0x47
#define HID_KEY_PAUSE                     0x48
#define HID_KEY_INSERT                    0x49
#define HID_KEY_HOME                      0x4A
#define HID_KEY_PAGE_UP                   0x4B
#define HID_KEY_DELETE                    0x4C
#define HID_KEY_END                       0x4D
#define HID_KEY_PAGE_DOWN                 0x4E
#define HID_KEY_ARROW_RIGHT               0x4F
#define HID_KEY_ARROW_LEFT                0x50
#define HID_KEY_ARROW_DOWN                0x51
#define HID_KEY_ARROW_UP                  0x52
#define HID_KEY_NUM_LOCK                  0x53
#define HID_KEY_KEYPAD_DIVIDE             0x54
#define HID_KEY_KEYPAD_MULTIPLY           0x55
#define HID_KEY_KEYPAD_SUBTRACT           0x56
#define HID_KEY_KEYPAD_ADD                0x57
#define HID_KEY_KEYPAD_ENTER              0x58
#define HID_KEY_KEYPAD_1                  0x59
#define HID_KEY_KEYPAD_2                  0x5A
#define HID_KEY_KEYPAD_3                  0x5B
#define HID_KEY_KEYPAD_4                  0x5C
#define HID_KEY_KEYPAD_5                  0x5D
#define HID_KEY_KEYPAD_6                  0x5E
#define HID_KEY_KEYPAD_7                  0x5F
#define HID_KEY_KEYPAD_8                  0x60
#define HID_KEY_KEYPAD_9                  0x61
#define HID_KEY_KEYPAD_0                  0x62
#define HID_KEY_KEYPAD_DECIMAL            0x63
#define HID_KEY_EUROPE_2                  0x64
#define HID_KEY_APPLICATION               0x65
#define HID_KEY_POWER                     0x66
#define HID_KEY_KEYPAD_EQUAL              0x67
#define HID_KEY_F13                       0x68
#define HID_KEY_F14                       0x69
#define HID_KEY_F15                       0x6A
#define HID_KEY_F16                       0x6B
#define HID_KEY_F17                       0x6C
#define HID_KEY_F18                       0x6D
#define HID_KEY_F19                       0x6E
#define HID_KEY_F20                       0x6F
#define HID_KEY_F21                       0x70
#define HID_KEY_F22                       0x71
#define HID_KEY_F23                       0x72
#define HID_KEY_F24                       0x73
#define HID_KEY_EXECUTE                   0x74
#define HID_KEY_HELP                      0x75
#define HID_KEY_MENU                      0x76
#define HID_KEY_SELECT                    0x77
#define HID_KEY_STOP                      0x78
#define HID_KEY_AGAIN                     0x79
#define HID_KEY_UNDO                      0x7A
#define HID_KEY_CUT                       0x7B
#define HID_KEY_COPY                      0x7C
#define HID_KEY_PASTE                     0x7D
#define HID_KEY_FIND                      0x7E
#define HID_KEY_MUTE                      0x7F
#define HID_KEY_VOLUME_UP                 0x80
#define HID_KEY_VOLUME_DOWN               0x81
#define HID_KEY_LOCKING_CAPS_LOCK         0x82
#define HID_KEY_LOCKING_NUM_LOCK          0x83
#define HID_KEY_LOCKING_SCROLL_LOCK       0x84
#define HID_KEY_KEYPAD_COMMA              0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN         0x86
#define HID_KEY_KANJI1                    0x87
#define HID_KEY_KANJI2                    0x88
#define HID_KEY_KANJI3                    0x89
#define HID_KEY_KANJI4                    0x8A
#define HID_KEY_KANJI5                    0x8B
#define HID_KEY_KANJI6                    0x8C
#define HID_KEY_KANJI7                    0x8D
#define HID_KEY_KANJI8                    0x8E
#define HID_KEY_KANJI9                    0x8F
#define HID_KEY_LANG1                     0x90
#define HID_KEY_LANG2                     0x91
#define HID_KEY_LANG3                     0x92
#define HID_KEY_LANG4                     0x93
#define HID_KEY_LANG5                     0x94
#define HID_KEY_LANG6                     0x95
#define HID_KEY_LANG7                     0x96
#define HID_KEY_LANG8                     0x97
#define HID_KEY_LANG9                     0x98
#define HID_KEY_ALTERNATE_ERASE           0x99
#define HID_KEY_SYSREQ_ATTENTION          0x9A
#define HID_KEY_CANCEL                    0x9B
#define HID_KEY_CLEAR                     0x9C
#define HID_KEY_PRIOR                     0x9D
#define HID_KEY_RETURN                    0x9E
#define HID_KEY_SEPARATOR                 0x9F
#define HID_KEY_OUT                       0xA0
#define HID_KEY_OPER                      0xA1
#define HID_KEY_CLEAR_AGAIN               0xA2
#define HID_KEY_CRSEL_PROPS               0xA3
#define HID_KEY_EXSEL                     0xA4
// RESERVED					                      0xA5-DF
#define HID_KEY_CONTROL_LEFT              0xE0
#define HID_KEY_SHIFT_LEFT                0xE1
#define HID_KEY_ALT_LEFT                  0xE2
#define HID_KEY_GUI_LEFT                  0xE3
#define HID_KEY_CONTROL_RIGHT             0xE4
#define HID_KEY_SHIFT_RIGHT               0xE5
#define HID_KEY_ALT_RIGHT                 0xE6
#define HID_KEY_GUI_RIGHT                 0xE7

#define MAGE_KEY_RAISE                    0xa5
#define MAGE_KEY_LOWER                    0xa6


const int MAX_KEYCODE = 0xe8;

const std::string state_names[] = {
	"HIGH",
	"NORMAL",
	"LOW",
	"CONTROL"
};

inline uint8_t get_from_map(std::unordered_map<std::string, uint8_t> map, std::string key) {
	if (map.find(key) == map.end()) {
		return -1;
	}
	return map[key];
}

const std::unordered_map<std::string, uint8_t> name_to_state = {
	{"HIGH", mage_const::STATE_HIGH},
	{std::to_string(mage_const::STATE_HIGH), mage_const::STATE_HIGH},
	{"NORMAL", mage_const::STATE_NORMAL},
	{std::to_string(mage_const::STATE_NORMAL), mage_const::STATE_NORMAL},
	{"LOW", mage_const::STATE_LOW},
	{std::to_string(mage_const::STATE_LOW), mage_const::STATE_LOW},
	{"CONTROL", mage_const::STATE_CONTROL},
	{std::to_string(mage_const::STATE_CONTROL), mage_const::STATE_CONTROL},
};





const std::unordered_map<std::string, uint8_t> name_to_key = {
	{"NONE", HID_KEY_NONE},
	{"A", HID_KEY_A},
	{"B", HID_KEY_B},
	{"C", HID_KEY_C},
	{"D", HID_KEY_D},
	{"E", HID_KEY_E},
	{"F", HID_KEY_F},
	{"G", HID_KEY_G},
	{"H", HID_KEY_H},
	{"I", HID_KEY_I},
	{"J", HID_KEY_J},
	{"K", HID_KEY_K},
	{"L", HID_KEY_L},
	{"M", HID_KEY_M},
	{"N", HID_KEY_N},
	{"O", HID_KEY_O},
	{"P", HID_KEY_P},
	{"Q", HID_KEY_Q},
	{"R", HID_KEY_R},
	{"S", HID_KEY_S},
	{"T", HID_KEY_T},
	{"U", HID_KEY_U},
	{"V", HID_KEY_V},
	{"W", HID_KEY_W},
	{"X", HID_KEY_X},
	{"Y", HID_KEY_Y},
	{"Z", HID_KEY_Z},
	{"1", HID_KEY_1},
	{"2", HID_KEY_2},
	{"3", HID_KEY_3},
	{"4", HID_KEY_4},
	{"5", HID_KEY_5},
	{"6", HID_KEY_6},
	{"7", HID_KEY_7},
	{"8", HID_KEY_8},
	{"9", HID_KEY_9},
	{"0", HID_KEY_0},
	{"ENTER", HID_KEY_ENTER},
	{"ESC", HID_KEY_ESCAPE},
	{"ESCAPE", HID_KEY_ESCAPE},
	{"BKSP", HID_KEY_BACKSPACE},
	{"BACKSPACE", HID_KEY_BACKSPACE},
	{"TAB", HID_KEY_TAB},
	{"SPACE", HID_KEY_SPACE},
	{"-", HID_KEY_MINUS},
	{"=", HID_KEY_EQUAL},
	{"[", HID_KEY_BRACKET_LEFT},
	{"]", HID_KEY_BRACKET_RIGHT},
	{"\\", HID_KEY_BACKSLASH},
	{"#", HID_KEY_EUROPE_1},
	{";", HID_KEY_SEMICOLON},
	{"\'", HID_KEY_APOSTROPHE},
	{"`", HID_KEY_GRAVE},
	{",", HID_KEY_COMMA},
	{".", HID_KEY_PERIOD},
	{"/", HID_KEY_SLASH},

	{"", HID_KEY_CAPS_LOCK},
	{"F1", HID_KEY_F1},
	{"F2", HID_KEY_F2},
	{"F3", HID_KEY_F3},
	{"F4", HID_KEY_F4},
	{"F5", HID_KEY_F5},
	{"F6", HID_KEY_F6},
	{"F7", HID_KEY_F7},
	{"F8", HID_KEY_F8},
	{"F9", HID_KEY_F9},
	{"F10", HID_KEY_F10},
	{"F11", HID_KEY_F11},
	{"F12", HID_KEY_F12},
	{"PRINT", HID_KEY_PRINT_SCREEN},
	{"SCROLLLOCK", HID_KEY_SCROLL_LOCK},
	{"PAUSE", HID_KEY_PAUSE},
	{"INSRT", HID_KEY_INSERT},
	{"INSERT", HID_KEY_INSERT},
	{"HOME", HID_KEY_HOME},
	{"PGUP", HID_KEY_PAGE_UP},
	{"PAGEUP", HID_KEY_PAGE_UP},
	{"DEL", HID_KEY_DELETE},
	{"END", HID_KEY_END},
	{"PGDN", HID_KEY_PAGE_DOWN},
	{"PAGEDOWN", HID_KEY_PAGE_DOWN},
	{"RIGHT", HID_KEY_ARROW_RIGHT},
	{"LEFT", HID_KEY_ARROW_LEFT},
	{"DOWN", HID_KEY_ARROW_DOWN},
	{"UP", HID_KEY_ARROW_UP},
	{"NUMLK", HID_KEY_NUM_LOCK},
	{"NUMLOCK", HID_KEY_NUM_LOCK},
	{"KPDIV", HID_KEY_KEYPAD_DIVIDE},
	{"KEYPADDIVIDE", HID_KEY_KEYPAD_DIVIDE},
	{"KPMUL", HID_KEY_KEYPAD_MULTIPLY},
	{"KEYPADMULIPLY", HID_KEY_KEYPAD_MULTIPLY},
	{"KPSUB", HID_KEY_KEYPAD_SUBTRACT},
	{"KEYPADSUBTRACT", HID_KEY_KEYPAD_SUBTRACT},
	{"KPADD", HID_KEY_KEYPAD_ADD},
	{"KEYPADADD", HID_KEY_KEYPAD_ADD},
	{"KPENR", HID_KEY_KEYPAD_ENTER},
	{"KEYPADENTER", HID_KEY_KEYPAD_ENTER},
	{"KP1", HID_KEY_KEYPAD_1},
	{"KEYPAD1", HID_KEY_KEYPAD_1},
	{"KP2", HID_KEY_KEYPAD_2},
	{"KEYPAD2", HID_KEY_KEYPAD_2},
	{"KP3", HID_KEY_KEYPAD_3},
	{"KEYPAD3", HID_KEY_KEYPAD_3},
	{"KP4", HID_KEY_KEYPAD_4},
	{"KEYPAD4", HID_KEY_KEYPAD_4},
	{"KP5", HID_KEY_KEYPAD_5},
	{"KEYPAD5", HID_KEY_KEYPAD_5},
	{"KP6", HID_KEY_KEYPAD_6},
	{"KEYPAD6", HID_KEY_KEYPAD_6},
	{"KP7", HID_KEY_KEYPAD_7},
	{"KEYPAD7", HID_KEY_KEYPAD_7},
	{"KP8", HID_KEY_KEYPAD_8},
	{"KEYPAD8", HID_KEY_KEYPAD_8},
	{"KP9", HID_KEY_KEYPAD_9},
	{"KEYPAD9", HID_KEY_KEYPAD_9},
	{"KP0", HID_KEY_KEYPAD_0},
	{"KEYPAD0", HID_KEY_KEYPAD_0},
	{"KPDEC", HID_KEY_KEYPAD_DECIMAL},
	{"KEYPADDEC", HID_KEY_KEYPAD_DECIMAL},
	{"KEYPADDECIMAL", HID_KEY_KEYPAD_DECIMAL},
	{"EUR2", HID_KEY_EUROPE_2},
	{"APP", HID_KEY_APPLICATION},
	{"POWER", HID_KEY_POWER},
	{"KPEQA", HID_KEY_KEYPAD_EQUAL},
	{"F13", HID_KEY_F13},
	{"F14", HID_KEY_F14},
	{"F15", HID_KEY_F15},
	{"F16", HID_KEY_F16},
	{"F17", HID_KEY_F17},
	{"F18", HID_KEY_F18},
	{"F19", HID_KEY_F19},
	{"F20", HID_KEY_F20},
	{"F21", HID_KEY_F21},
	{"F22", HID_KEY_F22},
	{"F23", HID_KEY_F23},
	{"F24", HID_KEY_F24},
	{"EXEC", HID_KEY_EXECUTE},
	{"HELP", HID_KEY_HELP},
	{"MENU", HID_KEY_MENU},
	{"SEL", HID_KEY_SELECT},
	{"STOP", HID_KEY_STOP},
	{"AGAIN", HID_KEY_AGAIN},
	{"UNDO", HID_KEY_UNDO},
	{"CUT", HID_KEY_CUT},
	{"COPY", HID_KEY_COPY},
	{"PASTE", HID_KEY_PASTE},
	{"FIND", HID_KEY_FIND},
	{"MUTE", HID_KEY_MUTE},
	{"VOLUP", HID_KEY_VOLUME_UP},
	{"VOLDN", HID_KEY_VOLUME_DOWN},
	{"LKCAP", HID_KEY_LOCKING_CAPS_LOCK},
	{"LKNUM", HID_KEY_LOCKING_NUM_LOCK},
	{"LKSCR", HID_KEY_LOCKING_SCROLL_LOCK},
	{"KPCOM", HID_KEY_KEYPAD_COMMA},
	{"KEYPADCOM", HID_KEY_KEYPAD_COMMA},
	{"KEYPADCOMMA", HID_KEY_KEYPAD_COMMA},
	{"KPEQS", HID_KEY_KEYPAD_EQUAL_SIGN},
	{"KEYPADEQS", HID_KEY_KEYPAD_EQUAL_SIGN},
	{"KEYPADEQUALSIGN", HID_KEY_KEYPAD_EQUAL_SIGN},
	{"KAN1", HID_KEY_KANJI1},
	{"KANJI1", HID_KEY_KANJI1},
	{"KAN2", HID_KEY_KANJI2},
	{"KANJI2", HID_KEY_KANJI2},
	{"KAN3", HID_KEY_KANJI3},
	{"KANJI3", HID_KEY_KANJI3},
	{"KAN4", HID_KEY_KANJI4},
	{"KANJI4", HID_KEY_KANJI4},
	{"KAN5", HID_KEY_KANJI5},
	{"KANJI5", HID_KEY_KANJI5},
	{"KAN6", HID_KEY_KANJI6},
	{"KANJI6", HID_KEY_KANJI6},
	{"KAN7", HID_KEY_KANJI7},
	{"KANJI7", HID_KEY_KANJI7},
	{"KAN8", HID_KEY_KANJI8},
	{"KANJI8", HID_KEY_KANJI8},
	{"KAN9", HID_KEY_KANJI9},
	{"KANJI9", HID_KEY_KANJI9},
	{"LANG1", HID_KEY_LANG1},
	{"LANG2", HID_KEY_LANG2},
	{"LANG3", HID_KEY_LANG3},
	{"LANG4", HID_KEY_LANG4},
	{"LANG5", HID_KEY_LANG5},
	{"LANG6", HID_KEY_LANG6},
	{"LANG7", HID_KEY_LANG7},
	{"LANG8", HID_KEY_LANG8},
	{"LANG9", HID_KEY_LANG9},
	{"ALTER", HID_KEY_ALTERNATE_ERASE},
	{"ALTERNATEERASE", HID_KEY_ALTERNATE_ERASE},
	{"SYSAT", HID_KEY_SYSREQ_ATTENTION},
	{"CANCL", HID_KEY_CANCEL},
	{"CLEAR", HID_KEY_CLEAR},
	{"PRIOR", HID_KEY_PRIOR},
	{"RET", HID_KEY_RETURN},
	{"SEP", HID_KEY_SEPARATOR},
	{"OUT", HID_KEY_OUT},
	{"OPER", HID_KEY_OPER},
	{"CLRAG", HID_KEY_CLEAR_AGAIN},
	{"CRSEL", HID_KEY_CRSEL_PROPS},
	{"EXSEL", HID_KEY_EXSEL},

	{"LCTRL", HID_KEY_CONTROL_LEFT},
	{"LEFTCTRL", HID_KEY_CONTROL_LEFT},
	{"LEFTCONTROL", HID_KEY_CONTROL_LEFT},
	{"LEFT_CONTROL", HID_KEY_CONTROL_LEFT},
	{"CTRLL", HID_KEY_CONTROL_LEFT},
	{"LSHFT", HID_KEY_SHIFT_LEFT},
	{"LEFTSHFT", HID_KEY_SHIFT_LEFT},
	{"LEFTSHIFT", HID_KEY_SHIFT_LEFT},
	{"LEFT_SHIFT", HID_KEY_SHIFT_LEFT},
	{"SHFTL", HID_KEY_SHIFT_LEFT},
	{"LALT", HID_KEY_ALT_LEFT},
	{"LEFTALT", HID_KEY_ALT_LEFT},
	{"LEFT_ALT", HID_KEY_ALT_LEFT},
	{"ALTL", HID_KEY_ALT_LEFT},
	{"LGUI", HID_KEY_GUI_LEFT},
	{"LEFTGUI", HID_KEY_GUI_LEFT},
	{"LEFT_GUI", HID_KEY_GUI_LEFT},
	{"GUIL", HID_KEY_GUI_LEFT},
	{"RCTRL", HID_KEY_CONTROL_RIGHT},
	{"RIGHTCTRL", HID_KEY_CONTROL_RIGHT},
	{"RIGHTCONTROL", HID_KEY_CONTROL_RIGHT},
	{"RIGHT_CONTROL", HID_KEY_CONTROL_RIGHT},
	{"CTRLR", HID_KEY_CONTROL_RIGHT},
	{"RSHFT", HID_KEY_SHIFT_RIGHT},
	{"RIGHTSHFT", HID_KEY_SHIFT_RIGHT},
	{"RIGHTSHIFT", HID_KEY_SHIFT_RIGHT},
	{"RIGHT_SHIFT", HID_KEY_SHIFT_RIGHT},
	{"SHFTR", HID_KEY_SHIFT_RIGHT},
	{"RALT", HID_KEY_ALT_RIGHT},
	{"RIGHTALT", HID_KEY_ALT_RIGHT},
	{"RIGHT_ALT", HID_KEY_ALT_RIGHT},
	{"ALTR", HID_KEY_ALT_RIGHT},
	{"RGUI", HID_KEY_GUI_RIGHT},
	{"RIGHTGUI", HID_KEY_GUI_RIGHT},
	{"RIGHT_GUI", HID_KEY_GUI_RIGHT},
	{"GUIR", HID_KEY_GUI_RIGHT},
	{"RAISE", MAGE_KEY_RAISE},
	{"LOWER", MAGE_KEY_LOWER},
};

const std::string keycode_names[] = {"NONE",
							  "NA",
							  "NA",
							  "NA",
							  "A",
							  "B",
							  "C",
							  "D",
							  "E",
							  "F",
							  "G",
							  "H",
							  "I",
							  "J",
							  "K",
							  "L",
							  "M",
							  "N",
							  "O",
							  "P",
							  "Q",
							  "R",
							  "S",
							  "T",
							  "U",
							  "V",
							  "W",
							  "X",
							  "Y",
							  "Z",
							  "1",
							  "2",
							  "3",
							  "4",
							  "5",
							  "6",
							  "7",
							  "8",
							  "9",
							  "0",
							  "ENTER",
							  "ESC",
							  "BKSP",
							  "TAB",
							  "SPACE",
							  "-",
							  "=",
							  "[",
							  "]",
							  "\\",
							  "#",
							  ";",
							  "\'",
							  "`",
							  ",",
							  ".",
							  "/",
							  "CAPS", // 0x39
							  "F1",
							  "F2",
							  "F3",
							  "F4",
							  "F5",
							  "F6",
							  "F7",
							  "F8",
							  "F9",
							  "F10",
							  "F11",
							  "F12",
							  "PRINT",
							  "SCRLK",
							  "PAUSE",
							  "INSRT",
							  "HOME",
							  "PGUP",
							  "DEL",
							  "END",
							  "PGDN",
							  "RIGHT",
							  "LEFT",
							  "DOWN",
							  "UP",
							  "NUMLK",
							  "KPDIV",
							  "KPMUL",
							  "KPSUB",
							  "KPADD",
							  "KPENR",
							  "KP1",
							  "KP2",
							  "KP3",
							  "KP4",
							  "KP5",
							  "KP6",
							  "KP7",
							  "KP8",
							  "KP9",
							  "KP0",
							  "KPDEC",
							  "EUR2",
							  "APP",
							  "POWER",
							  "KPEQA",
							  "F13",
							  "F14",
							  "F15",
							  "F16",
							  "F17",
							  "F18",
							  "F19",
							  "F20",
							  "F21",
							  "F22",
							  "F23",
							  "F24",
							  "EXEC",
							  "HELP",
							  "MENU",
							  "SEL",
							  "STOP",
							  "AGAIN",
							  "UNDO",
							  "CUT",
							  "COPY",
							  "PASTE",
							  "FIND",
							  "MUTE",
							  "VOLUP",
							  "VOLDN",
							  "LKCAP",
							  "LKNUM",
							  "LKSCR",
							  "KPCOM",
							  "KPEQS",
							  "KAN1",
							  "KAN2",
							  "KAN3",
							  "KAN4",
							  "KAN5",
							  "KAN6",
							  "KAN7",
							  "KAN8",
							  "KAN9",
							  "LANG1",
							  "LANG2",
							  "LANG3",
							  "LANG4",
							  "LANG5",
							  "LANG6",
							  "LANG7",
							  "LANG8",
							  "LANG9",
							  "ALTER",
							  "SYSAT",
							  "CANCL",
							  "CLEAR",
							  "PRIOR",
							  "RET",
							  "SEP",
							  "OUT",
							  "OPER",
							  "CLRAG",
							  "CRSEL",
							  "EXSEL", // 0xA4
							  "RAISE", // 0xa5
							  "LOWER", // 0xa6
							  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 0xa7 - 0xb7
							  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 0xb7 - 0xc7
							  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 0xc7 - 0xd7
							  "", "", "", "", "", "", "", "", "", // 0xd7 - 0xdf
							  "LCTRL", // 0xE0
							  "LSHFT",
							  "LALT",
							  "LGUI",
							  "RCTRL",
							  "RSHFT",
							  "RALT",
							  "RGUI"
};
