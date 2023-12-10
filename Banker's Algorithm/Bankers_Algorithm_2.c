#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, r, count=0, k=0, flag, executed;
	printf("Enter the number of processes : ");
	scanf("%d", &n);
	int visited[n], safe[n];
	printf("Enter the number of resources : ");
	scanf("%d", &r);

	int alloc[n][r], max[n][r], need[n][r], avail[r];

	printf("Enter the available resources : ");
	for(int i=0; i<r; i++) {
		scanf("%d", &avail[i]);
	}

	for(int i=0; i<n; i++) {
		visited[i] = 0;
		printf("Enter the allocation of P[%d] : ", i);
		for(int j=0; j<r; j++) {
			scanf("%d", &alloc[i][j]);
		}
		printf("Enter the max of P[%d] : ", i);
		for(int j=0; j<r; j++) {
			scanf("%d", &max[i][j]);
		}
	
		for(int j=0; j<r; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	
	printf("      Allocation\tMax\t\tNeed\t\tAvailable\n");
	for(int i=0; i<n; i++) {
		printf("P[%d]  ", i);
		for(int j=0; j<r; j++) {
			printf("%d ", alloc[i][j]);
		}
		printf("\t\t");
		for(int j=0; j<r; j++) {
			printf("%d ", max[i][j]);
		}
		printf("\t\t");
		for(int j=0; j<r; j++) {
			printf("%d ", need[i][j]);
		}
		if(i==0) {
			printf("\t\t");
			for(int j=0; j<r; j++) {
				printf("%d ", avail[j]);
			}
		}
		printf("\n");
	}

	while(count < n) {
		flag = 0;
		for(int i=0; i<n; i++) {
			executed = 0;
			for(int j=0; j<r; j++) {
				if(need[i][j] <= avail[j]) {
					executed++;
				}
			}
			if((executed==r) && visited[i]==0) {
				for(int j=0; j<r; j++) {
					avail[j] += alloc[i][j];
				}
				flag = 1;
				visited[i] = 1;
				safe[k++] = i;
				count++;
			}
		}
		if(flag==0) {
			printf("No safe sequence\n");
			exit(0);
		}

	}

	printf("Safe sequence : ");
	printf(" < ");
	for(int i=0; i<n; i++) {
		printf("P%d ", safe[i]);
	}
	printf(">\n");
}

/*
Enter the number of processes : 5
Enter the number of resources : 3
Enter the available resources : 3 3 2
Enter the allocation of P[0] : 0 1 0
Enter the max of P[0] : 7 5 3
Enter the allocation of P[1] : 2 0 0
Enter the max of P[1] : 3 2 2
Enter the allocation of P[2] : 3 0 2
Enter the max of P[2] : 9 0 2
Enter the allocation of P[3] : 2 1 1
Enter the max of P[3] : 2 2 2
Enter the allocation of P[4] : 0 0 2
Enter the max of P[4] : 4 3 3
      Allocation        Max             Need            Available
P[0]  0 1 0             7 5 3           7 4 3           3 3 2 
P[1]  2 0 0             3 2 2           1 2 2 
P[2]  3 0 2             9 0 2           6 0 0 
P[3]  2 1 1             2 2 2           0 1 1 
P[4]  0 0 2             4 3 3           4 3 1 
Safe sequence :  < P1 P3 P4 P0 P2 >
*/
