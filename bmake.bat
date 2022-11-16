@echo off

:: bmake PROJECT_ARG ADDITONAL_ARG
set logFile=logfile.txt

set num=0
for %%x in (%*) do Set /A num+=1

if %num%==1 (
    make %1 > %logfile% 2>&1
    :: Check error code
    if not %ERRORLEVEL%==0 (
        type %logFile%
    )
)

if %num%==2 (

    if "%2"=="clean" (
        make %1_clean > %logFile% 2>&1 

        :: Check error code
        if not %ERRORLEVEL%==0 (
            type %logFile%
        )

        call :EXIT
    )

    if "%2"=="run" (
        make %1_run > %logFile%
        make %1_clean > %logFile% 2>&1 

        :: Check error code
        if not %ERRORLEVEL%==0 (
            type %logFile%
        )
        call :EXIT
    )
        
    echo That input was invalid
    del /f %logFile% > NUL 2>&1
)


:EXIT
    EXIT /b