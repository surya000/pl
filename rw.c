#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
 int i=0,NumberofReaderThread=0,NumberofWriterThread;

omp_lock_t writelock,xlock;
omp_init_lock(&writelock);
omp_init_lock(&xlock);

int readCount=0;

int tid=0;
#pragma omp parallel sections shared(readCount) private(i)
{
 #pragma omp section
 {
    i=0;
    printf("\nReader %d is trying to enter into the Database for reading the data\n",i);

    omp_set_lock(&xlock);
    readCount++;
    if(readCount==1)
    {
      omp_set_lock(&writelock);
    }
    omp_unset_lock(&xlock);

    printf("\nReader %d is reading the database\n",i); 
    printf("\nReader %d is leaving the database\n",i);  
   
    omp_set_lock(&xlock);
    readCount--;
    if(readCount==0)
    {
      omp_unset_lock(&writelock);
    }
    omp_unset_lock(&xlock);
 }

#pragma omp section 
{
    i=0;
    printf("\nWriter %d is trying to enter into database for modifying the data\n",i);
    omp_set_lock(&writelock);
    printf("\nWriter %d is writting into the database\n",i); 
    printf("\nWriter %d is leaving the database\n",i); 
    omp_unset_lock(&writelock);
}

 #pragma omp section
 {
    i=1;
    printf("\nReader %d is trying to enter into the Database for reading the data\n",i);

    omp_set_lock(&xlock);
    readCount++;
    if(readCount==1)
    {
      omp_set_lock(&writelock);
    }
    omp_unset_lock(&xlock);

    printf("\nReader %d is reading the database\n",i); 
    printf("\nReader %d is leaving the database\n",i);  
   
    omp_set_lock(&xlock);
    readCount--;
    if(readCount==0)
    {
      omp_unset_lock(&writelock);
    }
    omp_unset_lock(&xlock);
 }

#pragma omp section
{
    i=1;
    printf("\nWriter %d is trying to enter into database for modifying the data\n",i);
    omp_set_lock(&writelock);
    printf("\nWriter %d is writting into the database\n",i); 
    printf("\nWriter %d is leaving the database\n",i); 
    omp_unset_lock(&writelock);
}

#pragma omp section
 {
    i=2;
    printf("\nReader %d is trying to enter into the Database for reading the data\n",i);

    omp_set_lock(&xlock);
    readCount++;
    if(readCount==1)
    {
      omp_set_lock(&writelock);
    }
    omp_unset_lock(&xlock);

    printf("\nReader %d is reading the database\n",i); 
    printf("\nReader %d is leaving the database\n",i);  
   
    omp_set_lock(&xlock);
    readCount--;
    if(readCount==0)
    {
      omp_unset_lock(&writelock);
    }
    omp_unset_lock(&xlock);
 }

}
	sleep(5);
  omp_destroy_lock(&writelock); 
  omp_destroy_lock(&xlock); 
 return 0;
}


/*-----------------------output----------------------------------
comp-sl-14@compsl14-OptiPlex-3020:~$ cd Desktop
comp-sl-14@compsl14-OptiPlex-3020:~/Desktop$ gcc rw.c -fopenmp
comp-sl-14@compsl14-OptiPlex-3020:~/Desktop$ ./a.out

Reader 0 is trying to enter into the Database for reading the data
Reader 0 is reading the database
Reader 0 is leaving the database
Reader 2 is trying to enter into the Database for reading the data
Reader 2 is reading the database
Reader 2 is leaving the database
Writer 1 is trying to enter into database for modifying the data
Writer 1 is writting into the database
Writer 1 is leaving the database
Writer 0 is trying to enter into database for modifying the data
Writer 0 is writting into the database
Writer 0 is leaving the database
Reader 1 is trying to enter into the Database for reading the data
Reader 1 is reading the database
Reader 1 is leaving the databasecomp-sl-14@compsl14-OptiPlex-3020:~/Desktop$ */


