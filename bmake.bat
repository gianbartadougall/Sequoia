@echo off

:: bmake PROJECT_ARG ADDITONAL_ARG
set logFile=logfile.txt

set num=0
set error=0
for %%x in (%*) do Set /A num+=1

:: If no arguments are passed, compile all
if %num%==0 (
    make all > %logfile% 2>&1
    set error=%ERRORLEVEL%
)

if %num%==1 (
    make %1 > %logfile% 2>&1
    set error=%ERRORLEVEL%
)

if %num%==2 (

    if "%2"=="clean" (
        make %1_clean > %logFile% 2>&1 
        set error=%ERRORLEVEL%

        goto :end
    )

    if "%2"=="run" (
        make %1_run 2> %logFile%
        set error=%ERRORLEVEL%

        goto :end
    )
        
    echo That input was invalid
)

:end

if not %error%==0 (
    type %logFile%
)

:: Delete the log file if it exists
del /f %logFile% > NUL 2>&1

:exit
    EXIT /b