#ifndef RADIX_CALC_SENTRY_H
#define RADIX_CALC_SENTRY_H

#include <stdio.h>
#include <stdlib.h>

enum { 
		MAX_RADIX_NUM = 16, 
		MAX_INPUT_LENGTH = 10, 
		MAX_BUF_LEN = 50, 
		MAX_FIRST_ARG_LENGTH = 2, 
		MAX_THIRD_ARG_LENGTH = 2,
		MAX_PROGRAM_ARGS = 4
	 };

enum { 
		BINARY = 2, 
		TERNARY, 
		QUATERNARY, 
		FIVEFOLD, 
		HEXADEC, 
		SEPTENARY, 
		OCTANARY, 
		NINE_DEC, 
		DECIMAL, 
		HEX = 16 
	 };

int str_len(const char* str);
int str_to_int(const char* str, int strlen, int radix);
int isCorrectTransferNum(const char* transfer_num, int strlen, int radix_transfer_num);
char* Transfer(int radix_old_num, char* transfer_num, int length_transfer_num, int radix_new_num);
int delNewLineChar(char (*str)[]);
void clear_stdin(void);
void get_str(char (*str)[], int max_str_len);
int input_get_first_arg(char (*str)[], int str_size);
void input_get_second_arg(char (*transfer_num)[], int radix_transfer_num);
int input_get_third_arg(char (*str)[], int str_size);
int cmd_get_first_arg(const char* argv1, int arg1_len);
int cmd_get_second_arg(char (*transfer_num)[], const char* argv2, int arg2_len, int radix_transfer_num);
int cmd_get_third_arg(const char* argv1, int arg3_len);

#endif
