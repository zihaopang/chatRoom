CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread -lcursesw
Target := client   #check_putin
Source := $(wildcard src/*.c) #src/check_putin.c
Objs := $(patsubst %.c,%.o,$(Source)) #src/check_putin.o
Modules += add_face change_passwd draw_menu log_table private_chat remind send_file tcp_client admin_table chat_table first_table no_say rcv_deal say set get_file out reg_table short_msg user_table 
AllObjs := $(addsuffix /src/*.o,$(Modules))
#check_putin/src/*.o pack_message/src/*.o main/src/*.o
