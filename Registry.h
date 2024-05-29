// Registry.h

#pragma once

#include <windows.h>
#include <commctrl.h>

DWORD RegistryGetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName, DWORD dwDefaultValue );

BOOL RegistrySetValue( HKEY hKeyTopLevel, LPCTSTR lpszSubKey, LPCTSTR lpszValueName, DWORD dwValue );
