#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void scan(int requests[], int n, int start, int direction) {
    int i, j;
    int totalMovement = 0;
    int currentPos = start;
    int nextPos;

    printf("Sequence of movement: ");

    if (direction == 1) {
        for (i = currentPos; i <= MAX_REQUESTS; i++) {
            printf("%d ", i);
            totalMovement += abs(currentPos - i);
            currentPos = i;
        }

        direction = -1;
        printf("%d ", MAX_REQUESTS);

        for (j = MAX_REQUESTS - 1; j >= 0; j--) {
            printf("%d ", j);
            totalMovement += abs(currentPos - j);
            currentPos = j;
        }
    } else {
        for (i = currentPos; i >= 0; i--) {
            printf("%d ", i);
            totalMovement += abs(currentPos - i);
            currentPos = i;
        }

        direction = 1;
        printf("%d ", 0);

        for (j = 1; j <= MAX_REQUESTS; j++) {
            printf("%d ", j);
            totalMovement += abs(currentPos - j);
            currentPos = j;
        }
    }

    printf("\nTotal head movement: %d\n", totalMovement);
}

int main() {
    int n, i;
    int requests[MAX_REQUESTS];
    int start;
    int direction;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests (cylinder numbers):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start);

    printf("Enter the initial direction (1 for towards higher cylinder numbers, -1 for towards lower cylinder numbers): ");
    scanf("%d", &direction);

    scan(requests, n, start, direction);

    return 0;
}
