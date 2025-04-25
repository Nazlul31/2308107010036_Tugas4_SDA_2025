#include <stdio.h>                  // Header standar untuk fungsi input/output
#include <stdlib.h>                 // Header untuk fungsi-fungsi umum seperti malloc dan exit
#include <string.h>                 // Header untuk manipulasi string seperti memcpy
#include <time.h>                   // Header untuk pengukuran waktu
#include "header.h"                 // Header khusus yang berisi deklarasi fungsi sorting

#define DATA_PATH_ANGKA "./data/data_angka.txt"   // Path ke file data angka
#define DATA_PATH_KATA "./data/data_kata.txt"     // Path ke file data kata

// Fungsi untuk membaca data angka dari file ke array
void read_numbers_from_file(const char *filename, int *arr, int n) {
    FILE *file = fopen(filename, "r");            // Membuka file untuk dibaca
    if (!file) {                                  // Jika gagal membuka file
        perror("Gagal membuka file data angka");  // Tampilkan pesan error
        exit(EXIT_FAILURE);                       // Keluar dari program
    }
    for (int i = 0; i < n; i++) {                 // Membaca setiap angka dari file
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);                                 // Menutup file setelah selesai
}

// Fungsi untuk membaca data kata dari file ke array 2 dimensi
void read_words_from_file(const char *filename, char arr[][MAX_WORD_LEN], int n) {
    FILE *file = fopen(filename, "r");            // Membuka file untuk dibaca
    if (!file) {
        perror("Gagal membuka file data kata");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {                 // Membaca setiap kata dari file
        fscanf(file, "%s", arr[i]);
    }
    fclose(file);                                 // Menutup file
}

// Fungsi untuk mencetak header tabel hasil
void print_header() {
    printf("+------------------------------+--------------+---------------+\n");
    printf("| %-28s | %-12s | %-13s |\n", "Algoritma",  "Waktu (s)", "Ukuran (MB)");
    printf("+------------------------------+--------------+---------------+\n");
}

// Fungsi untuk mencetak hasil benchmarking satu algoritma
void print_result(const char *algorithm, double time_used, double memory_used) {
    printf("| %-28s | %10.3f   |   %6.2f      |\n", algorithm, time_used, memory_used);
}

int main() {
    int n, choice, n_choice;
    clock_t start, end;                         // Variabel untuk mencatat waktu mulai dan akhir
    double time_used;                           // Variabel untuk menyimpan lama waktu eksekusi

    // Menu untuk memilih tipe data
    printf("Pilih tipe data:\n1. Angka\n2. Kata\nPilihan: ");
    scanf("%d", &choice);
    
    // Menu untuk memilih jumlah data
    printf("Pilih jumlah data:\n");
    printf("1. 10.000\n2. 50.000\n3. 100.000\n4. 250.000\n5. 500.000\n6. 1.000.000\n7. 1.500.000\n8. 2.000.000\n");
    printf("Pilihan: ");
    scanf("%d", &n_choice);
    
    // Menyesuaikan jumlah data sesuai pilihan pengguna
    switch(n_choice) {
        case 1: n = 10000; break;
        case 2: n = 50000; break;
        case 3: n = 100000; break;
        case 4: n = 250000; break;
        case 5: n = 500000; break;
        case 6: n = 1000000; break;
        case 7: n = 1500000; break;
        case 8: n = 2000000; break;
        default:
            printf("Pilihan tidak valid.\n");
            return 1;
    }

    // Proses untuk tipe data angka
    if (choice == 1) {
        int *original = malloc(sizeof(int) * n);           // Alokasi memori untuk data asli
        int *arr = malloc(sizeof(int) * n);                // Alokasi memori untuk data yang akan disortir
        if (!original || !arr) {
            printf("Gagal mengalokasikan memori.\n");
            free(original);                                // Bebaskan memori jika gagal
            free(arr);
            return 1;
        }

        read_numbers_from_file(DATA_PATH_ANGKA, original, n); // Baca data angka dari file
        double mem_mb = sizeof(int) * n / (1024.0 * 1024.0);  // Hitung penggunaan memori dalam MB
        print_header();                                       // Cetak header tabel

        // Bubble Sort
        memcpy(arr, original, sizeof(int) * n);
        start = clock(); bubble_sort(arr, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Bubble Sort", time_used, mem_mb);

        // Selection Sort
        memcpy(arr, original, sizeof(int) * n);
        start = clock(); selection_sort(arr, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Selection Sort", time_used, mem_mb);

        // Insertion Sort
        memcpy(arr, original, sizeof(int) * n);
        start = clock(); insertion_sort(arr, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Insertion Sort", time_used, mem_mb);

        // Merge Sort
        memcpy(arr, original, sizeof(int) * n);
        start = clock(); merge_sort(arr, 0, n - 1); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Merge Sort", time_used, mem_mb);

        // Quick Sort
        memcpy(arr, original, sizeof(int) * n);
        start = clock(); quick_sort(arr, 0, n - 1); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Quick Sort", time_used, mem_mb);

        // Shell Sort
        memcpy(arr, original, sizeof(int) * n);
        start = clock(); shell_sort(arr, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Shell Sort", time_used, mem_mb);

        free(original);     // Bebaskan memori
        free(arr);

    // Proses untuk tipe data kata
    } else if (choice == 2) {
        char (*original)[MAX_WORD_LEN] = malloc(sizeof(char[MAX_WORD_LEN]) * n); // Alokasi memori data asli
        char (*words)[MAX_WORD_LEN] = malloc(sizeof(char[MAX_WORD_LEN]) * n);    // Alokasi memori data sorting
        if (!original || !words) {
            printf("Gagal mengalokasikan memori.\n");
            free(original);
            free(words);
            return 1;
        }

        read_words_from_file(DATA_PATH_KATA, original, n); // Baca data kata dari file
        double mem_mb = sizeof(char[MAX_WORD_LEN]) * n / (1024.0 * 1024.0); // Hitung penggunaan memori
        print_header();

        // Bubble Sort
        memcpy(words, original, sizeof(char[MAX_WORD_LEN]) * n);
        start = clock(); bubble_sort_words(words, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Bubble Sort", time_used, mem_mb);

        // Selection Sort
        memcpy(words, original, sizeof(char[MAX_WORD_LEN]) * n);
        start = clock(); selection_sort_words(words, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Selection Sort", time_used, mem_mb);

        // Insertion Sort
        memcpy(words, original, sizeof(char[MAX_WORD_LEN]) * n);
        start = clock(); insertion_sort_words(words, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Insertion Sort", time_used, mem_mb);

        // Merge Sort
        memcpy(words, original, sizeof(char[MAX_WORD_LEN]) * n);
        start = clock(); merge_sort_words(words, 0, n - 1); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Merge Sort", time_used, mem_mb);

        // Quick Sort
        memcpy(words, original, sizeof(char[MAX_WORD_LEN]) * n);
        start = clock(); quick_sort_words(words, 0, n - 1); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Quick Sort", time_used, mem_mb);

        // Shell Sort
        memcpy(words, original, sizeof(char[MAX_WORD_LEN]) * n);
        start = clock(); shell_sort_words(words, n); end = clock();
        time_used = (double)(end - start) / CLOCKS_PER_SEC;
        print_result("Shell Sort", time_used, mem_mb);

        free(original); // Bebaskan memori
        free(words);
    } else {
        printf("Pilihan tipe data tidak valid.\n"); // Jika input tipe data salah
    }

    printf("+------------------------------+--------------+---------------+\n"); // Penutup tabel hasil
    return 0; // Program selesai
}
