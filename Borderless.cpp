// Borderless.cpp

#include "Borderless.h"

BOOL MainWindowMove( HWND hWndMain, int nLeft, int nTop )
{
	BOOL bResult = FALSE;

	int nDesktopWindowWidth;
	int nDesktopWindowHeight;
	int nMaximumLeft;
	int nMaximumTop;
	RECT rcWorkArea;

	// Get work area size
	SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWorkArea, 0 );

	// Calculate desktop window size
	nDesktopWindowWidth		= ( rcWorkArea.right - rcWorkArea.left );
	nDesktopWindowHeight	= ( rcWorkArea.bottom - rcWorkArea.top );

	// Calculate maximum window position
	nMaximumLeft	= ( nDesktopWindowWidth - MAIN_WINDOW_WIDTH );
	nMaximumTop		= ( nDesktopWindowHeight - MAIN_WINDOW_HEIGHT );

	// Limit window position to fit on screen
	nLeft	= ( ( nLeft < 0 ) ? 0 : nLeft );
	nTop	= ( ( nTop < 0 ) ? 0 : nTop );
	nLeft	= ( ( nLeft > nMaximumLeft ) ? nMaximumLeft : nLeft );
	nTop	= ( ( nTop > nMaximumTop ) ? nMaximumTop : nTop );

	// Move window
	bResult = SetWindowPos( hWndMain, NULL, nLeft, nTop, 0, 0, ( SWP_NOSIZE | SWP_NOOWNERZORDER ) );

	// Save window position
	RegistrySetValue( REGISTRY_TOP_LEVEL_KEY, REGISTRY_SUB_KEY, REGISTRY_LEFT_VALUE_NAME, nLeft );
	RegistrySetValue( REGISTRY_TOP_LEVEL_KEY, REGISTRY_SUB_KEY, REGISTRY_TOP_VALUE_NAME, nTop );

	return bResult;

} // End of function MainWindowMove

