@ECHO OFF

CD..

SET SRC=%cd%

:: Raylib pathways
SET RL_PATH=%SRC%\thirdparty\raylib
SET RL_BIN_PATH=%SRC%\thirdparty\raylib\bin
SET RL_LIB_PATH=%SRC%\thirdparty\raylib\lib
SET RL_INC_PATH=%SRC%\thirdparty\raylib\include  

:: set /DRELEASE_MODE to build int the release mode
:: set /DGUI_ENABLED to use GUI (in progress...)
SET BUILD_OPTIONS=/DDEBUG_MODE /DGUI_DISABLED

SET ENTRY_FILE=%SRC%\code\snake_game.c

SET CL_OPTS=/Zi /W3 /nologo /Od

SET COMMON_LINK_FLAGS=/opt:ref user32.lib 

IF NOT EXIST bulid MKDIR build

PUSHD build

:: Compile renderer as .dll
:: cl %CL_OPTS% 

:: Compile and link the game
cl %BUILD_OPTIONS% %CL_OPTS% %ENTRY_FILE% /I%INC_PATH% /LIBPATH:%RL_LIB_PATH% /link %COMMON_LINK_FLAGS%

POPD

CD code