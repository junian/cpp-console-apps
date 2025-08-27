#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#define WALL  '#'
#define PATH  ' '

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

//Tampilkan maze
void view_maze(char **maze, int input){
    int i, j;
    for(i=0; i<input; i++){
        for(j=0; j<input; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
}

//buat maze
void generate_maze(char **maze, int input, int x, int y){
    int direction = rand()%4;//random arah
    int trial = 1; //banyak uji coba pengecekan jalan

    maze[x][y] = PATH;//jadikan baris x kolom y sebagai jalan
    system("clear");
    view_maze(maze, input);
    getchar();

    while(trial<=4){ //coba sampai 4 kali
        if(trial<=4 && direction==UP){ //cek posisi atas
            trial++;
            if(x-2>=1 && maze[x-2][y] == WALL){
                maze[x-1][y] = PATH;
                generate_maze(maze, input, x-2, y);
            }
            direction++;
        }
        if(trial<=4 && direction==DOWN){ //cek posisi bawah
            trial++;
            if(x+2<input && maze[x+2][y] == WALL){
                maze[x+1][y] = PATH;
                generate_maze(maze, input, x+2, y);
            }
            direction++;
        }
        if(trial<=4 && direction==LEFT){//cek posisi kiri
            trial++;
            if(y-2>=1 && maze[x][y-2] == WALL){
                maze[x][y-1] = PATH;
                generate_maze(maze, input, x, y-2);
            }
            direction++;
        }
        if(trial<=4 && direction==RIGHT){//cek posisi kanan
            trial++;
            if(y+2<input && maze[x][y+2] == WALL){
                maze[x][y+1] = PATH;
                generate_maze(maze, input, x, y+2);
            }
            direction++;
        }
        direction = UP;
    }
}

int main(){
    char **maze;
    int n, input, i, j;

    srand((unsigned) time(NULL));

    //Masukkan ukuran maze
    do{
        system("clear");
        printf("MAZE CREATOR\n\nInput Size (0 ~ 30): ");
        fflush(stdin);
        scanf("%d", &n);
    }while(n<0 || n>30);

    if(n==0){
        printf("#");
        getchar();
        return 0;
    }

    input = 2*n+1;

    //buat maze kosong input x input
    maze = (char**)malloc(sizeof(char*) * input);

    //Jadikan semuanya cell tembok
    for(i=0; i<input; i++){
        maze[i] = (char*)malloc(sizeof(char) * input);
        for(j=0; j<input; j++)
            maze[i][j] = WALL;
    }

    //random start
    i = 2*(rand()%n)+1;
    j = 2*(rand()%n)+1;

    //buat maze
    generate_maze(maze, input, i, j);
    view_maze(maze, input);

    for(i=input-1; i>=0; i--){
        free(maze[i]);
    }

    free(maze);

    getchar();
    return 0;
}
