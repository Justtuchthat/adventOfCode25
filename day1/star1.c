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
    int dial = 50, password = 0; // Start dial in middle, password at 0;
    int change = readLine();
    while (change) { // If change is 0, EOF was reached so stop
        dial += change; // Add change
        dial %= 100; // Make sure dial stays in 0-99
        while (dial < 0) dial += 100; // Modulo stays negative, so have to do this to make positive
        change = readLine();
        if (dial == 0) password++; // increase password if dial at 0
    }
    printf("The password to the door is: %d\n", password);
    return 0;
}