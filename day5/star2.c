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
    if (list == NULL) return new; // If end is reached append newest range
    if (new->start < list->start) { // If current list start is bigger append it to newest range
        new->next = list;
        return new;
    }
    list->next = insertRange(list->next, new); // Newest range is bigger than first range in list, so run again on nest range in list
    return list;
}

Range* readRange() {
    unsigned long start, end;
    scanf("%lu-%lu", &start, &end); // Read first range
    Range* list = allocRange(start, end); // Start first list Item
    while (scanf("%lu-%lu", &start, &end) == 2) {
        Range* new = allocRange(start, end); // Make new range
        list = insertRange(list, new); // Insert new range in order in list
    }
    return list;
}

void compressRange(Range* list) {
    if (list == NULL) return; // No list = No compressing required
    if (list->next == NULL) return; // No following list = No compressing required
    if (list->end >= list->next->start-1) { // If the end of current range is bigger than start of following range compress the ranges
        Range* toFree = list->next; // Save following range to free the memory
        if (list->end < toFree->end) // If the current range end is smaller than the new range end save the new range end
            list->end = toFree->end;
        list->next = toFree->next; // Remove the next range from the list
        free(toFree); // Free the next range
        compressRange(list); // Compress this list again, maybe a few ranges in a row can be compressed
    }
    compressRange(list->next); // Since the first range cannot be compressed, try the next range
}

unsigned long countFreshIngredients(Range* list) {
    if (list == NULL) return 0; // End of list, return 0
    return list->end - list->start + 1 + countFreshIngredients(list->next); // Calculate how many fresh IDs are in current range, and add to the rest in the list
}

int main() {
    Range* list = readRange(); // Read the list
    compressRange(list); // Compress to save on runtime and to not double count IDs
    printf("Counted total fresh ingredeints: %lu\n", countFreshIngredients(list));
    freeRange(list); // Don't forget to clean up your memory
}