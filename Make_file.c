#include <stdio.h>
#include <string.h>
struct data{
	char problem[200];
	char decision1[200];
	int p1, c1, t1;
	char decision2[200];
	int p2, c2, t2;
	}value;

int main(){
	char file_name[10];
		char p1[5],c1[5],t1[5],p2[5],c2[5],t2[5];
	printf("Please enter file name:\n");
	scanf("%s",&file_name);
	FILE *fp;
	fp = fopen(file_name , "a+");
	printf("Please enter problem:\n");
	scanf("%s",&value.problem);
	fputs(value.problem , fp);
	printf("Please enter decision 1:\n");
	scanf("%s\n",&value.decision1);
	fputs(value.decision1 , fp);
	printf("Please enter effect on people ,court ,treasury in 1 decision:\n");
	scanf("%d%d%d",&value.p1,&value.c1,&value.t1);
	sprintf(p1 , "%d", value.p1 );
	fputs(p1 , fp);
	sprintf(c1 , "%d", value.c1 );
	fputs(c1 , fp);
	sprintf(t1 , "%d", value.t1 );
	fputs(t1 , fp);		
	printf("Please enter decision 2:\n");
	scanf("%s",&value.decision2);
	fputs(value.decision2 , fp);
	printf("Please enter effect on people ,court ,treasury in 2 decision:\n");
	scanf("%d%d%d",&value.p2,&value.c2,&value.t2);
	sprintf(p2 , "%d", value.p2 );
	fputs(p2 , fp);
	sprintf(c2 , "%d", value.c2 );
	fputs(c2 , fp);
	sprintf(t2 , "%d", value.t2 );
	fputs(t2 , fp);	
fclose(fp);
}
