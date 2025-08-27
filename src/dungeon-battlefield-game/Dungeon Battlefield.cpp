#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//define Keyboard Button
#define UP     72
#define LEFT   75
#define RIGHT  77
#define DOWN   80

//define Maze Icon
#define EX_WALL  '8' //destroyable wall
#define WALL     '#' //solid wall
#define PATH     ' '

void view_maze(char **maze, int size, int x, int y);
void generate_maze(char **maze, int size, int x, int y);
void play_game(char **maze, int size, int **posX, int **posY, int players);
void boom(char **maze, int bombX, int bombY, int total[2], int size);

int main(){
    char **maze;
    int **posX, **posY;
    int n, size, i, j;
    system("color f0");
    srand((unsigned)time(0));
    printf("Input Dungeon Level [lvl <= 0 to EXIT]: ");    
    fflush(stdin);
    scanf("%d", &n);
    
    if(n<=0) return 0;
    
    //level+2
    n+=2;
    size = 2*n+1;
    
    maze = (char**)malloc(sizeof(char*) * size);
    for(i=0; i<size; i++){
        maze[i] = (char*)malloc(sizeof(char) * (size + 1));
        for(j=0; j<size; j++) {
            if(i==0 || j==0 || i==size-1 || j==size-1 || rand()%100>25)
                maze[i][j] = WALL;    
            else maze[i][j] = EX_WALL;
        }
        maze[i][size]='\0';
    }
    
    //random posisi awal random
    i = 2*(rand()%n)+1;
    j = 2*(rand()%n)+1;
    
    generate_maze(maze, size, i, j);
        
    posX = (int**)malloc(sizeof(int*) * 2);
    posY = (int**)malloc(sizeof(int*) * 2);
    
    //masing-masing player diberi army sebanyak level yang telah
    //ditambah 2
    for(i=0; i<2; i++){
        posX[i] = (int*)malloc(sizeof(int)*n);
        posY[i] = (int*)malloc(sizeof(int)*n);
        for(j=0; j<n; j++){
            do{
                posX[i][j] = 2*(rand()%n)+1;
                posY[i][j] = 2*(rand()%n)+1;
            }while(maze[posX[i][j]][posY[i][j]] != PATH);
            maze[posX[i][j]][posY[i][j]] = i+1;
        }
    }
    
    //mulai permainan    
    play_game(maze, size, posX, posY, n);
    getchar();
    for(i=1; i>=0; i--){
        free(posY[i]);
        free(posX[i]);
    }
    free(posY);
    free(posX);
    for(i=size-1; i>=0; i--){
        free(maze[i]);
    }
    free(maze);
    return 0;
}

//menampilkan maze
void view_maze(char **maze, int size, int x, int y){
    printf(" ");
    for(int i=0; i<size; i++)
      if(i!=y) printf(" ");
      else printf("*");
    printf("\n");
    for(int i=0; i<size; i++){
        if(i!=x) printf(" ");
        else printf("*");
        printf("%s\n", maze[i]);
    }
    printf("\nPress ARROW KEY to MOVE\n");
    printf("Press SPACE BAR to TELEPORT Randomly\n");
    printf("Press A to PLACE the BOMB\n");
    printf("Press S to DETONATE the BOMB\n");
    printf("Press W to KAMIKAZE\n");
    printf("Press D to END your TURN\n");
}

//membuat maze
void generate_maze(char **maze, int size, int x, int y){
    int trial = 1,
        direction = rand()%4;
    
    maze[x][y] = PATH;
    while(trial<=4){
        if(trial<=4 && direction==0/*UP*/){
            trial++;
            if(x-2>=1 && maze[x-2][y] != PATH){
                maze[x-1][y] = PATH;
                generate_maze(maze, size, x-2, y);
            }
            direction++;
        }
        if(trial<=4 && direction==1/*DOWN*/){
            trial++;
            if(x+2<size && maze[x+2][y] != PATH){
                maze[x+1][y] = PATH;
                generate_maze(maze, size, x+2, y);
            }
            direction++;
        }
        if(trial<=4 && direction==2/*LEFT*/){
            trial++;
            if(y-2>=1 && maze[x][y-2] != PATH){
                maze[x][y-1] = PATH;
                generate_maze(maze, size, x, y-2);
            }
            direction++;
        }
        if(trial<=4 && direction==3/*RIGHT*/){
            trial++;
            if(y+2<size && maze[x][y+2] != PATH){
                maze[x][y+1] = PATH;
                generate_maze(maze, size, x, y+2);
            }
            direction++;
        }
        direction = 0/*UP*/;
    }
}

