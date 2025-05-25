#include "person.h"
#include <stdlib.h>
#include <string.h>

typedef struct person_t {
    char* f_name;
    char* l_name;
    int age;
} person_t;

person_t* person_new() {
    return (person_t*) malloc(sizeof(person_t));
}

void person_ctr(person_t* obj, const char* f_name, const char* l_name, const int age ) {
    obj->f_name = (char*) f_name;
    obj->l_name = (char*) l_name;
    obj->age = age;
}

void person_dtr(person_t* obj) {
    free(obj);
}

static char full_name[60];
const char* person_get_full_name(struct person_t* obj) {
    strcat(full_name, obj->f_name);
    strcat(full_name, " ");
    strcat(full_name, obj->l_name);

    return full_name;
}

int person_get_age(struct person_t* obj) {
    return obj->age;
}

void person_happy_birthday(struct person_t* obj) {
    return obj->age++;
}
