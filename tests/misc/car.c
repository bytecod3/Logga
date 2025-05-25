#include "car.h"
#include <stdlib.h>

struct Car {
    char* brand;
    char* color;
};

/* allocate memory for a car */
Car_type_t create_car() {
    return (Car_type_t) malloc(sizeof(struct Car));
}

void car_constr(Car_type_t obj,const char* brand, const char* color) {
    obj->brand = (char*) brand;
    obj->color = (char*) color;
}

const char* car_get_brand(Car_type_t obj) {
    return obj->brand;
}

const char* car_get_color(Car_type_t obj) {
    return obj->color;
}

void car_destr(Car_type_t obj) {
    free(obj);
}