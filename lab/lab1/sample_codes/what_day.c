/**
 * @file what_day.c
 * @author liyutong (davidliyutong@sjtu.edu.cn)
 * @brief
 * @version 0.1
 * @date 2021-09-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
/** @note Include stdlib.h to use exit() **/
#include <stdlib.h>
/** @note Include string.h to use strlen() **/
#include <string.h>

/**
 * @brief Convert a single digit from char to int by manipulating with ascii
 *
 * In ascii (https://baike.baidu.com/item/ASCII), '0' equals to 48(0x30)
 * - EVAL_CHAR(x) ((x) - '0')  =(expand as)=>  (x - '0')
 * - EVAL_CHAR('1')  =>  ('1' - '0') =>  1
 */
#define EVAL_CHAR(x) ((x) - '0')

 /**
  * @brief Parse a YYYY-mm-DD format string to year, month, day
  *
  * @param arg A string in YYYY-mm-DD format.
  * @param year year[*int]
  * @param month month[*int]
  * @param day day[*nt]
  * @return int Status code. 0 for success and -1 for failure
  * @remark The function will modify year, month and day using their pointer.
  *         The length of arg must by 10, the 5th and 8th position of arg must by '-'
  * @example
  * >>>
  * int year, month, day;
  * int ret = parse_arg(argv[1], &year, &month, &day);
  * printf("year:%d, month:%d, day:%d", year, month, day);
  * >>>
  */
int parse_arg(char* const arg, int* year, int* month, int* day) {

    if (strlen(arg) != 10 || arg[4] != '-' || arg[7] != '-') return -1; // Check format.

    *year = EVAL_CHAR(arg[0]) * 1000 + EVAL_CHAR(arg[1]) * 100 + EVAL_CHAR(arg[2]) * 10 + EVAL_CHAR(arg[3]); // Calculate year by adding digits
    *month = EVAL_CHAR(arg[5]) * 10 + EVAL_CHAR(arg[6]); // Calculate month by adding digits
    *day = EVAL_CHAR(arg[8]) * 10 + EVAL_CHAR(arg[9]); // Calculate day by adding digits

    return 0;
}

#define is_leap_year(year) ((((year) % 4 == 0) && ((year) % 100 != 0)) || ((year) % 400 == 0))

/**
 * @brief Return the day of a calendar date. (Mon., Tue., Wed., ...Sun.)
 * 
 * @ref https://www.zhihu.com/question/369735069
 *
 * @param year Year
 * @param month Month
 * @param day Day
 * @return int 1-6 for Mon.-Sat., 7 for Sun.
 */
int what_day(int year, int month, int day) {
    if (month == 1 || month == 2) {
        month += 12;
        year--;
    }
    int week_day = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400 + 1) % 7;
    return week_day;

}

#define DEBUG 0

int main(int argc, char** argv) {
    /** Varaibles holding year, month and day **/
    int year, month, day;

    /** Input buffer 1 byte larger than desired to store extra '\0' **/
    char buf[11];
    /** Limit scanf length to 10 **/
    scanf("%10s", buf);

    /** Parse input, check if the input is valid or not**/
    int ret = parse_arg(buf, &year, &month, &day);
    if (ret != 0) exit(ret);

    /** (For debug) Display parsed date 
     * This sentence will only be compiled if the macro DEBUG equals to positive value**/
#if (DEBUG)
    printf("Year:%d, Month:%d, Day:%d\n", year, month, day);
#endif

    /** Run algorithm **/
    printf("%d\n", what_day(year, month, day));
    return 0;
}