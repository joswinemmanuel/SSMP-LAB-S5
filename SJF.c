#include <stdio.h>

struct Process {
	int Name;
	int Burst_Time;
	int Arrival_Time;
	int Turn_Around_Time;
	int Waiting_Time;
};

int main() {
    int n, bt=0, min=0, k=1;
	float wt=0, tat=0, total_wt=0, total_tat=0;
	printf("Enter the number of process : ");
	scanf("%d", &n);
	struct Process p[n], temp;

    for(int i=0; i<n; i++) {
		p[i].Name = i;
		printf("\nEnter the Burst Time of P%d : ", i);
		scanf("%d", &p[i].Burst_Time);
        printf("Enter the Arrival Time of P%d : ", i);
		scanf("%d", &p[i].Arrival_Time);
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].Arrival_Time > p[j+1].Arrival_Time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    for(int i=0; i<n; i++) {
        bt += p[i].Burst_Time;
        min = p[k].Burst_Time;
        for(int j=k; j<n; j++) {
            if(bt>=p[j].Arrival_Time && p[j].Burst_Time<min) {
                temp = p[k];
                p[k] = p[j];
                p[j] = temp;
            }
        }
        k++;
    }

    p[0].Waiting_Time = 0;
    for(int i=1; i<n; i++) {
        wt += p[i-1].Burst_Time;
        p[i].Waiting_Time = wt - p[i].Arrival_Time;
        total_wt += p[i].Waiting_Time;
    }

    for(int i=0; i<n; i++) {
        tat += p[i].Burst_Time;
        p[i].Turn_Around_Time = tat - p[i].Arrival_Time;
        total_tat += p[i].Turn_Around_Time;
    }

    printf("\nGantt Chart\n");
	printf("|");
	for(int i=0; i<n; i++) {
		printf("  P%d  |", p[i].Name);
	}
	printf("\n");
	printf("0      ");
	for(int i=0; i<n; i++) {
		printf("%d      ", p[i].Turn_Around_Time+p[i].Arrival_Time);
	}
	printf("\n\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].Name > p[j+1].Name) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    printf("\n      Burst Time\tArrival Time\tTurn Around Time\tWaiting Time\n");
	for(int i=0; i<n; i++) {
		printf("P%d    %d\t\t\t%d\t\t%d\t\t\t%d\n", p[i].Name, p[i].Burst_Time, p[i].Arrival_Time, p[i].Turn_Around_Time, p[i].Waiting_Time);
	}
	printf("\n");
    printf("\n");

    printf("Total Turn Around Time : %f\n", total_tat);
	printf("Total Waiting Time : %f\n", total_wt);
	printf("Average Turn Around Time : %f\n", total_tat/n);
	printf("Average Waiting Time : %f\n\n", total_wt/n);
}

/*
Enter the number of process : 5

Enter the Burst Time of P0 : 6
Enter the Arrival Time of P0 : 2

Enter the Burst Time of P1 : 2
Enter the Arrival Time of P1 : 5

Enter the Burst Time of P2 : 8
Enter the Arrival Time of P2 : 1

Enter the Burst Time of P3 : 3
Enter the Arrival Time of P3 : 0

Enter the Burst Time of P4 : 4
Enter the Arrival Time of P4 : 4

Gantt Chart
|  P3  |  P0  |  P1  |  P4  |  P2  |
0      3      9      11      15      23      


      Burst Time        Arrival Time    Turn Around Time        Waiting Time
P0    6                 2               7                       1
P1    2                 5               6                       4
P2    8                 1               22                      14
P3    3                 0               3                       0
P4    4                 4               11                      7


Total Turn Around Time : 49.000000
Total Waiting Time : 26.000000
Average Turn Around Time : 9.800000
Average Waiting Time : 5.200000
*/
