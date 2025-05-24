#include <stdio.h>
#include "person.h"

int main() {

    struct person_t* p = person_new();
    person_ctr(p, "Edwin", "Mwiti", 25);

    printf("Person p: fname: %s\n", person_get_name(p) );

    return 0;
}