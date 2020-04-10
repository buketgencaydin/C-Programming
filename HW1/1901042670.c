/*
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670.c 
$ gcc 1901042670.o -o 1901042670 -lm
$ ./1901042670 
*/

#include <stdio.h> /* standard input/output definitions */
#include <math.h> /* mathematical declarations used for sqrt() and fabs() */

void find_root(); /* reads three integers as coefficients of an equation and calculates its roots */
void find_newtonian_root(); /* searchs for the roots of an equation by an iterative method called Newton's Algorithm */
int find_multiple_closest(int a, int b); /* calculates divisibility of the given first integer by second one.
                                            if it is not, it finds the closest divisible integer */

int main()
	{
		int num1, num2, result;

		find_root();

		find_newtonian_root();
		
	    printf("Enter the first integer:");
		scanf("%d", &num1);

		printf("Enter the second integer:");
		scanf("%d", &num2);

		result = find_multiple_closest(num1, num2);

		if(result == num1)
		{
			printf("Closest number to %d that is multiple of %d is itself.\n\n", num1, num2);
		}
		else
		{
			printf("Closest number to %d that is multiple of %d is %d.\n\n", num1, num2, result);
		}

		return 0;
	}

void find_root()
	{
		int coef1, coef2, coef3;
		double delta, root1, root2;
		
		printf("Please Enter the first coefficient:");
		scanf("%d", &coef1);

		printf("Please Enter the second coefficient:");
		scanf("%d", &coef2);

		printf("Please Enter the third coefficient:");
		scanf("%d", &coef3);

		delta = (coef2*coef2) - (4*coef1*coef3); /* delta = b*b - 4*a*c */

		if(delta < 0)
			{
				printf("Your equation %dx^2", coef1);

			    /* if statements will provide to print 
			       1x^2-3x-4  instead of 1x^2+-3x+-4 
			    */

			    if(coef2<0)
				    {
				    	printf("%dx",coef2);      
				    }
			    else
				    {
				    	printf("+%dx", coef2);
				    }


			    if(coef3<0)
				    {
				    	printf("%d",coef3);
				    }
			    else
				    {
				    	printf("+%d", coef3);
				    }
		        
		        printf(" does not have any real roots.\n\n"); 
			}
		else
			{   
				/* root1,2 = -b + sqrt(delta)  ,  -b - sqrt(delta)
				             ----------------     ---------------- 
		                            2a                 2a
		        */

				root1 = (-coef2 + sqrt(delta)) / (2*coef1);
				root2 = (-coef2 - sqrt(delta)) / (2*coef1);

				printf("Your equation  %dx^2", coef1);

			    /* if statements will provide to print 
			       1x^2-3x-4  instead of 1x^2+-3x+-4 
			    */

			    if(coef2<0)
				    {
				    	printf("%dx",coef2);      
				    }
			    else
				    {
				    	printf("+%dx", coef2);
				    }


			    if(coef3<0)
				    {
				    	printf("%d",coef3);
				    }
			    else
				    {
				    	printf("+%d", coef3);
				    }
					printf(" have real roots {%.0lf,%.0lf}.\n\n",root1, root2);

			}
	}		
	

void find_newtonian_root()
	{
		int coef1, coef2, coef3;
		double delta, root1, root2, root;
		int  coef_1;    /* coefficient for after derivation */
		double x, y, s;  /* variables for x, f(x) and f(x)/f'(x) */ 
		                  
		
		printf("Please Enter the first coefficient:");
		scanf("%d", &coef1);

		printf("Please Enter the second coefficient:");
		scanf("%d", &coef2);

		printf("Please Enter the third coefficient:");
		scanf("%d", &coef3);

		printf("Please Enter the initial:");
		scanf("%lf", &x);

        delta = (coef2*coef2) - (4*coef1*coef3); /* delta = b*b - 4*a*c */

		root1 = (-coef2 + sqrt(delta)) / (2*coef1);
		root2 = (-coef2 - sqrt(delta)) / (2*coef1);

		if((fabs(x-root1)) < (fabs(x-root2))) /* it chooses the closer root to initial for "difference" part */
			{
				root=root1;
			}
		else
			{
				root=root2;
			} 

	    printf("Your equation is %dx^2", coef1);

	    /* if statements will provide to print 
	       1x^2-3x-4  instead of 1x^2+-3x+-4 
	    */

	    if(coef2<0)
		    {
		    	printf("%dx",coef2);      
		    }
	    else
		    {
		        printf("+%dx", coef2);
		    }


	    if(coef3<0)
		    {
		    	printf("%d and iterations are\n\n",coef3);
		    }
	    else
		    {
		    	printf("+%d and iterations are\n\n", coef3);
		    }


	       printf("Step      x     f(x)      Difference\n\n");

	    /* 
		    "Newton's Algorithm"

		    x(n+1) = x(n)- f(x) 
		                  ------
		                   f'(x)

	    */

	       coef_1 = 2 * coef1; /*derivation for x^2 term */
	    
	      
	       s = (coef1*x*x + coef2*x + coef3)/(coef_1*x + coef2); /*  f(x)/f'(x)  */
	       x = x - s ; /* x(n+1) = x(n) - [f(x)/f'(x)] */
	       y = (coef1*x*x + coef2*x + coef3); /* f(x) */
	       printf("x%d     %.4lf  %.4lf     %.4lf\n",1,x,y,(x-root));  /* printing step 1 */
	    
	       
	       s = (coef1*x*x + coef2*x + coef3)/(coef_1*x + coef2);
	       x = x - s ;
	       y = (coef1*x*x + coef2*x + coef3);
	       printf("x%d     %.4lf  %.5lf     %.4lf\n",2,x,y,(x-root));  /* printing step 2 */

	      
	       s = (coef1*x*x + coef2*x + coef3)/(coef_1*x + coef2);
	       x = x - s ;
	       y = (coef1*x*x + coef2*x + coef3);
	       printf("x%d     %.4lf  %.5lf     %.4lf\n",3,x,y,(x-root));  /* printing step 3 */

	       
	       s = (coef1*x*x + coef2*x + coef3)/(coef_1*x + coef2);
	       x = x - s ;
	       y = (coef1*x*x + coef2*x + coef3);
	       printf("x%d     %.4lf  %.5lf     %.4lf\n",4,x,y,(x-root));  /* printing step 4 */

	       s = (coef1*x*x + coef2*x + coef3)/(coef_1*x + coef2);
	       x = x - s ;
	       y = (coef1*x*x + coef2*x + coef3);
	       printf("x%d     %.4lf  %.5lf     %.4lf\n\n",5,x,y,(x-root));  /* printing step 5 */
	}

int find_multiple_closest(int a, int b) 
	{
		int remainder = a % b;

		if(remainder == 0)
			{
				return a;
			}
		else if((b - remainder) <= remainder)
			{
				return a + (b - remainder);  /* returns closest number above the first number */
			}
	    else
		    {
		    	return a - remainder;  /* returns closest number below the first number */
		    }

	}

