#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <libstrings.h>
#include <libbst.h>

#include <libuber.h>


int help(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
// Manage rides
int del_ride(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
int get_ride(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);

int read_in_cars(int fd, uber::car *& standard, uber::car *& premium, uber::car *& group);
int user_action(int argc, char ** argv, uber::car *& standard, uber::car *& premium, uber::car *& group, uber::rides & rides);
