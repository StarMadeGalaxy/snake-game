@echo off

CD..

SET SRC=%cd%

SET SDL2_INC_PATH=%SRC%\vendor\SDL2\include
SET SDL2_LIB_PATH=%SRC%\vendor\SDL2\lib\SDL2.lib

:: Include pathways
SET INC_PATH=%SDL2_INC_PATH%

:: Libs pathways
SET LIB_PATH=%SRC%\vendor\SDL2\lib

:: SNAKE_GAME_OPTS instructions
:: set /DRELEASE_MODE to build int the release mode
:: set /DGUI_ENABLED to use GUI (in progress...)
:: set /DSNAKE_DOUBLY_LINKED_LIST to use snake as doubly-linked list
:: set /DSNAKE_SINGLY_LINKED_LIST to use snake as singly-linked list

SET SNAKE_GAME_OPTS=/DDEBUG_MODE /DGUI_ENABLED /DSNAKE_SINGLY_LINKED_LIST 

:: COMPILATION UNITS LIST
SET ENTRY_FILE=%SRC%\code\snake_game_entry.cpp 
SET ENTRY_FILE=%ENTRY_FILE% %SRC%\code\snake_logic.cpp
SET ENTRY_FILE=%ENTRY_FILE% %SRC%\code\snake_map.cpp

IF NOT EXIST %SDL2_LIB_PATH% ( ..\vendor\SDL2\get_lib64 ) 

:: /fsanitize=address
SET CL_OPTS=/Zi /W4 /nologo /Od /EHsc /std:c++17 /WX  

SET COMMON_LINK_FLAGS=/opt:ref user32.lib %SDL2_LIB_PATH%

IF NOT EXIST build ( MKDIR build ) 

PUSHD build 

:: Compile and link the game
cl %ENTRY_FILE% %SNAKE_GAME_OPTS% %CL_OPTS% /I%INC_PATH% /link %COMMON_LINK_FLAGS% /LIBPATH:%LIB_PATH%

@REM del *.ilk
@REM del *.exp
@REM del *.lib
@REM del *.pdb
@REM del *.obj

POPD

CD code
