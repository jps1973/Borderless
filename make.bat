cls

del *.exe

g++ -mwindows -m64 -static -Wall -Wextra Borderless.cpp Registry.cpp -o Borderless.exe
