#include <stdio.h>

#include <stdlib.h>
#include <time.h>

//mendeteksi apakah jawaban sudah penuh atau belum
int cek_end(char *board, int pos){
    for(int i=0; i<pos; i++)
      if(board[i] == '_') return 0; //jika masih ada '_' maka belum selesai
    return 1;
}

//tampilkan score
void view_score(int *score){
    printf("\nScore Board:");
    printf("\nPlayer 1\t%d", score[0]);
    printf("\nPlayer 2\t%d", score[1]);
    printf("\nComputer\t%d\n\n", score[2]);
}

//mengubah karakter kecil menjadi besar
char to_upper(char character){
    if(character >='a' && character <= 'z')
        character -= 32;
    return character;
}

//membandingkan string
int str_cmp(char *a, char *b){
    if(*a=='\0' && *b=='\0') return 0;
    *a = to_upper(*a);
    if(*a > *b) return 1;
    else if(*a++ < *b++) return -1;
    return str_cmp(a, b);
}

//menukar string
void swap_string(char **a, char **b){
    char *temp = *a;
    *a = *b;
    *b = temp;
}

//mengubah giliran
void next_turn(int *turn){
    if(*turn==0) *turn = 1;
    else if(*turn==1) *turn = 2;
    else *turn = 0;
}

//mecari panjang string
int str_length(char *string){
    int i=0;
    while(string[i]!='\0') i++;
    return i;
}

//mencari kata dalam kalimat dengan rekursi
int find_substring(char *string, char *substring, char *board){
    char word[25];
    int i=0, _counter=0;
    while(*(string+i)!=' ' && *(string+i)!='\0'){
        if(*(board+i) == '_') _counter++;
        word[i] = *(string+i);
        i++;
    }
    word[i] = '\0';
    if(str_cmp(substring, word)==0 && _counter!=0){
        for(i=0; i<str_length(substring); i++)
            *(board+i) = *(string+i);
        return 500;
    }
    else if(*(string+i)=='\0') return 0;
    else return find_substring(string+i+1, substring, board+i+1);
}

//guess 1 char dengan rekursi
int check_per_char(char *board, char *answer, char chr){
    if(*answer == '\0') return 0;
    board++;
    answer++;
    if(chr == *(answer-1)){
        if(*(board-1) == '_'){
            *(board-1) = *(answer-1);
            return (50 + check_per_char(board, answer, chr)); 
        }
    }
    return (0 + check_per_char(board, answer, chr));
}

//pilihan command jika user memilih B
void command_B(char *answer, char *board, int *score, int turn, int command){
    switch(command){
        case 1:
            printf("Guess One Char: ");
            char r;
            if(turn!=2){
                do{
                    fflush(stdin);
                    r=to_upper(getchar());
                }while(r<'A' || r>'Z');
            }else {//khusus untuk komputer
                _sleep(1500);
                do{
                    r = answer[(rand()%str_length(answer))]; 
                }while(r==' ');
            }
            printf("%c\n", r);
            score[turn] += check_per_char(board, answer, r);
            break;
        case 2:
            printf("View First Char\n");
            board[0] = answer[0];
            break;
        case 3:
            printf("View Last Char\n");
            board[str_length(answer)-1] = answer[str_length(answer)-1];
            break;
        case 4:
            printf("Guess One Word: ");
            char sub[25];
            if(turn != 2){
                fflush(stdin);
                scanf("%s", sub);
            }else{ //khusus komputer
                int i, j=0, _counter=0;
                for(i=0; answer[i]!='\0'; i++){
                    if(answer[i+1]=='\0'){
                        sub[j+1] = '\0';
                        break;
                    }
                    else if(answer[i]==' '){
                        if(_counter==0) {
                            j=-1;
                        }
                        else {
                            sub[j] = '\0';
                            break;
                        }
                    }else if(board[i]!='_'){
                        sub[j] = board[i];
                    }else {
                        _counter++;
                        do{
                            sub[j] = answer[rand()%str_length(answer)];
                        }while(sub[j]==' ');
                    }
                    j++;
                }
                printf("%s", sub);
            }
            score[turn] += find_substring(answer, sub, board);
            break;
        case 5:
            printf("Pass\n");
            break;
    }
    if(turn==2)
        _sleep(2000);
    else getchar();
}

