#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define CTRL_Z 26

int main()
{
    FILE *ex_file;
    char filename[256];
    char r;
    
    do{
        system("cls");
        printf("1. Baca File\n");
        printf("2. Tulis File\n");
        printf("3. Baca dan tulis file\n\n");
        printf("Masukkan pilihan: ");
        
        do{
            r=getch();
        }while(r<'1' || r>'6');
        
        printf("%c\n\n", r);
        switch(r){
            case '1': printf("Masukkan nama file yang akan dibaca: ");
                      fflush(stdin);
                      gets(filename);
                      if((ex_file = fopen(filename, "rt")) == NULL)
                      {
                          printf("\nColudn't Open File..!!!");
                      }else{
                          while((r=fgetc(ex_file))!= EOF) putchar(r);
                          fclose(ex_file);
                      }
                      break;
          
            case '2': printf("Masukkan nama file yang akan ditulis: ");
                      fflush(stdin);
                      gets(filename);
                      if((ex_file = fopen(filename, "wt")) == NULL)
                      {
                          printf("\nColudn't Open File..!!!");
                      }else{
                          while((r=getche())!= CTRL_Z) fputc(r, ex_file);
                          fclose(ex_file);
                      }
                      break;
          
            case '3': printf("Masukkan nama file yang akan dibaca & ditulis: ");
                      fflush(stdin);
                      gets(filename);
                      if((ex_file = fopen(filename, "at+")) == NULL)
                      {
                          printf("\nColudn't Open File..!!!");
                      }else{
                          while((r=fgetc(ex_file))!= EOF) putchar(r);
                          while((r=getche())!= CTRL_Z) fputc(r, ex_file);
                          fclose(ex_file);
                      }
                      break;
        }
        printf("\nIngin mengulang...?? [Y/N] ");
        
        do{
            r=getch();
        }while(r!='y' && r!='Y' && r!='n' && r!='N');
    }while(r=='y' || r=='Y');
    return 0;
}
