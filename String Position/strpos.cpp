#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int strpos(char *string, char *substring){
    int i, j;
    for(i=0; string[i]!='\0'; i++){
        //mula-mula dicek apakah ada karakter dalam string yang sama
        //dengan huruf awal substring
        if(string[i] == substring[0]){
            //jika ada lanjutkan hingga bertemu '\0'
            for(j=1; string[i+j]!='\0' && substring[j]!='\0'; j++){
                if(string[i+j]!=substring[j]) break;
            }
            //jika sampai pada karakter '\0' di substring
            //simpan posisi huruf awal
            if(substring[j]=='\0') return i;
        }
    }
    //jika tidak ada return -1
    return -1;
}

int main(){
    char r, string[256], substring[256];    
    int x;
    do{
        system("cls");
        printf("Program StrPos\n==============\n\n");
        printf("Masukkan String: ");
        fflush(stdin);
        gets(string);
        fflush(stdin);
        printf("Masukkan Sub String: ");
        gets(substring);
        x = strpos(string, substring);
        if(x>-1)
            printf("\"%s\" berada di dalam \"%s\" di posisi %d", 
               substring, string, x);
        else
            printf("\"%s\" tidak ditemukan di dalam \"%s\"", substring, string);
        printf("\nWanna try again [Y/N]? ");
        do{
            r=getch();
        }while(r!='Y' && r!='y' && r!='n' && r!='N');
    }while(r=='y' || r=='Y');
    return 0;
}
