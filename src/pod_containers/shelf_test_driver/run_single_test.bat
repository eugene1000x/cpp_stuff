
set testSuite=%~1
set testNo=%~2

copy "./test_suites/%testSuite%/shelf%testNo%.dat" "./workdir/shelf.dat"
cd "./workdir"
./shelf_test_driver.exe
cd "../"
fc.exe "./workdir/shelf.rez" "./test_suites/%testSuite%/shelf%testNo%.rez"
copy "./workdir/shelf.rez" "./log/shelf%testNo%.rez"
