# Copyright (C) 2012 NET GmbH
# Licensed under the GNU GPL.

dll: dll.c 
	$(CXX) $(CXXFLAGS) '-fPIC' --shared -o dll.so dll.c
	
	
clean:
	rm -f NETUSBtest 
	rm -f test.so 
.PHONY: clean

