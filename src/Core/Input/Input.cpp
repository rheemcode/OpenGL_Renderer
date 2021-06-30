#include "Input.h"
#include <Windows.h>

Input* Input::s_Instance;
Input* Input::GetSingleton() { return s_Instance; }
struct _WinTranslatePair
{
	uint32_t keysym;
	uint32_t keycode;
};

static _WinTranslatePair _vkToKeyCode[] =
{
	{ Key::BACKSPACE, VK_BACK},
	{ Key::TAB, VK_TAB},
	{ Key::ENTER, VK_RETURN},
	{ Key::LEFT_SHIFT, VK_LSHIFT },
	{ Key::RIGHT_SHIFT, VK_RSHIFT },
	{ Key::LEFT_CONTROL, VK_LCONTROL },
	{ Key::RIGHT_ALT, VK_RMENU },
	{ Key::LEFT_ALT, VK_LMENU },
	{ Key::PAUSE, VK_PAUSE },
	{ Key::ESCAPE, VK_ESCAPE },
	{ Key::SPACE, VK_SPACE },
	{ Key::PAGE_UP, VK_PRIOR },
	{ Key::PAGE_DOWN, VK_NEXT },
	{ Key::END, VK_END },
	{ Key::HOME, VK_HOME },
	{ Key::LEFT, VK_LEFT },
	{ Key::UP, VK_UP },
	{ Key::RIGHT, VK_RIGHT },
	{ Key::DOWN, VK_DOWN }, 
	{Key::K0, (0x30) }, ////0 key
	{Key::K1, (0x31) }, ////1 key
	{Key::K2, (0x32) }, ////2 key
	{Key::K3, (0x33) }, ////3 key
	{Key::K4, (0x34) }, ////4 key
	{Key::K5, (0x35) }, ////5 key
	{Key::K6, (0x36) }, ////6 key
	{Key::K7, (0x37) }, ////7 key
	{Key::K8, (0x38) }, ////8 key
	{Key::K9, (0x39) }, ////9 key
	{Key::A, (0x41) }, ////A key
	{Key::B, (0x42) }, ////B key
	{Key::C, (0x43) }, ////C key
	{Key::D, (0x44) }, ////D key
	{Key::E, (0x45) }, ////E key
	{Key::F, (0x46) }, ////F key
	{Key::G, (0x47) }, ////G key
	{Key::H, (0x48) }, ////H key
	{Key::I, (0x49) }, ////I key
	{Key::J, (0x4A) }, ////J key
	{Key::K, (0x4B) }, ////K key
	{Key::L, (0x4C) }, ////L key
	{Key::M, (0x4D) }, ////M key
	{Key::N, (0x4E) }, ////N key
	{Key::O, (0x4F) }, ////O key
	{Key::P, (0x50) }, ////P key
	{Key::Q, (0x51) }, ////Q key
	{Key::R, (0x52) }, ////R key
	{Key::S, (0x53) }, ////S key
	{Key::T, (0x54) }, ////T key
	{Key::U, (0x55) }, ////U key
	{Key::V, (0x56) }, ////V key
	{Key::W, (0x57) }, ////W key
	{Key::X, (0x58) }, ////X key
	{Key::Y, (0x59) }, ////Y key
	{Key::Z, (0x5A) }, ////Z key
	{ Key::MENU, VK_APPS }, //(0x5D)
	{ Key::KP_0, VK_NUMPAD0 }, //(0x60)
	{ Key::KP_1, VK_NUMPAD1 }, //(0x61)
	{ Key::KP_2, VK_NUMPAD2 }, //(0x62)
	{ Key::KP_3, VK_NUMPAD3 }, //(0x63)
	{ Key::KP_4, VK_NUMPAD4 }, //(0x64)
	{ Key::KP_5, VK_NUMPAD5 }, //(0x65)
	{ Key::KP_6, VK_NUMPAD6 }, //(0x66)
	{ Key::KP_7, VK_NUMPAD7 }, //(0x67)
	{ Key::KP_8, VK_NUMPAD8 }, //(0x68)
	{ Key::KP_9, VK_NUMPAD9 }, //(0x69)
	{ Key::KP_MULTIPLY, VK_MULTIPLY }, // (0x6A)
	{ Key::KP_ADD, VK_ADD }, // (0x6B)
	{ Key::KP_SUBTRACT, VK_SUBTRACT }, // (0x6D)
	{ Key::PERIOD, VK_DECIMAL }, // (0x6E)
	{ Key::KP_DIVIDE, VK_DIVIDE }, // (0x6F)
	{ Key::F1, VK_F1 }, // (0x70)
	{ Key::F2, VK_F2 }, // (0x71)
	{ Key::F3, VK_F3 }, // (0x72)
	{ Key::F4, VK_F4 }, // (0x73)
	{ Key::F5, VK_F5 }, // (0x74)
	{ Key::F6, VK_F6 }, // (0x75)
	{ Key::F7, VK_F7 }, // (0x76)
	{ Key::F8, VK_F8 }, // (0x77)
	{ Key::F9, VK_F9 }, // (0x78)
	{ Key::F10, VK_F10 }, // (0x79)
	{ Key::F11, VK_F11 }, // (0x7A)
	{ Key::F12, VK_F12 }, // (0x7B)
	{ Key::F13, VK_F13 }, // (0x7C)
	{ Key::F14, VK_F14 }, // (0x7D)
	{ Key::F15, VK_F15 }, // (0x7E)
	{ Key::F16, VK_F16 }, // (0x7F)
	{ Key::NUMLOCK, VK_NUMLOCK }, // (0x90)
	{ Key::SCROLLLOCK, VK_SCROLL }, // (0x91)
	{ Key::MENU, VK_LMENU }, // (0xA4)
	{ Key::MENU, VK_RMENU }, // (0xA5)
	{ Key::SEMICOLON, VK_OEM_1 }, // (0xBA)
	{ Key::EQUAL, VK_OEM_PLUS }, // (0xBB) // Windows 2000/XP: For any country/region, the '+' key
	{ Key::COMMA, VK_OEM_COMMA }, // (0xBC) // Windows 2000/XP: For any country/region, the ',' key
	{ Key::MINUS, VK_OEM_MINUS }, // (0xBD) // Windows 2000/XP: For any country/region, the '-' key
	{ Key::PERIOD, VK_OEM_PERIOD }, // (0xBE) // Windows 2000/XP: For any country/region, the '.' key
	{ Key::SLASH, VK_OEM_2 }, // (0xBF) //Windows 2000/XP: For the US standard keyboard, the '/?' key
	{ Key::LEFT_BRACKET, VK_OEM_4 }, // (0xDB)
	{ Key::BACKSLASH, VK_OEM_5 }, // (0xDC)
	{ Key::RIGHT_BRACKET, VK_OEM_6 }, // (0xDD)
	{ Key::APOSTROPHE, VK_OEM_7 }, // (0xDE)
};


