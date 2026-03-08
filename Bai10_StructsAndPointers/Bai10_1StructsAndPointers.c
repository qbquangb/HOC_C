#include <stdio.h>

typedef struct
{
   int age;
   float weight;
} person;

int main()
{
    person* personPtr;
    person person1;

    personPtr = &person1;

    printf("Enter age: ");
    scanf("%d", &personPtr->age);

    printf("Enter weight: ");
    scanf("%f", &personPtr->weight);

    printf("Displaying:\n");
    printf("Age: %d\n", personPtr->age); // personPtr->age is equivalent (tương đương) to (*personPtr).age
    printf("weight: %f", personPtr->weight);

    return 0;
}