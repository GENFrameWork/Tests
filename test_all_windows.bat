echo off 
call erase_all_artifacts
set vctype=%1
if "%vctype%"=="" (set vctype=Enterprise)
echo -------------------------------------------------------------
echo 32 Bits version
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64_x86
call ..\GEN\Batch\compile_windows UnitTests\Platforms\Windows\x86 
echo -------------------------------------------------------------
echo 64 Bits version
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\%vctype%\VC\Auxiliary\Build\vcvarsall.bat" amd64 
call ..\GEN\Batch\compile_windows UnitTests\Platforms\Windows\x64
call test_windows
