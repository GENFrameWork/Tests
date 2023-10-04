@echo off
call erase_all_windows.bat
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
echo -------------------------------------------------------------
for /f "tokens=1-4 delims=:.," %%a in ("%time%") do (
    set /a "start_time=(((%%a*60+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100)"
)
set "OUTFILE=..\..\..\..\Output.txt"
set "PRINTF=..\..\..\..\..\Utilities\printf\printf"
..\Utilities\printf\printf "Start process ... \n\n"
echo %DATE% %TIME% >> Output.txt
echo -------------------------------------------------------------
echo 32 Bits version
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
call ./../GEN/Batch/compile_windows.bat DevTestsConsole\Platforms\Windows \x32 devtestsconsole
call ./../GEN/Batch/compile_windows.bat DevTestsDevices\Platforms\Windows \x32 devtestsdevices
call ./../GEN/Batch/compile_windows.bat DevTestsCanvas2D\Platforms\Windows \x32 devtestscanvas2d
call ./../GEN/Batch/compile_windows.bat UnitTests\Platforms\Windows \x32 unit                                     
echo -------------------------------------------------------------
echo 64 Bits version
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64 
call ./../GEN/Batch/compile_windows.bat DevTestsConsole\Platforms\Windows \x64 devtestsconsole
call ./../GEN/Batch/compile_windows.bat DevTestsDevices\Platforms\Windows \x64 devtestsdevices
call ./../GEN/Batch/compile_windows.bat DevTestsCanvas2D\Platforms\Windows \x64 devtestscanvas2d
call ./../GEN/Batch/compile_windows.bat UnitTests\Platforms\Windows \x64 unit

for /f "tokens=1-4 delims=:.," %%a in ("%time%") do (
    set /a "end_time=(((%%a*60+1%%b %% 100)*60+1%%c %% 100)*100+1%%d %% 100)"
)

set /a "elapsed_time=end_time - start_time"

set /a "hours=elapsed_time / 360000"
set /a "minutes=(elapsed_time %% 360000) / 6000"
set /a "seconds=(elapsed_time %% 6000) / 100"

..\Utilities\printf\printf "End process.\nProcessing time: %%02d:%%02d:%%02d\n"  %hours% %minutes% %seconds%
pause
