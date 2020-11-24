// << (SHIFT LEFT)

// It shifts the bits of operand1 to the left operand 2 times
// (10101010) << (00000011) = (01010000)

// g++ bitwise_shift_left.c -o bitwise_shift_left.o

// https://stackoverflow.com/questions/6462938/error-itoa-was-not-declared-in-this-scope/6462973

#include <stdio.h>
#include <stdlib.h>

 
int main() {

  char buffer[4];
  for (int i = 0; i <= 16; i++) {
    snprintf(buffer, sizeof(buffer), "%d", i); // int to string

    if (i != 16) {
      printf("GPIO%s (1 << %d) Bit %d. Result: %d\n", buffer, i, i, 1 << i);
    } else {
      printf("GPIO_ALL 0xFFFF All bits 0 through 15. Result: %d\n", 1 << i);
    }
    
  }
  
  return 0;
}


/*
OUTPUT: 

GPIO0 (1 << 0) Bit 0. Result: 1
GPIO1 (1 << 1) Bit 1. Result: 2
GPIO2 (1 << 2) Bit 2. Result: 4
GPIO3 (1 << 3) Bit 3. Result: 8
GPIO4 (1 << 4) Bit 4. Result: 16
GPIO5 (1 << 5) Bit 5. Result: 32
GPIO6 (1 << 6) Bit 6. Result: 64
GPIO7 (1 << 7) Bit 7. Result: 128
GPIO8 (1 << 8) Bit 8. Result: 256
GPIO9 (1 << 9) Bit 9. Result: 512
GPIO10 (1 << 10) Bit 10. Result: 1024
GPIO11 (1 << 11) Bit 11. Result: 2048
GPIO12 (1 << 12) Bit 12. Result: 4096
GPIO13 (1 << 13) Bit 13. Result: 8192
GPIO14 (1 << 14) Bit 14. Result: 16384
GPIO15 (1 << 15) Bit 15. Result: 32768
GPIO_ALL 0xFFFF All bits 0 through 15. Result: 65536
*/