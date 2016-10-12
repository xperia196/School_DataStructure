#include <stdio.h>
#define MAX 25147
int main(void)
{
       char buf[100];
       int i,j;
	int state;
int num = 1;
 
       FILE *fp=fopen("words", "rt");
       if(fp==NULL){
               printf("not open");
               return 1;
       }
      for(j=0;j<=(MAX/25);j++){
system("clear");
  printf("\t---Words---\n");
for(i=0; i<25; i++){
               if(fgets(buf, sizeof(buf), fp)==NULL) break;
               printf("%5d %s",num,buf);
num++;
}
printf("\tPages : %d\n",j+1);
printf("Press [Enter] to show next words\n");
getchar();
system("clear");

  }
 
       state = fclose(fp);
       if(state!=0){
               printf("not close");
               return 1;
       }
      
       return 0;
}


