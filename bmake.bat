@echo off

:: bmake PROJECT_ARG ADDITONAL_ARG

set num=0
for %%x in (%*) do Set /A num+=1

if %num%==1 (
    make %1
)

if %num%==2 (

    if "%2"=="clean" (
        make %1_clean
    )

    if "%2"=="run" (
        make %1_run
    )

)