static _WinTranslatePair _scancodeToKeycode[] = {
	{ Key::ESCAPE, 0x01 },
	{ Key::K1, 0x02 },
	{ Key::K2, 0x03 },
	{ Key::K3, 0x04 },
	{ Key::K4, 0x05 },
	{ Key::K5, 0x06 },
	{ Key::K6, 0x07 },
	{ Key::K7, 0x08 },
	{ Key::K8, 0x09 },
	{ Key::K9, 0x0A },
	{ Key::K0, 0x0B },
	{ Key::MINUS, 0x0C },
	{ Key::EQUAL, 0x0D },
	{ Key::BACKSPACE, 0x0E },
	{ Key::TAB, 0x0F },
	{ Key::Q, 0x10 },
	{ Key::W, 0x11 },
	{ Key::E, 0x12 },
	{ Key::R, 0x13 },
	{ Key::T, 0x14 },
	{ Key::Y, 0x15 },
	{ Key::U, 0x16 },
	{ Key::I, 0x17 },
	{ Key::O, 0x18 },
	{ Key::P, 0x19 },
	{ Key::LEFT_BRACKET, 0x1A },
	{ Key::RIGHT_BRACKET, 0x1B },
	{ Key::ENTER, 0x1C },
	{ Key::LEFT_CONTROL, 0x1D },
	{ Key::A, 0x1E },
	{ Key::S, 0x1F },
	{ Key::D, 0x20 },
	{ Key::F, 0x21 },
	{ Key::G, 0x22 },
	{ Key::H, 0x23 },
	{ Key::J, 0x24 },
	{ Key::K, 0x25 },
	{ Key::L, 0x26 },
	{ Key::SEMICOLON, 0x27 },
	{ Key::APOSTROPHE, 0x28 },
	{ Key::LEFT_SHIFT, 0x2A },
	{ Key::BACKSLASH, 0x2B },
	{ Key::Z, 0x2C },
	{ Key::X, 0x2D },
	{ Key::C, 0x2E },
	{ Key::V, 0x2F },
	{ Key::B, 0x30 },
	{ Key::N, 0x31 },
	{ Key::M, 0x32 },
	{ Key::COMMA, 0x33 },
	{ Key::PERIOD, 0x34 },
	{ Key::SLASH, 0x35 },
	{ Key::RIGHT_SHIFT, 0x36 },
	{ Key::RIGHT_ALT, 0x38 },
	{ Key::SPACE, 0x39 },
	{ Key::CAPSLOCK, 0x3A },
	{ Key::F1, 0x3B },
	{ Key::F2, 0x3C },
	{ Key::F3, 0x3D },
	{ Key::F4, 0x3E },
	{ Key::F5, 0x3F },
	{ Key::F6, 0x40 },
	{ Key::F7, 0x41 },
	{ Key::F8, 0x42 },
	{ Key::F9, 0x43 },
	{ Key::F10, 0x44 },
	{ Key::NUMLOCK, 0x45 },
	{ Key::SCROLLLOCK, 0x46 },
	{ Key::HOME, 0x47 },
	{ Key::UP, 0x48 },
	{ Key::PAGE_UP, 0x49 },
	{ Key::KP_SUBTRACT, 0x4A },
	{ Key::LEFT, 0x4B },
	{ Key::KP_5, 0x4C },
	{ Key::RIGHT, 0x4D },
	{ Key::KP_ADD, 0x4E },
	{ Key::END, 0x4F },
	{ Key::DOWN, 0x50 },
	{ Key::PAGE_DOWN, 0x51 },
	{ Key::INSERT, 0x52 },
	{ Key::KDELETE, 0x53 },
	{ Key::F11, 0x57 },
	{ Key::F12, 0x58 },
	{ Key::MENU, 0x5D },
	{ Key::F13, 0x64 },
	{ Key::F14, 0x65 },
	{ Key::F15, 0x66 },
	{ Key::F16, 0x67 },
};

