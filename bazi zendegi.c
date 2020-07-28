#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

shift_right(char**arry,int satr ,int soton){
	int i,j;
	for(i = 0 ; i < satr - 1;i++){
		for(j = soton - 2 ; j >= 0 ; j--){
			arry[i][j + 1] = arry[i][j];
			arry[i][j]='\0';
		}
	}
}
shift_down(char**arry,int satr,int soton){
	int i,j;
	for (i = satr - 1;i >= 0;i--){
		for(j= 0;j < soton ;j++){
		
		arry[i+1][j]=arry[i][j];
		arry[i][j]='\0';
}
}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int n,t,i,j,satr,soton;
	char **arry;
	scanf("%d %d",&n,&t);
	satr=n;soton=n;
	arry = (char **)malloc(2*n * sizeof(char *));
	for(i = 0; i<2*n; i++)
		arry[i] = (char *)malloc(2*n * sizeof(char));
	for(i = 0; i<2*n; i++)
		for(j = 0; j <2*n; j++)
			arry[i][j] = '\0';

			int mgh=1;
			while(mgh==1){
				int a,b;
				scanf("%d%d",&a,&b);
					if((a<n)&&(b<n))
						arry[a][b]='*' ;
					else
						mgh++;
	}
	/*check mishe ke aya niyaz be taqir size hast*/
	for(i=0;i<satr;i++){
		for(j=0;j<soton;j++){
			if(arry[i][j]=='*'){
			if((i==0)&&(j==0)){
				satr++;
				soton++;
				shift_right(arry,satr,soton);
				shift_down(arry,satr,soton);
				break;
			}
			if((i==(soton-1))&&(j==0)){
				satr++;
				soton++;
				shift_right(arry,satr,soton);
				break;
			}
			else if(j==0){
				soton++;
				shift_right(arry,satr,soton);
				break;
}
			if((i==0)&&(j==(soton-1))){
				satr++;
				soton++;
				shift_down(arry,satr,soton);
				break;
			}
			if((i==(soton-1))&&(j==(soton-1))){
				satr++;
				soton++;
				break;
			}
			else if(j==(soton-1)){
				soton++;
				break;
}
		if(i==0){
			satr++;
			shift_down(arry,satr,soton);
			break;
		}
		if(i==(satr-1)){
			satr++;
			break;
			}

		}
	}
}
		for(i=0;i<satr;i++){
		printf("|");
		for(j=0;j<soton;j++){
			printf("%c|",arry[i][j]);	
	}
		printf("\n");
	}
int s;
for(s=0;s<t;s++){
	if((satr>=(2*n))||(soton>=(2*n))){
	printf("IT IS VERY BIGGGG :(");		
	
		exit(0);
}
	char **arry1;
		arry1 = (char **)malloc(2*n * sizeof(char *));
	for(i = 0; i <2*n; i++)
		arry1[i] = (char *)malloc(2*n * sizeof(char));
	for(i = 0; i <2*n; i++)
		for(j = 0; j <2*n; j++)
			arry1[i][j] = '\0';

	for(i=0;i<satr;i++){
			for(j=0;j<soton;j++){
	
		if(arry[i][j]=='*'){
		
			int count=0,k,l;
				for(l=j-1;(l<=j+1);l++){
					if(((i-1)>=0)&&(l>=0)&&(l<soton)){
						if(arry[i-1][l]=='*')
							count++;
			}
		}
				for(l=j-1;l<=j+1;l++){
					if(((i+1)<satr)&&(l>=0)&&(l<soton)){
						if(arry[i+1][l]=='*')
							count++;
					}
				}
				if(arry[i][j-1]=='*')
					count++;
				if(arry[i][j+1]=='*')
					count++;
				if((count==0)||(count==1)||(count==4)||(count==5)||(count==6)||(count==7)||(count==8))
					arry1[i][j]='\0';
				else{
			
				arry1[i][j]='*';	
		}
			}	
			
		else{
				int count=0,k,l;
				for(l=j-1;(l<=j+1);l++){
					if(((i-1)>=0)&&(l>=0)&&(l<soton)){
						if(arry[i-1][l]=='*')
							count++;
			}
		}
				for(l=j-1;l<=j+1;l++){
					if(((i+1)<satr)&&(l>=0)&&(l<soton)){
						if(arry[i+1][l]=='*')
							count++;
					}
				}
				if(arry[i][j-1]=='*')
					count++;
				if(arry[i][j+1]=='*')
					count++;
				if(count==3)
						{
						arry1[i][j]='*';
	if((i==0)&&(j==0)){
				satr++;
				soton++;
				shift_right(arry1,satr,soton);
				shift_down(arry1,satr,soton);
				break;
			}
			if((i==(soton-1))&&(j==0)){
				satr++;
				soton++;
				shift_right(arry1,satr,soton);
				break;
			}
			else if(j==0){
				soton++;
				shift_right(arry1,satr,soton);
				break;
}
			if((i==0)&&(j==(soton-1))){
				satr++;
				soton++;
				shift_down(arry1,satr,soton);
				break;
			}
			if((i==(soton-1))&&(j==(soton-1))){
				satr++;
				soton++;
				break;
			}
			else if(j==(soton-1)){
				soton++;
				break;
}
		if(i==0){
			satr++;
			shift_down(arry1,satr,soton);
			break;
		}
		if(i==(satr-1)){
			satr++;
			break;
			}
				
				}
			}
		}
	}
	
			
	printf("\n\n\n\n");
	for(i=0;i<satr;i++){
		printf("|");
		for(j=0;j<soton;j++){
			printf("%c|",arry1[i][j]);	
	}
		printf("\n");
	}
	Sleep(1000);
	for(i=0;i<satr;i++){
	for(j=0;j<soton;j++)
		arry[i][j]=arry1[i][j];
}
for(i = 0; i < satr; i++)
		free(arry1[i]);
	free(arry1); 
}
for(i = 0; i < satr; i++)
		free(arry[i]);
	free(arry);


	return 0;

}



