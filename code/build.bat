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
:: set /DSNAKE_DOUBLY_LINKED_LIST to use snake as doubly-linked list
:: set /DSNAKE_SINGLY_LINKED_LIST to use snake as singly-linked list

SET BUILD_OPTIONS=/DRELEASE_MODE /DGUI_DISABLED /DSNAKE_DOUBLY_LINKED_LIST 

SET ENTRY_FILE=%SRC%\code\snake_game.c
SET CON_REND_FILE=%SRC%\code\snake_renderer_console.c

SET CL_OPTS=/Zi /W3 /nologo /Od

SET COMMON_LINK_FLAGS=/opt:ref user32.lib snake_renderer_console.lib

IF NOT EXIST bulid MKDIR build

PUSHD build

:: Compiler console renderer as a dll
cl %CL_OPTS% /LD /Fesnake_renderer_console.dll %CON_REND_FILE% user32.lib

:: Compile and link the game
cl %BUILD_OPTIONS% %CL_OPTS% %ENTRY_FILE% /I%INC_PATH% /LIBPATH:%RL_LIB_PATH% /link %COMMON_LINK_FLAGS%

POPD

CD code