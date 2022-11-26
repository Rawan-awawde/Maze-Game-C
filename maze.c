#include "maze.h"

int main(int argc, char *argv[])
{
    set_terminal(true);
    srand(time(NULL));
    maze *maze1 = NULL;
    maze1 = read_maze(argv[1]);
    maze1->keys_num = 0;
    if (!maze1)
    {
        printf("error initializing maze\n");
        exit(1);
    }
    print_maze(maze1);
    bool game_over = false;
    handle_input(maze1, &game_over);
    free_maze(maze1);
    maze1 = NULL;
    set_terminal(false);
    return 0;
}

char visit[2] = {0};
char keys[2] = {0};
char doors[2] = {0};

void handle_input(maze *maze, bool *game_over)
{
    do
    {
        maze->message = MSG_NORMAL;
        // get user input
        int key = getchar();
        switch (key)
        {
        case EOF:
        case 'q':
        case 'Q': // exit game
            *game_over = true;
            maze->message = MSG_OUT;
            break;
        case 'a':
        case 'A': // go left
            if (0 == maze->player->j) {
				maze->message = MSG_HIT;
            }
            else if (maze->player->j > 0 && maze->tiles[maze->player->i][maze->player->j - 1] == S_WALL[7]) {
				maze->message = MSG_HIT;
            }
            else if (maze->player->j > 0 && maze->tiles[maze->player->i][maze->player->j - 1] == VERT_WALL[7]) {
				maze->message = MSG_WAY;
            }
            else if ((maze->player->j >0) && (maze->player->i == maze->target->i) && 
            (maze->player->j-1 == maze->target->j)) {
                if (0 == visit[0]) {
                   maze->message = MSG_TARG;
                   visit[0] = 1;
                   maze->player->j--;
                }
                else if (visit[0]!=0) {
                    maze->message= MSG_VIS;
                    maze->player->j--;
                }
            }
            else if ((maze->player->j >0) && (maze->player->i == maze->target2->i) && 
            (maze->player->j-1 == maze->target2->j)) {
                if (0 == visit[1]) {
                   maze->message= MSG_TARG;
                   visit[1] = 1;
                   maze->player->j--;
                }
                else if (visit[1]!=0) {
                    maze->message = MSG_VIS;
                    maze->player->j--; 
                }
            }
            else if ((maze->player->j >0) && ((maze->tiles[maze->player->i][maze->player->j] == '>') ||(maze->tiles[maze->player->i][maze->player->j] == '^')
             || (maze->tiles[maze->player->i][maze->player->j] == 'v'))) {
                maze->message = MSG_DIRECT ;
            }
            else if ((maze->player->j >0) &&  (maze->player->i == maze->key1->i) && 
            (maze->player->j-1 == maze->key1->j)) {
                if (0 == keys[0]){
                   maze->message = MSG_KEY;
                   keys[0] = 1;
                   maze->keys_num++;
                   maze->player->j--;
                }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->j--;
                }
            }
            else if ((maze->player->j >0) &&  (maze->player->i == maze->key2->i) && 
            (maze->player->j-1 == maze->key2->j)) { 
                   if (keys[1]==0) {
                   maze->message = MSG_KEY;
                   keys[1] = 1;
                   maze->keys_num++;
                   maze->player->j--;
                   }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->j--;
                }  
            }
            else if ((maze->player->j >0) &&  (maze->player->i == maze->door1->i) && 
            (maze->player->j-1 == maze->door1->j && (doors[0]!=1))) { 
                if (maze->keys_num>0) {
                   maze->message = MSG_DOOR;
                   doors[0] = 1;
                   maze->keys_num--;
                   maze->player->j--;
                }
                else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->j--;
                }
            }
            else if ((maze->player->j >0) &&  (maze->player->i == maze->door2->i) && 
            (maze->player->j-1 == maze->door2->j && (doors[1]!=1))) { 
                   if (maze->keys_num>0) {
                       maze->message = MSG_DOOR;
                       doors[1] = 1;
                       maze->keys_num--;
                       maze->player->j--;}
                    else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->j--;
                    }  
            }
            else {
				maze->player->j--;
            }
			break;
		case 'd':
		case 'D': // go right
			if (maze->player->j == maze->cols - 1) {
				maze->message = MSG_HIT;
			} else if (maze->player->j < maze->cols - 1 && maze->tiles[maze->player->i][maze->player->j + 1] == S_WALL[7]) {
				maze->message = MSG_HIT;
			} else if (maze->player->j < maze->cols - 1 && maze->tiles[maze->player->i][maze->player->j + 1] == VERT_WALL[7]) {
				maze->message = MSG_WAY;
            } else if ((maze->player->j < maze->cols - 1) && (maze->player->i == maze->target->i) && 
            (maze->player->j+1 == maze->target->j)) {
                if (0 == visit[0]) {
                   maze->message = MSG_TARG;
                   visit[0] = 1;
                   maze->player->j++;
                }
                else if (visit[0]!=0) {
                    maze->message = MSG_VIS;
                    maze->player->j++; 
                }
            } else if ((maze->player->j < maze->cols - 1) && (maze->player->i == maze->target2->i) && 
            (maze->player->j+1 == maze->target2->j)){
                if (0 == visit[1]) {
                   maze->message= MSG_TARG;
                   visit[1]=1;
                   maze->player->j++;
                }
                else if (visit[1]!=0) {
                    maze->message= MSG_VIS;
                    maze->player->j++; 
                }
            } else if ((maze->player->j < maze->cols - 1) && ((maze->tiles[maze->player->i][maze->player->j] == '<') ||(maze->tiles[maze->player->i][maze->player->j] == '^')
             || (maze->tiles[maze->player->i][maze->player->j] == 'v'))) {
                            maze->message = MSG_DIRECT ;
            } else if ((maze->player->j < maze->cols - 1) &&  (maze->player->i == maze->key1->i) && 
            (maze->player->j+1 == maze->key1->j)) {
                if (0 == keys[0]) {
                   maze->message = MSG_KEY;
                   keys[0] = 1;
                   maze->keys_num++;
                   maze->player->j++;
                }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->j++;
                }
            } else if ((maze->player->j < maze->cols - 1) &&  (maze->player->i == maze->key2->i) && 
            (maze->player->j+1 == maze->key2->j)) { 
                   if (0 == keys[1]){
                   maze->message = MSG_KEY;
                   keys[1] = 1;
                   maze->keys_num++;
                   maze->player->j++;
                }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->j++;
                }  
            } else if ((maze->player->j < maze->cols - 1) &&  (maze->player->i == maze->door1->i) && 
            (maze->player->j+1 == maze->door1->j && (doors[0]!=1))) { 
                if (maze->keys_num>0) {
                   maze->message = MSG_DOOR;
                   doors[0] = 1;
                   maze->keys_num--;
                   maze->player->j++;
                }
                else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->j++;
                }
            } else if ((maze->player->j < maze->cols - 1) &&  (maze->player->i == maze->door2->i) && 
            (maze->player->j+1 == maze->door2->j && (doors[1]!=1))) { 
                   if (maze->keys_num>0) {
                       maze->message = MSG_DOOR;
                       doors[1] = 1;
                       maze->keys_num--;
                       maze->player->j++;
                    }
                    else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->j++;
                    }
            } 
            else {
				maze->player->j++;
            }
			break;
		case 'w':
		case 'W': // go up
			if (0 == maze->player->i) {
				maze->message = MSG_HIT;
			} else if ((maze->player->i > 0 && maze->tiles[maze->player->i - 1][maze->player->j] == S_WALL[7])) {
				maze->message = MSG_HIT;
			} else if ((maze->player->i > 0 && maze->tiles[maze->player->i - 1][maze->player->j] == HORIZ_WALL[7])) {
				maze->message = MSG_WAY;
			} else if ((maze->player->i > 0) && (maze->player->i-1 == maze->target->i) && 
            (maze->player->j == maze->target->j)) {
                if (0 == visit[0]) {
                   maze->message = MSG_TARG;
                   visit[0] = 1;
                   maze->player->i--;
                }
                else if (visit[0]!=0) {
                    maze->message= MSG_VIS;
                    maze->player->i--; 
                }
            } else if ((maze->player->i > 0) && (maze->player->i-1 == maze->target2->i) && 
            (maze->player->j == maze->target2->j)) {
                if (0 == visit[1]) {
                   maze->message = MSG_TARG;
                   visit[1] = 1;
                   maze->player->i--;
                }
                else if (visit[1]!=0) {
                    maze->message = MSG_VIS;
                    maze->player->i--; 
                }
            } else if ((maze->player->i > 0) && ((maze->tiles[maze->player->i][maze->player->j] == '>') ||(maze->tiles[maze->player->i][maze->player->j] == '<') ||
                        (maze->tiles[maze->player->i][maze->player->j] == 'v'))) {
                            maze->message = MSG_DIRECT;
            } else if ((maze->player->i > 0) &&  (maze->player->i-1 == maze->key1->i) && 
            (maze->player->j == maze->key1->j)) {
                if (0 == keys[0]) {
                   maze->message = MSG_KEY;
                   keys[0] = 1;
                   maze->keys_num++;
                   maze->player->i--;
                }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->i--;
                }
            } else if ((maze->player->i >0) &&  (maze->player->i-1 == maze->key2->i) && 
            (maze->player->j == maze->key2->j)) { 
                   if (0 == keys[1]) {
                   maze->message = MSG_KEY;
                   keys[1]=1;
                   maze->keys_num++;
                   maze->player->i--;
                   }
                else{
                    maze->message = MSG_DONE_KEY;
                    maze->player->i--;
                }  
            } else if ((maze->player->i >0) &&  (maze->player->i-1 == maze->door1->i) && 
            (maze->player->j == maze->door1->j && (doors[0]!=1))) { 
                if (maze->keys_num>0) {
                   maze->message = MSG_DOOR;
                   doors[0] = 1;
                   maze->keys_num--;
                   maze->player->i--;
                }
                else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->i--;
                }
            } else if ((maze->player->i >0) &&  (maze->player->i-1 == maze->door2->i) && 
            (maze->player->j == maze->door2->j && (doors[1]!=1))) { 
                   if (maze->keys_num>0) {
                       maze->message = MSG_DOOR;
                       doors[1] = 1;
                       maze->keys_num--;
                       maze->player->i--;
                    }
                    else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->i--;
                    }
            } else { 
				maze->player->i--;
			}
			break;
		case 's':
		case 'S': // go down
			if (maze->player->i == maze->rows - 1) {
				maze->message = MSG_HIT;
			} else if ((maze->player->i < maze->rows - 1 && maze->tiles[maze->player->i + 1][maze->player->j] == S_WALL[7])) {
				maze->message = MSG_HIT;
			} else if ((maze->player->i < maze->rows - 1 && maze->tiles[maze->player->i + 1][maze->player->j] == HORIZ_WALL[7])) {
				maze->message = MSG_WAY;
			} else if ((maze->player->i < maze->rows - 1) && (maze->player->i+1 == maze->target->i) && 
            (maze->player->j == maze->target->j)) {
                if (0 == visit[0]) {
                   maze->message = MSG_TARG;
                   visit[0] = 1;
                   maze->player->i++;
                }
                else if (visit[0]!=0) {
                    maze->message= MSG_VIS;
                    maze->player->i++; 
                }
            } else if ((maze->player->i < maze->rows - 1) && (maze->player->i+1 == maze->target2->i) && 
            (maze->player->j == maze->target2->j)) {
                if (0 == visit[1]) {
                   maze->message = MSG_TARG;
                   visit[1] = 1;
                   maze->player->i++;
                }
                else if (visit[1]!=0) {
                    maze->message = MSG_VIS;
                    maze->player->i++;
                }
            } else if ((maze->player->i < maze->rows - 1) && ((maze->tiles[maze->player->i][maze->player->j] == '>') ||(maze->tiles[maze->player->i][maze->player->j] == '^') ||
                        (maze->tiles[maze->player->i][maze->player->j] == '<'))) {
                            maze->message= MSG_DIRECT ;
            } else if ((maze->player->i < maze->rows - 1) &&  (maze->player->i+1 == maze->key1->i) && 
            (maze->player->j == maze->key1->j)) {
                if (0 == keys[0]) {
                   maze->message = MSG_KEY;
                   keys[0] = 1;
                   maze->keys_num++;
                   maze->player->i++;
                }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->i++;
                }
            } else if ((maze->player->i < maze->rows - 1) &&  (maze->player->i+1 == maze->key2->i) && 
            (maze->player->j == maze->key2->j)) { 
                   if (0 == keys[1]){
                   maze->message = MSG_KEY;
                   keys[1] = 1;
                   maze->keys_num++;
                   maze->player->i++;
                   }
                else {
                    maze->message = MSG_DONE_KEY;
                    maze->player->i++;
                }  
            } else if ((maze->player->i < maze->rows - 1) &&  (maze->player->i+1 == maze->door1->i) && 
            (maze->player->j == maze->door1->j && (doors[0]!=1))) { 
                if (maze->keys_num>0){
                   maze->message = MSG_DOOR;
                   doors[0] = 1;
                   maze->keys_num--;
                   maze->player->i++;
                }
                else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->i++;
                }
            } else if ((maze->player->i < maze->rows - 1) &&  (maze->player->i+1 == maze->door2->i) && 
            (maze->player->j == maze->door2->j && (doors[1]!=1))) { 
                   if (maze->keys_num>0) {
                       maze->message = MSG_DOOR;
                       doors[1] = 1;
                       maze->keys_num--;
                       maze->player->i++;
                    }
                    else {
                    maze->message = MSG_CANT_DOOR;
                    //maze->player->i++;
                    }
            } else {
				maze->player->i++;
		    }
			break;
		default:
			maze->message = MSG_UNKNOWN;
	}
	if (visit[0]!=0 && visit[1]!=0) {
		maze->message = MSG_WIN;
		*game_over=true;
    }
    // print maze
    print_maze(maze);
    } while (!*game_over);
}

