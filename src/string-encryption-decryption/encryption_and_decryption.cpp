#include <stdio.h>

#include <stdlib.h>

#define ENCRYPT '1'
#define DECRYPT '2'
#define EXIT    '3'
#define CLS     '4'

//mencari panjang string
int str_length(char *string);
//mencari posisi karakter dalam suatu string
int get_pos(char *string, char charc);
//menukar karakter
void swap(char *a, char *b);
//membuat kumpulan text chiper
void create_chiper_list(char *str_base, char *str_chiper, char *pass);
//lakukan enkripsi / dekripsi
char *junicrypt(char *string, char *str_base, char *str_chiper, char command);

int main(){
    int i, n;
    char command, kalimat[256], password[256];
    char chiper_list[87], base_list[87] = " !@#$%^&*()_+-=,./;'<>?:";
    
    //Buat Base List dengan menambahkan A..Z, a..z, 0..9
    i = str_length(base_list);
    for(n = 'A'; n <= 'Z'; n++) base_list[i++] = n;
    for(n = 'a'; n <= 'z'; n++) base_list[i++] = n;
    for(n = '0'; n <= '9'; n++) base_list[i++] = n;
    base_list[i] = '\0';
    
    do{
        system("clear");
        printf("Encryption and Decryption Application\n");
        printf("=====================================");
        do{
            printf("\n\nWhat do you want to do?\n");
            printf("1. Encrypt Text\n");
            printf("2. Decrypt Text\n");
            printf("3. Clear Sreen\n");
            printf("4. Exit\n");
            printf("Choose a command [1-4]: ");
            do{
                command = getchar(); 
            }while(command<'1' || command>'4');
            if(command=='3' || command=='4') break;
            printf("%c", command);
            printf("\n\nInput Text:\n");
            fflush(stdin);
            gets(kalimat);
            printf("\nInput Password:\n");
            fflush(stdin);
            gets(password);
            create_chiper_list(base_list, chiper_list, password);
            printf("\nResult:\n");
            puts(junicrypt(kalimat, base_list, chiper_list, command));
        }while(command=='1' || command=='2');
    }while(command=='3');
    return 0;
}

int str_length(char *string){
    int x = 0;
    while(string[x] != '\0') x++;
    return x;
}

int get_pos(char *string, char charc){
    int x = 0;
    do{
        if(string[x] == charc) return x;
        x++;
    }while(string[x] != '\0');
    return -1;
}

void swap(char *a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

//membuat tabel str_chiper dengan metode random berdasarkan password
void create_chiper_list(char *str_base, char *str_chiper, char *pass){
    int x = 0, i;
    char temp[87];
    for(i=0; i<=str_length(str_base); i++) temp[i] = str_base[i];
    for(i=0; i<str_length(pass); i++) x += (int) pass[i];
    srand(x);
    str_chiper[86] = '\0';
    for(i=str_length(temp); i>=1; i--){
        x = rand()%i;
        str_chiper[i-1] = temp[x];
        swap(&temp[i-1], &temp[x]);
    }
}

//enkripsi/dekripsi menggunakan metode substitusi
//berdasarkan tabel str_base dan str_chiper
char *junicrypt(char *string, char *str_base, char *str_chiper, char command){
  char *crypt = (char*) malloc(sizeof(char) * (str_length(string)+1));
  int pos, x = 0;
  if(command == ENCRYPT){
     do{
        pos = get_pos(str_base, string[x]);
        if(pos>-1) crypt[x] = str_chiper[pos];
        else crypt[x] = string[x];
        x++;
    }while(string[x-1] != '\0');
  }else if(command == DECRYPT){
     do{
        pos = get_pos(str_chiper, string[x]);
        if(pos>-1) crypt[x] = str_base[pos];
        else crypt[x] = string[x];
        x++;
     }while(string[x-1] != '\0');
  }
  return crypt;
}
