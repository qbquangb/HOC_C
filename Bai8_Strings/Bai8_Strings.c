#include <stdio.h>
#include <stdlib.h>

/*

How to initialize strings
char c[] = "abcd";
char c[50] = "abcd";
char c[] = {'a', 'b', 'c', 'd', '\0'};
char c[5] = {'a', 'b', 'c', 'd', '\0'};

Hàm scanf() bỏ mọi ký tự trắng (spaces, tab, newline) hiện có trong luồng trước khi tiếp tục.

*/

int main() {

    char name[30];
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);  // read a line of string, đọc cho đến khi gặp \n
    printf("Name: ");
    puts(name);    // display string

    return 0;
}