#include <stdio.h>
#include <stdlib.h>

//mencari jumlah kemungkinan suatu titik untuk menuju ke titik lain sesuai
//langkah kuda
int get_chance(char **board, int x, int y){
    int chance = 0;
    
    if(x+2<8  && y+1<8  && board[x+2][y+1]==' ') chance++;
    if(x+2<8  && y-1>=0 && board[x+2][y-1]==' ') chance++;
    if(x-2>=0 && y+1<8  && board[x-2][y+1]==' ') chance++;
    if(x-2>=0 && y-1>=0 && board[x-2][y-1]==' ') chance++;
    
    if(y+2<8  && x+1<8  && board[x+1][y+2]==' ') chance++;
    if(y+2<8  && x-1>=0 && board[x-1][y+2]==' ') chance++;
    if(y-2>=0 && x+1<8  && board[x+1][y-2]==' ') chance++;
    if(y-2>=0 && x-1>=0 && board[x-1][y-2]==' ') chance++;
    
    return chance;
}

//keputusan kuda untuk bergerak berikutnya
//dengan cara mencari kemungkinan gerak suatu titik berikutnya
//yang terendah
void next_step(char **board, int *posX, int*posY){
    int chance = 8;
    int x = *posX;
    int y = *posY;
    
    if(x+2<8  && y+1<8  && board[x+2][y+1]==' '){
        if(get_chance(board, x+2, y+1) < chance){
            chance = get_chance(board, x+2, y+1);
            *posX = x + 2;
            *posY = y + 1;
        }
    }
    
    if(x+2<8  && y-1>=0 && board[x+2][y-1]==' '){
        if(get_chance(board, x+2, y-1) < chance){
            chance = get_chance(board, x+2, y-1);
            *posX = x + 2;
            *posY = y - 1;
        }
    }
    
    if(x-2>=0 && y+1<8  && board[x-2][y+1]==' '){
        if(get_chance(board, x-2, y+1) < chance){
            chance = get_chance(board, x-2, y+1);
            *posX = x - 2;
            *posY = y + 1;
        }
    }
    
    if(x-2>=0 && y-1>=0 && board[x-2][y-1]==' '){
        if(get_chance(board, x-2, y-1) < chance){
            chance = get_chance(board, x-2, y-1);
            *posX = x - 2;
            *posY = y - 1;
        }
    }
    
    if(y+2<8  && x+1<8  && board[x+1][y+2]==' '){
        if(get_chance(board, x+1, y+2) < chance){
            chance = get_chance(board, x+1, y+2);
            *posY = y + 2;
            *posX = x + 1;
        }
    }
    
    if(y+2<8  && x-1>=0 && board[x-1][y+2]==' '){
        if(get_chance(board, x-1, y+2) < chance){
            chance = get_chance(board, x-1, y+2);
            *posY = y + 2;
            *posX = x - 1;
        }
    }
    
    if(y-2>=0 && x+1<8  && board[x+1][y-2]==' '){
        if(get_chance(board, x+1, y-2) < chance){
            chance = get_chance(board, x+1, y-2);
            *posY = y - 2;
            *posX = x + 1;
        }
    }
    
    if(y-2>=0 && x-1>=0 && board[x-1][y-2]==' '){
        if(get_chance(board, x-1, y-2) < chance){
            chance = get_chance(board, x-1, y-2);
            *posY = y - 2;
            *posX = x - 1;
        }
    }
    
    
}

//tampilkan board
void view_board(char **board){
    printf("�������������������������������ͻ\n");
    for(int i=0; i<8; i++){
        printf("�");
        for(int j=0; j<8; j++)
            printf(" %c �", board[i][j]);
        if (i<7) printf("\n�������������������������������͹\n");
    }
    printf("\n�������������������������������ͼ\n");
}

//gerakkan kuda hingga 64 langkah
void move_knight(char **board, int *posX, int *posY, char token){
    system("clear");
    printf("x: %d  y: %d\n", *posX, *posY);
    board[*posX][*posY] = token;
    next_step(board, posX, posY);
    board[*posX][*posY] = '$';
    
    token++;
    if(token=='9'+1) token = 'A';
    else if(token=='Z'+1) token = 'a';
    else if(token=='z'+1) token = '&';
    view_board(board);
    getchar();
    
    if (token == '&'+1)
		return;
    else move_knight(board, posX, posY, token);
}

int main(){
    char r;
    char **board;
    int i, j;
    do{  
        system("clear");
        board = (char**)malloc(sizeof(char*)*8);
        for(i=0; i<8; i++){
            board[i] = (char*)malloc(sizeof(char) * 8);
            for(j=0; j<8; j++) board[i][j] = ' ';
        }
        
        scanf("%d%d", &i, &j); 
        
        board[i][j] = '$';
        view_board(board);
        getchar();
        
        move_knight(board, &i, &j, '0');
        
        printf("\nIngin mengulang [Y/N]? ");
        do{
            r = getchar();
        }while(r!='y' && r!='Y' && r!='n' && r!='N');
        for(i=7; i>=0; i--) free(board[i]);
        free(board);
    }while(r=='Y' || r=='y');
}
