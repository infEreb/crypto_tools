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

#define DEFAULT_ACTION 'e'

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
			{
				data_arr++;
				continue;
			}

			if (*data_arr >= 'a' && *data_arr < lowCase_end)
        	{
        		*data_arr = 'z' - lowCase_end + *data_arr + 1;
        		data_arr++;
				continue;
        	}
			else if (*data_arr >= 'A' && *data_arr < upCase_end)
			{
        		*data_arr = 'Z' - upCase_end + *data_arr + 1;
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
		{
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
		}
		case 3:
		{
			;
			char flag;
			char deecrypt = DEFAULT_ACTION;
			int shift = DEFAULT_SHIFTING;
			
			int *de_data = (int *)malloc(MAX_LENGHT);
			
			for(int i = 1; i <= 2; i++)
			{
				flag = flag_definer(*(argv+i));
				if (flag == 'c') shift = atoi((*(argv+i)+3));
			}
			for(int i = 1; i <= 2; i++)
			{
				flag = flag_definer(*(argv+i));
				if (flag == 'd' || flag == 'e')
				{
					deecrypt = flag;
					break;
				}

			}

			for(int i = 1; i <= 2; i++)
			{
				flag = flag_definer(*(argv+i));
				switch(flag)
				{
					case 'h':
						help_message();
						break;

					case 'f':
						if((de_data = file_data_read(*(argv+1)+3, de_data)) != NULL)
						{
							if(deecrypt == 'd')
								de_data = decrypt_data(de_data, shift);
							else
								de_data = encrypt_data(de_data, shift);

							printf("%ls", de_data);
						}
						free(de_data);
						break;

					default:
						break;
				}
			}
			break;
		}
		case 4:
		{
			char flag = ' ';
			char deecrypt = DEFAULT_ACTION;
			int shift = DEFAULT_SHIFTING;
		
			int *de_data = (int *)malloc(MAX_LENGHT);

			for(int i = 1; i <= 3; i++)
			{
				flag = flag_definer(*(argv+i));
				if (flag == 'c') shift = atoi((*(argv+i)+3));
			}

			for(int i = 1; i <= 2; i++)
			{
				flag = flag_definer(*(argv+i));
				if (flag == 'd' || flag == 'e')
				{
					deecrypt = flag;
					break;
				}

			}

			for(int i = 1; i <= 3; i++)
			{
				flag = flag_definer(*(argv+i));
				switch(flag)
				{
					case 'h':
						help_message();
						break;

					case 'f':
						if((de_data = file_data_read(*(argv+1)+3, de_data)) != NULL)
						{
							if(deecrypt == 'd')
								de_data = decrypt_data(de_data, shift);
							else
								de_data = encrypt_data(de_data, shift);

							printf("%ls", de_data);
						}
						free(de_data);
						break;

					default:
						break;
				}
			}
			break;
		}
		default :
			return help_message();
                
    }

	return 0;
}
