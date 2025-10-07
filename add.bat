@echo off
cmake -DCLASS_NAME=%1 -DCLASS_PATH=%2 -DFLAG=%3 -P scripts/add.cmake