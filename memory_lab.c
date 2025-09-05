#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// stack overflow
 void stack_overflow() {
      int i = 1;
        int arr[1000000]; 
        while (1) {
            arr[i] = i;
            i++;
        }
 }


 // memory leak
 void memory_leak() {
      int *p = malloc(100 * sizeof(int)); 
        for (int i = 0; i < 100; i++) {
            p[i] = i;
        }
 }


 // out of memory
 void out_of_memory() {
     while (1) {
         void *p = (char *)malloc(1024 * 1024 * 10); 
         if (p == NULL) {
             printf("Out of memory!\n");
         }
      }
 }


 int main() {
    
     stack_overflow();                  

     memory_leak();
    
     out_of_memory();

     return 0;
 }                                                     