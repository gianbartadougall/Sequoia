@echo off

:: bmake PROJECT_ARG ADDITONAL_ARG
set logFile=logfile.txt
set errFile=errFile.txt

set num=0
set error=0
set verboseFlag=-v
set verbose=0

for %%x in (%*) do (
    Set /A num+=1

    :: Check if any of the arguments passed in is the verbose flag argument
    if "%%x"=="%verboseFlag%" (
        set verbose=1
    )
)

:: Print error if the number of arguments is 3 and the verbose
:: flag is not set
if %num%==3 (
    if not "%verbose%"=="1" (
        echo Third argument invalid
        goto :exit
    )
)

:main

    :: Num args == 0 -> Run Sequoia
    if %num%==0 (
        make > NUL
        goto :exit
    )

    :: Num args == 1 -> Make given project (no args) or Make Seqouia (verbose mode)
    if %num%==1 (
        if "%verbose%"=="1" (
            make
        ) else (
            make %1 > NUL
        )

        goto :exit
    )

    :: Num args == 2 -> Running sub recipe of project (i.e run, clean) or
    :: Make project (verbose mode)
    if %num%==2 (
        if "%verbose%"=="1" (
            make %1
        ) else (
            :: Underscore between args 2 and 3 to call appropriate sub recipe
            make %1_%2 > NUL
        )

        goto :exit
    )

    :: Num args == 3 -> Running sub recipe of project (i.e run, clean) in verbose mode
    if %num%==3 (
        make %1_%2 > NUL
        goto :exit
    )

:exit
    EXIT /b

