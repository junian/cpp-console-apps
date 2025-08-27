#include <stdio.h>

#include <stdlib.h>

#define WALL    -2 //tembok maze
#define MOUSE   -4 //tikus
#define PATH    -8 //jalan yang dilalui tikus
#define CHEESE   1 //keju

#define ROW    13
#define COLUMN 11
#define JUMLAH 4

typedef struct koordinat{
    int x;
    int y;
}KOORD;

//Tampilkan maze
void view_maze(int maze[ROW][COLUMN]){
    int i, j;
    for(i=0; i<ROW; i++){
        for(j=0; j<COLUMN; j++) 
            switch(maze[i][j]){
                case WALL   : printf("#");     break;
                case MOUSE  : printf("%c", 1); break;
                case CHEESE : printf("%c", 3); break;
                case PATH   : printf("*");     break;
                default     : printf(" ");     break;
            }
        printf("\n");
    }
}

void smelling(int maze[ROW][COLUMN], KOORD listA[JUMLAH], KOORD listB[JUMLAH], int number){
    int i, x=0;
    
    //cek apakah list A semuanya kosong..???
    for(int i=0; i<JUMLAH; i++) 
        if(listA[i].x==-1) x++;
        
    //jika semuanya kosong maka hentikan rekursi
    if(x==JUMLAH)return;
    
    //kosongkan semua isi list B
    for(i=0; i<JUMLAH; i++) listB[i].x = -1;
    
    x = -1;
    
    //sebarkan bau ke empat arah yang mungkin
    for(i=0; i<JUMLAH; i++){
        if(listA[i].x != -1 && maze[listA[i].y-1][listA[i].x] == 0){
            x++;
            maze[listA[i].y-1][listA[i].x] = number;
            listB[x].y = listA[i].y-1;
            listB[x].x = listA[i].x;
        }
        if(listA[i].x != -1 && maze[listA[i].y+1][listA[i].x] == 0){
            x++;
            maze[listA[i].y+1][listA[i].x] = number;
            listB[x].y = listA[i].y+1;
            listB[x].x = listA[i].x;
        }
        if(listA[i].x != -1 && maze[listA[i].y][listA[i].x-1] == 0){
            x++;
            maze[listA[i].y][listA[i].x-1] = number;
            listB[x].y = listA[i].y;
            listB[x].x = listA[i].x-1;
        }
        if(listA[i].x != -1 && maze[listA[i].y][listA[i].x+1] == 0){
            x++;
            maze[listA[i].y][listA[i].x+1] = number;
            listB[x].y = listA[i].y;
            listB[x].x = listA[i].x+1;
        }
    }
    
    //sebarkan bau dan tukar listA listB
    smelling(maze, listB, listA, number+1);
}

int main(){
    int n;
    KOORD mouse, cheese;
    KOORD listA[JUMLAH], listB[JUMLAH];
    char r;
    do{
        //initialize maze
        int maze[ROW][COLUMN] = {-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
                                 -2,  0, -2,  0,  0, -2,  0, -2,  0,  0, -2,
                                 -2,  0, -2, -2,  0,  0,  0, -2,  0,  0, -2,
                                 -2,  0,  0, -2,  0, -2,  0, -2, -2,  0, -2,
                                 -2,  0,  0,  0,  0, -2,  0,  0,  0,  0, -2,
                                 -2, -2, -2, -2, -2, -2,  0, -2, -2, -2, -2,
                                 -2,  0,  0,  0,  0, -2,  0,  0, -2,  0, -2,
                                 -2,  0,  0, -2,  0, -2, -2,  0, -2,  0, -2,
                                 -2,  0, -2, -2,  0,  0,  0,  0, -2,  0, -2,
                                 -2,  0,  0, -2,  0, -2, -2, -2, -2,  0, -2,
                                 -2, -2,  0, -2,  0,  0,  0,  0, -2,  0, -2,
                                 -2,  0,  0, -2,  0,  0, -2,  0,  0,  0, -2,
                                 -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2};
        system("clear");
        view_maze(maze);
        printf("\nRange:\n");
        printf("x -> 1 - %d\n", COLUMN-2);
        printf("y -> 1 - %d\n", ROW-2);
    
        //input koordinat tikus
        do{
           printf("Input Mouse  Coord (x, y): ");
           fflush(stdin);
           scanf("%d %d", &mouse.x, &mouse.y);
        }while(mouse.x<=0 || mouse.y<=0 || mouse.x>COLUMN-2 || mouse.y >ROW-2 ||
            maze[mouse.y][mouse.x] != 0);
    
        //input koordinat keju
        do{
            printf("Input Cheese Coord (x, y): ");
            fflush(stdin);
            scanf("%d %d", &cheese.x, &cheese.y);
        }while(cheese.x<=0 || cheese.y<=0 || cheese.x>COLUMN-2 || cheese.y >ROW-2
           || maze[cheese.y][cheese.x] != 0 || 
           (cheese.x == mouse.x && cheese.y == mouse.y));
    
        //letakkan keju di maze
        maze[cheese.y][cheese.x] = CHEESE;
    
        //kosongkan semua list
        for(n=0; n<JUMLAH; n++)
        {
            listA[n].x = -1;
            listB[n].x = -1;
        }
        //mula-mula listA[0] = koordinat cheese
        listA[0].x = cheese.x;
        listA[0].y = cheese.y;
    
        //sebarkan bau keju
        smelling(maze, listA, listB, CHEESE+1);
    
        //re-use cheese untuk koordinat alamat awal mouse
        cheese = mouse;
    
        //telusuri maze dengan mencari angka yang menurun
        while(1){
            if(maze[mouse.y-1][mouse.x] - maze[mouse.y][mouse.x] == -1){
                maze[mouse.y][mouse.x] = PATH;
                mouse.y--;
            }
            else if(maze[mouse.y+1][mouse.x] - maze[mouse.y][mouse.x] == -1){
                maze[mouse.y][mouse.x] = PATH;
                mouse.y++;
            }
            else if(maze[mouse.y][mouse.x-1] - maze[mouse.y][mouse.x] == -1){
                maze[mouse.y][mouse.x] = PATH;
                mouse.x--;
            }
            else if(maze[mouse.y][mouse.x+1] - maze[mouse.y][mouse.x] == -1){
                maze[mouse.y][mouse.x] = PATH;
                mouse.x++;
            }
            else break;
        }
        
        //tampilkan hasil
        system("clear");
        maze[cheese.y][cheese.x] = MOUSE;
        view_maze(maze);
    
        printf("\nIngin mengulang [Y/N]? ");
        do{
            r=getchar();
        }while(r!='y' && r!='Y' && r!='n' && r!='N');
    }while(r=='y' || r=='Y');
    return 0;
}
