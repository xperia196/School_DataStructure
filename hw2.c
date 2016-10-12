#include "stdio.h"

struct student{
int identify;
int subs[5];
int sum;
float avg;
};

int main(void)
{
system("clear");
FILE* file=fopen("scr2016.txt", "rt");
if(file==NULL)	{
printf(" scr2016.txt File not found. Aborting..");
return 1;
}
int i, score, class;
int id=0;
int grade=1;
struct student s;
s.sum = 0;
s.avg = 0;
s.identify = 0;

fscanf(file, "%d", &id);
for	(class = 1; class<7; class++)
{
int check_endoffile;
s.identify = 0;
for	(i=0; i<5; i++)	s.subs[i] = 0;
printf("성적 열람 : %d 학년 %d반\n", grade, class);
printf("학번    국어   산수    사회    과학    체육      총점    평균\n");

if(id ==0)	fscanf(file, "%d", &id);
do
{
printf("%-7d\t ", id);
for(i=0; i<5; i++)
{
fscanf(file, "%d", &score);
printf("%-4d\t", score);
s.subs[i]+=score;
s.sum+=score;
}
s.identify++;
s.avg = (float) s.sum/5;
printf(" %-7d %-7.1lf\n", s.sum, s.avg);
s.sum = 0;
s.avg = 0;
check_endoffile = fscanf(file, "%d", &id);
}
while(((id/100)%10 == class) && check_endoffile != EOF);
printf("--------------------------------------------------------------\n\n");
printf("반평균   ");
for(i=0;i<5; i++)	printf("%-8d",s.subs[i]/s.identify);
if (class!=6){
printf("\n\n[Enter]를 눌러 %d반의 성적을 확인하세요", class+1);}
else {
printf("\n\n모든 반의 성적을 확인하셨습니다. [Enter]를 눌러 프로그램 종료");}

getchar();
system("clear");
}
fclose(file);
return 0;
}

