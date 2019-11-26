# -*- coding: utf-8 -*-
"""
Created on Tue Nov 26 15:00:43 2019

@author: sergey
"""
import ctypes
# Загрузка библиотеки
testpp = ctypes.CDLL('/home/sergey/Git/iCubeNS1130CU/c_void_p/test.so')

# Указываем, что функция возвращает указатель
testpp.test_new.restype = ctypes.c_void_p
# Создание класса test
test = testpp.test_new() 

##
# Работа с методами
##

# Указываем, что функция возвращает char *
testpp.test_ret_str.restype = ctypes.c_char_p
# Указываем, что функция принимает аргумент void * и char *
testpp.test_ret_str.argtypes = [ctypes.c_void_p, ctypes.c_char_p]

# Указываем, что функция возвращает int
testpp.test_ret_int.restype = ctypes.c_int
# Указываем, что функция принимает аргумент void * и int
testpp.test_ret_int.argtypes = [ctypes.c_void_p, ctypes.c_int]

# Указываем, что функция возвращает double
testpp.test_ret_double.restype = ctypes.c_double
# Указываем, что функция принимает аргумент void * и double
testpp.test_ret_double.argtypes = [ctypes.c_void_p, ctypes.c_double]

print('Работа с методами:')
# В качестве 1-ого аргумента передаем указатель на наш класс
print('ret test_ret_str: ', testpp.test_ret_str(test, 'Hello!'.encode('utf-8')).decode("utf-8"))
print('ret test_ret_int: ', testpp.test_ret_int(test, 123))
print('ret test_ret_double: ', testpp.test_ret_double(test, 9.87654321))

##
# Работа с переменными
##

# Указываем, что функция возвращает int
testpp.test_get_a.restype = ctypes.c_int
# Указываем, что функция возвращает double
testpp.test_get_b.restype = ctypes.c_double
# Указываем, что функция возвращает char
testpp.test_get_c.restype = ctypes.c_char

print('\nРабота с переменными:')
print('ret test_get_a: ', testpp.test_get_a(test))
print('ret test_get_b: ', testpp.test_get_b(test))
print('ret test_get_c: ', testpp.test_get_c(test).decode("utf-8"))

# Удаляем класс
testpp.test_del(test) 