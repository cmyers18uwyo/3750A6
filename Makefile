##################################
#Makefile
#Charles Myers
#COSC 3750 Spring 2021
#Homework 3
#February 16, 2021
#
#This file will compile the supplied files for HW3
##################################
CC=gcc
CFLAGS=-ggdb -Wall -I .
RM=/bin/rm -f
#tidy and clean are not files
.PHONY : tidy clean
#approxe will use the approxe.c file and the object files from OBJS
#and create an executable called approxe
wytar : wytar.c $(OBJS)
	$(CC) $(CFLAGS) -o wytar wytar.c $(OBJS)
#tidy will remove any object files in the directory
tidy :
	$(RM) *.o
#clean will run tidy and remove the executable approxe
clean : tidy
	$(RM) wytar
