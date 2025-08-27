#include <stdio.h>


struct manusia
{
    char nama[50];
    int umur;
};

int main()
{
    struct manusia data1;
    struct manusia *data2;
    gets(data1.nama);
    scanf("%d", &data1.umur);
    data2 = &data1;
    puts(data2->nama);
    printf("%d", data2->umur);
    getchar();
    return 0;
}
