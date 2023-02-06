ECHO OFF
Echo Remove directorys
call ..\GEN\Batch\erase_artifacts DevTestsConsole
call ..\GEN\Batch\erase_artifacts DevTestsDevices
call ..\GEN\Batch\erase_artifacts UnitTests
pause

