echo "Running unit tests:"

for i in tests/*_tests
do
	if test -f $i
	then
		if $VALGRIND ./$i 2>> tests/list_tests.log
		then
			echo $i PASS
		else
			echo "ERROR in test $i: here's tests/list_tests.log"
			echo "------"
			tail tests/list_tests.log
			exit 1
		fi
	fi
done

echo ""

