@echo off

pushd ..\build

PATH = P:\C\snake_game\thirdparty\raylib\bin;%PATH%

start snake_game.exe

popd;