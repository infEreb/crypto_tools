#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HELP_MESS "Ceaser_Cipher 0.2 created by ie.\n\nOptions:\n\t-h - show this message.\n\n\t-f=<path/to/file> - input encrypt/decrypt data file.\n\n\t-d - decrypt file data (left side shifting).\n\n\t-e - encrypt file data (right side shifting).\n\n\t-c=<shift_count> - count of shifting from 'a' (3 as default)."

#define MAX_LENGHT 1000 // lenght of encrypt/decrypt message
#define DEFAULT_SHIFTING 3


#define HELP_FLAG "-h"
#define FILE_FLAG "-f="
#define DECRYPT_FLAG "-d"
#define ENCRYPT_FLAG "-e"
#define SHIFT_FLAG "-c="

#define DEFAULT_ACTION "-e"

int help_message(void)
{
	printf("Execute this program with '-h' option.\n");
	return -1;
}

int *file_data_read(const char *file_name, int *data_arr)
{
	FILE *file_data = fopen(file_name, "r");
	int *temp = data_arr;

	if(file_data != NULL)
	{
		int i = 0;
		while(i < MAX_LENGHT-1 && (*data_arr = fgetc(file_data)) != EOF)
		{
			data_arr++;
			i++;
		}
		*data_arr = '\0';

		fclose(file_data);
		return temp;
	}
	else
	{
		fprintf(stderr, "Error opening file...\n");
		return NULL;
	}
}

int *decrypt_data(int *data_arr, int shift) //
{
	const int lowCase_end = 'a' + shift;
	const int upCase_end = 'A' + shift;

	int *temp = data_arr;
	
	if(shift <= 0 || shift >= 26)
	{
		return data_arr;
	}
	else
	{
		while(*data_arr != '\0')
		{
			if(!isalpha(*data_arr))
				continue;

			if (*data_arr >= 'a' && *data_arr < lowCase_end)
        	{
        		*data_arr = 'z' - *data_arr + lowCase_end + 1;
        		data_arr++;
				continue;
        	}
			else if (*data_arr >= 'A' && *data_arr < upCase_end)
			{
        		*data_arr = 'Z' - *data_arr + upCase_end + 1;
        		data_arr++;
				continue;
			}

			*data_arr = *data_arr - shift;
			data_arr++;
		}

		*data_arr = '\0';
		return temp;
	}
}

int *encrypt_data(int *data_arr, int shift) // 
{
	const int lowCase_end = 'z' - shift;
	const int upCase_end = 'Z' - shift;
	
	int *temp = data_arr;

	if(shift <= 0 || shift >= 26)
	{
		return data_arr;
	}
	else
	{
		while(*data_arr != '\0')
		{
			if(!isalpha(*data_arr))
			{
				data_arr++;
				continue;
			}

			if (*data_arr <= 'z' && *data_arr > lowCase_end)
        	{
        		*data_arr = 'a' + *data_arr - lowCase_end - 1;
        		data_arr++;
				continue;
        	}
			else if (*data_arr <= 'Z' && *data_arr > upCase_end)
			{
        		*data_arr = 'A' + *data_arr - upCase_end - 1;
        		data_arr++;
				continue;
			}

			*data_arr = *data_arr + shift;
			data_arr++;
		}

		*data_arr = '\0';
		return temp;
	}
}
/*
int *de_file(const char *file_name, int shift) // decrypt/encrypt data
{
    const int lowReg_end = 'z' - shift;
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
    
	int iter = 0;
    while((*data_iter = fgetc(iter_file)) != EOF && iter < MAX_LENGHT-1)
    {
        data_iter++;
		iter++;
    }
	*data_iter = EOF;
    data_iter = data;

    while(*data_iter != EOF)
    {
        //printf("%c - %d\n", *data_iter, *data_iter);
		
        if (!isalpha(*data_iter))
        {
            data_iter++;
            continue;
        }
        
        if (*data_iter >= 'a' && *data_iter > lowreg_end)
        {
        	*data_iter = 'a' + *data_iter - lowreg_end - 1;
        	data_iter++;
			continue;
        }
		else if (*data_iter <= 'z' && *data_iter > upreg_end)
		{
        	*data_iter = 'a' + *data_iter - upreg_end - 1;
        	data_iter++;
			continue;
		}
		*data_iter = *data_iter + shift;
		data_iter++;
    }
    *data_iter = '\0';
    
    return data;
}
*/
char flag_definer(char *flag)
{
		if(*flag == '-')
		{
			if (!strcmp(flag, HELP_FLAG))
				return 'h';
			if (!strcmp(flag, DECRYPT_FLAG))
				return 'd';
			if (!strcmp(flag, ENCRYPT_FLAG))
				return 'e';
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
            
			int *de_data = (int *)malloc(MAX_LENGHT);

			if((de_data = file_data_read(*(argv+1)+3, de_data)) != NULL)
				de_data = encrypt_data(de_data, DEFAULT_SHIFTING);
			else
				return -1;

            printf("%ls", de_data);
            free(de_data);

			break;

		case 3:
			;
			char fg;
			char de;
			int shift = DEFAULT_SHIFTING;
			
			for(int i = 1; i <= 2; i++)
			{
				fg = flag_definer(*(argv+i));
				if (fg == 'c') shift = atoi((*(argv+i)+3));
			}
			for(int i = 1; i <= 2; i++)
			{
				fg = flag_definer(*(argv+i));
				if (fg == 'd')
				{
					de = fg;
					break;
				}
				else if (fg == 'e')
				{
					de = fg;
					break;
				}

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
						//if()
						//int *de_data = de_file(*(argv+i)+3, shift);
						//printf("%ls\n", de_data);
						//free(de_data);
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
						//int *de_data = de_file(*(argv+i)+3, shift);
						//printf("%ls\n", de_data);
						//free(de_data);
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