unsigned int Input::GetKeySym(unsigned int p_code) {
	for (int i = 0; _vkToKeyCode[i].keysym != 0; i++) {
		if (_vkToKeyCode[i].keycode == p_code) {
			return _vkToKeyCode[i].keysym;
		}
	}

	return 0;
}

unsigned int Input::GetScanSym(unsigned int p_code) {
	unsigned int keycode = 0;
	for (int i = 0; _scancodeToKeycode[i].keysym != 0; i++) {
		if (_scancodeToKeycode[i].keycode == p_code) {
			keycode = _scancodeToKeycode[i].keysym;
			break;
		}
	}
	return keycode;
}

int Input::GetKeyMods()
{
	int mods = 0;

	if (GetKeyState(VK_SHIFT) & 0x8000)
		mods |= Key::MODSHIFT;
	if (GetKeyState(VK_CONTROL) & 0x8000)
		mods |= Key::MODCONTROL;
	if (GetKeyState(VK_MENU) & 0x8000)
		mods |= Key::MODALT;
	if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000)
		mods |= Key::MOD_SUPER;
	if (GetKeyState(VK_CAPITAL) & 1)
		mods |= Key::MOD_CAPS_LOCK;
	if (GetKeyState(VK_NUMLOCK) & 1)
		mods |= Key::MOD_NUM_LOCK;

	return mods;
}