@ECHO OFF
SETLOCAL

SET DIRECTORIES=server client libs common tests
SET PATTERNS=*.cpp *.hpp

ECHO Running clang-format...

FOR %%D IN (%DIRECTORIES%) DO (
    IF EXIST %%D (
        FOR %%P IN (%PATTERNS%) DO (
            FOR /R %%D %%F IN (%%P) DO (
                clang-format -i "%%F"
            )
        )
    ) ELSE (
        ECHO Warning: Directory %%D does not exist.
    )
)

ECHO Formatting complete.

ENDLOCAL