maze *init_maze(char *message, int cols, int rows, int player_loc_c, int player_loc_r, int target_loc_c, int target_loc_r, int targ_num,
                int target2_loc_c, int target2_loc_r, int key1_loc_c, int key1_loc_r,
                int key2_loc_c, int key2_loc_r, int door1_loc_c, int door1_loc_r, int door2_loc_c,
                int door2_loc_r)
{
    maze *result = NULL;
    if (NULL == (result = (maze *)malloc(sizeof(maze))))
    {
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->player = malloc(sizeof(location))))
    {
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->target = malloc(sizeof(location))))
    {
        free(result->player);
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->target2 = malloc(sizeof(location))))
    {
        free(result->player);
        free(result->target);
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->key1 = malloc(sizeof(location))))
    {
        free(result->player);
        free(result->target);
        free(result->target2);
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->key2 = malloc(sizeof(location))))
    {
        free(result->player);
        free(result->target);
        free(result->target2);
        free(result->key1);
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->door1 = malloc(sizeof(location))))
    {
        free(result->player);
        free(result->target);
        free(result->target2);
        free(result->key1);
        free(result->key2);
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    if (NULL == (result->door2 = malloc(sizeof(location))))
    {
        free(result->player);
        free(result->target);
        free(result->target2);
        free(result->key1);
        free(result->key2);
        free(result->door1);
        free(result);
        printf("Error! Allocation failed\n");
        exit(1);
    }
    result->target->i = target_loc_r;
    result->target->j = target_loc_c;
    result->target2->i = target2_loc_r;
    result->target2->j = target2_loc_c;
    result->player->i = player_loc_r;
    result->player->j = player_loc_c;
    result->message = message;
    result->targ_num = targ_num;
    result->key1->i = key1_loc_r;
    result->key1->j = key1_loc_c;
    result->key2->i = key2_loc_r;
    result->key2->j = key2_loc_c;
    result->door1->i = door1_loc_r;
    result->door1->j = door1_loc_c;
    result->door2->i = door2_loc_r;
    result->door2->j = door2_loc_c;
    if (NULL == (result->tiles = malloc(rows * sizeof(char *))))
    {
        free(result->player);
        free(result->target);
        free(result->target2);
        free(result->key1);
        free(result->key2);
        free(result->door1);
        free(result->door2);
        free(result);
        exit(1);
    }
    for (int i = 0; i < rows; i++)
    {
        result->tiles[i] = malloc(cols * sizeof(char *));
        if (NULL == (result->tiles[i]))
        {
            free(result->player);
            free(result->target);
            free(result->target2);
            free(result->key1);
            free(result->key2);
            free(result->door1);
            free(result->door2);
            free(result->tiles);
            free(result);
            exit(1);
        }
    }
    result->cols = cols;
    result->rows = rows;
    return result;
}

