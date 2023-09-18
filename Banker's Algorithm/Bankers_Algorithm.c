#include<stdio.h>
#include<stdlib.h>
void main() {
	int n,r,i,j,k=0,c=0,f=0,exec=0;
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	int vis[n];
	int a[n];
	printf("Enter the number of resources : ");
	scanf("%d",&r);
	int alloc[n][r],max[n][r],avail[r],need[n][r];
	printf("Enter the available resources : ");
	for(i=0;i<r;i++)
		scanf("%d",&avail[i]);
	for(i=0;i<n;i++) {
		vis[i]=0;
		printf("Enter the max of the process P%d : ",i);
		for(j=0;j<r;j++)
			scanf("%d",&max[i][j]);
		printf("Enter the allocation of the process P%d : ",i);
		for(j=0;j<r;j++)
			scanf("%d",&alloc[i][j]);
		for(j=0;j<r;j++)
			need[i][j]=max[i][j]-alloc[i][j];
	}
	printf("\nAllocation	Max	Need\n");
	for(i=0;i<n;i++) {
		for(j=0;j<r;j++)
			printf("%d ",alloc[i][j]);
		printf("\t\t");
		for(j=0;j<r;j++)
			printf("%d ",max[i][j]);
		printf("\t");
		for(j=0;j<r;j++)
			printf("%d ",need[i][j]);
		printf("\n");
	}
	while(c<n) {
		f=0;
		for(i=0;i<n;i++) {
			exec=0;
			for(j=0;j<r;j++) {
				if(need[i][j]<=avail[j])
				exec++;
				}
			if(exec==r&&vis[i]==0) {
				for(j=0;j<r;j++)
					avail[j]+=alloc[i][j];
				f=1;
				vis[i]=1;
				c++;
				a[k++]=i;
			}
		}
		if(f==0) {
			printf("No safe sequence!!");
			exit(0);
		}
	}
	printf("\nSafe Sequence : \n");
	printf("<");
	for(i=0;i<n;i++)
		printf("P%d ",a[i]);
	printf(">\n");
}

/*
Enter the number of processes : 5
Enter the number of resources : 3
Enter the available resources : 3 3 2
Enter the max of the process P0 : 7 5 3
Enter the allocation of the process P0 : 0 1 0
Enter the max of the process P1 : 3 2 2
Enter the allocation of the process P1 : 2 0 0
Enter the max of the process P2 : 9 0 2
Enter the allocation of the process P2 : 3 0 2
Enter the max of the process P3 : 2 2 2
Enter the allocation of the process P3 : 2 1 1
Enter the max of the process P4 : 4 3 3
Enter the allocation of the process P4 : 0 0 2

Allocation	Max	Need
0 1 0 		7 5 3 	7 4 3 
2 0 0 		3 2 2 	1 2 2 
3 0 2 		9 0 2 	6 0 0 
2 1 1 		2 2 2 	0 1 1 
0 0 2 		4 3 3 	4 3 1 

Safe Sequence : 
< P1 P3 P4 P0 P2 >
*/
