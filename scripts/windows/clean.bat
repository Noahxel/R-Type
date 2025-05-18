@ECHO OFF
SETLOCAL

REM Change to the script's directory
CD /D "%~dp0\..\.."

ECHO Cleaning up...

IF EXIST build (
    RMDIR /S /Q build
    ECHO Removed build directory.
)

IF EXIST r-type_client.exe (
    DEL /F /Q r-type_client.exe
    ECHO Removed r-type_client executable.
)

IF EXIST r-type_server.exe (
    DEL /F /Q r-type_server.exe
    ECHO Removed r-type_server executable.
)

ECHO Clean completed.

ENDLOCAL
