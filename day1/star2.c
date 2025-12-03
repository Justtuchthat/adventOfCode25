#include <stdio.h>

int readLine() {
    char dir;
    int amount;
    if (scanf("%c%d\n", &dir, &amount) == EOF) {
        return 0;
    }
    if (dir == 'L') amount *= -1; // When turning left, return negative number
    return amount;
}

int main() {
    int dial = 50, password = 0; /// Start dial in middle, password at 0;
    int change = readLine();
    while (change) { // If change is 0, EOF was reached so stop
        if (change < 0) { // Turning left
            while (change) {
                dial--; // Decrease dial by 1
                change++;
                if (dial == 0) password++; // If rotating past, or end on 0 increment password
                if (dial == -1) dial = 99; // if rotating left from 0, go to 99
            }
        } else { // Turning right
            while (change) {
                dial++; // Increase dial by 1
                change--;
                if (dial == 100) dial = 0; // If rotating right from 99, go to 0
                if (dial == 0) password++; // If rotating past, or end on 0 increment password
            }
        }
        change = readLine();
    }
    printf("The password to the door is: %d\n", password);
    return 0;
}