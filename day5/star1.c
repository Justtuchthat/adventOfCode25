#include <stdio.h>
#include <stdlib.h>

typedef struct Range {
    unsigned long start, end;
    struct Range* next;
} Range;

typedef enum Freshness {
    FRESH, SPOILED // To ensure I dont twist what is what
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
    scanf("%lu-%lu", &start, &end);
    Range* list = allocRange(start, end); // First range in list
    while (scanf("%lu-%lu", &start, &end) == 2) { // Continue while can read 2 numbers
        Range* new = allocRange(start, end); // Create new range
        list = insertRange(list, new); // Add new range to list
    }
    Range* firstID = allocRange(start, start); // First ID is read, so return it using another range object
    firstID->next = list; // Add the list to the range object returning the first ID
    return firstID;
}

void compressRange(Range* list) {
    if (list == NULL) return; // No list = No compressing required
    if (list->next == NULL) return; // No following list = No compressing required
    if (list->end > list->next->start) { // If the end of current range is bigger than start of following range compress the ranges
        Range* toFree = list->next; // Save following range to free the memory
        if (list->end < toFree->end) // If the current range end is smaller than the new range end save the new range end
            list->end = toFree->end;
        list->next = toFree->next; // Remove the next range from the list
        free(toFree); // Free the next range
        compressRange(list); // Compress this list again, maybe a few ranges in a row can be compressed
    }
    compressRange(list->next); // Since the first range cannot be compressed, try the next range
}

Freshness checkIfFresh(Range* list, unsigned long id) {
    if (list == NULL) return SPOILED; // If we run out of ranges to check, ingredient ID is spoiled
    if (id < list->start) return SPOILED; // If ID is smaller than current starting range, it is spoiled
    if (id <= list->end) return FRESH; // Ingredient is larger than or equal to start, and smaller or equal to end of range, so fresh
    return checkIfFresh(list->next, id); // Ingredient is larger than end of range, so check next range
}

int main() {
    Range* list = readRange(); // Read range list
    unsigned long id = list->start; // Get first ID from range list
    Range* toFree = list; // Save first range object to free the memory
    list = list->next; // Get the actual list of ranges
    free(toFree); // Free the object returning the first ID
    compressRange(list); // Compress ranges to save on runtime
    int available = checkIfFresh(list, id) == FRESH; // Calculate if first ID is fresh
    while (scanf("%lu\n", &id) != EOF) { // Continue until we reach EOF
        if (checkIfFresh(list, id) == FRESH) available++; // Increase available ingredients counter if ingredient ID is fresh
    }
    printf("Available ingredients: %d\n", available);
    freeRange(list); // Dont forget to clean your memory
}