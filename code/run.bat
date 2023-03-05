@ECHO OFF

SET SRC=%CD%
SET SDL_DLL=..\vendor\SDL2\bin\SDL2.dll

PUSHD ..\build

IF NOT EXIST SDL2.dll ( XCOPY %SDL_DLL% %CD% )

start snake_game_entry.exe

POPD

