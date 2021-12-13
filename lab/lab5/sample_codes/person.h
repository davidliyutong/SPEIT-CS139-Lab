#ifndef _PERSON_H
#define _PERSON_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME_LEN 20
#define MAX_DOMAIN_LEN 20
#define MAX_EMAIL_LEN 64
#define MAX_ADDRESS_LEN 128
#define MAX_DATE_LEN 10
#define ID_LEN 18

#ifndef STR1
#define STR1(R) #R
#endif
#ifndef STR2
#define STR2(R) STR1(R)
#endif

typedef enum {
    PERSON_STUDENT,
    PERSON_PROFESSOR,
} person_type_t;

typedef union {
    int grade;
    char domain[MAX_DOMAIN_LEN];
} person_grade_domain_t;

typedef enum {
    PERSON_COLLEGE_PARISTECH,
    PERSON_COLLEGE_OTHER,
} person_college_t;

typedef struct {
    unsigned int day:5;
    unsigned int month:4;
    unsigned int year:14;
} person_birthday_t;

typedef struct {
    unsigned int is_present:1;
    unsigned int is_infected:1;
    unsigned int is_cured:1;
    unsigned int is_curing:1;
    unsigned int is_inoculated_1:1;
    unsigned int is_inoculated_2:1;
    unsigned int is_inoculated_3:1;
    unsigned int is_alive:1;
} person_covid_t;

#define LEVEL 1
#if (LEVEL == 1)
typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    person_type_t type;
    person_grade_domain_t grade_domain;
    char email[MAX_EMAIL_LEN];
    char birthday[MAX_DATE_LEN];
} person_t;

#elif (LEVEL == 2)
typedef struct {
    char name[MAX_NAME_LEN];
    int age;
    person_type_t type;
    person_grade_domain_t grade_domain;
    char email[MAX_EMAIL_LEN];
    person_birthday_t birthday;
    person_covid_t covid;
} person_t;
#endif

#endif