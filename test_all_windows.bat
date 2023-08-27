echo off
call erase_all_windows.bat
pause
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
set "OUTFILE=..\..\..\..\Output.txt"
set "PRINTF=..\..\..\..\..\Utilities\printf\printf"
echo -------------------------------------------------------------
echo 32 Bits version
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
call ./../GEN/Batch/compile_windows.bat DevTestsConsole\Platforms\Windows \x32 devtestsconsole
call ./../GEN/Batch/compile_windows.bat DevTestsDevices\Platforms\Windows \x32 devtestsdevices
call ./../GEN/Batch/compile_windows.bat UnitTests\Platforms\Windows \x32 unit                                     
echo -------------------------------------------------------------
echo 64 Bits version
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64 
call ./../GEN/Batch/compile_windows.bat DevTestsConsole\Platforms\Windows \x64 devtestsconsole
call ./../GEN/Batch/compile_windows.bat DevTestsDevices\Platforms\Windows \x64 devtestsdevices
call ./../GEN/Batch/compile_windows.bat UnitTests\Platforms\Windows \x64 unit
pause