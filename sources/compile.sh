#!/bin/bash

gcc -c ../libs/error_control/error_control.c -o ../libs/error_control/error_control.o
ar -crs ../libs/liberror_control.a ../libs/error_control/error_control.o

gcc -c ../libs/sala/sala.c -o ../libs/sala/sala.o -lerror_control -L../libs
ar -crs ../libs/libsala.a ../libs/sala/sala.o

gcc misala.c -o misala -lsala -lerror_control -L../libs
gcc test_parcial.c -o test_parcial -lsala -lerror_control -L../libs
