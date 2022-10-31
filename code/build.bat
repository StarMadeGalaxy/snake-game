@ECHO OFF

CD..

SET SRC=%cd%

:: Raylib pathways
SET RL_PATH=%SRC%\thirdparty\raylib
SET RL_BIN_PATH=%SRC%\thirdparty\raylib\bin
SET RL_LIB_PATH=%SRC%\thirdparty\raylib\lib
SET RL_INC_PATH=%SRC%\thirdparty\raylib\include  

SET ENTRY_FILE=%SRC%\code\snake_game.c

SET CL_OPTS=-Zi -W3

IF NOT EXIST bulid MKDIR build

PUSHD build

cl %CL_OPTS% %ENTRY_FILE% /I%INC_PATH% /LIBPATH:%RL_LIB_PATH% 

POPD

CD code