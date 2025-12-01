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
        dial += change;
        dial %= 100;
        while (dial < 0) dial += 100;
        change = readLine();
        if (dial == 0) password++;
    }
    printf("The password to the door is: %d\n", password);
    return 0;
}