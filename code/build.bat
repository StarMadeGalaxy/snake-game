@echo off

CD..

SET SRC=%cd%

:: Include pathways
SET SDL2_PATH=%SRC%\vendor\SDL\include

SET INC_PATH=%SDL2_PATH%
:: Add new include pathways below
SET INC_PATH=%INC_PATH%

:: Libs pathways (/LIBPATH:%LIB_PATH%)
SET LIB_PATH=

:: SNAKE_GAME_OPTS instructions
:: set /DRELEASE_MODE to build int the release mode
:: set /DGUI_ENABLED to use GUI (in progress...)
:: set /DSNAKE_DOUBLY_LINKED_LIST to use snake as doubly-linked list
:: set /DSNAKE_SINGLY_LINKED_LIST to use snake as singly-linked list

SET SNAKE_GAME_OPTS=/DDEBUG_MODE /DGUI_ENABLED /DSNAKE_DOUBLY_LINKED_LIST 

:: COMPILATION UNITS LIST
SET ENTRY_FILE=%SRC%\code\snake_game_entry.cpp 
SET ENTRY_FILE=%ENTRY_FILE% %SRC%\code\snake_logic.cpp
SET ENTRY_FILE=%ENTRY_FILE% %SRC%\code\snake_map.cpp

:: /fsanitize=address
SET CL_OPTS=/Zi /W4 /nologo /Od /EHsc /std:c++17 /WX 

SET COMMON_LINK_FLAGS=/opt:ref user32.lib

IF NOT EXIST bulid ( MKDIR build ) 

PUSHD build 

:: Compile and link the game
cl %ENTRY_FILE% %SNAKE_GAME_OPTS% %CL_OPTS% /I%INC_PATH% /link %COMMON_LINK_FLAGS%

@REM del *.ilk
@REM del *.exp
@REM del *.lib
@REM del *.pdb
@REM del *.obj

POPD

CD code
