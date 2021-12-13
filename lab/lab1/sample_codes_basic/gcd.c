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
int gcd(int a, int b) {
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