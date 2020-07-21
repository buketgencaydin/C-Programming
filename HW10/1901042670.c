/*
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670.c 
$ -o 1901042670.o 1901042670 -lm
$ ./1901042670 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 4096

struct point
{
	double x;
	double y;
	char name[100];
};
struct line
{
	struct point points[2];
	char name[100];
};
struct polygon
{	
	struct line lines[100];
	struct point points[100];
	char name[100];
};
void data(char str[ARRAY_SIZE],int *point,int *line,int *polygon,struct point points[100],struct line lines[100],struct polygon polygons[100]);
void read_file(char arr[ARRAY_SIZE], char str[ARRAY_SIZE]);
void action(char str[ARRAY_SIZE], char result[ARRAY_SIZE],int *point,int *line,int *polygon,struct point points[100],struct line lines[100],struct polygon polygons[100]);

int main()
{
	struct point points[100];
	struct line lines[100];
	struct polygon polygons[100];
	
	char arr[4096];
	int i;
	int obj_num, act_num;
	char ch;
	char foo;
	int point=0, line=0,polygon=0;
	char str[ARRAY_SIZE];
	char result[ARRAY_SIZE];
	
	char e[20][100];
	char out_file[ARRAY_SIZE];

	FILE *fp = fopen("commands.txt","r");
	FILE *output;

	do
	{
		fgets(arr,sizeof(arr),fp);
		read_file(arr,str);

		if(strcmp(str,"data") == 0)
		{
			/* finds the number of 2D objects */
			fgets(arr,sizeof(arr),fp);
			read_file(arr,str);
			sscanf(str,"%d%c",&obj_num,&foo);


			/* reads the input file and fills the object structures */ 
			for(i=0 ; i<obj_num ; i++)
			{
				fgets(arr,sizeof(arr),fp);
				read_file(arr,str);
				
				data(str,&point,&line,&polygon,points,lines,polygons);
			}
		}
		else if(strcmp(str,"actions") == 0)
		{
			fgets(arr,sizeof(arr),fp);
			read_file(arr,str);
			
			sprintf(out_file, "%s", str);
			output = fopen(out_file,"w");

			/* finds the number of actions */
			fgets(arr,sizeof(arr),fp);
			read_file(arr,str);
			sscanf(str,"%d%c",&act_num,&foo);

			/* reads the input file, calculates the actions and writes the results to aoutput file */ 
			for(i=0 ; i<act_num ; i++)
			{
				fgets(arr,sizeof(arr),fp);
				read_file(arr,str);
				action(str,result,&point,&line,&polygon,points,lines,polygons);
				printf("%s\n",result);
				fprintf(output,"%s\n",result);
			}
		}
	}while(!feof(fp));

	return 0;
}
void action(char str[ARRAY_SIZE],char result[ARRAY_SIZE],int *point,int *line,int *polygon,struct point points[100],struct line lines[100],struct polygon polygons[100])
{
	char e[10][100];
	double res=0,sum=0;
	double x0,y0,x1,x2,y1,y2,x3,y3,x4,y4;
	int i,j,k=0;
	double cosinus=0;
	double px,qx,py,qy;
	char record[50],rec[50];
	int flag1=0, flag2=0, c=0, count=0;
	double x[30],y[30];
	int index;

	sscanf(str,"%s %s %s %s",e[0],e[1],e[2],e[3]);

	if(strcmp(e[0],"Distance") == 0)
	{
		if(e[1][0] == 'P' && e[2][0] == 'P') // distance between two points
		{
			for(i=0 ; i<(*point) ; i++)
			{
				if(strcmp(points[i].name,e[1]) == 0) index=i;
			}
			x1 = points[index].x; y1 = points[index].y;

			for(i=0 ; i<(*point) ; i++)
			{
				if(strcmp(points[i].name,e[2]) == 0) index=i;
			}
			x2 = points[index].x; y2 = points[index].y;

			res = sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));

			sprintf(result, "%s(%s,%s) = %.1lf", e[0],e[1],e[2],res);
		}
		else  // distance between a point and a line
		{
			for(i=0 ; i<(*point) ; i++)
			{
				if(strcmp(points[i].name,e[1]) == 0) index=i;
				if(strcmp(points[i].name,e[2]) == 0) index=i;

			}
			x0 = points[index].x; y0 = points[index].y;

			for(i=0 ; i<(*line) ; i++)
			{
				if(strcmp(lines[i].name,e[1]) == 0) index=i;
				if(strcmp(lines[i].name,e[2]) == 0) index=i;
			}
			x1 = lines[index].points[0].x; y1 = lines[index].points[0].y;
			x2 = lines[index].points[1].x; y2 = lines[index].points[1].y;

			res = fabs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 -y2*x1) / sqrt(pow(y2-y1,2.0)+pow(x2-x1,2.0));

			sprintf(result, "%s(%s,%s) = %.1lf", e[0],e[1],e[2],res);

		}
	}
	else if(strcmp(e[0],"Angle") == 0)
	{
		for(i=0 ; i<(*line) ; i++)
		{
			if(strcmp(lines[i].name,e[1]) == 0) index=i;
		}
		px = (lines[index].points[1].x)-(lines[index].points[0].x);
		py = (lines[index].points[1].y)-(lines[index].points[0].y);

		for(i=0 ; i<(*line) ; i++)
		{
			if(strcmp(lines[i].name,e[2]) == 0) index=i;
		}
		qx = (lines[index].points[1].x)-(lines[index].points[0].x);
		qy = (lines[index].points[1].y)-(lines[index].points[0].y);

		cosinus = (px*qx + py*qy) / (sqrt(pow(px,2.0)+pow(py,2.0))*sqrt(pow(qx,2.0)+pow(qy,2.0)));
		res = acos(cosinus) * 180 / M_PI;

		if(res == 180.0) res=0.0; //parallel lines

		sprintf(result, "%s(%s,%s) = %.1lf", e[0],e[1],e[2],res);
	}
	else if(strcmp(e[0],"Length") == 0)
	{
		if(e[1][0] == 'L')
		{
			for(i=0 ; i<(*line) ; i++)
			{
				if(strcmp(lines[i].name,e[1]) == 0) index=i;
			}
			x1 = lines[index].points[0].x; y1 = lines[index].points[0].y;
			x2 = lines[index].points[1].x; y2 = lines[index].points[1].y;

			res = sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
		}
		else
		{
			for(i=0 ; i<(*polygon) ; i++)
			{
				if(strcmp(polygons[i].name,e[1]) == 0) index=i;
			}
			if(polygons[index].lines[0].name[0] == 'L') // a polygon defined by lines
			{
			do
				{
					x1 = polygons[index].lines[k].points[0].x; y1 = polygons[index].lines[k].points[0].y;
					x2 = polygons[index].lines[k].points[1].x; y2 = polygons[index].lines[k].points[1].y;

					res += sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
					k++;
					
				}while(polygons[index].lines[k].points[0].name[0] == 'P');
			}
			else // a polygon defined by points
			{
				do
				{
					x1 = polygons[index].points[k].x; y1 = polygons[index].points[k].y;
					x2 = polygons[index].points[k+1].x; y2 = polygons[index].points[k+1].y;

					res += sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
					k++;
					
				}while(polygons[index].points[k+1].name[0] == 'P');

				x1 = polygons[index].points[0].x; y1 = polygons[index].points[0].y;
				x2 = polygons[index].points[k].x; y2 = polygons[index].points[k].y;
				res += sqrt(pow(x1-x2,2.0)+pow(y1-y2,2.0));
			}
		}
		sprintf(result, "%s(%s) = %.1lf", e[0],e[1],res);
		
	}
	else if(strcmp(e[0],"Area") == 0)
	{
		for(i=0 ; i<(*polygon) ; i++)
		{
			if(strcmp(polygons[i].name,e[1]) == 0) index=i;
		}

		if(polygons[index].points[0].name[0] == 'P') // a polygon defined by points
		{
			do
			{
				sum += (polygons[index].points[k].x)*(polygons[index].points[k+1].y)-(polygons[index].points[k+1].x)*(polygons[index].points[k].y);
				k++;
			}while(polygons[index].points[k+1].name[0] == 'P');
			sum += (polygons[index].points[k].x)*(polygons[index].points[0].y)-(polygons[index].points[0].x)*(polygons[index].points[k].y);
			res=sum/2;

			sprintf(result, "%s(%s) = %.1lf", e[0],e[1],res);
		}
		else
		{
			do
			{
				record[count]=polygons[index].lines[count].name[1];
				record[k+1]=polygons[index].lines[count].name[2];
				k++;
				count++;
				flag1++;
			}while(polygons[index].lines[count].points[0].name[0] == 'P');

			for(i=0 ; i<flag1 ; i++)
			{
				for(j=0 ; j<flag1 ; j++)
				{
					if(record[i] == rec[j]) flag2++;
				}
				if(flag2 == 0) 
				{
					rec[c]=record[i];
					c++;
				}
				flag2=0;
			}
			k=0;
			for(i=0 ; i<c-1 ; i++)
			{
				sum += (points[k].x)*(points[k+1].y)-(points[k+1].x)*(points[k].y);
				k++;
			}
			sum += (points[k].x)*(points[0].y)-(points[0].x)*(points[k].y);	
			res=sum/2;

			sprintf(result, "%s(%s) = %.1lf", e[0],e[1],res);
			
		}
	}
}
void data(char str[ARRAY_SIZE],int *point, int *line,int *polygon,struct point points[100],struct line lines[100],struct polygon polygons[100])
{
	char e[30][100];
	int k=0;
	int i,index=0;

	sscanf(str,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",e[0],e[1],e[2],e[3],e[4],e[5],e[6],e[7],e[8],e[9],e[10],e[11],e[12],e[13],e[14],e[15],e[16],e[17],e[18],e[19],e[20],e[21]);

	if(e[0][0] != 'P' && e[0][0] != 'L') // this is a point
	{
		points[*point].x = strtof(e[0],NULL);
		points[*point].y = strtof(e[1],NULL);
		strcpy(points[*point].name,e[2]);
		(*point)++;
	}
	else if(e[0][0] == 'P' && e[2][0] == 'L') // this is a line
	{
		lines[*line].points[0] = points[(int)e[0][1]-49];
		lines[*line].points[1] = points[(int)e[1][1]-49];
		strcpy(lines[*line].name,e[2]);
		(*line)++;
	}
	else // this is a polygon
	{
		if(e[k][0] == 'P')
		{
			do
			{
				for(i=0 ; i<(*point) ; i++)
				{
					if(strcmp(points[i].name,e[k]) == 0) index=i;
				}
				
				polygons[*polygon].points[k] = points[index];
				
				k++;
			}while(e[k][1] != 'G');
		}
		else if(e[k][0] == 'L')
		{
			do
			{
				for(i=0 ; i<(*line) ; i++)
				{
					if(strcmp(lines[i].name,e[k]) == 0) index=i;
				}
				polygons[*polygon].lines[k] = lines[index];
				k++;
			}while(e[k][1] != 'G');
		}
		
		strcpy(polygons[*polygon].name,e[k]);

		
		(*polygon)++;
	}
}
void read_file(char arr[ARRAY_SIZE],char str[ARRAY_SIZE])
{
	char* st;

	sscanf(arr,"%[^\r]",arr);
	st = strtok(arr,"/"); 
	st = strtok(arr,"\\");
	strcpy(str,st);

	/* 
		You had said that comments starts with “\\” in pdf 
		   but in example text file, you've used "//" for comments
		   		so i've checked the line for both of them, 
		   			because i do not know which one is true.
	*/
}



			
