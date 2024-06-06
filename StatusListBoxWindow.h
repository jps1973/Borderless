// StatusListBoxWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define STATUS_LIST_BOX_WINDOW_CLASS_NAME										WC_LISTBOX

#define STATUS_LIST_BOX_WINDOW_EXTENDED_STYLE									0
#define STATUS_LIST_BOX_WINDOW_STYLE											( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define STATUS_LIST_BOX_WINDOW_TEXT												NULL

#define STATUS_LIST_BOX_WINDOW_HEIGHT											100

#define STATUS_LIST_BOX_WINDOW_TEXT_COLOR										GetSysColor( COLOR_GRAYTEXT )
#define STATUS_LIST_BOX_WINDOW_BACKGROUND_COLOR									GetSysColor( COLOR_WINDOW )

BOOL IsStatusListBoxWindow( HWND hWnd );

int StatusListBoxWindowAddLine( LPCTSTR lpszLine );

int StatusListBoxWindowAddText( LPCTSTR lpszText );

LRESULT StatusListBoxWindowControlColor( WPARAM wParam );

BOOL StatusListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, int nLeft, int nTop, int nWidth, int nHeight );

int StatusListBoxWindowGetCurrentSelection();

int StatusListBoxWindowGetItemText( int nWhichItem, LPTSTR lpszItemText );

BOOL StatusListBoxWindowGetRect( LPRECT lpRect );

BOOL StatusListBoxWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) );

BOOL StatusListBoxWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

HWND StatusListBoxWindowSetFocus();

void StatusListBoxWindowSetFont( HFONT hFont );

