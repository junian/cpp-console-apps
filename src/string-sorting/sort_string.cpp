#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define ZERO 0

//mengubah huruf kecil jadi besar tanpa mengubah
//string yang asli (tdk seperti strupr)
char *strupper(char *s);
//menukar alamat memori string
void swap_string(char **, char **);
//metode sorting dengan algoritma quicksort
void quicksort(char **, int, int);

int main(){
    char r;
    char **s;
    int  i, j, n;
    
    do{
        system("clear");
        printf("String Sorter\n=============\n\n");
        
        //input jumlah string
        do{
            printf("Input Jumlah String: ");
            fflush(stdin);
            scanf("%d", &n);
        }while(!(n >= 0));
        
        printf("\n");
        s = (char**) malloc(sizeof(char*) * n);
        for(i=0; i<n; i++)
            s[i] = (char*) malloc(sizeof(char)*256);
    
        //Input string
        for(i=0; i<n; i++){
            printf("#%d: ", i+1);
            fflush(stdin);
            gets(s[i]);
        }
        
        //urutkan data    
        quicksort(s, ZERO, n-1);
        printf("\nSorted String:\n\n");
        for(i=0; i<n; i++) printf("#%d: %s\n", i+1, s[i]);
        free(s);
        
        printf("\nIngin Mengulang [Y/N]? ");
        do{
            r=getchar();
        }while(r!='Y' && r!='y' && r!='n' && r!='N');
    }while(r=='y' || r=='Y');
    
    return 0;
}

char *strupper(char *s){
    char *x;
    x = (char*) malloc(sizeof(char) * strlen(s) + 1);
    strcpy(x, s);
    strupr(x);
    return x;
}

void swap_string(char **s1, char **s2){
    char *t;
    t = *s1;
    *s1 = *s2;
    *s2 = t;
}

void quicksort(char **data, int left, int right){
    //jika batas kiri >= batas kanan maka hentikan rekursi
    if(left >= right) return;
    //pivot dianggap sebagai elemen paling kiri
    int pivot = left, pointer = right;
    //arah pointer mula-mula dari kanan ke kiri
    int pointerMove = -1, temp, pos;
    //selama pivot tidak bertemu pointer
    while(pivot != pointer){
        pos = strcmp(strupper(data[pivot]), strupper(data[pointer]));
        if((pos>0 && pointerMove == -1) || (pos<0 && pointerMove == +1)){
               swap_string(&data[pivot], &data[pointer]);
               temp = pivot;
               pivot = pointer;
               pointer = temp;
               pointerMove *= -1; //ubah arah pointer
        }
        pointer += pointerMove; //gerakkan pointer
    }
    quicksort(data, left, pivot - 1);
    quicksort(data, pivot + 1, right);
}
