#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP_MESS "Ceaser_Chiper 0.1 created by ie.\n\nOptions:\n\t-h - show this message.\n\n\t-f=<path/to/file> - input encrypt/decrypt data file.\n\n\t-c=<shift_count> - count of shifting from 'a' (3 as default)."

#define MAX_LENGHT 1000
#define DEFAULT_SHIFTING 3

int *de_file(const char *file_name, int shift) // decrypt/encrypt data function
{
    const int end_of_letters = 'z' - shift;
    const int upReg_end = 'Z' - shift;
    
    FILE *data_file = fopen(file_name, "r");
    if(data_file == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    FILE *iter_file = data_file;
    
    int *data = (int *)malloc(MAX_LENGHT);
    int *data_iter = data;
    
    while((*data_iter = fgetc(iter_file)) != EOF)
    {
        data_iter++;
    }
    data_iter = data;
    while(*data_iter != EOF)
    {
        //printf("%c - %d\n", *data_iter, *data_iter);
        if (*data_iter == '\n' || *data_iter == '\t' || *data_iter == ' ')
        {
            data_iter++;
            continue;
        }
        
        int a[3] = {'a', 'b', 'c'};
        *a += shift;
        
        if (*data_iter > end_of_letters)
        {
            
            *data_iter = 'A' + shift - ('z'-(*data_iter)+1);
            data_iter++;
            //printf(">");
            continue;
        }
        if(*data_iter > upReg_end && *data_iter <= 'Z')
        {
            *data_iter += shift + 3;
        }
        
        *data_iter = *data_iter + shift;
        data_iter++;
            
    }
    *data_iter = '\0';
    
    return data;
}

int main(int argc, char **argv)
{
	
	
	switch(argc) {
		case 1:
			printf("Enter %s -h for help\n", *argv);
			return -1;
		case 2:
			if (!strcmp(*(argv+1), "-h"))
            {
				printf("%s\n", HELP_MESS);
                return 0;
            }
            char *f = "-f=";
            for(int i = 0; i < 3; i++)
            {
                if ((*(*(argv+1)+i) == *(f+i))) continue;
                else return -1;
            }
            
            int *de_data = de_file(*(argv+1)+3, DEFAULT_SHIFTING);
            printf("%ls\n", de_data);
            free(de_data);
                
    }
	return 0;
}
