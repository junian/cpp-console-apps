#include <stdio.h>
#include <conio.h> //kbhit()
#include <stdlib.h> //rand() srand() system("cls") _sleep();
#include <time.h> //time(NULL)

//prototype prosedur menampilkan board
void showBoard(int, char*, char*, char*);

int main(){
    system("color f0");
    //mengubah background menjadi putih dan text menjadi hitam
    char r;
    do{
        //variabel
        //--------
        //keadaan board player, giliran, dan shortcut
        char p[2][100], turn = 1, warp[100];
        //icon tiap player (ASCII), posisi msg2 player
        char icon[2] = {1, 2}, pos[2] = {0,0};
        int i, j, k, 
            n, //ukuran board
            dice = 0,//nilai awal dadu
            adder = 1;//penambah/pengurang posisi
        char press;//utk menyimpan kondisi X ditekan atau tidak
        
        system("cls");//bersihkan layar
        printf("Snakes and Ladders Game\n=======================\n\n");
        printf("%c ==> Player\n%c ==> Computer\n\n", 1,2);
        
        //masukkan ukuran board NxN
        do{
            printf("Input Board Size [3-10]: "); 
            fflush(stdin);
            scanf("%d", &n);
        }while(n<=2 || n>10);
    
        //start random
        srand((unsigned)time(NULL));
        
        //initialize shortcut
        for(i=0; i<n*n; i++) warp[i]=0;
    
        for(i=0; i<(33*n*n)/100; i++){
            for(;;){
                j = (rand()%(n*n-2))+1;
                k = (rand()%(n*n-2))+1;
                if(j != k && warp[j] == 0 && warp[k] == 0){
                    warp[j] = k+1; //isi posisi warp[j] dengan shortcut
                    warp[k] = k+1;//isi shortcut dengan nilai sendiri
                        //agar tidak ada lebih dari satu shortcut menuju ke
                        //tempat yang sama
                    break;
                }
            }
        }
        
        //setiap shortcut yang berisi nilainya sendiri akan dihapus
        for(i=0; i<n*n; i++) 
            if(warp[i] == i+1)
                warp[i]=0;
                
        //initialize board   
        for(i=0; i<n*n; i++){
            p[0][i] = ' ';
            p[1][i] = ' ';
        }
        
        //masing2 player dimulai di posisi 0 atau start
        p[0][pos[0]] = icon[0];
        p[1][pos[1]] = icon[1];
    
        showBoard(n, p[0], p[1], warp);
    
        //proses mulai dari rolling dice hingga mencetak board
        do{
          printf("\n\nPress any key to roll the dice...");
          getch();
          turn = !(turn);//pergantian giliran, 0 utk user, 1 utk AI
          printf("\n\nRolling Dice\n%c Turn\n\nPress X to stop:  ", icon[turn]);
          if(turn==0){//randomize untuk player
            do{ 
                do{
                    dice = rand()%6+1;
                    printf("\b%d", dice);
                }while(!kbhit());
                press = getch();
            }while(press != 'x' && press != 'X');
            //jika x atau X ditekan maka rolling akan berhenti
          }else{//random khusus AI
            for(i=0; i<100; i++){
                dice = rand()%6+1;
                _sleep(10);
                printf("\b%d", dice);
            }
          }
          printf("\n");
          _sleep(1000);
          system("pause");//berhenti sesaat
          
          //animasikan pergerakan player untuk shortcut dan jalan biasa
          for(;;){
            while(dice > 0){
                p[turn][pos[turn]] = ' ';
                //jika melebihi maka bergerak mundur
                if(pos[turn]==n*n-1) adder*=-1; 
                pos[turn]+=adder;
                p[turn][pos[turn]] = icon[turn];
                showBoard(n, p[0], p[1], warp);
                dice--;
            }
            //kembalikan adder menjadi positif jika sekarang negatif
            if(adder<0) adder*=-1;
            if(warp[pos[turn]] != 0)//jika ditemukan shortcut
            //jika posisi sekarang lebih dari posisi shortcut
            //maka atur bergerak mundur
                if(pos[turn] > warp[pos[turn]]-1){
                    adder *= -1;
                    dice = pos[turn] - warp[pos[turn]]+1;
                //jika posisi skrng kurang dari posisi shortcut bergerak maju
                }else dice = warp[pos[turn]] - pos[turn]-1;
            else break;
            printf("\n\n%c found shortcut...", icon[turn]);
            _sleep(1500);
          }
           
        }while(pos[0]!=n*n-1 && pos[1]!=n*n-1);//jika ada yang sampai finish
        
        //tampilkan pemenangnya
        printf("\n\n%c WIN THE GAME...\n", icon[turn]);
        printf("\nWanna try again? [Y/N] ");
        do{
            r=getch();
        }while(r!='Y' && r!='y' && r!='N' && r!='n');
    }while(r=='y' || r=='Y');
    return 0;
}

//prosedur untuk menampilkan board dengan animasi
void showBoard(int n, char *p1, char *p2, char *warp){
    int i, j, k;
    j = n*n;
    system("cls");
    printf("Snakes and Ladders Game\n=======================\n\n");
    printf("%c ==> Player\n%c ==> Computer\n\n", 1,2);

    //cetak frame bagian atas
    printf("ษ");
    for(k = j-n; k<j; k++) printf("อออออออออออห");
    printf("\bป\nบ");
    
    for(i=n; i>=1; i--){
        
        if(i!=n){
            printf("ฬ");
            for(k = j-n; k<j; k++) printf("อออออออออออฮ");
            printf("\bน\nบ");
        }
        
        //setiap baris yang ganjil cetak board dari kiri ke kanan
        if(i % 2 == 1){
            for(k = j-n; k<j; k++){
                printf(" %3d ", k+1);
                if(*(warp+k) != 0)
                    printf("- %3.0d บ", *(warp+k));
                else
                    printf("      บ", *(warp+k));
            }    
            printf("\nบ");
            for(k = j-n; k<j; k++)
                printf("     %c     บ", *(p1+k));
            printf("\nบ");
            for(k = j-n; k<j; k++)
                printf("     %c     บ", *(p2+k));
       
        //setiap baris yang genap cetak board dari kanan ke kiri
        }else{
            for(k = j-1; k >= j-n; k--){
                printf(" %3d ", k+1);
                if(*(warp+k) != 0)
                    printf("- %3.0d บ", *(warp+k));
                else
                    printf("      บ", *(warp+k));
            }
            printf("\nบ");
            for(k = j-1; k >= j-n; k--)
                printf("     %c     บ", *(p1+k));
            printf("\nบ");
            for(k = j-1; k >= j-n; k--)
                printf("     %c     บ", *(p2+k));
        }
        printf("\n");
        j-=n;
    }
    
    //cetak frame bagian bawah
    printf("ศ");
    for(k=0; k<n; k++) printf("อออออออออออส");
    printf("\bผ");
    _sleep(250);
}
