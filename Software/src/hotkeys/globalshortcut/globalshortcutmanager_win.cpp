/*
 * globalshortcutmanager_win.cpp - Windows implementation of global shortcuts
 * Copyright (C) 2003-2006  Justin Karneges, Maciej Niedzielski
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "globalshortcutmanager.h"
#include "globalshortcuttrigger.h"

#include <QWidget>

#include <windows.h>
#include <winuser.h>
#include <QDebug>

class GlobalShortcutManager::KeyTrigger::Impl : public QWidget
{
public:
	/**
	 * Constructor registers the hotkey.
	 */
	Impl(GlobalShortcutManager::KeyTrigger* t, const QKeySequence& ks)
		: trigger_(t)
		, id_(0)
	{
        UINT mod = 0, key = 0;
		if (convertKeySequence(ks, &mod, &key))
            if (RegisterHotKey(winId(), nextId, mod, key))
				id_ = nextId++;
	}

	/**
	 * Destructor unregisters the hotkey.
	 */
	~Impl()
	{
		if (id_)
			UnregisterHotKey(winId(), id_);
	}

	/**
	 * Triggers triggered() signal when the hotkey is activated.
	 */
	bool winEvent(MSG* m, long* result)
	{
		if (m->message == WM_HOTKEY && m->wParam == id_) {
			emit trigger_->triggered();
			return true;
		}
		return QWidget::winEvent(m, result);
	}

private:
	KeyTrigger* trigger_;
	WPARAM id_;
	static WPARAM nextId;

private:
	struct Qt_VK_Keymap
	{
		int key;
		UINT vk;
	};
	static Qt_VK_Keymap qt_vk_table[];

	static bool convertKeySequence(const QKeySequence& ks, UINT* mod_, UINT* key_)
	{
        int code = ks;

        UINT mod = 0;
		if (code & Qt::META)
			mod |= MOD_WIN;
		if (code & Qt::SHIFT)
			mod |= MOD_SHIFT;
		if (code & Qt::CTRL)
			mod |= MOD_CONTROL;
		if (code & Qt::ALT)
			mod |= MOD_ALT;

        code &= ~Qt::KeyboardModifierMask;


		UINT key = 0;        

        qDebug() << "Code is->" << code;
        if (code >= 0x20 && code <= 0x7f && !isBugKeyCode(&code))
			key = code;
		else {
			for (int n = 0; qt_vk_table[n].key != Qt::Key_unknown; ++n) {
				if (qt_vk_table[n].key == code) {
					key = qt_vk_table[n].vk;
					break;
				}
			}
			if (!key)
				return false;
		}

		if (mod)
			*mod_ = mod;
		if (key)
			*key_ = key;

		return true;
	}

    // Function check current key code value and if it's one of known bug keys, replace original key code with new one.
    // Also we replace shifted cimbination(such as !)
    // return true if keo code converted.
    // return false if key code normal or not supported.
    static bool isBugKeyCode(int *code)
    {
        switch (*code)
        {
            // ! key
            case 33:
                *code = Qt::Key_1;
                return false;
            break;

            // @ key
            case 64:
                *code = Qt::Key_2;
                return false;
            break;

            // # key
            case 35:
                *code = Qt::Key_3;
                return false;
            break;

            // $ key
            case 36:
                *code = Qt::Key_4;
                return false;
            break;

            // % key
            case 37:
                *code = Qt::Key_5;
                return false;
            break;

            // ^ key
            case 94:
                *code = Qt::Key_6;
                return false;
            break;

            // & key
            case 38:
                *code = Qt::Key_7;
                return false;
            break;

            // ( key
            case 40:
                *code = Qt::Key_9;
                return false;
            break;

            // ) key
            case 41:
                *code = Qt::Key_0;
                return false;
            break;

            // Multiply key.
            case 42:
                *code = Qt::Key_multiply;
                return false;
            break;

            // Plus key
            case 43:
               *code = Qt::Key_Plus;
                return true;
            break;

            // Comma key
            case 44:
            case 60:
                *code = Qt::Key_Comma;
                return true;
            break;

            // Subtract key
            case 45:
            case 95:
                *code = Qt::Key_Minus;
                return true;
            break;

            // Dot key
            case 46:
            case 62:
                *code = Qt::Key_Period;
                return true;
            break;

            // Divide key
            case 47:
            case 63:
                *code = Qt::Key_division;
                return true;
            break;

            // ` and ~ keys
            case 96:
            case 126:
                *code = Qt::Key_AsciiTilde;
                return true;
            break;

            // \ key
            case 92:
            // |key
            case 124:
                *code = Qt::Key_brokenbar;
                return true;
            break;

            // [ key
            case 91:
            // { key
            case 123:
                *code = Qt::Key_BracketLeft;
                return true;
            break;

            // ] key
            case 93:
            // } key
            case 125:
                *code = Qt::Key_BracketRight;
                return true;
            break;
        }
        return false;
    }
};

