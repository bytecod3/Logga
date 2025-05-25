
#ifndef LOGGA_CAR_H
#define LOGGA_CAR_H

typedef struct Car* Car_type_t; // forward declare a car type

// create a car
Car_type_t create_car();

// "member" functions
void car_constr(Car_type_t obj, const char* brand, const char* color);
void car_destr(Car_type_t obj);
const char* car_get_brand(Car_type_t obj);
const char* car_get_color(Car_type_t obj);

#endif //LOGGA_CAR_H
