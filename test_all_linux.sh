#!/bin/sh
echo -------------------------------------------------------------
echo 64 Bits version
sh ./../GEN/Batch/compile_linux.sh UnitTests/Platforms/Linux /x64
sh ./test_linux.sh

