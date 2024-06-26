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

int ShowAboutMessage( HWND hWndParent )
{
	int nResult = 0;

	MSGBOXPARAMS mbp;

	// Clear message box parameter structure
	ZeroMemory( &mbp, sizeof( mbp ) );

	// Initialise message box parameter structure
	mbp.cbSize		= sizeof( MSGBOXPARAMS );
	mbp.hwndOwner	= hWndParent;
	mbp.hInstance	= NULL;
	mbp.lpszText	= ABOUT_MESSAGE_TEXT;
	mbp.lpszCaption	= ABOUT_MESSAGE_CAPTION;
	mbp.dwStyle		= ( MB_OK | MB_USERICON );
	mbp.lpszIcon	= MAIN_WINDOW_CLASS_ICON_NAME;

	// Show message box
	nResult = MessageBoxIndirect( &mbp );

	return nResult;

} // End of function ShowAboutMessage

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
			HINSTANCE hInstance;
			int nStatusListBoxWindowLeft;
			int nStatusListBoxWindowTop;
			int nStatusListBoxWindowWidth;
			int nStatusListBoxWindowHeight;

			// Get instance
			hInstance = ( ( LPCREATESTRUCT )lParam )->hInstance;

			// Calculate status list box window size
			nStatusListBoxWindowWidth	= ( MAIN_WINDOW_WIDTH - ( MAIN_WINDOW_SEPARATOR_SIZE + MAIN_WINDOW_SEPARATOR_SIZE ) );
			nStatusListBoxWindowHeight	= STATUS_LIST_BOX_WINDOW_HEIGHT;

			// Calculate status list box window position
			nStatusListBoxWindowLeft	= MAIN_WINDOW_SEPARATOR_SIZE;
			nStatusListBoxWindowTop		= ( MAIN_WINDOW_HEIGHT - ( nStatusListBoxWindowHeight + MAIN_WINDOW_SEPARATOR_SIZE + BUTTON_WINDOWS_BUTTON_HEIGHT + MAIN_WINDOW_SEPARATOR_SIZE ) );

			// Create status list box window
			if( StatusListBoxWindowCreate( hWndMain, hInstance, nStatusListBoxWindowLeft, nStatusListBoxWindowTop, nStatusListBoxWindowWidth, nStatusListBoxWindowHeight ) )
			{
				// Successfully created status list box window
				HFONT hFont;
				int nFileListBoxWindowLeft;
				int nFileListBoxWindowTop;
				int nFileListBoxWindowWidth;
				int nFileListBoxWindowHeight;

				// Get font
				hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

				// Set status list box window font
				StatusListBoxWindowSetFont( hFont );

				// Calculate file list box window size
				nFileListBoxWindowWidth		= ( MAIN_WINDOW_WIDTH - ( MAIN_WINDOW_SEPARATOR_SIZE + MAIN_WINDOW_SEPARATOR_SIZE ) );
				nFileListBoxWindowHeight	= ( MAIN_WINDOW_HEIGHT - ( MAIN_WINDOW_SEPARATOR_SIZE + MAIN_WINDOW_SEPARATOR_SIZE + STATUS_LIST_BOX_WINDOW_HEIGHT + MAIN_WINDOW_SEPARATOR_SIZE + BUTTON_WINDOWS_BUTTON_HEIGHT + MAIN_WINDOW_SEPARATOR_SIZE ) );

				// Calculate file list box window position
				nFileListBoxWindowLeft	= MAIN_WINDOW_SEPARATOR_SIZE;
				nFileListBoxWindowTop	= MAIN_WINDOW_SEPARATOR_SIZE;

				// Create file list box window
				if( FileListBoxWindowCreate( hWndMain, hInstance, nFileListBoxWindowLeft, nFileListBoxWindowTop, nFileListBoxWindowWidth, nFileListBoxWindowHeight ) )
				{
					// Successfully created status list box window
					// Set file list box window font
					FileListBoxWindowSetFont( hFont );

				} // End of successfully created file list box window

			} // End of successfully created status list box window

			// Break out of switch
			break;

		} // End of a create message
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
				case( BUTTON_WINDOWS_BROWSE_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The browse button has been pressed

					// Display message
					MessageBox( hWndMain, "The browse button has been pressed", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of the browse button has been pressed
				case( BUTTON_WINDOWS_FILTER_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The filter button has been pressed

					// Display message
					MessageBox( hWndMain, "The filter button has been pressed", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of the filter button has been pressed
				case( BUTTON_WINDOWS_COPY_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The copy button has been pressed

					// Display message
					MessageBox( hWndMain, "The copy button has been pressed", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of the copy button has been pressed
				case( BUTTON_WINDOWS_MOVE_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The move button has been pressed

					// Display message
					MessageBox( hWndMain, "The move button has been pressed", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of the move button has been pressed
				case( BUTTON_WINDOWS_RENAME_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The rename button has been pressed

					// Display message
					MessageBox( hWndMain, "The rename button has been pressed", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of the rename button has been pressed
				case( BUTTON_WINDOWS_DELETE_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The delete button has been pressed

					// Display message
					MessageBox( hWndMain, "The delete button has been pressed", INFORMATION_MESSAGE_CAPTION, ( MB_OK | MB_ICONINFORMATION ) );

					// Break out of switch
					break;

				} // End of the delete button has been pressed
				case( BUTTON_WINDOWS_ABOUT_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The about button has been pressed

					// Show about message
					ShowAboutMessage( hWndMain );

					// Break out of switch
					break;

				} // End of the about button has been pressed
				case( BUTTON_WINDOWS_EXIT_BUTTON + BUTTON_WINDOWS_FIRST_BUTTON_ID ):
				{
					// The exit button has been pressed

					// Destroy window
					DestroyWindow( hWndMain );

					// Break out of switch
					break;

				} // End of the exit button has been pressed
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
			//LPNMHDR lpNmHdr;

			// Get notify message handler
			//lpNmHdr = ( LPNMHDR )lParam;

			// Source window is lpNmHdr->hwndFrom

			// Call default procedure
			lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			// Break out of switch
			break;

		} // End of a notify message
		case WM_CTLCOLORLISTBOX:
		{
			// A control color list box message

			// See if message is from status list box window
			if( IsStatusListBoxWindow( ( HWND )lParam ) )
			{
				// Message is from status list box window

				// Control color of status list box window
				lr = StatusListBoxWindowControlColor( wParam );

			} // End of message is from status list box window
			else
			{
				// Message is not from status list box window

				// Call default window procedure
				lr = DefWindowProc( hWndMain, uMessage, wParam, lParam );

			} // End of message is not from status list box window

			// Break out of switch
			break;

		} // End of a control color list box message
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

		// Bring running instance of window to top
		BringWindowToTop( hWndRunning );

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
				int nButtonWindowTop;
				HFONT hFont;

				// Get initial window position
				nLeft	= RegistryGetValue( REGISTRY_TOP_LEVEL_KEY, REGISTRY_SUB_KEY, REGISTRY_LEFT_VALUE_NAME, MAIN_WINDOW_DEFAULT_LEFT );
				nTop	= RegistryGetValue( REGISTRY_TOP_LEVEL_KEY, REGISTRY_SUB_KEY, REGISTRY_TOP_VALUE_NAME, MAIN_WINDOW_DEFAULT_TOP );

				// Move window
				MainWindowMove( hWndMain, nLeft, nTop );
				// Note that the move function checks that the left and top values are valid
				// That is why we didn't create the window at this position

				// Get font
				hFont = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

				// Calculate button window position
				nButtonWindowTop = ( MAIN_WINDOW_HEIGHT - ( MAIN_WINDOW_SEPARATOR_SIZE + BUTTON_WINDOWS_BUTTON_HEIGHT ) );

				// Create button windows
				ButtonWindowsCreate( hWndMain, hInstance, hFont, nButtonWindowTop, MAIN_WINDOW_SEPARATOR_SIZE );

				// Add about text to status list box window
				StatusListBoxWindowAddText( ABOUT_MESSAGE_TEXT );

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
