@echo off

SET SRC=%cd%

SET SDL_DLL=%SRC%\bin\SDL2.dll

IF NOT EXIST lib ( MKDIR lib ) 

PUSHD lib

dumpbin /EXPORTS %SDL_DLL% > SDL2.def

python ../get_def.py

lib /def:SDL2.def /out:SDL2.lib /machine:x64

del SDL2.def
del SDL2.exp

POPD







