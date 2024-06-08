cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Borderless.cpp ButtonWindows.cpp FileListBoxWindow.cpp Registry.cpp StatusListBoxWindow.cpp -o Borderless.exe
