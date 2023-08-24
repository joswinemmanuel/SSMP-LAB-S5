#include <stdio.h>

struct Process {
	int Name;
	int Burst_Time;
	int Priority;
	int Completion_Time;
	int Turn_Around_Time;
	int Waiting_Time;
};

int main() {
	int n, current_ct=0;
	float total_tat=0, total_wt=0;
	printf("Enter the number of process : ");
	scanf("%d", &n);
	struct Process p[n], temp;

	for(int i=0; i<n; i++) {
		p[i].Name = i;
		printf("\nEnter the Burst Time of P%d : ", i);
		scanf("%d", &p[i].Burst_Time);
        printf("Enter the Priority of P%d : ", i);
		scanf("%d", &p[i].Priority);
    }

	for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(p[j].Priority > p[j+1].Priority) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

	for(int i=0; i<n; i++) {
		current_ct += p[i].Burst_Time;
		p[i].Completion_Time = current_ct;
		p[i].Turn_Around_Time = p[i].Completion_Time;
		p[i].Waiting_Time = p[i].Turn_Around_Time - p[i].Burst_Time;
	}

	printf("Gantt Chart\n");
	printf("|");
	for(int i=0; i<n; i++) {
		printf("  P%d  |", p[i].Name);
	}
	printf("\n");
	printf("0      ");
	for(int i=0; i<n; i++) {
		printf("%d      ", p[i].Completion_Time);
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

	printf("\n      Burst Time\tPriority\tTurn Around Time\tWaiting Time\n");
	for(int i=0; i<n; i++) {
		printf("P%d    %d\t\t\t%d\t\t%d\t\t\t%d\n", p[i].Name, p[i].Burst_Time, p[i].Priority, p[i].Turn_Around_Time, p[i].Waiting_Time);
		total_tat += p[i].Turn_Around_Time;
		total_wt += p[i].Waiting_Time;
	}
	printf("\n");

	printf("Total Turn Around Time : %f\n", total_tat);
	printf("Total Waiting Time : %f\n", total_wt);
	printf("Average Turn Around Time : %f\n", total_tat/n);
	printf("Average Waiting Time : %f\n\n", total_wt/n);
}

/*
Enter the number of process : 4

Enter the Burst Time of P0 : 6
Enter the Priority of P0 : 4

Enter the Burst Time of P1 : 8
Enter the Priority of P1 : 1

Enter the Burst Time of P2 : 7
Enter the Priority of P2 : 3

Enter the Burst Time of P3 : 3
Enter the Priority of P3 : 2
Gantt Chart
|  P1  |  P3  |  P2  |  P0  |
0      8      11      18      24      


      Burst Time        Priority        Turn Around Time        Waiting Time
P0    6                 4               24                      18
P1    8                 1               8                       0
P2    7                 3               18                      11
P3    3                 2               11                      8

Total Turn Around Time : 61.000000
Total Waiting Time : 37.000000
Average Turn Around Time : 15.250000
Average Waiting Time : 9.250000
*/
