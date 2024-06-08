// FileListBoxWindow.h

#pragma once

#include <windows.h>
#include <commctrl.h>

#include "Ascii.h"
#include "Common.h"

#define FILE_LIST_BOX_WINDOW_CLASS_NAME											WC_LISTBOX

#define FILE_LIST_BOX_WINDOW_EXTENDED_STYLE										0
#define FILE_LIST_BOX_WINDOW_STYLE												( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY )
#define FILE_LIST_BOX_WINDOW_TEXT												NULL

#define FILE_LIST_BOX_WINDOW_HEIGHT												100

#define FILE_LIST_BOX_WINDOW_TEXT_COLOR											GetSysColor( COLOR_GRAYTEXT )
#define FILE_LIST_BOX_WINDOW_BACKGROUND_COLOR									GetSysColor( COLOR_WINDOW )

BOOL IsFileListBoxWindow( HWND hWnd );

int FileListBoxWindowAddLine( LPCTSTR lpszLine );

int FileListBoxWindowAddText( LPCTSTR lpszText );

LRESULT FileListBoxWindowControlColor( WPARAM wParam );

BOOL FileListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, int nLeft, int nTop, int nWidth, int nHeight );

int FileListBoxWindowGetCurrentSelection();

int FileListBoxWindowGetItemText( int nWhichItem, LPTSTR lpszItemText );

BOOL FileListBoxWindowGetRect( LPRECT lpRect );

BOOL FileListBoxWindowHandleCommandMessage( WPARAM wParam, LPARAM lParam, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) );

BOOL FileListBoxWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint = TRUE );

HWND FileListBoxWindowSetFocus();

void FileListBoxWindowSetFont( HFONT hFont );

