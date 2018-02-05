#define LOG_SUCCESS 1
#define LOG_FAIL 2
#define LOGIN_SUCCESS 3
#define LOGIN_FAIL 4
#define LOG 5
#define LOGIN 6
#define ALARM 7
#define STO 8
#define BACKSPACE 9
#define MAX_LEN 10
#define DIS 11
#define STO_SUCCESS 12
#define ENTER 13
#define STA 14
#define DIS_SUCCESS 15
#define STO_FAIL 16
#define STA_SUCCESS 17
#define NO_SAY 18
#define SAY 19
#define OUT 20
#define CHP 21
#define CHP_SUCCESS 22
#define CHP_FAIL 23
#define SNF 24
#define SNF_END 25
#define SNF_SUCCESS 26
#define SNF_FAIL 27
#define BLANK_1 28
#define BLANK_2 29
#define SURE 30
#define CHAT 31
#define FACE 32
#define MSG 33
#define FLE 34
#define SEND 35
#define EXIT 36
#define SET 37
#define MAX_SIZE 100
#define portnumber 3333

#include <curses.h>
#include <unistd.h>
#include <sqlite3.h>

struct content
{
    WINDOW *chat_win;

    int num;
    char name[10];
};

struct message
{
    int id;
    int action;
    char name[20];
    char passwd[10];
    char toname[20];
    char msg[1024];
    char users[30][10];
};

struct online
{
    int state;
    int new_fd;
    char name[20];

    struct online* next;
};

typedef struct online Online;
typedef Online* Link;
typedef struct content Content;

int insert_new_user(Link *new_user,Link *head);