void free_maze(maze *maze)
{
    if (maze != NULL)
    {
        free(maze->player);
        free(maze->target);
        free(maze->target2);
        free(maze->key1);
        free(maze->key2);
        free(maze->door1);
        free(maze->door2);
        for (int i = 0; i < maze->rows; i++)
        {
            free(maze->tiles[i]);
        }
        free(maze->tiles);
        free(maze);
    }
}

#define puts_no_newline(s) fputs(s, stdout)

maze *read_maze(const char *file_name)
{
    FILE *fp = NULL;
    maze *maze = NULL;
    fp = fopen(file_name, "r");
    if (NULL == fp)
    {
        printf("couldn't open file %s", file_name);
        exit(1);
    }
    char *message = NULL;
    message = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (!message)
    {
        printf("couldn't allocate message");
        exit(1);
    }
    int rows, cols;
    fgets(message, BUFFER_SIZE, fp);
    fscanf(fp, "%d %d", &rows, &cols);
    char **tiles = NULL;
    if (rows <= 2 || cols <= 2)
        return NULL;
    if (NULL == (tiles = (char **)malloc(rows * sizeof(char *))))
    {
        return NULL;
    }
    for (unsigned int i = 0; i < rows; i++)
    {
        if (NULL == (tiles[i] = (char *)malloc(cols * sizeof(char))))
        {
            return NULL;
        }
    }
    location player, target, target2, key1, key2, door1, door2;
    char c;
    int num_of_players = 0, num_of_targets = 1, num_of_keys = 1, num_of_doors = 1;
    unsigned i = 0, j = 0;
    do
    {
        if (i >= rows)
        {
            break;
        }
        if (j >= cols)
        {
            j = 0;
            i++;
            continue;
        }
        c = (char)fgetc(fp);
        while ('\n' == c  || '\r' == c )
        {
            c = (char)fgetc(fp);
            if (EOF == c)
                break;
        }
        if (EOF == c)
            break;
        // fscanf(fp, "%c", %c);
        switch (c)
        {
        case '@':
            num_of_players++;
            player.i = i;
            player.j = j;
            strncpy(&tiles[i][j], &c, 1);
            break;
        case '$':
            if ( 1 == num_of_targets)
            {
                num_of_targets++;
                target.i = i;
                target.j = j;
                strncpy(&tiles[i][j], &c, 1);
            }
            else if (2 == num_of_targets)
            {
                num_of_targets++;
                target2.i = i;
                target2.j = j;
                strncpy(&tiles[i][j], &c, 1);
            }
            else
            {
                num_of_targets++;
            }
            break;
        case '-':
            strncpy(&tiles[i][j], &c, 1);
            break;
        case '|':
            strncpy(&tiles[i][j], &c, 1);
            break;
        case '&':
            if (1 == num_of_keys)
            {
                num_of_keys++;
                key1.i = i;
                key1.j = j;
                strncpy(&tiles[i][j], &c, 1);
            }
            else if (2 == num_of_keys)
            {
                num_of_keys++;
                key2.i = i;
                key2.j = j;
                strncpy(&tiles[i][j], &c, 1);
            }
            else
            {
                num_of_keys++;
            }
            break;
        case '+':
            if (1 == num_of_doors)
            {
                num_of_doors++;
                door1.i = i;
                door1.j = j;
                strncpy(&tiles[i][j], &c, 1);
            }
            else if (2 == num_of_doors)
            {
                num_of_doors++;
                door2.i = i;
                door2.j = j;
                strncpy(&tiles[i][j], &c, 1);
            }
            else
            {
                num_of_doors++;
            }
            break;        
        default:
            strncpy(&tiles[i][j], &c, 1);
            break;
        }
        j++;
    } while ((c != EOF));
    if (num_of_players != 1 || num_of_targets > 3 || num_of_keys>3 || num_of_doors>3)
    {
        printf("wrong number of objects\n");
        exit(1);
    }
    maze = init_maze(message, cols, rows, player.j, player.i, target.j, target.i, num_of_targets, target2.j, target2.i,
           key1.j ,key1.i ,key2.j ,key2.i ,door1.j ,door1.i ,door2.j ,door2.i);
    maze->tiles = tiles;
    maze->keys_num=num_of_keys;
    fclose(fp);
    return maze;
}

