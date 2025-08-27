#include <stdio.h>

#include <stdlib.h>
#include <string.h>

//elemen dasar linked list
typedef struct mahasiswa
{
    char nama[50];
    char alamat[128];
    char noTelp[13];
    struct mahasiswa *next;
}MHS;

//menghapus data di linked list
void remove_list(MHS **data)
{
    if(data == NULL) {
        printf("Data not found...\n");
        return;
   }
	MHS *trash = *data;
	*data = (*data)->next;
	free(trash);
	printf("Data removed...\n");
}

//mencari nama di linked list
MHS **search_list(MHS **data, char *nama)
{
	while (*data != NULL)
	{
		if (strcmp((*data)->nama, nama)==0)
		{
			return data;
		}
		data = &(*data)->next;
	}
	return NULL;
}

//menambahkan element linked list
MHS *add_list(MHS **data, char *nama, char *alamat, char *noTelp)
{
    MHS *new_data = (MHS*) malloc(sizeof(MHS));
    if(new_data == NULL) return NULL;
    new_data->next = *data;
    *data = new_data;
    strcpy(new_data->nama, nama);
    strcpy(new_data->alamat, alamat);
    strcpy(new_data->noTelp, noTelp);
    return *data;
}

//menampilkan isi linked list
void show_list(MHS *data)
{
	if (data == NULL)
	{
		printf("-== KOSONG ==-\n");
	}
	while (data != NULL)
	{
		printf("Nama       : %s\n", data->nama);
		printf("Alamat     : %s\n", data->alamat);
		printf("No. Telp   : %s\n", data->noTelp);
		printf("\n");
		data = data -> next;
	}
}

int main()
{
    FILE *ex_file, *data_file;
    MHS *data = NULL;
    char choice, kar;
    char filename[256];
    char nama[50], alamat[128], noTelp[13];
    int loaded = 0;

    //MAIN MENU
    while(1)
    {
        system("clear");
        printf("\n\t\t\t          MAIN MENU\n");
        printf("\t\t\t*===========================*\n");
        printf("\t\t\t|1.INPUT DATA               |\n");
        printf("\t\t\t|2.TAMPILKAN DATA LINK LIST |\n");
        printf("\t\t\t|3.HAPUS DATA               |\n");
        printf("\t\t\t|4.LOAD DATA                |\n");
        printf("\t\t\t|5.BUKA FILE EXTERNAL       |\n");
        printf("\t\t\t|6.KELUAR                   |\n");
        printf("\t\t\t*===========================*\n");
        printf("\t\t\tCreated by: The Best PPT Team\n");
        printf("\n\nMasukkan pilihan: ");

        //pilih command
        do{
            choice = getchar();
        }while(choice < '1' || choice > '6');
        printf("%c\n\n", choice);

        //masing-masing command
        switch(choice)
        {
            //Input Data
            case '1': do{
                        printf("\nNama    : ");
                        gets(nama);
                        printf("Alamat  : ");
                        gets(alamat);
                        printf("Telp/HP : ");
                        gets(noTelp);
                        add_list(&data, nama, alamat, noTelp);
                        printf("\ningin input lagi? (y/t)");
                        do{
                            choice = getchar();
                        }while(choice != 'Y' && choice != 'y' && choice != 'T' && choice != 't');
                      }while(choice == 'Y' || choice == 'y');
                      break;

            //Tampilkan linked list
            case '2': printf("ISI LINKED LIST\n\n");
                      show_list(data);
                      break;

            //menghapus data
            case '3': printf("Masukkan nama yang akan dihapus: ");
                      gets(nama);
                      remove_list(search_list(&data, nama));
                      break;

            //me-LOAD data (hanya bisa dilakukan sekali setiap running)
            case '4': if(!loaded)
                      {
                        if((data_file = fopen("data.jtx", "rb")) == NULL)
                        {
                           printf("Couldn't Load Data....\n");
                        }
                        else
                        {
                           loaded = 1;
                           while(!feof(data_file))
                           {
                              if(fgets(nama, 50, data_file)==NULL) break;
                              if(nama[strlen(nama)-1] == '\n')
                                 nama[strlen(nama)-1] = '\0';
                              if(fgets(alamat, 128, data_file)==NULL) break;
                              if(alamat[strlen(alamat)-1] == '\n')
                                 alamat[strlen(alamat)-1] = '\0';
                              if(fgets(noTelp, 13, data_file)==NULL) break;
                              if(noTelp[strlen(noTelp)-1] == '\n')
                                 noTelp[strlen(noTelp)-1] = '\0';
                              printf("Nama       : %s\n", nama);
		                        printf("Alamat     : %s\n", alamat);
                              printf("No. Telp   : %s\n", noTelp);
		                        printf("\n");
		                        add_list(&data, nama, alamat, noTelp);
                           }
                           fclose(data_file);
                        }
                      }
                      else
                      {
                          printf("All data have been loaded...\n");
                      }
                      break;

            //BACA file external
            case '5': do{
                         printf("\nMasukkan nama file yang akan dibaca: ");
                         gets(filename);
                         if((ex_file = fopen(filename, "rb")) == NULL)
                         {
                             printf("Couldn't open file...\n");
                         }
                         else
                         {
                             while((kar = getc(ex_file)) != EOF)
                             {
                                 putchar(kar);
                             }
                             fclose(ex_file);
                         }
                         printf("\ningin membuka file lagi? (y/t)");
                         do{
                            choice = getchar();
                         }while(choice != 'Y' && choice != 'y' && choice != 'T' && choice != 't');
                      }while(choice == 'Y' || choice == 'y');
                      break;

            //save and close the program
            case '6': if(loaded) data_file = fopen("data.jtx", "wb");
                      else data_file = fopen("data.jtx", "ab");
                      if(data_file!=NULL)
                      {
                         while (data != NULL)
	                      {
		                     fprintf(data_file, "%s\n", data->nama);
                        	 fprintf(data_file, "%s\n", data->alamat);
                        	 fprintf(data_file, "%s\n", data->noTelp);
                    		 data = data -> next;
	                      }
                         fclose(data_file);
                      }
                      return 0;
        }
        printf("\nPress any key to go to main menu...");
        getchar();
    }
}
