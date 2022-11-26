
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *msg_hit[] = {"Ouch!", "You hit!", "Oops!"};
char *msg_out[] = {"Bye!", "Goodbye!", "Farewell!"};
char *msg_start[] = {"Welcome!", "Hello!", "Hi!"};
char *msg_unknown[] = {"I dont know what this is!", "Uknown letter!", "Uknown Input!"};
char *msg_win[] = {"You win!", "Congrats!"};
char *msg_normal[] = {"Press A/S/D/W to move, Q to quit"};
char *msg_way[] = {"You cant enter from here", "Try to press something else!", "No entrance!", "Wrong way!"};
char *msg_targ[] = {"You reached a target!", "Good job,continue to other targets!"};
char *msg_vis[] = {"You visited me!"};
char *msg_change_direct[]={"change your direct","Try again!","there is no exit from here!"};
char *msg_port[]={"Wheee!","Its a portal!","Your location has been changed!"};
char *msg_key[]={"You have picked up a key!"};
char *msg_door[]={"You have opened a door!"};
char *msg_cant_door[]={"You dont have enough keys!","You cant open this door!"};
char *msg_done_key[]={"You have already picked me!","I cant be picked up again,Haha!","Nice try to get more keys!"};

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define MSG_NORMAL msg_normal[rand() % ARR_SIZE(msg_normal)]
#define MSG_START msg_start[rand() % ARR_SIZE(msg_start)] 
#define MSG_UNKNOWN msg_unknown[rand() % ARR_SIZE(msg_unknown)]
#define MSG_OUT msg_out[rand() % ARR_SIZE(msg_out)]
#define MSG_HIT msg_hit[rand() % ARR_SIZE(msg_hit)]
#define MSG_WIN msg_win[rand() % ARR_SIZE(msg_win)]
#define MSG_WAY msg_way[rand() % ARR_SIZE(msg_way)]
#define BUFFER_SIZE 1024
#define MSG_TARG msg_targ[rand() % ARR_SIZE(msg_targ)]
#define MSG_VIS msg_vis[rand() % ARR_SIZE(msg_vis)]
#define MSG_DIRECT msg_change_direct[rand() % ARR_SIZE(msg_change_direct)]
#define MSG_KEY msg_key[rand() % ARR_SIZE(msg_key)]
#define MSG_DOOR msg_door[rand() % ARR_SIZE(msg_door)]
#define MSG_CANT_DOOR msg_cant_door[rand() % ARR_SIZE(msg_cant_door)]
#define MSG_DONE_KEY msg_done_key[rand() % ARR_SIZE(msg_done_key)]

typedef struct location{
    int i;
    int j;
} location ;

typedef struct maze {                       
    char *message;
    int cols;
    int rows;
    location *player;
    location *target;
    location *target2;
    char **tiles;
    int targ_num;
    int keys_num;
    location *key1;
    location *key2;
    location *door1;
    location *door2;
} maze;

void free_maze(maze *maze);
maze *init_maze(char *message, int cols, int rows, int player_loc_c, int player_loc_r, int target_loc_c, int target_loc_r, int targ_num,
                int target2_loc_c, int target2_loc_r,int key1_loc_c,int key1_loc_r,
                int key2_loc_c,int key2_loc_r,int door1_loc_c, int door1_loc_r,int door2_loc_c,
                int door2_loc_r);
void set_terminal(bool start);
void print_maze(maze *maze);
void handle_input(maze *maze1,bool *game_over);
maze *read_maze(const char *filename);

/************************************
 * TERMINAL CODES ("MAGIC STRINGS") *
 ************************************/

#define COLOR_OFF       "\e[0m"
#define COLOR_BLACK     "\e[0;30m"
#define COLOR_GRAY      "\e[1;30m"
#define COLOR_RED       "\e[0;31m"
#define COLOR_LT_RED    "\e[1;31m"
#define COLOR_GREEN     "\e[0;32m"
#define COLOR_LT_GREEN  "\e[1;32m"
#define COLOR_BROWN     "\e[0;33m"
#define COLOR_YELLOW    "\e[1;33m"
#define COLOR_BLUE      "\e[0;34m"
#define COLOR_LT_BLUE   "\e[1;34m"
#define COLOR_PURPLE    "\e[0;35m"
#define COLOR_LT_PURPLE "\e[1;35m"
#define COLOR_CYAN      "\e[0;36m"
#define COLOR_LT_CYAN   "\e[1;36m"
#define COLOR_LT_GRAY   "\e[0;37m"
#define COLOR_WHITE     "\e[1;37m"

#define CLEAR_SCREEN    "\e[2J\e[1;1H"

/*****************************
 * SYMBOLS FOR GAME ELEMENTS *
 *****************************/

#define S_FLOOR     " "
#define S_PLAYER    COLOR_BLUE "@" COLOR_OFF
#define S_WALL      COLOR_GRAY "#" COLOR_OFF
#define TARGET      COLOR_PURPLE "$" COLOR_OFF
#define REACH_TARG COLOR_BLUE "$" COLOR_OFF
#define PASS_TARG COLOR_YELLOW "$" COLOR_OFF
#define VERT_WALL COLOR_GREEN "|" COLOR_OFF
#define HORIZ_WALL COLOR_RED "-" COLOR_OFF 
#define REACH_VERT_WALL COLOR_BLUE "|" COLOR_OFF
#define REACH_HORIZ_WALL COLOR_BLUE "-" COLOR_OFF
#define FINAL_TARG COLOR_CYAN "$" COLOR_OFF 
#define GO_DOWN COLOR_CYAN "v" COLOR_OFF
#define GO_LEFT COLOR_CYAN "<" COLOR_OFF 
#define GO_RIGHT COLOR_CYAN ">" COLOR_OFF 
#define GO_UP COLOR_CYAN "^" COLOR_OFF
#define REACH_GO_LEFT COLOR_BLUE "<" COLOR_OFF 
#define REACH_GO_RIGHT COLOR_BLUE ">" COLOR_OFF 
#define REACH_GO_UP COLOR_BLUE "^" COLOR_OFF
#define REACH_GO_DOWN COLOR_BLUE "v" COLOR_OFF  
#define KEY COLOR_LT_PURPLE "&" COLOR_OFF
#define REACH_KEY COLOR_BLUE "&" COLOR_OFF
#define DOOR COLOR_LT_RED "+" COLOR_OFF
#define REACH_DOOR COLOR_BLUE "+" COLOR_OFF
#define DONE_KEY COLOR_YELLOW "&" COLOR_OFF

