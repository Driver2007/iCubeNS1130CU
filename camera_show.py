"""
Simply display the contents of the webcam with optional mirroring using OpenCV 
via the new Pythonic cv2 interface.  Press <esc> to quit.
"""

import cv2
import sys
import PyTango
from PIL import Image, ImageChops
import time
from ctypes import *
from binascii import hexlify

buffSize = {
    0:230400,
    1:921600,
    2:1082880,
    3:1440000,
    4:2359296,
    5:3932160,
    6:5760000,
    7:9437184,
    8:15116544,
    9:31656960
}

camera=PyTango.DeviceProxy("icube/camera/image")
def show_webcam2(mirror=False):
    while True:
        if camera.State() == PyTango.DevState.ON:
            if camera.read_attribute("start_stop_streaming").value==True:
                mode=camera.read_attribute("Mode").value
                x,y=camera.read_attribute("Resolution").value.split("x")
                imgSize=[int(x),int(y)]
                print (imgSize)
                image_pointer=hex(camera.read_attribute("image_pointer").value)
                print("image_pointer",image_pointer)
                print (sys.getsizeof(image_pointer))
                print(hexlify(string_at(id(image_pointer), buffSize[mode])))
                #(ctypes.c_char * buffSize[mode])
                #image_buffer = (c_char * buffSize[mode]).from_address(image_pointer)
                #print (type(image_buffer)),image_buffer
                #img = Image.frombytes('I', buffSize[mode], image_buffer.raw, 'raw')#
                #cv2.imshow('my webcam', img)
                #if cv2.waitKey(1) == 27: 
                #    break  # esc to quit
        time.sleep(2)
    cv2.destroyAllWindows()
    
        
show_webcam2(mirror=True)        
        
def show_webcam(mirror=False):
    cam = cv2.VideoCapture(0)
    while True:
        ret_val, img = cam.read()
        if mirror:
            img = cv2.flip(img, 1)
        cv2.imshow('my webcam', img)
        if cv2.waitKey(1) == 27:
            break  # esc to quit
    


#def main():
#    show_webcam2(mirror=True)


#if __name__ == '__main__':
#    main()
