#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 void stack_overflow() {
      int i = 1;
        int arr[1000000]; 
        while (1) {
            arr[i] = i;
            i++;
        }
 }

 void memory_leak() {
      int *p = malloc(100 * sizeof(int)); 
        for (int i = 0; i < 100; i++) {
            p[i] = i;
        }
 }

 void out_of_memory() {
     while (1) {
         void *p = (char *)malloc(1024 * 1024 * 10); 
         if (p == NULL) {
             printf("Out of memory!\n");
         }
      }
 }

 int main() {
    int choice;
    printf("=== ERROR SIMULATOR ===\n");
    printf("1. Stack overflow\n");
    printf("2. Memory leak\n");
    printf("3. Out of memory\n");
    printf("Choose error type (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Simulating stack overflow...\n");
            stack_overflow();
            break;
        case 2:
            printf("Simulating memory leak...\n");
            memory_leak();
            break;
        case 3:
            printf("Simulating out of memory...\n");
            out_of_memory();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}