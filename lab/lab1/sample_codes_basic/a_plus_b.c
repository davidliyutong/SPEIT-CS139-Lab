/**
 * @file a_plus_b.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/** @note Include stdio.h to use printf and scanf**/
#include <stdio.h>

/**
 * @brief Program that read two integer numbers from keyboard
 * 
 * @param argc Unused
 * @param argv Unused
 * @return int 0
 */
int main(int argc, char** argv) {

    /** Define two integer variables **/
    int a, b; 

    /** Use scanf to get values from stdin 
     * 
     * - scanf() read keyboard input
     * - "%d" is the pattern for integer input
     * - &a represent the address of variable a, scanf() modifies a via this address
    **/
    scanf("%d %d", &a, &b);

    /** Use printf to put values to stdout 
     * 
     * - printf() prints
     * - "%d" is the pattern for integer output
     * - a + b is the value of answer, printf use it to format output
    **/
    printf("%d\n", a + b);

    /** Normally exiting the program, return 0 **/
    return 0;
}