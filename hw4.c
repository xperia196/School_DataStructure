#include "stdio.h"
#include "string.h"

int fileinput(FILE *fp, char buffer[])
{
	int split = 0;
	printf("Reading User information");
	while(fgets(buffer, 100, fp))
	{
		if(buffer != " ")
		{
			if(++split % 50 ==0)	printf(".");
		}
	}
	printf("%d User table estalished.\n", split);
	return split;
}

int compare(char id[], char buffer[])
{
	int i, result;
	
	for(i = 0; buffer[i] != '\0'; i++)
	{
		if(id[i] != buffer[i])
		{
			result = 0;
		}
		else
		{
			if(strstr(buffer, id))
			{
				int id_number = split(id);
				int buffer_number = split(buffer);
				
				if(id_number = buffer_number)
					break;
			}
			result = 1;
		}
		return result;
	}
}

int split(char c[])
{
	int i, counter = 0;
	for(i=0; c[i] != '\0' && c[i] != '\n' && c[i] != ':'; i++)	counter++;
	return counter;
}

void search(FILE *fp, char buffer[], int all_count_number, char id[])	{
	int compare_counter = 0;
	int search_result = 0;
	
	printf("User : %s", id);
	while(fgets(buffer, 100, fp))
	{
		if(buffer != " ")
		{
			++compare_counter;
			search_result = compare(id, buffer);
			
			if(search_result)
			{
				int i;
				printf("\t INFO : ");
				for(i = 0; i<100; i++)
					if(buffer[i] != '\n')
						printf("%c", buffer[i]);
					else break;
					break;
			}
			else if (compare_counter == all_count_number)	{
				printf("Failed to find");
				break;
			}
		}
	}
	printf(" Count : %d\n", compare_counter);
}

int main()
{
	char buffer[128], id[128];
	int count = 0, total_id;
	FILE *fp = fopen("sorted_passwd", "rt");
	system("clear");
	printf("Form of User table\n");
	if(fp==NULL)
	{
		printf("File sorted_passwd not found. Halting..\n");
		return 1;
	}
	total_id = fileinput(fp, buffer);
	printf("Find user information with Binary search\n");
	printf("========================================================\n");
	while(1)	{
		rewind(fp);
		printf("Enter User ID : ");
		gets(id);
		if(id[0] == '\0')
		{
			printf("Halting..\n");
			break;
		}	else	search(fp, buffer, total_id, id);
	}
	fclose(fp);
	return 0;
}