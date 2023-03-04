@ECHO OFF

SET SDL_DLL=..\vendor\SDL2\bin\SDL2.dll

PUSHD ..\build

IF NOT EXIST %SDL_DLL% ( XCOPY %SDL_DLL% . )

start snake_game_entry.exe

POPD

