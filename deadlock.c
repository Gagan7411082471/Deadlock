#include <stdio.h>

// Number of processes
#define P 2

// Number of resources
#define R 2

// Function to check for deadlock
int isDeadlock(int alloc[][R], int max[][R], int avail[]) {
    int need[P][R];
    int finish[P] = {0};
    int work[R];
    
    // Calculate the need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize work to available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    // Resource can be allocated
                    for (int k = 0; k < R; k++) {
                        work[k] += alloc[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0) {
            return 1; // Deadlock detected
        }
    }
    return 0; // No deadlock
}

int main() {
    int alloc[P][R], max[P][R], avail[R];

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum matrix
    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }

    // Check for deadlock
    if (isDeadlock(alloc, max, avail)) {
        printf("System is in deadlock.\n");
    } else {
        printf("System is not in deadlock.\n");
    }

    return 0;
}
