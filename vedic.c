#include<stdio.h>
#include<omp.h>

int main()
{

 int x,c,i,y,z,tid=0;
 char ch;
 do{ 
 printf("\nEnter number:");
  scanf("%d",&x);
 omp_set_dynamic(0);

 #pragma omp parallel num_threads(4) shared(x,c,y,z,i) private(tid)
  {
#pragma omp sections
  {
   #pragma omp section
    {
      tid = omp_get_thread_num();  
      i=x%10;
	printf("\n Vedic Maths Logic");
	printf("\n Step 1 : Get mod of the number to be square");
      printf("\nMod %d by thread %d\n",i,tid);
    }
   }
  #pragma omp sections
   {
   #pragma omp section
    {
      tid = omp_get_thread_num(); 
	printf("\n Step 2 : Add mod to the number"); 
      z=x+i;
      printf("\nNo+mod= %d by thread %d\n",z,tid);
    }
   #pragma omp section
    {
      tid = omp_get_thread_num(); 
	printf("\n Step 3 : Subtract mod from the number");  
      y=x-i;
      printf("\nNo-Mod= %d by thread %d\n",y,tid);
    }
   }
   #pragma omp master
    { 
	printf("\n Step 4 : Sqaure is obtained by (No in step 2 * No in step 3) + (mod*mod)"); 
      tid = omp_get_thread_num();  
      c =(z*y)+(i*i); 
     printf("\n Square is:%d by thread %d\n",c,tid);
    }
}
  
printf("Do u want to continue y/n =");
scanf("%s",&ch);
   }while(ch=='y');


 return 0;
}

//output:-
comp-sl-22@compsl22-OptiPlex-3020:~/Desktop/pl3/B3$ gcc vedic.c -fopenmp
comp-sl-22@compsl22-OptiPlex-3020:~/Desktop/pl3/B3$ ./a.out

Enter number:12

 Vedic Maths Logic
 Step 1 : Get mod of the number to be square
Mod 2 by thread 0

 Step 2 : Add mod to the number
No+mod= 14 by thread 1

 Step 3 : Subtract mod from the number
No-Mod= 10 by thread 3

 Step 4 : Sqaure is obtained by (No in step 2 * No in step 3) + (mod*mod)
 Square is:144 by thread 0
Do u want to continue y/n =n
comp-sl-22@compsl22-OptiPlex-3020:~/Desktop/pl3/B3$
