#include "record.c"
#include "sortingalgorithms.c"
#include "filereader.c"
#include "timer.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RECORDS 100000

int main()
{
    char filename[] = "random25000.txt"; 

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    int n;
    if (fscanf(fp, "%d", &n) != 1) {
        printf("Error: File does not start with an integer count.\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    Record *arr = (Record *)malloc(n * sizeof(Record));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    readFile(arr, filename);

    Record *copy = (Record *)malloc(n * sizeof(Record));
    if (copy == NULL) {
        free(arr);
        return 1;
    }

    memcpy(copy, arr, n * sizeof(Record));

    printf("Sorting %d records from %s...\n", n, filename);

    long startTime = currentTimeMillis();
    insertionSort(copy, n);
    long endTime = currentTimeMillis();

    printf("Done!\n");
    printf("Time: %ld ms\n", endTime - startTime);

    free(copy);
    free(arr);

    return 0;
}

