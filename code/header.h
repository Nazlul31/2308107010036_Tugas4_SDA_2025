#ifndef HEADER_H
#define HEADER_H

#include <string.h>

#define MAX_WORD_LEN 100

// ALGORITMA BUBBLE SORT
// Bubble Sort untuk angka
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Bubble Sort untuk kata
void bubble_sort_words(char arr[][MAX_WORD_LEN], int n) {
    char temp[MAX_WORD_LEN];
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j+1]);
                strcpy(arr[j+1], temp);
            }
        }
    }
}

// ALGORITMA SELECTION SORT
// Selection Sort untuk angka
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// Selection Sort untuk kata
void selection_sort_words(char arr[][MAX_WORD_LEN], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0)
                min_idx = j;
        }
        if (min_idx != i) {
            char temp[MAX_WORD_LEN];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[min_idx]);
            strcpy(arr[min_idx], temp);
        }
    }
}

//ALGORITMA INSERTION SORT
// Insertion Sort untuk angka
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Insertion Sort untuk kata
void insertion_sort_words(char arr[][MAX_WORD_LEN], int n) {
    for (int i = 1; i < n; i++) {
        char key[MAX_WORD_LEN];
        strcpy(key, arr[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            strcpy(arr[j + 1], arr[j]);
            j--;
        }
        strcpy(arr[j + 1], key);
    }
}

// ALGORITMA MERGE SORT
// Fungsi bantu Merge untuk angka
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Alokasi memori di heap untuk menghindari stack overflow
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    if (!L || !R) {
        printf("Gagal mengalokasikan memori untuk merge angka. n1 = %d, n2 = %d\n", n1, n2);
        exit(EXIT_FAILURE);
    }

    // Salin elemen dari array utama ke L dan R
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // Gabungkan L dan R ke array utama secara terurut
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    // Salin sisa elemen jika masih ada
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Bebaskan memori heap
    free(L);
    free(R);
}


// Merge Sort untuk angka
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Fungsi bantu Merge untuk kata
void merge_words(char arr[][MAX_WORD_LEN], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Alokasi memori di heap untuk menghindari stack overflow
    char (*L)[MAX_WORD_LEN] = malloc(n1 * sizeof(char[MAX_WORD_LEN]));
    char (*R)[MAX_WORD_LEN] = malloc(n2 * sizeof(char[MAX_WORD_LEN]));

    if (!L || !R) {
        printf("Gagal mengalokasikan memori untuk merge_words.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++) strcpy(L[i], arr[l + i]);
    for (int j = 0; j < n2; j++) strcpy(R[j], arr[m + 1 + j]);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0)
            strcpy(arr[k++], L[i++]);
        else
            strcpy(arr[k++], R[j++]);
    }
    while (i < n1) strcpy(arr[k++], L[i++]);
    while (j < n2) strcpy(arr[k++], R[j++]);

    // Bebaskan memori setelah selesai
    free(L);
    free(R);
}

// Merge Sort untuk kata
void merge_sort_words(char arr[][MAX_WORD_LEN], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_words(arr, l, m);
        merge_sort_words(arr, m + 1, r);
        merge_words(arr, l, m, r);
    }
}

// ALGORITMA QUICK SORT
// Quick Sort untuk angka
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Quick Sort untuk kata
int partition_words(char arr[][MAX_WORD_LEN], int low, int high) {
    char pivot[MAX_WORD_LEN];
    strcpy(pivot, arr[high]);
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) <= 0) {
            i++;
            char temp[MAX_WORD_LEN];
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
        }
    }
    char temp[MAX_WORD_LEN];
    strcpy(temp, arr[i + 1]);
    strcpy(arr[i + 1], arr[high]);
    strcpy(arr[high], temp);
    return i + 1;
}

void quick_sort_words(char arr[][MAX_WORD_LEN], int low, int high) {
    if (low < high) {
        int pi = partition_words(arr, low, high);
        quick_sort_words(arr, low, pi - 1);
        quick_sort_words(arr, pi + 1, high);
    }
}

// ALGORITMA SHELL SORT
// Shell Sort untuk angka
void shell_sort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// Shell Sort untuk kata
void shell_sort_words(char arr[][MAX_WORD_LEN], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char temp[MAX_WORD_LEN];
            strcpy(temp, arr[i]);
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap)
                strcpy(arr[j], arr[j - gap]);
            strcpy(arr[j], temp);
        }
    }
}

#endif
