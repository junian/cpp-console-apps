#include <stdio.h>

#include <stdlib.h>

//prototype fungsi pergerakan hanoi
void hanoi(int , int, int*, char , char , char , char*, char*, char*);

//prototype fungsi pencetak isi array masing-masing tower
void cetakDisk(char [50], char [50], char [50], int );

int main(){
    char r;
    do{
        char a[50], b[50], c[50]; //isi disk masing-masing tower
        int n, i, j, step=0; //mula-mula jumlah langkah dianggap 0
    
        system("clear"); //bersihkan layar
        printf("TOWER OF HANOI SOLVER\n");
        printf("=====================\n\n");
        do{
            printf("Input disk [1-50]: ");
            fflush(stdin);
            scanf("%d", &n);
        }while(n<=0 || n>50); //jika jumlah disk>50 atau <=0 maka input lagi
        
        //isi tower a dengan n disk, kosongi tower b dan c
        for(i=0; i<n; i++){
            a[i]=i+1;
            b[i]=0;
            c[i]=0;
        }
        
        //cetak isi masing-masing tower
        cetakDisk(a, b, c, n);
        
        printf("\nLet's move them to C\n\n");
        getchar();
        
        //gerakkan hanoi
        hanoi(n, n, &step, 'A', 'B', 'C', a, b, c);
        
        //cetak jumlah langkah
        printf("\nFinished in %d step(s)", step);
        printf("\n\nWanna try again [Y/N]? ");
        
        do{
           r=getchar();
        }while(r!='y' && r!='Y' && r!='n' && r!='N');
    }while(r=='y' || r=='Y'); 
    return 0;
}


void hanoi(int n, int jml, int *step, char src, char asst, char dest, 
            char*a, char*b, char*c)
{       
    if(n==0) return; //jika n mencapai 0 maka keluar
    
    //pindahkan disk bagian atas ke tower bantuan
    hanoi(n-1, jml, step, src, dest, asst, a, c, b);
    
    char temp;
    int i=0;
    
    //tukar isi array yang kosong teratas tower tujuan
    //dengan disk teratas tower asal
    while(*(a+i)==0 ) i++;
    int j=jml-1;
    while(*(c+j)!=0 ) j--;
    temp=*(a+i);
    *(a+i)=*(c+j);
    *(c+j)=temp;
    
    //cetak disk dengan pola-pola tertentu
    if(src=='C' && dest=='A') cetakDisk(c, b, a, jml);
    else if(src=='B' && dest=='A') cetakDisk(c, a, b, jml);
    else if(src=='A' && dest=='B') cetakDisk(a, c, b, jml);
    else if(src=='C' && dest=='B') cetakDisk(b, c, a, jml);
    else if(src=='B' && dest=='C') cetakDisk(b, a, c, jml);
    else if(src=='A' && dest=='C') cetakDisk(a, b, c, jml);
    
    *step += 1;//naikkan jumlah langkah
    
    //cetak langkah-langkahnya
    printf("\nStep %d, Move Disk %d from %c to %c\n", *step, n, src, dest);
    
    getchar();
    
    //pindahkan disk di tower bantuan ke tower tujuan
    hanoi(n-1, jml, step, asst, src, dest, b, a, c);
}

//cetak isi masing-masing array atau tower
void cetakDisk(char a[50], char b[50], char c[50], int n){
    for(int i=0; i<n; i++)
        printf("\n%2.0d\t%2.0d\t%2.0d", a[i], b[i], c[i]);
    printf("\n---\t---\t---\n A \t B \t C\n");    
}
