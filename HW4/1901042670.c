/*
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670.c 
$ gcc 1901042670.o -o 1901042670 -lm
$ ./1901042670 
*/

#include <stdio.h>  /* standard input/output definitions */
#include <stdlib.h> /* used for srand() and rand() functions */
#include <math.h> 	/* mathematical declarations, used for sqrt() function */
#include <time.h> 	/* used for time() function */

void menu();
void decrypt_and_print(char* file_path);
char decrypt_numbers(int number);
void deep_decrypt_and_print(char* file_path);
void track_machine(); // machine to track the position of the enemy camp
void refresh_position(int *X, int *Y, double *D, double *R);
void encrypt_messages (char* file_path);
int encrypt_characters(char character);

int main()
{
	menu();
	return 0;
}

void menu()
{
	int choice;
	
	do
	{
		printf("\n1-) Decrypt and print encrypted_p1.img\n");
		printf("2-) Decrypt and print encrypted_p2.img\n");
		printf("3-) Switch on the tracking machine\n");
		printf("4-) Encrypt the message\n");
		printf("5-) Switch off\n\n");
		
		printf("Please make your choice:\n");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
			decrypt_and_print("encrypted_p1.img");
			break;

			case 2:
			deep_decrypt_and_print("encrypted_p2.img");
			break;
			
			case 3:
			track_machine();
			break;
			
			case 4:
			encrypt_messages("decrypted_p4.img");
			break;
		}

	}while(choice != 5);
}
void decrypt_and_print(char* file_path)
{
	char number;
	int count;

	FILE *fp = fopen(file_path,"r");

        while(fscanf(fp,"%c",&number) != EOF)
        {
	    if(number=='\n')
	    {
		printf("\n");
	    }

	    else
	    {
		number = (int)number; /* transforming a character to a integer */
		number -= 48;

		printf("%c",decrypt_numbers(number));
	    }
        }
        fclose(fp);
}
char decrypt_numbers(int number)
{
	char message;

	switch(number)
	{
		case 0:
		message=' ' ;
       		break;

		case 1:
		message='-';
		break;
		
		case 2:
		message='_';
		break;
		
		case 3:
		message='|';
		break;
		
		case 4:
		message='/';
		break;
		
		case 5:
		message='\\';
		break;
		
		case 6:
		message='O';
        	break;

	}
	return message;
}
void deep_decrypt_and_print(char* file_path)
{
	char number;
	int count, sum=0, i,j,x=0;

	FILE *fp = fopen(file_path,"r");

	/*
		if a line begins with 34215... --> first step = 342 --> 9 % 7
							second step = 421 --> 7 % 7
								third step = 215  --> 8 % 7 
									and so on...

		if a line ends with ...6421, last steps --> 642 --> 12 % 7
								 421 --> 7 % 7
								   210 --> 3 % 10 
								     100 --> 1 % 10
	*/

	for(i=0;i<=2;i++)   // addition of first three number in the first line             
	{
		fscanf(fp,"%c",&number);
		number = (int)number;
		number -= 48;
		sum += (int)number;
	}
	x = sum % 7;
	printf(" %c",decrypt_numbers(x));
	sum=0;
	       
 	while(fscanf(fp,"%c",&number) != EOF)
        { 
		fseek(fp,-3,SEEK_CUR);

		for(j=0 ; j<=2 ; j++)
	     	{
			fscanf(fp,"%c",&number);
			if(number=='\n')
			{
				if(j==2)        
				{
					printf("\n");

					for(i=0;i<=2;i++)
					{
						fscanf(fp,"%c",&number);
						number = (int)number;
						number -= 48;
						sum += (int)number;
					}
					x = sum % 7;
					printf("%c",decrypt_numbers(x));
					sum=0;
				}
				else if(j==1)
				{
					fscanf(fp,"%c",&number);
					number = (int)number;
					number -= 48;
				        sum -= (int)number;
				        fseek(fp,-2,SEEK_CUR);
				}
		        }
			else if(number!='\n')
			{
				number = (int)number;
				number -= 48;
				sum += (int)number;
			}
		}
		x = sum % 7;
		printf("%c",decrypt_numbers(x));
		sum=0;
	}
	fclose(fp);
}
void track_machine()
{
	int X, Y, i, j;
	double D, R;
	char com; // variable for command

	X=0;
	Y=0;
	
	do
    	{
	    	refresh_position(&X, &Y, &D, &R);
		
		for(i=1;i<=11;i++)
		{
			for(j=1;j<=11;j++)
			{
				if(i==6 && j==6) printf("O\t");
				else if(i==X && j==Y) printf("E\t");
				else printf(".\t");
			}
			printf("\n");
		}
		printf("Enemies X position: %d, Y position: %d, Displacement: %lf, Distance to our camp: %lf\n",X,Y,R,D);
		
		printf("Command waiting...:");
		scanf(" %c",&com);
	
	}while(com=='R' && com!='E'); /* works until the operator gives ‘E’ command to machine and 
					 it refreshes the view of screen on each ‘R’ command */
}
void refresh_position(int *X, int *Y, double *D, double *R)
{
	double our_x=6.0, our_y=6.0;
	double x1, y1, x2, y2, last_x, last_y;

	last_x= *X;
	last_y= *Y;

	srand(time(NULL));

	*X = 1+rand()%11; 
	*Y = 1+rand()%11;

	x1 = ((double)*X - our_x);  /* distance of enemy to our camp at the x coordinate */
	y1 = ((double)*Y - our_y);  /* distance of enemy to our camp at the y coordinate */

	*D = sqrt(x1*x1 + y1*y1); /* distance of enemy to our camp */

	x2 = ((double)*X - last_x);  
	y2 = ((double)*Y - last_y);

	*R = sqrt(x2*x2 + y2*y2);  /* distance between current position and the last position of the enemy camp */
}
void encrypt_messages (char* file_path)
{
	char character;
	int i, flag=0, sum=0, x=0, num=0;
	char new= '\n';

	FILE *fp = fopen(file_path,"r");
	FILE *fp2 = fopen("encrypted_p4.img","w");
	
	
	while(fscanf(fp,"%c",&character) != EOF)
	{
		if(character== '\n')
		{
			fprintf(fp2,"%c",new);
			flag=0;
		}
		else
		{
			/*
				if a line begins with 1123... --> first step = 001 --> 1 % 7
										       		second step = 011 --> 2 % 7
										        		third step = 112  --> 4 % 7 
										           			and so on...
				if a line ends with ...6421, last steps --> 642 --> 12 % 7
															 421 --> 7 % 7
			*/
			
			num=encrypt_characters(character);
			
			if(flag==0)    /* first step on a newline */
			{
				sum += num;
				x = sum % 7;
				fprintf(fp2,"%d",x);
			}
			if(flag==1)   /* second step on a newline */
			{
				num=encrypt_characters(character);
				sum += num;
				x = sum % 7;
				fprintf(fp2,"%d",x);
			}
			if(flag != 0 && flag != 1)
			{
				fseek(fp,-3,SEEK_CUR);
				
				for(i=0;i<=2;i++)
				{
					fscanf(fp,"%c",&character);
					num=encrypt_characters(character);
					sum += num;
				}
			    	x = sum % 7;
				fprintf(fp2,"%d",x);
				sum=0;
			}
			flag++;
		}
	}
	fclose(fp);
	fclose(fp2);
}
int encrypt_characters(char character)
{
	int message;

	switch(character)
	{
		case ' ':
		message=0 ;
        	break;

		case '-':
		message=1;
		break;
		
		case '_':
		message=2;
		break;
		
		case '|':
		message=3;
		break;
		
		case '/':
		message=4;
		break;
		
		case '\\':
		message=5;
		break;
		
		case 'O':
		message=6;
        	break;
	}
	return message;
}   
