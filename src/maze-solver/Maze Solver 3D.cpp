#include <stdio.h>

#include <stdlib.h>

#define LEVEL   5
#define ROW    13
#define COLUMN 11

#define MOUSE   -2
#define CHEESE   1
#define PATH    -4
#define WALL    -1

typedef struct
{
    int x;
    int y;
    int z;
}KOORD;

void traceback(int maze[LEVEL][ROW][COLUMN], KOORD mouse, int label);
void view_maze(int maze[LEVEL][ROW][COLUMN]);
bool check_next(int maze[LEVEL][ROW][COLUMN], KOORD *ring_next, int *nring_next, int x, int y, int z, int label);
bool region_grow(int maze[LEVEL][ROW][COLUMN], KOORD *ring_now, int *nring_now, KOORD *ring_next, int *nring_next, int label);

int main()
{
    KOORD mouse, cheese;
    KOORD *ring_now, *ring_next, *ring_temp;
    int nring_now, nring_next;
    int label;
    int maze[LEVEL][ROW][COLUMN] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1,  0,  0, -1,
                                    -1,  0, -1, -1,  0,  0,  0, -1,  0,  0, -1,
                                    -1,  0,  0, -1,  0, -1,  0, -1, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1,  0, -1, -1, -1, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1,  0, -1,  0, -1,
                                    -1,  0, -1, -1,  0,  0,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1, -1, -1,  0, -1,
                                    -1, -1,  0, -1,  0,  0,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0,  0, -1,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1,  0,  0, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1, -1,  0, -1,
                                    -1,  0, -1, -1,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,
                                    -1, -1, -1, -1, -1, -1,  0, -1, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1,  0, -1,  0, -1,
                                    -1,  0, -1, -1,  0,  0, -1,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1, -1, -1,  0, -1,
                                    -1, -1, -1, -1,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1,  0,  0, -1,
                                    -1,  0, -1, -1,  0,  0,  0, -1,  0,  0, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1, -1,  0, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1,  0,  0, -1,
                                    -1,  0, -1, -1,  0, -1,  0, -1, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0, -1, -1,  0, -1, -1,  0,  0,  0, -1,
                                    -1,  0, -1,  0,  0,  0,  0,  0, -1,  0, -1,
                                    -1,  0, -1,  0, -1, -1, -1, -1, -1, -1, -1,
                                    -1,  0, -1,  0, -1,  0,  0,  0, -1,  0, -1,
                                    -1,  0,  0,  0,  0,  0, -1,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1,  0,  0, -1,
                                    -1,  0, -1, -1,  0,  0,  0, -1,  0,  0, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1,  0, -1, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1,  0, -1,  0, -1,
                                    -1, -1,  0, -1,  0,  0,  0,  0, -1, -1, -1,
                                    -1,  0,  0, -1,  0, -1, -1,  0, -1,  0, -1,
                                    -1, -1,  0, -1,  0, -1, -1,  0, -1, -1, -1,
                                    -1,  0,  0, -1,  0,  0,  0,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1,  0,  0, -1,
                                    -1,  0, -1, -1,  0,  0,  0, -1,  0,  0, -1,
                                    -1,  0, -1,  0,  0, -1,  0, -1, -1,  0, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1,  0, -1, -1, -1, -1,
                                    -1,  0,  0,  0,  0, -1,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1,  0, -1,  0, -1,
                                    -1,  0, -1, -1,  0,  0,  0,  0,  0,  0, -1,
                                    -1,  0,  0, -1,  0, -1, -1, -1, -1, -1, -1,
                                    -1, -1,  0, -1,  0,  0,  0,  0, -1,  0, -1,
                                    -1,  0,  0, -1,  0,  0, -1,  0,  0,  0, -1,
                                    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                   };
    
    printf("3D MAZE SOLVER by A Ninja @ Junior IT\n");
    printf("=====================================\n\n");
    
    //input koordinat tikus
    do{
        printf("Input mouse Coordinate (x, y, z): ");
        fflush(stdin);
        scanf("%d,%d,%d", &mouse.x, &mouse.y, &mouse.z);
    }while(mouse.x<0 || mouse.x>=COLUMN || mouse.y<0 || mouse.y>=ROW || mouse.z<0 || mouse.z>=LEVEL 
          || maze[mouse.z][mouse.y][mouse.x]!=0);
    
    //input koordinat keju
    do{    
        printf("Input cheese Coordinate (x, y, z): ");
        fflush(stdin);
        scanf("%d,%d,%d", &cheese.x, &cheese.y, &cheese.z);
    }while(cheese.x<0 || cheese.x>=COLUMN || cheese.y<0 || cheese.y>=ROW || cheese.z<0 || cheese.z>=LEVEL 
           || maze[cheese.z][cheese.y][cheese.x]!=0);
    
    label = CHEESE;
    ring_now = (KOORD*) malloc(sizeof(KOORD)*2*(LEVEL+ROW+COLUMN));
    ring_next = (KOORD*) malloc(sizeof(KOORD)*2*(LEVEL+ROW+COLUMN));
    maze[mouse.z][mouse.y][mouse.x] = MOUSE;
    maze[cheese.z][cheese.y][cheese.x] = label;
    nring_now = 1;
    nring_next = 0;
    ring_now[0].x = cheese.x;
    ring_now[0].y = cheese.y;
    ring_now[0].z = cheese.z;
    
    //menyebarkan region dari keju
    while(true)
    {
        if(region_grow(maze, ring_now, &nring_now, ring_next, &nring_next, ++label)){
            traceback(maze, mouse, label);
            break;
        }
        
        //indikator jalan buntu
        if(nring_next == 0){
            printf("Jalannya Buntu....\n");
            break;
        }
        ring_temp = ring_now;
        ring_now  = ring_next;
        ring_next = ring_temp;
        
        nring_now = nring_next;
        nring_next = 0;         
    }
    
    view_maze(maze);
    getchar();
    return 0;
}

