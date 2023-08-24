#include <stdio.h>

struct Process {
	int Name;
	int Burst_Time;
	int Completion_Time;
	int Turn_Around_Time;
	int Waiting_Time;
    int Remaining_Time;
};

int main() {
    int n, current_ct=0, time_slice, k=0, flag=0, a[50];
	float total_tat=0, total_wt=0;
	printf("Enter the number of process : ");
	scanf("%d", &n);
	struct Process p[n];

	for(int i=0; i<n; i++) {
		p[i].Name = i;
		printf("Enter the Burst Time of P%d : ", i);
		scanf("%d", &p[i].Burst_Time);
        p[i].Remaining_Time = p[i].Burst_Time;
    }

    printf("Enter the time slice : ");
    scanf("%d", &time_slice);

    printf("Gantt Chart\n");
    printf("\n|");
    for(int i=0; i<n; i++) {
        flag = 0;
        if(p[i].Remaining_Time<time_slice && p[i].Remaining_Time>0) {
            printf("  P%d  |", i);
            current_ct += p[i].Remaining_Time;
            p[i].Completion_Time = current_ct;
            p[i].Remaining_Time = 0;
            a[k++] = current_ct;
        }
        else if(p[i].Remaining_Time>0) {
            printf("  P%d  |", i);
            current_ct += time_slice;
            p[i].Remaining_Time = p[i].Remaining_Time-time_slice;
            if(p[i].Remaining_Time==0) {
                p[i].Completion_Time = current_ct;
            }
            a[k++] = current_ct;
        }
        for(int j=0; j<n; j++) {
            if(p[j].Remaining_Time != 0)
                flag=1;
        } 
        if((i==n-1) && (flag==1))
            i=-1;
    }

    printf("\n");
    printf("0      ");
    for(int i=0; i<k; i++)
        printf("%d      ", a[i]);
    printf("\n");
        
    for(int i=0; i<n; i++) {
        p[i].Turn_Around_Time = p[i].Completion_Time;
        p[i].Waiting_Time = p[i].Turn_Around_Time-p[i].Burst_Time;
    }

    printf("\n    Turnaround time\tWaiting time\n");
    for(int i=0; i<n; i++) {
        printf("P%d  %d\t\t\t%d\n", i, p[i].Turn_Around_Time, p[i].Waiting_Time);
        total_tat += p[i].Turn_Around_Time;
        total_wt += p[i].Waiting_Time;
    }

    printf("\nTotal Turnaround time : %f ", total_tat);
    printf("\nTotal Waiting time : %f ", total_wt);
    printf("\nAverage Turnaround time : %f ", total_tat/n);
    printf("\nAverage Waiting time : %f \n", total_wt/n);
}

/*
Enter the number of process : 3
Enter the Burst Time of P0 : 5
Enter the Burst Time of P1 : 4
Enter the Burst Time of P2 : 6
Enter the time slice : 3
Gantt Chart

|  P0  |  P1  |  P2  |  P0  |  P1  |  P2  |
0      3      6      9      11      12      15      

    Turnaround time     Waiting time
P0  11                  6
P1  12                  8
P2  15                  9

Total Turnaround time : 38.000000 
Total Waiting time : 23.000000 
Average Turnaround time : 12.666667 
Average Waiting time : 7.666667 
*/
