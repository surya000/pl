
/*------------------------------------------------------------------------
Assignment No:
Title: Implement concurrent prims algorithm using OPENMP
Batch:
------------------------------------------------------------------------*/#include<stdio.h>
#include<omp.h>
int a,b,u,v,n,i,j,ne=1,tid;
int visited[10]={0},min,mincost=0,cost[10][10];
void main()
{
	//clrscr();
	printf("\nEnter the number of nodes:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	{
		scanf("%d",&cost[i][j]);
		if(cost[i][j]==0)
		cost[i][j]=999;
	}
	
visited[1]=1;
printf("\n");

while(ne < n)
{

printf("\n\tMin Cost\n");
min=999;


	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
		{
		   #pragma omp parallel sections shared(tid)
		   {
		     #pragma omp section
			if(cost[i][j]< min)
			{
		        	if(visited[i]!=0)
				{
					min=cost[i][j];
					a=u=i;
					b=v=j;
					tid=omp_get_thread_num();
					printf("Thread id =%d\n",tid);
				}
			}
		}
	}	
			
	if(visited[u]==0 || visited[v]==0)
	{
		printf("\n Edge %d:(%d %d) cost:%d\n",ne++,a,b,min);
		mincost+=min;
		visited[b]=1;
	}
	
	cost[a][b]=cost[b][a]=999;

}
}
	printf("\n Minimun cost=%d",mincost);
	printf("\nThread id =%d",tid);
printf("\n\t---- END -----");
printf("\n");

}


/*------------------------------------------------------------------------
OUTPUT
comp-sl-09@compsl09-OptiPlex-3020:~/Desktop$ cc primscon.c -fopenmp
comp-sl-09@compsl09-OptiPlex-3020:~/Desktop$ ./a.out

Enter the number of nodes:4

Enter the adjacency matrix:
0 1 2 4
1 0 3 4
2 3 0 1
4 4 1 0


	Min Cost
Thread id =3

 Edge 1:(1 2) cost:1

	Min Cost
Thread id =1

 Edge 2:(1 3) cost:2
Thread id =2

 Edge 3:(3 4) cost:1

 Minimun cost=4
Thread id =2
	---- END -----
------------------------------------------------------------------------*/
