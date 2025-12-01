#include <stdio.h>

int readLine() {
    char dir;
    int amount;
    if (scanf("%c%d\n", &dir, &amount) == EOF) {
        return 0;
    }
    if (dir == 'L') amount *= -1;
    return amount;
}

int main() {
    int dial = 50, password = 0;
    int change = readLine();
    while (change) {
        if (change < 0) {
            while (change) {
                dial--;
                change++;
                if (dial == 0) password++;
                if (dial == -1) dial = 99;
            }
        } else {
            while (change) {
                dial++;
                change--;
                if (dial == 100) dial = 0;
                if (dial == 0) password++;
            }
        }
        change = readLine();
    }
    printf("The password to the door is: %d\n", password);
    return 0;
}