// FileListBoxWindow.cpp

#include "FileListBoxWindow.h"

// Global variables
static HWND g_hWndFileListBox;

BOOL IsFileListBoxWindow( HWND hWnd )
{
	// See if supplied window is file list box window
	return( hWnd == g_hWndFileListBox );

} // End of function IsFileListBoxWindow

int FileListBoxWindowAddLine( LPCTSTR lpszLine )
{
	// Add line to file list box window
	return ::SendMessage( g_hWndFileListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszLine );

} // End of function FileListBoxWindowAddLine

int FileListBoxWindowAddText( LPCTSTR lpszText )
{
	int nResult = 0;

	LPTSTR lpszLine;
	LPTSTR lpszTemp;
	DWORD dwTextLength;

	// Get text length
	dwTextLength = lstrlen( lpszText );

	// Allocate string memory
	lpszTemp = new char[ dwTextLength + sizeof( char ) ];

	// Copy text into a temporary string
	lstrcpy( lpszTemp, lpszText );

	// Get first line
	lpszLine = strtok( lpszTemp, NEW_LINE_TEXT );

	// Loop through all lines
	while( lpszLine )
	{
		// Ensure that line is not empty
		if( lpszLine[ 0 ] )
		{
			// Line is not empty

			// Add line to file list box window
			if( ::SendMessage( g_hWndFileListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszLine ) >= 0 )
			{
				// Successfully added line to file list box window

				// Get next line
				lpszLine = strtok( NULL, NEW_LINE_TEXT );

				// Update return value
				nResult ++;

			} // End of successfully added line to file list box window
			else
			{
				// Unable to add line to list box window

				// Force exit from loop
				lpszLine = NULL;

			} // End of unable to add line to list box window

		} // End of line is not empty
		else
		{
			// Line is empty

			// Get next line
			lpszLine = strtok( NULL, NEW_LINE_TEXT );

		} // End of line is empty
	
	}; // End of loop through all lines

	// Free string memory
	delete [] lpszTemp;

	return nResult;

} // End of function FileListBoxWindowAddLine

LRESULT FileListBoxWindowControlColor( WPARAM wParam )
{
	LRESULT lr;

	HDC hdc;

	// Get dc
	hdc = ( HDC )wParam;

	// Set text color
	SetTextColor( hdc, FILE_LIST_BOX_WINDOW_TEXT_COLOR );

	// Set background color
	SetBkColor( hdc, FILE_LIST_BOX_WINDOW_BACKGROUND_COLOR );

	// Update return value
	lr = ( LRESULT )CreateSolidBrush( FILE_LIST_BOX_WINDOW_BACKGROUND_COLOR );

	return lr;

} // End of function FileListBoxWindowControlColor

BOOL FileListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, int nLeft, int nTop, int nWidth, int nHeight )
{
	BOOL bResult = FALSE;

	// Create file list box window
	g_hWndFileListBox = ::CreateWindowEx( FILE_LIST_BOX_WINDOW_EXTENDED_STYLE, FILE_LIST_BOX_WINDOW_CLASS_NAME, FILE_LIST_BOX_WINDOW_TEXT, FILE_LIST_BOX_WINDOW_STYLE, nLeft, nTop, nWidth, nHeight, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that file list box window was created
	if( g_hWndFileListBox )
	{
		// Successfully created file list box window

		// Update return value
		bResult = TRUE;

	} // End of successfully created file list box window
	return bResult;

} // End of function FileListBoxWindowCreate

int FileListBoxWindowGetCurrentSelection()
{
	// Get current selection item
	return ::SendMessage( g_hWndFileListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function FileListBoxWindowGetCurrentSelection

int FileListBoxWindowGetItemText( int nWhichItem, LPTSTR lpszItemText )
{
	// Get item text
	return::SendMessage( g_hWndFileListBox, LB_GETTEXT, ( WPARAM )nWhichItem, ( LPARAM )lpszItemText );

} // End of function FileListBoxWindowGetItemText

BOOL FileListBoxWindowGetRect( LPRECT lpRect )
{
	// Get file list box window rect
	return ::GetWindowRect( g_hWndFileListBox, lpRect );

} // End of function FileListBoxWindowGetRect

BOOL FileListBoxWindowHandleCommandMessage( WPARAM wParam, LPARAM, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Select file list box window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_DBLCLK:
		{
			// A file list box window double click notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelectedItemText = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = FileListBoxWindowGetCurrentSelection();

			// Get selected item text
			if( FileListBoxWindowGetItemText( nSelectedItem, lpszSelectedItemText ) )
			{
				// Successfully got selected item text

				// Call double click function
				( *lpDoubleClickFunction )( lpszSelectedItemText );

				// Update return value
				bResult = TRUE;

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelectedItemText;

			// Break out of switch
			break;

		} // End of a file list box window double click notification code
		case LBN_SELCHANGE:
		{
			// A file list box window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelectedItemText = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = FileListBoxWindowGetCurrentSelection();

			// Get selected item text
			if( FileListBoxWindowGetItemText( nSelectedItem, lpszSelectedItemText ) )
			{
				// Successfully got selected item text

				// Call selection changed function
				( *lpSelectionChangedFunction )( lpszSelectedItemText );

				// Update return value
				bResult = TRUE;

			} // End of successfully got selected item text

			// Free string memory
			delete [] lpszSelectedItemText;

			// Break out of switch
			break;

		} // End of a file list box window selection change notification code

	}; // End of selection for file list box window notification code

	return bResult;

} // End of function FileListBoxWindowHandleCommandMessage

BOOL FileListBoxWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move file list box window
	return ::MoveWindow( g_hWndFileListBox, nX, nY, nWidth, nHeight, bRepaint );

} // End of function FileListBoxWindowMove

HWND FileListBoxWindowSetFocus()
{
	// Focus on file list box window
	return ::SetFocus( g_hWndFileListBox );

} // End of function FileListBoxWindowSetFocus

void FileListBoxWindowSetFont( HFONT hFont )
{
	// Set file list box window font
	::SendMessage( g_hWndFileListBox, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function FileListBoxWindowSetFont
