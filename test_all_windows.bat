echo off 
call erase_all_artifacts
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
echo -------------------------------------------------------------
echo 32 Bits version
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
call ..\GEN\Batch\compile_windows DevTestsConsole\Platforms\Windows\x86
call ..\GEN\Batch\compile_windows DevTestsDevices\Platforms\Windows\x86
call ..\GEN\Batch\compile_windows UnitTests\Platforms\Windows\x86 
echo -------------------------------------------------------------
echo 64 Bits version
call "C:\Program Files\Microsoft Visual Studio\2022\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64 
call ..\GEN\Batch\compile_windows DevTestsConsole\Platforms\Windows\x64
call ..\GEN\Batch\compile_windows DevTestsDevices\Platforms\Windows\x64
call ..\GEN\Batch\compile_windows UnitTests\Platforms\Windows\x64
call test_windows
