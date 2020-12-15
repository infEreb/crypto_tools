#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HELP_MESS "Ceaser_Chiper 0.1 created by ie.\n\nOptions:\n\t-h - show this message.\n\n\t-f=<path/to/file> - input encrypt/decrypt data file.\n\n\t-c=<shift_count> - count of shifting from 'a' (3 as default)."

#define MAX_LENGHT 1000 // lenght of encrypt/decrypt message
#define DEFAULT_SHIFTING 3


#define HELP_FLAG "-h"
#define FILE_FLAG "-f="
#define SHIFT_FLAG "-c="

int help_message(void)
{
	printf("Execute this program with '-h' option.\n");
	return -1;
}

int *de_file(const char *file_name, int shift) // decrypt/encrypt data
{
    const int downReg_end = 'z' - shift;
    const int upReg_end = 'Z' - shift;
    
    FILE *data_file = fopen(file_name, "r");
    if(data_file == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
		 exit(-1);
    }
    FILE *iter_file = data_file;
    
    int *data = (int *)malloc(MAX_LENGHT);
    int *data_iter = data;

	if(shift <= 0 || shift >= 26)
	{
		while(fread(data_iter, 1, 1, iter_file))
		{
			data_iter++;
		}
		fclose(data_file);
		return data;
	}
    
    while((*data_iter = fgetc(iter_file)) != EOF)
    {
        data_iter++;
    }
    data_iter = data;
    while(*data_iter != EOF)
    {
        //printf("%c - %d\n", *data_iter, *data_iter);
		
        if (!isalpha(*data_iter))
        {
            data_iter++;
            continue;
        }
        
        if (*data_iter >= 'a' && *data_iter > downReg_end)
        {
        	*data_iter = 'a' + *data_iter - downReg_end - 1;
        	data_iter++;
			continue;
        }
		else if (*data_iter <= 'Z' && *data_iter > upReg_end)
		{
        	*data_iter = 'A' + *data_iter - upReg_end - 1;
        	data_iter++;
			continue;
		}
		*data_iter = *data_iter + shift;
		data_iter++;
    }
    *data_iter = '\0';
    
    return data;
}

char flag_definer(char *flag)
{
		if(*flag == '-')
		{
			if (!strcmp(flag, HELP_FLAG))
				return 'h';
			if (*(flag+2) == '=')
			{
				if (*(flag+1) == 'f')
					return 'f';
				else if (*(flag+1) == 'c')
					return 'c';
				else
					exit(help_message());
			}
		}
		return '0';
}

int main(int argc, char **argv)
{
	
	
	switch(argc) {
		case 1:
			return help_message();

		case 2:
            for(int i = 0; i < 3; i++)
            {
                if ((*(*(argv+1)+i) == *(FILE_FLAG+i))) continue;
                else return help_message();
            }
            
            int *de_data = de_file(*(argv+1)+3, DEFAULT_SHIFTING);
            printf("%ls\n", de_data);
            free(de_data);

			break;

		case 3:
			;
			char fg;
			int shift = DEFAULT_SHIFTING;
			
			for(int i = 1; i <= 2; i++)
			{
				fg = flag_definer(*(argv+i));
				if (fg == 'c') shift = atoi((*(argv+i)+3));
			}
			for(int i = 1; i <= 2; i++)
			{
				fg = flag_definer(*(argv+i));
				switch(fg)
				{
					case 'h':
						help_message();
						break;

					case 'f':
						;
						int *de_data = de_file(*(argv+i)+3, shift);
						printf("%ls\n", de_data);
						break;

					default:
						break;
				}
			}
			break;
		
		case 4:
			;
			fg = ' ';
			shift = DEFAULT_SHIFTING;
			
			for(int i = 1; i <= 3; i++)
			{
				fg = flag_definer(*(argv+i));
				if (fg == 'c') shift = atoi((*(argv+i)+3));
			}
			for(int i = 1; i <= 3; i++)
			{
				fg = flag_definer(*(argv+i));
				switch(fg)
				{
					case 'h':
						help_message();
						break;

					case 'f':
						;
						int *de_data = de_file(*(argv+i)+3, shift);
						printf("%ls\n", de_data);
						break;

					default:
						break;
				}
			}
			break;

		default :
			return help_message();
                
    }

	return 0;
}