//mulai permainan
void play_game(char **maze, int size, int **posX, int **posY, int players){
    int total[2] = {players, players},
        turn = 1,
        dice1 = 0, dice2 = 0, 
        step = 0,
        pos = 0, bombX = 0, bombY = 0;
    int *x, *y;
    char move;
    
    //selama belum ada yang kehabisan army
    while(total[0]>0 && total[1]>0){
        turn = !turn; //ganti giliran
        system("clear");
        printf("Player %d's turn\n\n", turn+1);
        do{
            pos = rand()%players;
            x = &(posX[turn][pos]);
            y = &(posY[turn][pos]);
        }while(maze[*x][*y] == PATH);
        view_maze(maze, size, *x, *y);
        printf("Dice Roll (A to STOP): x x");
        do{
            do{
                dice1=rand()%6 + 1;
                dice2=rand()%6 + 1;
                printf("\b\b\b%d %d", dice1, dice2);
            }while(!kbhit());
            move=toupper(getchar());
        }while(move!='A'); 
        step = dice1 + dice2;
        getchar();
        do{
            system("clear");
            printf("Player %d's turn (Steps: %d)\n\n", turn+1, step);
            view_maze(maze, size, *x, *y);
            move=toupper(getchar());
            if(step>0) {
                switch(move){
                    case UP:
                        if(maze[*x-1][*y] == PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *x = *x - 1;
                            maze[*x][*y] = turn + 1;
                        }else if(maze[*x-1][*y]!=WALL && maze[*x-2][*y]==PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *x = *x - 2;
                            maze[*x][*y] = turn + 1;
                        }
                        break;
                    case LEFT:
                        if(maze[*x][*y-1] == PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *y = *y - 1;
                            maze[*x][*y] = turn + 1;
                        }else if(maze[*x][*y-1]!=WALL && maze[*x][*y-2]==PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *y = *y - 2;
                            maze[*x][*y] = turn + 1;
                        }
                        break;
                    case RIGHT:
                        if(maze[*x][*y+1] == PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *y = *y + 1;
                            maze[*x][*y] = turn + 1;
                        }else if(maze[*x][*y+1]!=WALL && maze[*x][*y+2]==PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *y = *y + 2;
                            maze[*x][*y] = turn + 1;
                        }
                        break;
                    case DOWN:
                        if(maze[*x+1][*y] == PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *x = *x + 1;
                            maze[*x][*y] = turn + 1;
                        }else if(maze[*x+1][*y]!=WALL && maze[*x+2][*y]==PATH){
                            maze[*x][*y] = PATH;
                            step--;
                            *x = *x + 2;
                            maze[*x][*y] = turn + 1;
                        }
                        break;
                    case ' ':
                        if(step>=2){
                            do{
                                dice1 = rand()%size;
                                dice2 = rand()%size;
                            }while(maze[dice1][dice2]!=PATH);
                            maze[*x][*y] = PATH;
                            step-=2;
                            *x = dice1;
                            *y = dice2;
                            maze[*x][*y] = turn + 1;
                        }
                        break;
                    default: break;
                }
            }
            switch(move){
                case 'A':
                    if(maze[bombX][bombY]!='O'){
                        system("clear");
                        printf("Press ARROW KEY to PLACE the BOMB ");
                        printf("or Press A to CANCEL this ACTION\n\n");
                        view_maze(maze, size, *x, *y);
                        do{
                            move = toupper(getchar());
                            switch(move){
                                case UP:
                                    if(maze[*x-1][*y] == PATH){
                                        bombX = *x - 1;
                                        bombY = *y;
                                        maze[bombX][bombY] = 'O';
                                        move = 'A';
                                    }
                                    break;
                                case LEFT:
                                    if(maze[*x][*y-1] == PATH){
                                        bombX = *x;
                                        bombY = *y-1;
                                        maze[bombX][bombY] = 'O';
                                        move = 'A';
                                    }
                                    break;
                                case DOWN:
                                    if(maze[*x+1][*y] == PATH){
                                        bombX = *x + 1;
                                        bombY = *y;
                                        maze[bombX][bombY] = 'O';
                                        move = 'A';
                                    }
                                    break;
                                case RIGHT:
                                    if(maze[*x][*y+1] == PATH){
                                        bombX = *x;
                                        bombY = *y+1;
                                        maze[bombX][bombY] = 'O';
                                        move = 'A';
                                    }
                                    break;
                                default: break;
                            }
                        }while(move!='A');
                    }
                    break;
                case 'S':
                    if(maze[bombX][bombY] == 'O'){
                        system("clear");
                        printf("FIRE IN THE HOLE.....!!!\n\n");
                        boom(maze, bombX, bombY, total, size);
                    }
                    break;
                case 'W':
                    total[turn]--;
                    if(maze[bombX][bombY] == 'O')
                        maze[bombX][bombY] = PATH;
                    system("clear");
                    printf("KAMIKAZE ATTACK...!!!\n\n");
                    boom(maze, *x, *y, total, size);
                    move = 'D';
                    break;
                default: break;        
            }
        }while(maze[*x][*y]!=PATH && move!='D' && total[0]>0 && total[1]>0);
        if(maze[bombX][bombY] == 'O')
            maze[bombX][bombY] = PATH;
    }
    system("clear");
    
    //untuk mengecek siapa pemenangnya
    if(total[0]>total[1]) printf("The Winner is Player 1\n\n");
    else if(total[1]>total[0]) printf("The Winner is Player 2\n\n");
    else printf("The Game is DRAW...\n\n");
    view_maze(maze, size, 0, 0);
}

