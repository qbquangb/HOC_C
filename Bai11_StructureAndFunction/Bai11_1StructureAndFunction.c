#include <stdio.h>

struct student {
   char name[50];
   int age;
};

// function prototype
void display(struct student s);

int main() {
   struct student s1;

   printf("Enter name: ");

   // Dòng này là một “mẹo” thường dùng để đọc một dòng văn bản (tới trước \n) vào s1.name 
   // và loại bỏ ký tự newline \n còn lại trong bộ đệm
   // gồm 2 lần đọc
   // lần 1 đọc %[^\n] gán cho biến s1.name, không đọc kí tự \n
   // lần 2 đọc một ký tự %*c không gán cho biến nào, mục đích tiêu thụ ký tự newline ('\n') còn lại sau %[^\n]
   // giới hạn 49 ký tự
   if (scanf("%49[^\n]%*c", &s1.name) != 1) return 1;

   printf("Enter age: ");
   scanf("%d", &s1.age);

   display(s1); // passing struct as an argument

   return 0;
}

void display(struct student s) {
   printf("\nDisplaying information\n");
   printf("Name: %s", s.name);
   printf("\nAge: %d", s.age);
}