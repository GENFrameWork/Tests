#!/bin/sh
echo -------------------------------------------------------------
START_TIME=$(date +%s)
OUTFILE="../../../../Output.txt"
export OUTFILE
printf "Start process ... \n\n"
date >> Output.txt
printf "Test Linux PC x64 ... \n\n"

sh ../GEN/Batch/compile_linux.sh DevTestsConsole/Platforms/Linux /x64 devtestconsole
sh ../GEN/Batch/compile_linux.sh DevTestsDevices/Platforms/Linux /x64 devtestsdevices
sh ../GEN/Batch/compile_linux.sh UnitTests/Platforms/Linux /x64 unit

END_TIME=$(date +%s)
ELAPSED_TIME=$((END_TIME - START_TIME))
HOURS=$((ELAPSED_TIME / 3600))
MINUTES=$(((ELAPSED_TIME % 3600) / 60 ))
SECONDS=$((ELAPSED_TIME % 60))

printf "End process.\nProcessing time: %02d:%02d:%02d\n" "$HOURS" "$MINUTES" "$SECONDS"