GlobalShortcutManager::KeyTrigger::Impl::Qt_VK_Keymap
GlobalShortcutManager::KeyTrigger::Impl::qt_vk_table[] = {
	{ Qt::Key_Escape,      VK_ESCAPE },
	{ Qt::Key_Tab,         VK_TAB },
	{ Qt::Key_Backtab,     0 },
	{ Qt::Key_Backspace,   VK_BACK },
	{ Qt::Key_Return,      VK_RETURN },
	{ Qt::Key_Enter,       VK_RETURN },
	{ Qt::Key_Insert,      VK_INSERT },
	{ Qt::Key_Delete,      VK_DELETE },
	{ Qt::Key_Pause,       VK_PAUSE },
	{ Qt::Key_Print,       VK_PRINT },
	{ Qt::Key_SysReq,      0 },
	{ Qt::Key_Clear,       VK_CLEAR },
	{ Qt::Key_Home,        VK_HOME },
	{ Qt::Key_End,         VK_END },
	{ Qt::Key_Left,        VK_LEFT },
	{ Qt::Key_Up,          VK_UP },
	{ Qt::Key_Right,       VK_RIGHT },
	{ Qt::Key_Down,        VK_DOWN },
	{ Qt::Key_PageUp,      VK_PRIOR },
	{ Qt::Key_PageDown,    VK_NEXT },
	{ Qt::Key_Shift,       VK_SHIFT },
	{ Qt::Key_Control,     VK_CONTROL },
	{ Qt::Key_Meta,        VK_LWIN },
	{ Qt::Key_Alt,         VK_MENU },
	{ Qt::Key_CapsLock,    VK_CAPITAL },
	{ Qt::Key_NumLock,     VK_NUMLOCK },
	{ Qt::Key_ScrollLock,  VK_SCROLL },
	{ Qt::Key_F1,          VK_F1 },
	{ Qt::Key_F2,          VK_F2 },
	{ Qt::Key_F3,          VK_F3 },
	{ Qt::Key_F4,          VK_F4 },
	{ Qt::Key_F5,          VK_F5 },
	{ Qt::Key_F6,          VK_F6 },
	{ Qt::Key_F7,          VK_F7 },
	{ Qt::Key_F8,          VK_F8 },
	{ Qt::Key_F9,          VK_F9 },
	{ Qt::Key_F10,         VK_F10 },
	{ Qt::Key_F11,         VK_F11 },
	{ Qt::Key_F12,         VK_F12 },
	{ Qt::Key_F13,         VK_F13 },
	{ Qt::Key_F14,         VK_F14 },
	{ Qt::Key_F15,         VK_F15 },
	{ Qt::Key_F16,         VK_F16 },
	{ Qt::Key_F17,         VK_F17 },
	{ Qt::Key_F18,         VK_F18 },
	{ Qt::Key_F19,         VK_F19 },
	{ Qt::Key_F20,         VK_F20 },
	{ Qt::Key_F21,         VK_F21 },
	{ Qt::Key_F22,         VK_F22 },
	{ Qt::Key_F23,         VK_F23 },
	{ Qt::Key_F24,         VK_F24 },
	{ Qt::Key_F25,         0 },
	{ Qt::Key_F26,         0 },
	{ Qt::Key_F27,         0 },
	{ Qt::Key_F28,         0 },
	{ Qt::Key_F29,         0 },
	{ Qt::Key_F30,         0 },
	{ Qt::Key_F31,         0 },
	{ Qt::Key_F32,         0 },
	{ Qt::Key_F33,         0 },
	{ Qt::Key_F34,         0 },
	{ Qt::Key_F35,         0 },
	{ Qt::Key_Super_L,     0 },
	{ Qt::Key_Super_R,     0 },
	{ Qt::Key_Menu,        0 },
	{ Qt::Key_Hyper_L,     0 },
	{ Qt::Key_Hyper_R,     0 },
	{ Qt::Key_Help,        0 },
	{ Qt::Key_Direction_L, 0 },
    { Qt::Key_Direction_R, 0 },
    { Qt::Key_multiply,    VK_MULTIPLY },
    { Qt::Key_Comma,       188 }, // VK_OEM_COMMA
    { Qt::Key_Plus,        VK_ADD },
    { Qt::Key_Minus,       VK_SUBTRACT },
    { Qt::Key_Period,      190 },   // VK_OEM_PERIOD
    { Qt::Key_division,    VK_DIVIDE },
    { Qt::Key_AsciiTilde,  192 },   // VK_OEM_3
    { Qt::Key_BracketLeft, 219 },   // VK_OEM_4
    { Qt::Key_BracketRight,221 },   // VK_OEM_6
    { Qt::Key_brokenbar,   220 },   // VK_OEM_5

	{ Qt::Key_unknown,     0 },
};

WPARAM GlobalShortcutManager::KeyTrigger::Impl::nextId = 1;

GlobalShortcutManager::KeyTrigger::KeyTrigger(const QKeySequence& key)
{
	d = new Impl(this, key);
}

GlobalShortcutManager::KeyTrigger::~KeyTrigger()
{
	delete d;
	d = 0;
}
