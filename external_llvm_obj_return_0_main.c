#include <stdio.h>

  extern int func();  // Declared in the LLVM-generated object file
  
  int main() {
      printf("LLVM function returned: %d\n", func());
      return 0;
  }