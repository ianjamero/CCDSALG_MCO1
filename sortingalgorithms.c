#ifndef SORTINGALGORITHMS_C
#define SORTINGALGORITHMS_C

#include <stdio.h>
#include <stdlib.h>
#include "record.c"

/*
    Simple beginner-style sorting implementations.
    Assumes Record has a field: int id;
*/

/* ---------------- INSERTION SORT ---------------- */
void insertionSort(Record *arr, int n)
{
    int i, j;
    Record key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j].idNumber > key.idNumber)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/* ---------------- SELECTION SORT ---------------- */
void selectionSort(Record *arr, int n)
{
    int i, j, min_idx;
    Record temp;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;

        for (j = i + 1; j < n; j++)
        {
            if (arr[j].idNumber < arr[min_idx].idNumber)
                min_idx = j;
        }

        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

/* ---------------- MERGE FUNCTION ---------------- */
void merge(Record *arr, int p, int q, int r)
{
    int i, j, k;
    int n1 = q - p + 1;
    int n2 = r - q;

    Record *L = (Record *)malloc(sizeof(Record) * n1);
    Record *R = (Record *)malloc(sizeof(Record) * n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[p + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[q + 1 + j];

    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2)
    {
        if (L[i].idNumber <= R[j].idNumber)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

/* ---------------- MERGE SORT ---------------- */
void mergeSort(Record *arr, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;

        mergeSort(arr, p, q);
        mergeSort(arr, q + 1, r);
        merge(arr, p, q, r);
    }
}

/* ---------------- PARTITION (for quick sort) ---------------- */
int partition(Record *arr, int low, int high)
{
    Record pivot = arr[high];
    int i = low - 1;
    int j;
    Record temp;

    for (j = low; j < high; j++)
    {
        if (arr[j].idNumber < pivot.idNumber)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

/* ---------------- QUICK SORT ---------------- */
void quickSort(Record *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#endif

