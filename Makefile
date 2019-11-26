# Copyright (C) 2012 NET GmbH
# Licensed under the GNU GPL.

NETUSBtest: NETUSBtest.c 
	$(CXX) $(CXXFLAGS) -o NETUSBtest NETUSBtest.c  -lNETUSBCAM
	$(CXX) $(CXXFLAGS) '-fPIC' --shared -o test.so NETUSBtest.c -lNETUSBCAM
	
	
clean:
	rm -f NETUSBtest 
	rm -f test.so 
.PHONY: clean

