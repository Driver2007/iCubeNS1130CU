#!/usr/bin/env python3

import sys
from ctypes import CDLL, POINTER, \
    Structure, \
    c_int, c_void_p, \
    addressof, pointer


DLL = "/home/sergey/Git/iCubeNS1130CU/c_type_p/dll.so"


class Effect(Structure):
    _fields_ = [("ptr", c_void_p)]


def hex64_str(item):
    return "0x{:016X}".format(item)


def print_addr(ctypes_inst, inst_name, heading=""):
    print("{:s}{:s} addr: {:s} (type: {:})".format(heading, "{:s}".format(inst_name) if inst_name else "", hex64_str(addressof(ctypes_inst)), type(ctypes_inst)))


def main():
    dll_dll = CDLL(DLL)
    test_func = dll_dll._Z4testP6Effecti
    test_func.argtypes = [POINTER(Effect), c_int]

    effect = Effect()
    print_addr(effect, "effect")
    test_func(pointer(effect), 1)

    print_addr(effect, "effect", "\nSecond time...\n    ")
    print("Python addrs (irrelevant): effect: {:s}, effect.ptr: {:s}".format(hex64_str(id(effect)), hex64_str(id(effect.ptr))))


if __name__ == "__main__":
    print("Python {:s} on {:s}\n".format(sys.version, sys.platform))
    main()
