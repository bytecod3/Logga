#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* fp;

    float total;
    char str[80];

    fp = fopen("data.txt", "w+");

    if(fp == NULL) {
        printf("File does not exist, please check");
        exit(1);
    }

    fprintf(fp, "%f %s", 90.55, "MISC"); // write to file
    rewind(fp);
    fscanf(fp, "%f", &total);
    fscanf(fp, "%s", str);

    fclose(fp);

    printf("%f %s", total, str);

    return 0;
}