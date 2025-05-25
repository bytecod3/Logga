//
// Created by User on 5/23/2025.
//

#ifndef LOGGA_PERSON_H
#define LOGGA_PERSON_H

struct person_t; /* forward declaration */


struct person_t* person_new(); // creation function

/* constructor */
void person_ctr(struct person_t* obj, const char* f_name, const char* l_name, const int age);
void person_dtr(struct person_t* obj);
const char* person_get_full_name(struct person_t* obj);
int person_get_age(struct person_t* obj);
void person_happy_birthday(struct person_t* obj);


#endif //LOGGA_PERSON_H
