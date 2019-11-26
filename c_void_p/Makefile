# Copyright (C) 2012 NET GmbH
# Licensed under the GNU GPL.

test: test.c 
	$(CXX) $(CXXFLAGS) -std=c++11 '-fPIC' --shared -o test.so test.c
	
	
clean:
	rm -f NETUSBtest 
	rm -f test.so 
.PHONY: clean