void print_row(maze *maze)
{
    for (int j = 0; j < maze->cols + 2; j++)
        puts_no_newline(S_WALL);
    putchar('\n');
}

int targ1 = 0;
int targ2 = 0;

void print_maze(maze *maze)
{
    static unsigned frame_num; // this variable retains its value between calls
    // clear terminal
    puts_no_newline(CLEAR_SCREEN);
    // print frame number and message
    printf("%-*.*s%4d%4d\n", maze->cols - 2, maze->cols - 2, maze->message, frame_num++,maze->keys_num);
    //printf("%-*.*s%4d\n", maze->cols - 2, maze->cols - 2,"The numbers of keys you have: ", maze->keys_num);
    // print header row
    print_row(maze);
    // print maze rows (including player)
    for (int i = 0; i < maze->rows; i++)
    {
        puts_no_newline(S_WALL);
        for (int j = 0; j < maze->cols; j++)
        {
            if (i == maze->player->i && j == maze->player->j)
            {
                if ((maze->player->j == maze->target->j) && (maze->player->i == maze->target->i) && (maze->targ_num != 0))
                {
                    targ1++;
                    puts_no_newline(REACH_TARG);
                }
                else if (maze->tiles[i][j] == '-')
                {
                    puts_no_newline(REACH_HORIZ_WALL);
                }
                else if (maze->tiles[i][j] == '|')
                {
                    puts_no_newline(REACH_VERT_WALL);
                }
                else if ((maze->player->j == maze->target2->j) && (maze->player->i == maze->target2->i) && (maze->targ_num != 0))
                {
                    targ2++;
                    puts_no_newline(REACH_TARG);
                }
                else if (maze->tiles[i][j] == '<')
                {
                    puts_no_newline(REACH_GO_LEFT);
                }
                else if (maze->tiles[i][j] == '>')
                {
                    puts_no_newline(REACH_GO_RIGHT);
                }
                else if (maze->tiles[i][j] == '^')
                {
                    puts_no_newline(REACH_GO_UP);
                }
                else if (maze->tiles[i][j] == 'v')
                {
                    puts_no_newline(REACH_GO_DOWN);
                }
                else if (((maze->player->j == maze->key1->j) && (maze->player->i == maze->key1->i)) || 
                ((maze->player->j == maze->key2->j) && (maze->player->i == maze->key2->i)))
                {
                    puts_no_newline(REACH_KEY);
                }
                else if (((maze->player->j == maze->door1->j) && (maze->player->i == maze->door1->i)) || 
                ((maze->player->j == maze->door2->j) && (maze->player->i == maze->door2->i)))
                {
                    puts_no_newline(REACH_DOOR);
                }
                else
                {
                    puts_no_newline(S_PLAYER);
                }
            }
            else if (i == maze->target->i && j == maze->target->j)
            {
                if (targ1 != 0)
                {
                    puts_no_newline(PASS_TARG);
                }
                else
                {
                    puts_no_newline(TARGET);
                }
            }
            else if (i == maze->target2->i && j == maze->target2->j)
            {
                if (targ2 != 0)
                {
                    puts_no_newline(PASS_TARG);
                }
                else
                {
                    puts_no_newline(TARGET);
                }
            }
            else if (i == maze->key1->i && j == maze->key1->j)
            {
                if (1== keys[0])
                {
                    puts_no_newline(DONE_KEY);
                }
                else
                {
                    puts_no_newline(KEY);
                }
            }
            else if (i == maze->key2->i && j == maze->key2->j)
            {
                if (1 == keys[1])
                {
                    puts_no_newline(DONE_KEY);
                }
                else
                {
                    puts_no_newline(KEY);
                }
            }
            else if (i == maze->door1->i && j == maze->door1->j)
            {
                if (1 == doors[0])
                {
                    puts_no_newline(S_FLOOR);
                }
                else
                {
                    puts_no_newline(DOOR);
                }
            }
            else if (i == maze->door2->i && j == maze->door2->j)
            {
                if (1 == doors[1])
                {
                    puts_no_newline(S_FLOOR);
                }
                else
                {
                    puts_no_newline(DOOR);
                }
            }
            else if (maze->tiles[i][j] == '#')
            {
                puts_no_newline(S_WALL);
            }
            else if (maze->tiles[i][j] == '-')
            {
                puts_no_newline(HORIZ_WALL);
            }
            else if (maze->tiles[i][j] == '|')
            {
                puts_no_newline(VERT_WALL);
            }
            else if (maze->tiles[i][j] == '<')
            {
                puts_no_newline(GO_LEFT);
            } 
            else if (maze->tiles[i][j] == '>')
            {
                puts_no_newline(GO_RIGHT);
            } 
            else if (maze->tiles[i][j] == 'v')
            {
               puts_no_newline(GO_DOWN);
            } 
            else if (maze->tiles[i][j] == '^')
            {
                puts_no_newline(GO_UP);
            }
            else
            {
                puts_no_newline(S_FLOOR);
            }
        }
        puts_no_newline(S_WALL);
        putchar('\n');
    }
    // print footer row
    print_row(maze);
}
