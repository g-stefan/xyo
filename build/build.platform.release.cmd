@echo off
rem Public domain
rem http://unlicense.org/
rem Created by Grigore Stefan <g_stefan@yahoo.com>

echo -^> platform release xyo

goto cmdXDefined
:cmdX
%*
if errorlevel 1 goto cmdXError
goto :eof
:cmdXError
echo "Error: release"
exit 1
:cmdXDefined

call :cmdX cmd.exe /C "build\build.msvc64.cmd clean"
call :cmdX cmd.exe /C "build\build.msvc64.cmd release"
call :cmdX cmd.exe /C "build\build.msvc64.cmd clean"

call :cmdX cmd.exe /C "build\build.msvc32.cmd clean"
call :cmdX cmd.exe /C "build\build.msvc32.cmd release"
call :cmdX cmd.exe /C "build\build.msvc32.cmd clean"

call :cmdX cmd.exe /C "build\build.mingw64.cmd clean"
call :cmdX cmd.exe /C "build\build.mingw64.cmd release"
call :cmdX cmd.exe /C "build\build.mingw64.cmd clean"

call :cmdX cmd.exe /C "build\build.mingw32.cmd clean"
call :cmdX cmd.exe /C "build\build.mingw32.cmd release"
call :cmdX cmd.exe /C "build\build.mingw32.cmd clean"

call :cmdX cmd.exe /C "build\build.wsl-ubuntu-20.04.cmd clean"
call :cmdX cmd.exe /C "build\build.wsl-ubuntu-20.04.cmd release"
call :cmdX cmd.exe /C "build\build.wsl-ubuntu-20.04.cmd clean"

call :cmdX cmd.exe /C "build\build.wsl-ubuntu-18.04.cmd clean"
call :cmdX cmd.exe /C "build\build.wsl-ubuntu-18.04.cmd release"
call :cmdX cmd.exe /C "build\build.wsl-ubuntu-18.04.cmd clean"
