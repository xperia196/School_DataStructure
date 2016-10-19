#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** words_list(int* count, char** word)
{
char buffer[500];
int i;
FILE* fileio = fopen("ranwords", "rt");

while (fgets(buffer, sizeof(buffer), fileio) != NULL)
{
(*count)++;
if (*count % 2000 == 0)
printf(".");
}
printf("%d Words read.", *count);
rewind(fileio);

word = (char**)malloc((*count) * sizeof(char*));
for (i = 0; i<(*count); i++)
word[i] = (char*)malloc(256 * sizeof(char));

for (i = 0; i<(*count); i++)
fscanf(fileio, "%s", word[i]);
fclose(fileio);
return word;
}

int search(char* buffer, char** word, int count, int* line)
{
int i, check;


i = 0; *line = 0;
do
{
check = strcmp(word[i], buffer);
(*line)++;
i++;
}
while ((check != 0) && (i<count));

return check;
}
void my_free(char** word, int count)
{
int i;
for (i = 0; i<count; i++)
free(word[i]);
free(word);
}
int main(void)
{
FILE* filecheck = fopen("ranwords", "rt");
char buffer[256];
int count = 0, check, line;
char** word = NULL;
system("clear");
printf("Form of English words\n");
printf("==============================\n");
printf("Reading words from file..");
if(filecheck==NULL)
{
printf("File ranwords not found. Halting..\n");
return 1;
}
word = words_list(&count, word);
printf("\n");
printf("Find English words(Sequential Search)\n");
printf("==============================\n");

do
{
printf("Which word do you want to find?\n");
gets(buffer);
if (buffer[0] != '\0')
{
check = search(buffer, word, count, &line);
if (check != 0)
{
printf("\n");
printf("We couldn't find word '%s', %d tried.\n", buffer, line);
}
else 
{
printf("\n");
printf("We found word '%s' in line %d\n", buffer, line);
}
}
}
while (buffer[0] != '\0');
printf("==============================\n");
printf("Program halted. Good bye.\n");
my_free;
return 0;
}