//pemilihan command A atau B
void choose_command(char *answer, char *board, int *score, int turn){
    char command;
    int i;
    
    printf("A. Guess the Answer\n");
    printf("B. Random Action\n");
    printf("Choose a command [A/B]: ");
    
    if(turn!=2){
        do{
            fflush(stdin);
            command = getchar();
        }while(command!='a' && command!='A' && command!='b' && command!='B');
    }else{ //khusus komputer
        _sleep(1500);
        if(rand()%10>2) command = 'B';
        else command = 'A';
    }
    
    printf("%c\n\n", to_upper(command));
    switch(to_upper(command)){
        //Langsung tebak
        case 'A': 
            char tebak[25];
            printf("Your Guess: ");
            if(turn!=2){
                fflush(stdin);
                gets(tebak);
                getchar();
            }else{//khusus komputer
                for(i=0; i<str_length(answer); i++)
                    if(board[i]!='_') tebak[i]=board[i];
                    else {
                        do{
                            tebak[i] = answer[rand()%str_length(answer)];
                        }while(tebak[i]==' ');
                    }
                tebak[i]='\0';
                printf("%s", tebak);
                _sleep(3000);
            }
            if(str_cmp(tebak, answer)==0){
                for(i=0; answer[i]!='\0'; i++)
                    board[i] = answer[i];
                score[turn] += 1000;
            }
            break;
        
        //Random pilihan
        case 'B': 
            int rand_num;
            printf("Press X to stop:  ");
            do{
                if(turn!=2){
                    do{
                        rand_num = rand()%8;
                        if(rand_num<3)      rand_num=1; //37.5%
                        else if(rand_num<4) rand_num=2; //12.5%
                        else if(rand_num<5) rand_num=3; //12.5%
                        else if(rand_num<7) rand_num=4; //25%
                        else if(rand_num<8) rand_num=5; //12.5%
                        printf("\b%d", rand_num);
                    }while(!kbhit());
                    command = getchar();
                }else{ //khusus komputer
                    for(i=0; i<100; i++){
                        rand_num = rand()%8;
                        if(rand_num<3)      rand_num=1; //37.5%
                        else if(rand_num<4) rand_num=2; //12.5%
                        else if(rand_num<5) rand_num=3; //12.5%
                        else if(rand_num<7) rand_num=4; //25%
                        else if(rand_num<8) rand_num=5; //12.5%
                        printf("\b%d", rand_num);
                        _sleep(10);
                    }
                    command='X';
                }
            }while(command!='x' && command!='X');
            printf("\n");
            command_B(answer, board, score, turn, rand_num);    
            break;
    }
}

//membuat pertanyaan dan jawaban
void generate_questions(char **question, char **answer){
    question[0] = "Orang kaya yang mendirikan Microsoft";
    answer  [0] = "BILL GATES";
    
    question[1] = "Game gabungan raksasa animasi, Disney dan Square Enix";
    answer  [1] = "KINGDOM HEARTS";
    
    question[2] = "Pelantun Haruka Kanata";
    answer  [2] = "ASIAN KUNG FU GENERATION";
    
    question[3] = "Game keren sepanjang masa";
    answer  [3] = "FINAL FANTASY";
    
    question[4] = "Tokoh Akatsuki yang paling keren";
    answer  [4] = "UCHIHA ITACHI";
    
    question[5] = "Karakter FF VIII yang paling keren";
    answer  [5] = "SQUALL LEONHART";
    
    question[6] = "Makanan Favorit Naruto";
    answer  [6] = "MIE RAMEN";
    
    question[7] = "Ilmuwan paling Genius";
    answer  [7] = "ALBERT EINSTEIN";
    
    question[8] = "Karakter Naruto paling keren";
    answer  [8] = "HATAKE KAKASHI";
    
    question[9] = "Judul theme song Final Fantasy IX";
    answer  [9] = "MELODIES OF LIFE";
}

int main(){
    char **question, **answer;
    char *board;
    char r;
    
    int i, turn, quest, end;
    int score[3], rnd;
    
    question = (char**)malloc(sizeof(char*) * 10);
    answer   = (char**)malloc(sizeof(char*) * 10);
    generate_questions(question, answer);
    srand((unsigned) time(NULL));
    
    do{
        turn = 2; //giliran, 0 untuk player 1, 1 untuk player 2, 2 untuk komputer
        quest = 11;
        score[0] = 0;
        score[1] = 0;
        score[2] = 0;
        while(quest>1){//akan berjalan terus hingga 10 pertanyaan terjawab
            quest--;
            rnd = rand()%quest; //random pertanyaan
            board = (char*)malloc(sizeof(char) * str_length(answer[rnd]));
            
            //buat board yang berbentuk seperti _ _ _ _   _ _ _
            for(i=0; answer[rnd][i]!='\0'; i++)
                if(answer[rnd][i] != ' ') board[i] = '_';
                else board[i] = ' ';
            
            end = 0; 
            
            while(!end){//selama pertanyaan belum terjawab
                next_turn(&turn);
                system("clear");
                printf("Wheel of Fortune\n");
                printf("(C) 2008 by A Ninja @ Junior IT\n");
                printf("===============================\n");
                view_score(score);
                printf("Question #%d:\n\n%s\n\n", 11-quest, question[rnd]);
                for(i=0; answer[rnd][i]!='\0'; i++) printf("%c ", board[i]);
                printf("\n\n");
                switch(turn){
                    case 0:
                        printf("Player 1:\n");
                        break;
                    case 1:
                        printf("Player 2:\n");
                        break;
                    case 2:
                        printf("Computer:\n");
                        break;
                }
                choose_command(answer[rnd], board, score, turn);
                
                //menentukan apakah pertanyaan sudah terjawab atau belum
                if(end = cek_end(board, str_length(answer[rnd]))){
                    printf("\nYou Got It...");
                    printf("\nThe answer of Question #%d is\n", 11-quest);
                    for(i=0; answer[rnd][i]!='\0'; i++) printf("%c ", board[i]);
                    getchar();
                }
            }
            
            //question yang sudah dipakai dipindah ke belakang
            //agar tidak muncul di random berikutnya
            if(rnd!=quest-1){
                swap_string(&question[rnd], &question[quest-1]);
                swap_string(&answer[rnd], &answer[quest-1]);
            }
            free(board); 
        }
        printf("\n\nThe End\n");
        printf("\nWanna try again [Y/N]? ");
        do{
            r=getchar();
        }while(r!='Y' && r!='y' && r!='n' && r!='N');
    }while(r=='y' || r=='Y');
    
    return 0;
}
