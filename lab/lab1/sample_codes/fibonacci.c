/**
 * @file fibonacci.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
 /** @note Include stdlib.h to use strtol() **/
#include <stdlib.h>

/**
 * @brief Calculate fibonacci(n) with while loops
 *
 * @param a
 * @param b
 * @return int
 */
int fibonacci1(int n) {
    int t1 = 0, t2 = 1, t_next;
    if (n == 0) return 0;
    if (n == 1) return 1;
    /** To obtain fibonacci(n), we have to loop for n - 2 times **/
    for (int idx = 1; idx <= n - 1; ++idx) {
        t_next = t1 + t2;
        t1 = t2;
        t2 = t_next;
    }
    return t_next;
}

/**
 * @brief Calculate fibonacci(n) recursively
 *
 * @param a
 * @param b
 * @return int
 */
int fibonacci2(int n) {
    int t1 = 0, t2 = 1, t_next;

    /** Recursion ends when n == 0 or n == 1 **/
    if (n <= 0) return 0;
    else if (n == 1) return 1;
    else {
        /** Recursively calls fibonacci2 **/
        return fibonacci2(n - 1) + fibonacci2(n - 2);
    }
}

int(*_fibonacci)(int) = fibonacci1;
#define fibonacci(x) (*_fibonacci)(x)

/**
 * @brief Program that calculates GCD(a,b)
 *
 * @param argc should be at least 2
 * @param argv argv[1] represents n
 * @return int 0
 */
int main(int argc, char** argv) {

    /** Creates integer variable to store n **/
    int n;
    /** Endptr is used in strtol() **/
    char* endptr = NULL;

    /** Check if we passed sufficient parameters 
     * 
     * - If n arguments are passed, argc will be n+1
     * - If argc <= 1, exit program with return code 1
    **/
    if (argc <= 1) exit(1);

    /** Use strtol to convert char string to integer
     * 
     * - The return of strtol is 'long int', we use (int) to convert the value to int
     * - argv[1] is a char pointer (char*)
     * - &endptr is the address of endptr, which is a point of char pointer (char **)
     * - If the input is illegal and strtol cannot proceed, endptr will be set to beginning of the string, which is argv[1]. If endptr equals to argv[1], then we know the input is not a number
    **/
    n = (int) strtol(argv[1], &endptr, 10);
    if (endptr == argv[1]) exit(2);

    /** Ouput the result of fibonacci(n) **/
    printf("%d\n", fibonacci(n));

    /** Normally exiting the program, return 0 **/
    return 0;
}