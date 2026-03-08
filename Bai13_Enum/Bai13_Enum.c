#include <stdio.h>

typedef enum
{
    LOW, // 0
    MEDIUM, // 1
    HIGH // 2
} Level;

int main()
{

    Level myVar = MEDIUM;
    // Print the enum variable
    printf("%d\n", myVar);
    // Change
    myVar = LOW;
    printf("%d\n", myVar);

    switch (myVar) {
    case 0:
      printf("Low Level\n");
      break;
    case 1:
      printf("Medium level\n");
      break;
    case 2:
      printf("High level\n");
      break;
  }

   return 0;
}