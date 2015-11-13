prefix=/usr/local
includedir=$(prefix)/include

check: test

test_03: string_view.hpp string_view_test.cpp
	$(CXX) -std=c++03 -Wall string_view_test.cpp -o $@
	./$@

test_11: string_view.hpp string_view_test.cpp
	$(CXX) -std=c++11 -Wall string_view_test.cpp -o $@
	./$@

test_14: string_view.hpp string_view_test.cpp
	$(CXX) -std=c++14 -Wall string_view_test.cpp -o $@
	./$@

test: test_03 test_11 test_14

clean:
	rm -f test_03
	rm -f test_11
	rm -f test_14


.PHONY: test check clean
