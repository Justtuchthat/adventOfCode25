#include <stdio.h>
#include <stdlib.h>

typedef struct Range {
    unsigned long start, end;
    struct Range* next;
} Range;

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
    return list;
}

void compressRange(Range* list) {
    if (list == NULL) return;
    if (list->next == NULL) return;
    if (list->end >= list->next->start-1) {
        Range* toFree = list->next;
        if (list->end < toFree->end)
            list->end = toFree->end;
        list->next = toFree->next;
        free(toFree);
        compressRange(list);
    }
    compressRange(list->next);
}

unsigned long countFreshIngredients(Range* list) {
    if (list == NULL) return 0;
    return list->end - list->start + 1 + countFreshIngredients(list->next);
}

int main() {
    Range* list = readRange();
    compressRange(list);
    printf("Counted total fresh ingredeints: %lu\n", countFreshIngredients(list));
    freeRange(list);
}