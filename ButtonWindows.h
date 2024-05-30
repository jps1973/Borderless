// ButtonWindows.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define BUTTON_WINDOWS_CLASS_NAME												WC_BUTTON

#define BUTTON_WINDOWS_EXTENDED_STYLE											0
#define BUTTON_WINDOWS_STYLE													( WS_CHILD | WS_VISIBLE | BS_FLAT | BS_VCENTER )

#define BUTTON_WINDOWS_BUTTON_WIDTH												60
#define BUTTON_WINDOWS_BUTTON_HEIGHT											25

#define BUTTON_WINDOWS_TITLES													{ "Browse...", "Filter...", "Copy...", "Move...", "Delete...", "Rename", "About", "Exit" }

#define BUTTON_WINDOWS_FIRST_BUTTON_ID											WM_USER

typedef enum ButtonWindowsButtons
{
	BUTTON_WINDOWS_BROWSE_BUTTON = 0,
	BUTTON_WINDOWS_FILTER_BUTTON,
	BUTTON_WINDOWS_COPY_BUTTON,
	BUTTON_WINDOWS_MOVE_BUTTON,
	BUTTON_WINDOWS_DELETE_BUTTON,
	BUTTON_WINDOWS_RENAME_BUTTON,
	BUTTON_WINDOWS_ABOUT_BUTTON,
	BUTTON_WINDOWS_EXIT_BUTTON,

	BUTTON_WINDOWS_NUMBER_OF_BUTTONS

} BUTTON_WINDOWS_BUTTONS;

BOOL ButtonWindowsCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont, int nTop, int nSeparatorSize );

BOOL ButtonWindowsMove( int nTop, int nSeparatorSize );
