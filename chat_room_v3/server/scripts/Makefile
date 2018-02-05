CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread -lsqlite3
Target := server  #check_putin
Source := $(wildcard src/*.c) #src/check_putin.c
Objs := $(patsubst %.c,%.o,$(Source)) #src/check_putin.o
Modules += change_passwd display_user id_set login_judge out private_chat tcp_server check_state del_user group_chat insert_new_user log_judge no_say say send_file
AllObjs := $(addsuffix /src/*.o,$(Modules))
#check_putin/src/*.o pack_message/src/*.o main/src/*.o
