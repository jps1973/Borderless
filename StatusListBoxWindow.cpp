// StatusListBoxWindow.cpp

#include "StatusListBoxWindow.h"

// Global variables
static HWND g_hWndStatusListBox;

BOOL IsStatusListBoxWindow( HWND hWnd )
{
	// See if supplied window is status list box window
	return( hWnd == g_hWndStatusListBox );

} // End of function IsStatusListBoxWindow

int StatusListBoxWindowAddLine( LPCTSTR lpszLine )
{
	// Add line to status list box window
	return ::SendMessage( g_hWndStatusListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszLine );

} // End of function StatusListBoxWindowAddLine

int StatusListBoxWindowAddText( LPCTSTR lpszText )
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

			// Add line to status list box window
			if( ::SendMessage( g_hWndStatusListBox, LB_ADDSTRING, ( WPARAM )NULL, ( LPARAM )lpszLine ) >= 0 )
			{
				// Successfully added line to status list box window

				// Get next line
				lpszLine = strtok( NULL, NEW_LINE_TEXT );

				// Update return value
				nResult ++;

			} // End of successfully added line to status list box window
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

} // End of function StatusListBoxWindowAddLine

LRESULT StatusListBoxWindowControlColor( WPARAM wParam )
{
	LRESULT lr;

	HDC hdc;

	// Get dc
	hdc = ( HDC )wParam;

	// Set text color
	SetTextColor( hdc, STATUS_LIST_BOX_WINDOW_TEXT_COLOR );

	// Set background color
	SetBkColor( hdc, STATUS_LIST_BOX_WINDOW_BACKGROUND_COLOR );

	// Update return value
	lr = ( LRESULT )CreateSolidBrush( STATUS_LIST_BOX_WINDOW_BACKGROUND_COLOR );

	return lr;

} // End of function StatusListBoxWindowControlColor

BOOL StatusListBoxWindowCreate( HWND hWndParent, HINSTANCE hInstance, int nLeft, int nTop, int nWidth, int nHeight )
{
	BOOL bResult = FALSE;

	// Create status list box window
	g_hWndStatusListBox = ::CreateWindowEx( STATUS_LIST_BOX_WINDOW_EXTENDED_STYLE, STATUS_LIST_BOX_WINDOW_CLASS_NAME, STATUS_LIST_BOX_WINDOW_TEXT, STATUS_LIST_BOX_WINDOW_STYLE, nLeft, nTop, nWidth, nHeight, hWndParent, ( HMENU )NULL, hInstance, NULL );

	// Ensure that status list box window was created
	if( g_hWndStatusListBox )
	{
		// Successfully created status list box window

		// Update return value
		bResult = TRUE;

	} // End of successfully created status list box window
	return bResult;

} // End of function StatusListBoxWindowCreate

int StatusListBoxWindowGetCurrentSelection()
{
	// Get current selection item
	return ::SendMessage( g_hWndStatusListBox, LB_GETCURSEL, ( WPARAM )NULL, ( LPARAM )NULL );

} // End of function StatusListBoxWindowGetCurrentSelection

int StatusListBoxWindowGetItemText( int nWhichItem, LPTSTR lpszItemText )
{
	// Get item text
	return::SendMessage( g_hWndStatusListBox, LB_GETTEXT, ( WPARAM )nWhichItem, ( LPARAM )lpszItemText );

} // End of function StatusListBoxWindowGetItemText

BOOL StatusListBoxWindowGetRect( LPRECT lpRect )
{
	// Get status list box window rect
	return ::GetWindowRect( g_hWndStatusListBox, lpRect );

} // End of function StatusListBoxWindowGetRect

BOOL StatusListBoxWindowHandleCommandMessage( WPARAM wParam, LPARAM, void( *lpDoubleClickFunction )( LPCTSTR lpszItemText ), void( *lpSelectionChangedFunction )( LPCTSTR lpszItemText ) )
{
	BOOL bResult = FALSE;

	// Select status list box window notification code
	switch( HIWORD( wParam ) )
	{
		case LBN_DBLCLK:
		{
			// A status list box window double click notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelectedItemText = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = StatusListBoxWindowGetCurrentSelection();

			// Get selected item text
			if( StatusListBoxWindowGetItemText( nSelectedItem, lpszSelectedItemText ) )
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

		} // End of a status list box window double click notification code
		case LBN_SELCHANGE:
		{
			// A status list box window selection change notification code
			int nSelectedItem;

			// Allocate string memory
			LPTSTR lpszSelectedItemText = new char[ STRING_LENGTH ];

			// Get selected item
			nSelectedItem = StatusListBoxWindowGetCurrentSelection();

			// Get selected item text
			if( StatusListBoxWindowGetItemText( nSelectedItem, lpszSelectedItemText ) )
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

		} // End of a status list box window selection change notification code

	}; // End of selection for status list box window notification code

	return bResult;

} // End of function StatusListBoxWindowHandleCommandMessage

BOOL StatusListBoxWindowMove( int nX, int nY, int nWidth, int nHeight, BOOL bRepaint )
{
	// Move status list box window
	return ::MoveWindow( g_hWndStatusListBox, nX, nY, nWidth, nHeight, bRepaint );

} // End of function StatusListBoxWindowMove

HWND StatusListBoxWindowSetFocus()
{
	// Focus on status list box window
	return ::SetFocus( g_hWndStatusListBox );

} // End of function StatusListBoxWindowSetFocus

void StatusListBoxWindowSetFont( HFONT hFont )
{
	// Set status list box window font
	::SendMessage( g_hWndStatusListBox, WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

} // End of function StatusListBoxWindowSetFont
