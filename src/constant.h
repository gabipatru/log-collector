/*
 * constant.h
 *
 *  Created on: 19 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

/**
 * General Constants
 */
#define PI 3.141592;


/**
 * LINUX RETURN CODES
 */
#define LINUX_NO_ERROR 0;
#define LINUX_ERROR 1;

/**
 * Useful Typedefs
 */
typedef int* PINT;
typedef char* PCHAR;
typedef const char* CPCHAR;

typedef std::string STRINGCLASS;

/**
 * Running on Linux or Windows ?
 */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#define RUNNING_ON_WINDOWS 1
#define RUNNING_ON_LINUX 0
#define CLEAR_SCREEN "CLS"
#else
#define RUNNING_ON_WINDOWS 0
#define RUNNING_ON_LINUX 1
#define CLEAR_SCREEN "clear"
#endif

/**
 * Linux Terminal Colors
 */
#define LINUX_TERMINAL_NOCOLOR "\e[0m"
#define LINUX_TERMINAL_WHITE "\e[1;37m"
#define LINUX_TERMINAL_BLACK "\e[0;30m"
#define LINUX_TERMINAL_BLUE "\e[0;34m"
#define LINUX_TERMINAL_LIGHTBLUE "\e[1;34m"
#define LINUX_TERMINAL_GREEN "\e[0;32m"
#define LINUX_TERMINAL_LIGHTGREEN "\e[1;32m"
#define LINUX_TERMINAL_CYAN "\e[0;36m"
#define LINUX_TERMINAL_LIGHTCYAN "\e[1;36m"
#define LINUX_TERMINAL_RED "\e[0;31m"
#define LINUX_TERMINAL_LIGHTRED "\e[1;31m"
#define LINUX_TERMINAL_PURPLE "\e[0;35m"
#define LINUX_TERMINAL_LIGHTPURPLE "\e[1;35m"
#define LINUX_TERMINAL_BROWN "\e[0;33m"
#define LINUX_TERMINAL_LIGHTBROWN "\e[1;33m"
#define LINUX_TERMINAL_YELLOW "\e[1;33m"
#define LINUX_TERMINAL_GRAY "\e[0;30m"
#define LINUX_TERMINAL_LIGHTGRAY "\e[0;37m"

#endif /* SRC_CONSTANTS_H_ */