//efek ledakan bomb ataupun kamikaze
void boom(char **maze, int bombX, int bombY, int total[2], int size){
    int turn;
    //Ubah jadi bintang (sebagai efek ledakan) dengan ukuran 3x3
    //Kecuali jika objek yang dituju WALL
    maze[bombX][bombY] = '*';
    if(maze[bombX+1][bombY] != WALL){
        if(maze[bombX+1][bombY] != PATH){
            turn = maze[bombX+1][bombY];
            total[turn-1]--;
        }
        maze[bombX+1][bombY] = '*';
    }
    if(maze[bombX-1][bombY] != WALL){
        if(maze[bombX-1][bombY] != PATH){
            turn = maze[bombX-1][bombY];
            total[turn-1]--;
        }
        maze[bombX-1][bombY] = '*';
    }
    if(maze[bombX][bombY+1] != WALL){
        if(maze[bombX][bombY+1] != PATH){
            turn = maze[bombX][bombY+1];
            total[turn-1]--;
        }
        maze[bombX][bombY+1] = '*';
    }
    if(maze[bombX][bombY-1] != WALL){
        if(maze[bombX][bombY-1] != PATH){
            turn = maze[bombX][bombY-1];
            total[turn-1]--;
        }
        maze[bombX][bombY-1] = '*';
    }
    if(maze[bombX+1][bombY+1] != WALL){
        if(maze[bombX+1][bombY+1] != PATH){
            turn = maze[bombX+1][bombY+1];
            total[turn-1]--;
        }
        maze[bombX+1][bombY+1] = '*';
    }
    if(maze[bombX+1][bombY-1] != WALL){
        if(maze[bombX+1][bombY-1] != PATH){
            turn = maze[bombX+1][bombY-1];
            total[turn-1]--;
        }
        maze[bombX+1][bombY-1] = '*';
    }
    if(maze[bombX-1][bombY+1] != WALL){
        if(maze[bombX-1][bombY+1] != PATH){
            turn = maze[bombX-1][bombY+1];
            total[turn-1]--;
        }
        maze[bombX-1][bombY+1] = '*';
    }
    if(maze[bombX-1][bombY-1] != WALL){
        if(maze[bombX-1][bombY-1] != PATH){
            turn = maze[bombX-1][bombY-1];
            total[turn-1]--;
        }
        maze[bombX-1][bombY-1] = '*';
    }
    
    printf("\a");
    view_maze(maze, size, bombX, bombY);
    _sleep(1500);
    
    //Jadikan jalan objek yang sudah meledak tadi
    maze[bombX][bombY] = PATH;
    if(maze[bombX+1][bombY] == '*')
        maze[bombX+1][bombY] = PATH;
    if(maze[bombX-1][bombY] == '*')
        maze[bombX-1][bombY] = PATH;
    if(maze[bombX][bombY+1] == '*')
        maze[bombX][bombY+1] = PATH;
    if(maze[bombX][bombY-1] == '*')
        maze[bombX][bombY-1] = PATH;
    if(maze[bombX+1][bombY+1] == '*')
        maze[bombX+1][bombY+1] = PATH;
    if(maze[bombX+1][bombY-1] == '*')
        maze[bombX+1][bombY-1] = PATH;
    if(maze[bombX-1][bombY+1] == '*')
        maze[bombX-1][bombY+1] = PATH;
    if(maze[bombX-1][bombY-1] == '*')
        maze[bombX-1][bombY-1] = PATH;
}
