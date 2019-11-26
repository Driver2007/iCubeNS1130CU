# -*- coding: utf-8 -*-
"""
Created on Wed Nov 13 23:56:14 2019

@author: sergey
"""
import time
from ctypes import *
so_file = '/home/sergey/Git/iCubeNS1130CU/test.so'
camera = CDLL(so_file)
i=0
print camera
i=camera.main()
time.sleep(0.1)
camera._Z4namei(i)
camera.close(i)
print "over"

