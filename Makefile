#########################################################################################
# Raul Fosselman, William Nelson
# Username: cssc2104
# Class: CS570 Summer 2020
# Project: CS-570 Assignment 1
# File: Makefile
#########################################################################################

bots: main.cpp
	g++ -o bots main.cpp -lpthread -lrt

clean:
	rm *.o bots

############################### EOF: Makefile ###########################################