@ECHO OFF

CD..

SET SRC=%cd%

:: Raylib pathways
SET RL_PATH=%SRC%\thirdparty\raylib
SET RL_BIN_PATH=%SRC%\thirdparty\raylib\bin
SET RL_LIB_PATH=%SRC%\thirdparty\raylib\lib
SET RL_INC_PATH=%SRC%\thirdparty\raylib\include  

:: SNAKE_GAME_OPTS instructions
:: set /DRELEASE_MODE to build int the release mode
:: set /DGUI_ENABLED to use GUI (in progress...)
:: set /DSNAKE_DOUBLY_LINKED_LIST to use snake as doubly-linked list
:: set /DSNAKE_SINGLY_LINKED_LIST to use snake as singly-linked list

SET SNAKE_GAME_OPTS=/DRELEASE_MODE /DGUI_DISABLED /DSNAKE_DOUBLY_LINKED_LIST 

SET ENTRY_FILE=%SRC%\code\snake_game_entry.cpp

SET CL_OPTS=/Zi /W3 /nologo /Od /std:c++20

SET COMMON_LINK_FLAGS=/opt:ref user32.lib

IF NOT EXIST bulid MKDIR build

PUSHD build

:: Compile and link the game
cl %SNAKE_GAME_OPTS% %CL_OPTS% %ENTRY_FILE% /I%INC_PATH% /LIBPATH:%RL_LIB_PATH% /link %COMMON_LINK_FLAGS%

del *.ilk
del *.exp
del *.lib
del *.pdb
del *.obj

POPD

CD code
