#include <stdio.h>
#include <stdlib.h>

//fungsi untuk memfilter kata
void filter(char kalimat[512], char **word, int total_words);
//menukar string
void swap_string(char **s1, char **s2);
//sorting string
void quicksort(char **data, int left, int right);
//metode pencarian string dengan binary search
//yang direturn adalah indeks dari string yang cocok
//jika tidak ada return -1
int bin_search(char *kalimat, char **word, int left, int right);
//membandingkan string
int strcmp(char *a, char *b);

int main()
{
    int total_case, total_words, i;
    char kalimat[512], **word;
    
    //innput jumlah test case
    scanf("%d\n", &total_case);
    
    do
    {
        //input jumlah kata yang difilter
        scanf("%d\n", &total_words);
        word = (char**) malloc(sizeof(char*) * total_words);
        //input kata yang difilter
        for(i=0; i<total_words; i++)
        {
            word[i] = (char*)malloc(sizeof(char) * 25);
            gets(word[i]);
        }
        //sort kata-kata yang disorting
        quicksort(word, 0, total_words-1);
        gets(kalimat);
        //filter kalimat
        filter(kalimat, word, total_words);
        printf("%s\n", kalimat);
        for(i=total_words-1; i>=0; i--) free(word[i]);
        free(word);
        total_case--;
    }
    while(total_case>0);
    return 0;
}

//mencari string yang cocok dengan binary search
int bin_search(char *kalimat, char **word, int left, int right){
    if(right<left) return -1;
    char temp[512];
    int i, compare, 
        mid = (right+left)/2;
    for(i=0; *(kalimat+i) != '\0' && word[mid][i] != '\0'; i++)
        temp[i] = *(kalimat+i);
    temp[i] = '\0';
    compare = strcmp(temp, word[mid]);
    if(compare > 0) mid = bin_search(kalimat, word, mid + 1, right);
    else if(compare < 0) mid = bin_search(kalimat, word, left, mid - 1);
    return mid;
}

//menukar string
void swap_string(char **s1, char **s2){
    char *t;
    t = *s1;
    *s1 = *s2;
    *s2 = t;
}

//membandingkan string
int strcmp(char *a, char *b){
    while(*a!='\0' && *b!='\0'){
        if(*a > *b) return 1;
        else if(*a < *b) return -1;
        a++, b++;
    }
    return 0;
}

//men-sorting string
void quicksort(char **data, int left, int right){
    //jika batas kiri >= batas kanan maka hentikan rekursi
    if(left >= right) return;
    //pivot dianggap sebagai elemen paling kiri
    int pivot = left, pointer = right;
    //arah pointer mula-mula dari kanan ke kiri
    int pointerMove = -1, temp, pos;
    //selama pivot tidak bertemu pointer
    while(pivot != pointer){
        pos = strcmp(data[pivot], data[pointer]);
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

void filter(char kalimat[512], char **word, int total_words)
{
    int i, j, k;
    for(i=0; kalimat[i] != '\0'; i++){
        j = bin_search(&(kalimat[i]), word, 0, total_words-1);
        if(j>=0){
            for(k=1; word[j][k+1] != '\0'; k++)
                kalimat[i+k] = '*';
        }
    }
}
