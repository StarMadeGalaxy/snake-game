@ECHO OFF

CD.. 

SET SRC=%cd%

SET RL_DLL_PATH=%SRC%\thirdparty\raylib\bin

:: Recently I came up with this solution.
:: Is there any way to specify dll's locations to the executable?
PATH=%RL_DLL_PATH%;%PATH%

PUSHD build

START snake_game.exe

POPD

CD code