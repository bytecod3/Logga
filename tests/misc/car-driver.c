#include <stdio.h>
#include "misc/car.h"

int main() {
    Car_type_t my_car = create_car();

    car_constr(my_car, "Peugeot", "Gray");

    printf("brand: %s\n",car_get_brand(my_car) );
    printf("color: %s\n",car_get_color(my_car)) ;

    // free the car memory
    car_destr(my_car);

    return 0;
}