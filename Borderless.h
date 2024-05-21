// Borderless.h

#pragma once

#include <windows.h>

#define MAIN_WINDOW_CLASS_NAME													"Main Borderless Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, IDI_APPLICATION )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_NAME												NULL

#define MAIN_WINDOW_EXTENDED_STYLE												0
#define MAIN_WINDOW_TITLE														"Borderless"
#define MAIN_WINDOW_STYLE														WS_POPUP

#define MAIN_WINDOW_MINIMUM_WIDTH												500
#define MAIN_WINDOW_MINIMUM_HEIGHT												400

#define STRING_LENGTH															2048

#define ABOUT_MESSAGE_CAPTION													"About"
#define INFORMATION_MESSAGE_CAPTION												"Information"
#define ERROR_MESSAGE_CAPTION													"Error"
#define WARNING_MESSAGE_CAPTION													"Warning"

#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to create main window"
#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to register main window class"
