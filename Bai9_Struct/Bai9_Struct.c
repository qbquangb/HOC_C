#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person {
    char name[50];
    int citNo;
    float salary;
} Person;   // now 'Person' is a type alias
typedef float Temperature;

int main() {

    Person person1;
    // assign value to name of person1
    strcpy(person1.name, "George Orwell");

    // assign values to other person1 variables
    person1.citNo = 1984;
    person1. salary = 2500;

    // print struct variables
    printf("Name: %s\n", person1.name);
    printf("Citizenship No.: %d\n", person1.citNo);
    printf("Salary: %.2f", person1.salary);

    Temperature today = 25.5;
    printf("Today: %.1f C\n", today);

    return 0;
}