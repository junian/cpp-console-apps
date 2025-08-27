#include <stdio.h>

#include <stdlib.h>

struct hasil
{
   char tanggal[10];
   int  laba;
};

int main()
{
    FILE *ex_file;
    struct hasil data;
    char bulan[3], filename[256];
    int  month, last_month, i, banyak_input;
    char month_list[12][10] = {"Januari  ",
                               "Februari ",
                               "Maret    ",
                               "April    ",
                               "Mei      ",
                               "Juni     ",
                               "Juli     ",
                               "Agustus  ",
                               "September",
                               "Oktober  ",
                               "November ",
                               "Desember "};
    last_month = 0;
    
    printf("Program pencetak laba\n");
    printf("=====================\n\n");
    
    printf("Masukkan nama file yang akan disimpan: ");
    fflush(stdin);
    gets(filename);
    ex_file = fopen(filename, "at");
    
    printf("Masukkan Jumlah Data: ");
    fflush(stdin);
    scanf("%d", &banyak_input);
    for(i=0; i<banyak_input; i++)
    {
         printf("\nDATA %d\n", i+1);
         
         printf("Masukkan tanggal (dd/mm/yyyy): ");
         fflush(stdin);
         gets(data.tanggal);
         
         printf("Msukkan laba (Rp): ");
         fflush(stdin);
         scanf("%d", &data.laba);
         
         bulan[0] = data.tanggal[3];
         bulan[1] = data.tanggal[4];
         bulan[2] = '\0';
         month = atoi(bulan);
         
         if(month!=last_month)
         {
            last_month = month;
            fprintf(ex_file, "\nTanggal      Bulan                Laba\n");
            fprintf(ex_file, "======================================\n");
         }
         fprintf(ex_file, "%s   %s   Rp.%10d\n", data.tanggal, month_list[month-1], data.laba);
    }
    fclose(ex_file);
    printf("\nData has been saved...");
    getchar();
    return 0;
}
