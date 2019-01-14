
set testNo1=%~1
set testNo2=%~2
set testNo3=%~3
set testSuite=%~4

echo off
for /L %%i in (%testNo1%, %testNo2%, %testNo3%) do
(
	call ./run_single_test.bat "%testSuite%" "%%i"
)
