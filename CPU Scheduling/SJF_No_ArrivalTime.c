#include <stdio.h>

struct Process {
	int name;
	int burst_time;
	int completion_time;
	int turn_around_time;
	int waiting_time;
};

int main() {
	int n, current=0;
	float total_tat=0, total_wt=0;
	printf("Enter the number of process : ");
	scanf("%d", &n);

	struct Process p[n], temp;

	for(int i=0; i<n; i++) {
		p[i].name = i;
		printf("Enter the burst time of process P%d : ", i);
		scanf("%d", &p[i].burst_time);
	}

	for(int i=0; i<n; i++) {
		for(int j=0; j<n-i-1; j++) {
			if(p[j].burst_time > p[j+1].burst_time) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}

	for(int i=0; i<n; i++) {
		current += p[i].burst_time;
		p[i].completion_time = current;
		p[i].turn_around_time = p[i].completion_time;
		p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
	}

	printf("\nGantt chart\n");
	printf("|");
	for(int i=0; i<n; i++) {
		printf("   P%d   |", p[i].name);
	}
	printf("\n");
	printf("0");
	for(int i=0; i<n; i++) {
		printf("        %d", p[i].completion_time);
	}
	printf("\n\n");

	for(int i=0; i<n; i++) {
		for(int j=0; j<n-i-1; j++) {
			if(p[j].name > p[j+1].name) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}

	printf("     Burst Time		Turn Around Time	Waiting Time\n");
	for(int i=0; i<n; i++) {
		printf("P%d   %d			%d			%d\n", p[i].name, p[i].burst_time, p[i].turn_around_time, p[i].waiting_time);
		total_tat += p[i].turn_around_time;
		total_wt += p[i].waiting_time;
	}

	printf("\nTotal Turn Around Time : %f\n", total_tat);
	printf("Total Waiting Time : %f\n", total_wt);
	printf("Average Turn Around Time : %f\n", total_tat/n);
	printf("Average Waiting Time : %f\n", total_wt/n);
}

/*
Enter the number of process : 5
Enter the burst time of process P0 : 3
Enter the burst time of process P1 : 1
Enter the burst time of process P2 : 4
Enter the burst time of process P3 : 2 
Enter the burst time of process P4 : 5

Gantt chart
|   P1   |   P3   |   P0   |   P2   |   P4   |
0        1        3        6        10        15

     Burst Time         Turn Around Time        Waiting Time
P0   3                  6                       3
P1   1                  1                       0
P2   4                  10                      6
P3   2                  3                       1
P4   5                  15                      10

Total Turn Around Time : 35.000000
Total Waiting Time : 20.000000
Average Turn Around Time : 7.000000
Average Waiting Time : 4.000000
*/
