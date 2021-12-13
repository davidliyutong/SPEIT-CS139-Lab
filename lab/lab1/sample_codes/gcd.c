/**
 * @file gcd.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>


 /**
  * @brief Swap the value of a and b using their point
  *
  * @param p_a pointer of a
  * @param p_b pointer of b
  */
void swap(int* p_a, int* p_b) {
    int temp; // local varaible that helps us exchange values
    /** The operator '*' allows us to access to pointer's value **/
    temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;
}

/**
 * @brief Calculate gcd(a,b) with Euclidean algorithm
 *
 * @param a
 * @param b
 * @return int
 */
int gcd1(int a, int b) {
    int r;
    /** If a < b, swap a and b and continue **/
    swap(&a, &b);

    /** Euclidean algorithm **/
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/**
 * @brief Another version of gcd(a, b)
 *
 * @param a
 * @param b
 * @return int
 */
int gcd2(int a, int b) {
    int r;
    /** Infact, there is no need to switch a and b **/
    if (a < b) gcd2(b, a);
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

/**
 * @brief Another version of gcd(a, b), recursively calculates gcd(a,b)
 *
 * @param a
 * @param b
 * @return int
 */
int gcd3(int a, int b) {
    return b > 0 ? gcd3(b, a % b) : a;
}

/** @brief Define the function pointer *_gcd that points to a function:
 * - returns int value
 * - accept (int, int) as parameters
 *
 * We can change this pointer to other functions, for example
 *
 * @example
 * int(*_gcd)(int, int) = gcd2;
 **/
int(*_gcd)(int, int) = gcd1;

/** @brief Define the macro gcd(x, y) that calls (*_gcd)(x,y)
 *
 * Macros works at compling stage of the program. The can replace a certain selection of text with desired content.
 * **/
#define gcd(x,y) (*_gcd)(x, y)

 /**
  * @brief Program that calculates GCD(a,b)
  *
  * @param argc Unused
  * @param argv Unused
  * @return int 0
  */
int main(int argc, char** argv) {

    int a, b;
    scanf("%d %d", &a, &b);

    /** Here we simply use the macro gcd **/
    printf("%d\n", gcd(a, b));

    /** Normally exiting the program, return 0 **/
    return 0;
}