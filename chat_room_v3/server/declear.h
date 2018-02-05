#include <sqlite3.h>

int change_passwd(int new_fd,sqlite3 *passwd_db);
int log_judge(sqlite3 *passwd_db,int new_fd);
int login_judge(sqlite3 *passwd_db,int new_fd);
int del_user(int new_fd);
int group_chat(int new_fd);
int out();
int private_chat(int new_fd);
void send_file(int new_fd);
int check_state(int new_fd);
int display_user(int new_fd);
int id_set();
int no_say();
int say(int new_fd);
void read_msg(void *arg);
