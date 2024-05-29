// Borderless.h

#pragma once

#include <windows.h>
#include <windowsx.h>

#include "Ascii.h"
#include "Common.h"

#include "Registry.h"

#define MAIN_WINDOW_CLASS_NAME													"Main Borderless Window Class"

#define MAIN_WINDOW_CLASS_STYLE													0
#define MAIN_WINDOW_CLASS_ICON													LoadIcon( NULL, IDI_APPLICATION )
#define MAIN_WINDOW_CLASS_CURSOR												LoadCursor( NULL, IDC_ARROW )
#define MAIN_WINDOW_CLASS_BACKGROUND											( HBRUSH )( COLOR_WINDOW + 1 )
#define MAIN_WINDOW_CLASS_MENU_NAME												NULL

#define MAIN_WINDOW_EXTENDED_STYLE												0
#define MAIN_WINDOW_TITLE														"Borderless"
#define MAIN_WINDOW_STYLE														WS_POPUP | WS_BORDER

#define MAIN_WINDOW_DEFAULT_LEFT												100
#define MAIN_WINDOW_DEFAULT_TOP													100
#define MAIN_WINDOW_WIDTH														500
#define MAIN_WINDOW_HEIGHT														400

#define MAIN_WINDOW_MINIMUM_WIDTH												500
#define MAIN_WINDOW_MINIMUM_HEIGHT												400

#define REGISTRY_TOP_LEVEL_KEY													HKEY_CURRENT_USER
#define REGISTRY_SUB_KEY														"SOFTWARE\\Jim Smith\\Borderless"
#define REGISTRY_LEFT_VALUE_NAME												"Left"
#define REGISTRY_TOP_VALUE_NAME													"Top"

#define UNABLE_TO_CREATE_MAIN_WINDOW_ERROR_MESSAGE								"Unable to create main window"
#define UNABLE_TO_REGISTER_MAIN_WINDOW_CLASS_ERROR_MESSAGE						"Unable to register main window class"
