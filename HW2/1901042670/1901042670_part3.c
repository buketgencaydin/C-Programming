#include <stdio.h>

#define EURO 6.69
#define DOLLAR 6.14

int main()
{
	double amount;
	int currency1,currency2;

	printf("***** Welcome to ABC Exchange Office *****\n\n");

	printf("Enter your amount:\n");
	scanf("%lf",&amount);

	printf("\nPlease select your currency\n");
	printf("1. Turkish Lira\n");
	printf("2. Euro\n");
	printf("3. Dollar\n\n");

	scanf("%d",&currency1);

	if(currency1==1 || currency1==2 || currency1==3)
	{

	switch(currency1)
	{
		case 1 :
		printf("You have %lf Turkish Liras\n",amount);

		printf("Choose which currency you want to convert\n");
	    scanf("%d",&currency2);

	    if(currency2==1 || currency2==2 || currency2==3)
	    {
	    
		    switch(currency2)
		    {
		    	case 1 :
			    printf("\nYou have %lf Turkish Liras\n",amount);
			    break; 

			    case 2 :
			    printf("\nYou have %lf Euro\n",(amount/EURO));
			    break;

				case 3 :
		        printf("\nYou have %lf Dollar\n",(amount/DOLLAR));
		        break;
		    }
		}
		else
		{
		    printf("\nYour selection is invalid!\n");	
		}
		break;

		case 2 :
		printf("You have %lf Euro\n",amount);

		printf("Choose which currency you want to convert\n");
	    scanf("%d",&currency2);

	    if(currency2==1 || currency2==2 || currency2==3)
	    {
	    

			switch(currency2)
		    {
			    case 1 :
			    printf("\nYou have %lf Turkish Liras\n",(amount*EURO));
			    break;

			    case 2 :
		        printf("You have %lf Euro\n",amount);
		        break;

                case 3 :
		        printf("\nYou have %lf Dollar\n",(amount*(EURO/DOLLAR)));
		        break;
		    }
		}
		else
		{
			printf("\nYour selection is invalid!\n");
		}

		 break;
		

        case 3 :
		printf("You have %lf Dollar\n",amount);

		printf("Choose which currency you want to convert\n");
	    scanf("%d",&currency2);

	    if(currency2==1 || currency2==2 || currency2==3)
	    {
	    

			switch(currency2)
		    {
			    case 1 :
			    printf("\nYou have %lf Turkish Liras\n",(amount*DOLLAR));
			    break;

				case 2 :
		        printf("\nYou have %lf Euro\n",(amount*(DOLLAR/EURO)));
		        break;

		        case 3 :
		        printf("You have %lf Dollar\n",amount);
		        break;
            }
        }
        else
        {
        	printf("\nYour selection is invalid!\n");
        }
		break;
   
}
}
 else
 {
 	printf("\nYour selection is invalid!\n");
 }

	return 0;


}