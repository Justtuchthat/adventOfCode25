#include <stdio.h>
#include <stdlib.h>

typedef struct Range {
    unsigned long start, end;
    struct Range* next;
} Range;

typedef enum Freshness {
    FRESH, SPOILED
} Freshness;

Range* allocRange(unsigned long start, unsigned long end) {
    Range* range = calloc(1, sizeof(Range));
    range->start = start;
    range->end = end;
    range->next = NULL;
    return range;
}

void freeRange(Range* toFree) {
    if (toFree == NULL) return;
    freeRange(toFree->next);
    free(toFree);
}

Range* insertRange(Range* list, Range* new) {
    if (list == NULL) return new;
    if (new->start < list->start) {
        new->next = list;
        return new;
    }
    list->next = insertRange(list->next, new);
    return list;
}

Range* readRange() {
    unsigned long start, end;
    scanf("%lu-%lu", &start, &end);
    Range* list = allocRange(start, end);
    while (scanf("%lu-%lu", &start, &end) == 2) {
        Range* new = allocRange(start, end);
        list = insertRange(list, new);
    }
    Range* firstID = allocRange(start, start);
    firstID->next = list;
    return firstID;
}

void compressRange(Range* list) {
    if (list == NULL) return;
    if (list->next == NULL) return;
    if (list->end > list->next->start) {
        Range* toFree = list->next;
        if (list->end < toFree->end)
            list->end = toFree->end;
        list->next = toFree->next;
        free(toFree);
        compressRange(list);
    }
    compressRange(list->next);
}

Freshness checkIfFresh(Range* list, unsigned long id) {
    if (list == NULL) return SPOILED;
    if (id < list->start) return SPOILED;
    if (id <= list->end) return FRESH;
    return checkIfFresh(list->next, id);
}

int main() {
    Range* list = readRange();
    unsigned long id = list->start;
    Range* toFree = list;
    list = list->next;
    free(toFree);
    compressRange(list);
    int available = checkIfFresh(list, id) == FRESH;
    while (scanf("%lu\n", &id) != EOF) {
        if (checkIfFresh(list, id) == FRESH) available++;
    }
    printf("Available ingredients: %d\n", available);
    freeRange(list);
}