// Main window procedure
LRESULT CALLBACK MainWndProc( HWND hWndMain, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = 0;

	static int s_nClickX;
	static int s_nClickY;

	// Select message
	switch( uMessage )
	{
		case WM_CREATE:
		{
			// A create message

			// Break out of switch
			break;

		} // End of a create message
		case WM_SIZE:
		{
			// A size message
			int nClientWidth;
			int nClientHeight;

			// Store client width and height
			nClientWidth	= ( int )LOWORD( lParam );
			nClientHeight	= ( int )HIWORD( lParam );

			// Break out of switch
			break;

		} // End of a size message
		case WM_ACTIVATE:
		{
			// An activate message

			// Break out of switch
			break;

		} // End of an activate message
		case WM_GETMINMAXINFO:
		{
			// A get min max info message
			MINMAXINFO FAR *lpMinMaxInfo;

			// Get min max info structure
			lpMinMaxInfo = ( MINMAXINFO FAR * )lParam;

			// Update min max info structure
			lpMinMaxInfo->ptMinTrackSize.x = MAIN_WINDOW_MINIMUM_WIDTH;
			lpMinMaxInfo->ptMinTrackSize.y = MAIN_WINDOW_MINIMUM_HEIGHT;

			// Break out of switch
			break;

		} // End of a get min max info message
		case WM_LBUTTONDOWN:
		{
			// A left mouse button down message

			// Set mouse capture to main window
			SetCapture( hWndMain );

			// Store static variables
			s_nClickX = GET_X_LPARAM( lParam );
			s_nClickY = GET_Y_LPARAM( lParam );

			// Break out of switch
			break;

		} // End of a left mouse button down message
		case WM_LBUTTONUP:
		{
			// A left mouse button up message

			// Release mouse capture
			ReleaseCapture();

			// Break out of switch
			break;

		} // End of a left mouse button up message
		case WM_MOUSEMOVE:
		{
			// A mouse move message

			// See if main window has mouse capture
			if( GetCapture() == hWndMain )
			{
				// Main window has mouse capture
				RECT rc;
				int nMouseX;
				int nMouseY;
				int nWindowX;
				int nWindowY;

				// Get window position
				GetWindowRect( hWndMain, &rc );

				// Store mouse position
				nMouseX = GET_X_LPARAM( lParam );
				nMouseY = GET_Y_LPARAM( lParam );

				// Calculate window position
				nWindowX = ( ( rc.left + nMouseX ) - s_nClickX );
				nWindowY = ( ( rc.top + nMouseY ) - s_nClickY );

				// Move window
				MainWindowMove( hWndMain, nWindowX, nWindowY );

			} // End of main window has mouse capture
			else
			{
				// Main window does not have mouse capture

				// Call default procedure
				lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			} // End of main window does not have mouse capture

			// Break out of switch
			break;

		} // End of a mouse move message
		case WM_DROPFILES:
		{
			// A drop files message
			UINT uFileCount;
			HDROP hDrop;
			UINT uWhichFile;
			UINT uFileSize;

			// Allocate string memory
			LPTSTR lpszFilePath = new char[ STRING_LENGTH ];

			// Get drop handle
			hDrop = ( HDROP )wParam;

			// Count dropped files
			uFileCount = DragQueryFile( hDrop, ( UINT )-1, NULL, 0 );

			// Loop through dropped files
			for( uWhichFile = 0; uWhichFile < uFileCount; uWhichFile ++ )
			{
				// Get size of dropped file
				uFileSize = DragQueryFile( hDrop, uWhichFile, NULL, 0 );

				// Ensure that file size is valid
				if( uFileSize != 0 )
				{
					// File size is valid

					// Get file path
					if( DragQueryFile( hDrop, uWhichFile, lpszFilePath, ( uFileSize + sizeof( char ) ) ) )
					{
						// Successfully got file path

						// Display file path
						MessageBox( hWndMain, lpszFilePath, INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					} // End of successfully got file path

				} // End of file size is valid

			}; // End of loop through dropped files

			// Free string memory
			delete [] lpszFilePath;

			// Break out of switch
			break;

		} // End of a drop files message
		case WM_COMMAND:
		{
			// A command message

			// Select command
			switch( LOWORD( wParam ) )
			{
				default:
				{
					// Default command

					// Source window is ( HWND )lParam

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default command

			}; // End of selection for command

			// Break out of switch
			break;

		} // End of a command message
		case WM_SYSCOMMAND:
		{
			// A system command message

			// Select system command
			switch( LOWORD( wParam ) )
			{
				default:
				{
					// Default system command

					// Call default procedure
					lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

					// Break out of switch
					break;

				} // End of default system command

			}; // End of selection for system command

			// Break out of switch
			break;

		} // End of a system command message
		case WM_NOTIFY:
		{
			// A notify message
			LPNMHDR lpNmHdr;

			// Get notify message handler
			lpNmHdr = ( LPNMHDR )lParam;

			// Source window is lpNmHdr->hwndFrom

			// Call default procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of a notify message
		case WM_CLOSE:
		{
			// A close message

			// Destroy main window
			DestroyWindow( hWndMain );

			// Break out of switch
			break;

		} // End of a close message
		case WM_DESTROY:
		{
			// A destroy message

			// Terminate thread
			PostQuitMessage( 0 );

			// Break out of switch
			break;

		} // End of a destroy message
		default:
		{
			// Default message

			// Call default window procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of default message

	}; // End of selection for message

	return lr;

} // End of function MainWndProc

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow )
{
	MSG msg;

	HWND hWndRunning;

	// Clear message structure
	ZeroMemory( &msg, sizeof( msg ) );

	// Attempt to find running instance of window
	hWndRunning = FindWindow( MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE );

	// See if running instance of window was found
	if( hWndRunning )
	{
		// Successfully found running instance of window

		// Close running instance of window
		SendMessage( hWndRunning, WM_CLOSE, ( WPARAM )NULL, ( LPARAM )NULL );

	} // End of successfully found running instance of window
	else
	{
		// Unable to find running instance of window
		WNDCLASSEX wcMain;

		// Clear main window class structure
		ZeroMemory( &wcMain, sizeof( wcMain ) );

		// Initialise main window class structure
		wcMain.cbSize			= sizeof( WNDCLASSEX );
		wcMain.lpfnWndProc		= MainWndProc;
		wcMain.hInstance		= hInstance;
		wcMain.lpszClassName	= MAIN_WINDOW_CLASS_NAME;
		wcMain.style			= MAIN_WINDOW_CLASS_STYLE;
		wcMain.hIcon			= MAIN_WINDOW_CLASS_ICON;
		wcMain.hCursor			= MAIN_WINDOW_CLASS_CURSOR;
		wcMain.hbrBackground	= MAIN_WINDOW_CLASS_BACKGROUND;
		wcMain.lpszMenuName		= MAIN_WINDOW_CLASS_MENU_NAME;
		wcMain.hIconSm			= MAIN_WINDOW_CLASS_ICON;

		// Register main window class
		if( RegisterClassEx( &wcMain ) )
		{
			// Successfully registered main window class
			HWND hWndMain;

			// Create main window
			hWndMain = CreateWindowEx( MAIN_WINDOW_EXTENDED_STYLE, MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_TITLE, MAIN_WINDOW_STYLE, MAIN_WINDOW_DEFAULT_LEFT, MAIN_WINDOW_DEFAULT_TOP, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, NULL, NULL, hInstance, NULL );

			// Ensure that main window was created
			if( hWndMain )
			{
				// Successfully created main window
				int nLeft;
				int nTop;

				// Get initial window position
				nLeft	= RegistryGetValue( REGISTRY_TOP_LEVEL_KEY, REGISTRY_SUB_KEY, REGISTRY_LEFT_VALUE_NAME, MAIN_WINDOW_DEFAULT_LEFT );
				nTop	= RegistryGetValue( REGISTRY_TOP_LEVEL_KEY, REGISTRY_SUB_KEY, REGISTRY_TOP_VALUE_NAME, MAIN_WINDOW_DEFAULT_TOP );

				// Move window
				MainWindowMove( hWndMain, nLeft, nTop );
				// Note that the move function checks that the left and top values are valid
				// That is why we didn't create the window at this position

				// Show main window
				ShowWindow( hWndMain, nCmdShow );

				// Update main window
				UpdateWindow( hWndMain );

				// Message loop
				while( GetMessage( &msg, NULL, 0, 0 ) > 0 )
				{
					// Translate message
					TranslateMessage( &msg );

					// Dispatch message
					DispatchMessage( &msg );

				}; // End of message loop

			} // End of successfully created main window
			else
			{
				// Unable to create main window

				// Display error message
				MessageBox( NULL, UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

			} // End of unable to create main window

		} // End of successfully registered main window class
		else
		{
			// Unable to register main window class

			// Display error message
			MessageBox( NULL, UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE, ERROR_MESSAGE_CAPTION, ( MB_OK | MB_ICONERROR ) );

		} // End of unable to register main window class

	} // End of unable to find running instance of window

	return msg.wParam;

} // End of function WinMain
