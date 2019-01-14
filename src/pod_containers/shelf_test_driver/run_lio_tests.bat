
set testNo1=0
set testNo2=1
set testNo3=25
set testSuite=lio_tests

call ./run_tests.bat "%testNo1%" "%testNo2%" "%testNo3%" "%testSuite%" > ./log/log.txt
