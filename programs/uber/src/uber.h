/*
 * John Andersen
 * File: uber/src/uber.h
*/

#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libstrings.h>
#include <libbst.h>

#include <libuber.h>


int help(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
// Manage rides
int list_rides(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
int list_cars(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
int add_ride(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
int add_car(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);

int read_in_cars(int fd, uber::car *& standard, uber::car *& premium, uber::car *& group);
int user_action(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
