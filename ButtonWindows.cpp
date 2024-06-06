// ButtonWindows.cpp

#include "ButtonWindows.h"

// Global variables
static HWND g_hWndButton[ BUTTON_WINDOWS_NUMBER_OF_BUTTONS ];

BOOL ButtonWindowsCreate( HWND hWndParent, HINSTANCE hInstance, HFONT hFont, int nTop, int nSeparatorSize )
{
	BOOL bResult = TRUE; // Assume success

	int nWhichButton;
	int nLeft = nSeparatorSize;
	LPCTSTR lpszTitles [] = BUTTON_WINDOWS_TITLES;

	// Loop through buttons
	for( nWhichButton = 0; nWhichButton < BUTTON_WINDOWS_NUMBER_OF_BUTTONS; nWhichButton ++ )
	{
		// Create button window
		g_hWndButton[ nWhichButton ] = CreateWindowEx( BUTTON_WINDOWS_EXTENDED_STYLE, BUTTON_WINDOWS_CLASS_NAME, lpszTitles[ nWhichButton ], BUTTON_WINDOWS_STYLE, nLeft, nTop, BUTTON_WINDOWS_BUTTON_WIDTH, BUTTON_WINDOWS_BUTTON_HEIGHT, hWndParent, ( HMENU )INT_PTR( nWhichButton + BUTTON_WINDOWS_FIRST_BUTTON_ID ), hInstance, NULL );

		// Ensure that button window was created
		if( g_hWndButton[ nWhichButton ] )
		{
			// Successfully created button window

			// Set button window font
			SendMessage( g_hWndButton[ nWhichButton ], WM_SETFONT, ( WPARAM )hFont, ( LPARAM )TRUE );

			// Update button window position for next button
			nLeft += ( BUTTON_WINDOWS_BUTTON_WIDTH + nSeparatorSize );

		} // End of successfully created button window
		else
		{
			// Unable to create button window

			// Update return value
			bResult = FALSE;

			// Force exit from loop
			nWhichButton = BUTTON_WINDOWS_NUMBER_OF_BUTTONS;

		} // End of unable to create button window

	} // End of loop through buttons

	return bResult;

} // End of function ButtonWindowsCreate