//untuk menyebarkan region keju
bool region_grow(int maze[LEVEL][ROW][COLUMN], KOORD *ring_now, int *nring_now, KOORD *ring_next, int *nring_next, int label)
{
    int i, x, y, z;
    for(i=0; i<*nring_now; i++)
    {
        x = ring_now[i].x;
        y = ring_now[i].y;
        z = ring_now[i].z;
        
        if(check_next(maze, ring_next, nring_next, x-1, y, z, label))
            return true;
        if(check_next(maze, ring_next, nring_next, x+1, y, z, label))
            return true;
        if(check_next(maze, ring_next, nring_next, x, y-1, z, label))
            return true;
        if(check_next(maze, ring_next, nring_next, x, y+1, z, label))
            return true;
        if(check_next(maze, ring_next, nring_next, x, y, z-1, label))
            return true;
        if(check_next(maze, ring_next, nring_next, x, y, z+1, label))
            return true;
    }
    return false;
}

//fungsi untuk mengecek tetangganya
bool check_next(int maze[LEVEL][ROW][COLUMN], KOORD *ring_next, int *nring_next, int x, int y, int z, int label)
{
    if(z<0 || z>=LEVEL)
        return false;
    if(maze[z][y][x]==MOUSE)
        return true;
    if(maze[z][y][x]==0)
    {
        maze[z][y][x] = label;
        ring_next[*nring_next].x = x;
        ring_next[*nring_next].y = y;
        ring_next[*nring_next].z = z;
        (*nring_next)++;
    }
    return false;
}

//fungsi untuk menampilkan maze
void view_maze(int maze[LEVEL][ROW][COLUMN])
{
    int i, j, k;
    for(i=0; i<LEVEL; i++)
    {
        printf("\nLEVEL %d\n", i);
        for(j=0; j<ROW; j++)
        {
            for(k=0; k<COLUMN; k++)
            {
                if(maze[i][j][k] == WALL)
                    printf("#");
                else if(maze[i][j][k] == PATH)
                    printf("*");
                else if(maze[i][j][k] == MOUSE)
                    printf("M");
                else if(maze[i][j][k] == CHEESE)
                    printf("C");
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
}


//fungsi untuk trcaeback dari tikus ke keju
void traceback(int maze[LEVEL][ROW][COLUMN], KOORD mouse, int label)
{
    int x, y, z;
    
    x = mouse.x;
    y = mouse.y;
    z = mouse.z;
    
    while(true)
    {
        --label;
        printf("(x, y, z): %d, %d, %d\n", x, y, z);
        if(maze[z][y][x-1]==label)
            x = x-1;                    
        else if(maze[z][y][x+1]==label)
            x = x+1;
        else if(maze[z][y-1][x]==label)
            y = y-1;
        else if(maze[z][y+1][x]==label)
            y = y+1;
        else if(z>0 && maze[z-1][y][x]==label)
            z = z-1;
        else if(z<LEVEL-1 && maze[z+1][y][x]==label)
            z = z+1;
        
        if(label==0) return;
        else if(label!=1) maze[z][y][x] = PATH;
    }  
}      
