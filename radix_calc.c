#ifndef RADIX_CALC_SENTRY_C
#define RADIX_CALC_SENTRY_C

#include "radix_calc.h"


/*																			*/
int str_len(const char* str)
{
	int result = 0;
	for ( ; str[result]; result++ ) {}

	return result;
}

int str_to_int(const char* str, int strlen, int radix)
{
	/*
	 *	Предполагается, что строка подаётся на вход без символа \n
	 * */

	if ( isCorrectTransferNum(str, strlen, radix) == 0 )
		return 0;

	
	int result = 0;
	int i = strlen-1;
	int multiply = 1;

	while ( i >= 0 )
	{
		if ( (i == 0) && (str[i] == '-' || str[i] == '+' ) )
			break;
		
		if ( radix == HEX )
		{
			switch (str[i])
			{
				case 'A':
				case 'a':
					result += 10 * multiply;
					break;
				case 'B':
				case 'b':
					result += 11 * multiply;
					break;
				case 'C':
				case 'c':
					result += 12 * multiply;
					break;
				case 'D':
				case 'd':
					result += 13 * multiply;
					break;
				case 'E':
				case 'e':
					result += 14 * multiply;
					break;
				case 'F':
				case 'f':
					result += 15 * multiply;
					break;
				default:
					result += (str[i]-'0') * multiply;
			}
		}
		else
		{
			result += (str[i]-'0') * multiply;
		}
		i--;
		multiply *= radix;
	}
	
	if ( str[0] == '-' )
		result *= -1;

	return result;
}

int isCorrectTransferNum(const char* transfer_num, int strlen, int radix_transfer_num)
{
	const char* correct_symbols[MAX_RADIX_NUM+2] = {
										"",
										"",
										"-+01",
										"-+012",
										"-+0123",
										"-+01234",
										"-+012345",
										"-+0123456",
										"-+01234567",
										"-+012345678",
										"-+0123456789",
										"",
										"",
										"",
										"",
										"",
										"-+0123456789AaBbCcDdEeFf",
										NULL
									  };
	
	
	if (  transfer_num[0] == '\0' )
		return 0;

	if ( strlen > MAX_INPUT_LENGTH )
	{
		printf("%s", "Your input string is over than 10 symbols!\n");
		return 0;
	}
	
	int i = 0, j = 0;
	int sum_correct_symbols = 0;

	for ( ; correct_symbols[radix_transfer_num][i]; i++ )
	{
		if ( transfer_num[j] == correct_symbols[radix_transfer_num][i] )
		{
			if ( (transfer_num[j] == '-' || transfer_num[j] == '+') && (j != 0) )
				return 0;

			sum_correct_symbols++;
			i = -1;
			j++;
		}
		continue;
	}

	if ( sum_correct_symbols != strlen )
		return 0;
	
	if ( strlen == MAX_INPUT_LENGTH && (radix_transfer_num != HEX) )
	{
		if (transfer_num[0] == '-')
		{
			if (transfer_num[1] >= '2')
			{
				if ( transfer_num[1] > '2' )
				{
					printf("%s\n", "Your number is below than MIN INTEGER VALUE!");
					return 0;
				}
				else
				{
					if (transfer_num[2] > '1')
					{
						printf("%s\n", "Your number is below than MIN INTEGER VALUE!");
						return 0;
					}
					else
					{
						if (transfer_num[3] > '4')
						{
							printf("%s\n", "Your number is below than MIN INTEGER VALUE!");
							return 0;
						}
						else
						{
							if (transfer_num[4] > '7')
							{
								printf("%s\n", "Your number is below than MIN INTEGER VALUE!");
								return 0;
							}
							else
							{
								if (transfer_num[5] > '0')
								{
									printf("%s\n", "Your number is below than MIN INTEGER VALUE!");
									return 0;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if (transfer_num[0] >= '2')
			{
				if ( transfer_num[0] > '2' )
				{
					printf("%s\n", "Your number is above than MAX INTEGER VALUE!");
					return 0;
				}
				else
				{
					if (transfer_num[1] > '1')
					{
						printf("%s\n", "Your number is above than MAX INTEGER VALUE!");
						return 0;
					}
					else
					{
						if (transfer_num[2] > '4')
						{
							printf("%s\n", "Your number is above than MAX INTEGER VALUE!");
							return 0;
						}
						else
						{
							if (transfer_num[3] > '7')
							{
								printf("%s\n", "Your number is above than MAX INTEGER VALUE!");
								return 0;
							}
							else
							{
								if (transfer_num[4] > '0')
								{
									printf("%s\n", "Your number is above than MAX INTEGER VALUE!");
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}

	return 1;
}

char* Transfer(int radix_old_num, char* transfer_num, int length_transfer_num, int radix_new_num)
{	
	int i;
	if ( radix_old_num == radix_new_num )
	{	
		char* result = malloc(sizeof(char) * length_transfer_num + 1);
		if ( result == NULL )
			return NULL;

		for ( i = 0; transfer_num[i]; i++ )
		{
			result[i] = transfer_num[i];
			if ( i >= MAX_BUF_LEN-1 )
			{
				i++;
				break;
			}
		}
		result[i] = '\0';
		return result;
	}
	
	
	int t_num_length = str_len(transfer_num);
	int decimal = str_to_int(transfer_num, t_num_length, radix_old_num);
	int decimal_copy = decimal;
	
	/*printf("decimal = %d\ndecimal_copy = %d\n", decimal, decimal_copy);*/ //

	if ( (decimal < 0) && (radix_new_num == DECIMAL) )
		decimal *= -1;
	else if ( (decimal < 0) && (radix_new_num != DECIMAL) )
		decimal = 0x7fffffff + decimal + 1;			/*находим число обратное(положительное) данному отрицательному*/
	
	/*printf("decimal (1) = %d\n", decimal);*/								//
	
	char* buffer = malloc(sizeof(char) * MAX_BUF_LEN+1);
	if (buffer == NULL)
		return NULL;

	int j = 0;
	while (decimal > 0)
	{
		if ( radix_new_num == HEX )
		{
			switch (decimal % radix_new_num)
			{
				case 10:
					buffer[j] = 'A';
					break;
				case 11:
					buffer[j] = 'B';
					break;
				case 12:
					buffer[j] = 'C';
					break;
				case 13:
					buffer[j] = 'D';
					break;
				case 14:
					buffer[j] = 'E';
					break;
				case 15:
					buffer[j] = 'F';
					break;
				default:
					buffer[j] = (decimal % radix_new_num) + '0';
			}
		}
		else
		{
			buffer[j] = (decimal % radix_new_num) + '0';
		}
		j++;
		decimal /= radix_new_num;
	}
	
	if ( (decimal_copy < 0) && (radix_new_num == DECIMAL) )
	{
		buffer[j] = '-';
		j++;
	}
	buffer[j] = '\0';
	
	/*printf("buffer = %s\n", buffer);*/									//

	int buflen = j;
	
	i = 0;
	j = buflen-1;
	
	char* result = malloc(sizeof(char) * buflen + 1);
	if (result == NULL)
		return NULL;

	while ( j >= 0 )
	{
		result[i] = buffer[j];
		i++;
		j--;
	}
	result[i] = '\0';
	
	free(buffer);
	
	/*printf("result = %s\n", result);*/									//

	return result;
}

int delNewLineChar(char (*str)[])
{
	int i = 0;
	while ((*str)[i])
	{
		if ( (*str)[i] == '\n' )
		{
			(*str)[i] = '\0';
			return 1;
		}
		i++;
	}
	return 0;
}

/*Поглощает в себя символы из стандартного потока ввода*/
void clear_stdin(void)
{
	int c;
	do
	{ 
		c = getchar();
	}
	while (c != EOF && c != '\n');
}

void get_str(char (*str)[], int max_str_len)
{
	int c;
	int i = 0;
	while ( ((c = getchar()) != '\n') )
	{	
		if (i < max_str_len)
			(*str)[i] = c;

		if (i == max_str_len)
			(*str)[i] = '\0';
		i++;		
	}
	if (i < max_str_len)
		(*str)[i] = '\0';

	if ( i > max_str_len)
		clear_stdin();
}

int input_get_first_arg(char (*str)[], int str_size)
{
	int flag = 0;
	int radix_transfer_num = 0;
	int rt_buf_length = 0;

	do
	{
		flag = 0;
		printf("%s", "Enter FIRST argument\n"
					 "(radix_transfer_num): ");
		get_str(str, MAX_FIRST_ARG_LENGTH);
		rt_buf_length = str_len(*str);
		/*
		printf("%s", "    radix_trans_buf = ");									//
		int i;
		for (i = 0; (*str)[i]; i++)
			printf("%d ", (*str)[i]);
		printf("%d\n", (*str)[i]);
		printf("    rt_buf_length = %d\n", rt_buf_length);
		*/
		/*delNewLineChar(&radix_trans_buf);
		printf("%s", "    radix_trans_buf = ");									//
		for (i = 0; radix_trans_buf[i]; i++)
			printf("%d ", radix_trans_buf[i]);
		printf("%d\n", radix_trans_buf[i]);
		*/
		radix_transfer_num = str_to_int(*str, rt_buf_length, DECIMAL);
		/*
		printf("    radix_transfer_num = %d\n\n", radix_transfer_num);			//
		*/
		if ( (radix_transfer_num >= BINARY && radix_transfer_num <= DECIMAL) || (radix_transfer_num == HEX) )
			flag = 1;
	}
	while ( (!flag) );

	return radix_transfer_num;
}

void input_get_second_arg(char (*transfer_num)[], int radix_transfer_num)
{
	int res = 0;
	do
	{
		printf("%s", "Enter SECOND argument\n"
					 "(transfer_num): ");
		get_str(transfer_num, MAX_INPUT_LENGTH);
		/*
		printf("    *transfer_num = %s\n", *transfer_num);
		*/
		int t_num_length = str_len(*transfer_num);
		/*
		printf("    t_num_length = %d\n", t_num_length);
		*/
		res = isCorrectTransferNum(*transfer_num, t_num_length, radix_transfer_num);
		/*
		printf("    res = %d\n", res);
		*/
	}
	while (!res);
}

int input_get_third_arg(char (*str)[], int str_size)
{
	int flag;
	int radix_result_num = 0;
	int rr_buf_length = 0;

	do
	{
		flag = 0;
		printf("%s", "Enter THIRD argument\n"
					 "(radix_result_num): ");
		get_str(str, MAX_THIRD_ARG_LENGTH);
		rr_buf_length = str_len(*str);
		/*
		printf("%s", "    radix_trans_buf = ");									//
		int i;
		for (i = 0; (*str)[i]; i++)
			printf("%d ", (*str)[i]);
		printf("%d\n", (*str)[i]);
		printf("    rt_buf_length = %d\n", rr_buf_length);
		*/
		radix_result_num = str_to_int(*str, rr_buf_length, DECIMAL);
		/*
		printf("    radix_transfer_num = %d\n\n", radix_result_num);	
		*/
		if ( (radix_result_num >= BINARY && radix_result_num <= DECIMAL) || (radix_result_num == HEX) )
			flag = 1;
	}
	while ( (!flag) );
	
	return radix_result_num;
}

int cmd_get_first_arg(const char* argv1, int arg1_len)
{
	int radix_transfer_num = 0;
	
	radix_transfer_num = str_to_int(argv1, arg1_len, DECIMAL);
	if ( !radix_transfer_num )
	{
		printf("%s\n", "Incorrect FIRST command line argument!");
		return 0;
	}
	if ( (radix_transfer_num < BINARY || radix_transfer_num > DECIMAL) && (radix_transfer_num != HEX) )
	{
		printf("%s\n", "Incorrect FIRST argument range value");
		return 0;
	}

	return radix_transfer_num;
}

int cmd_get_second_arg(char (*transfer_num)[], const char* argv2, int arg2_len, int radix_transfer_num)
{
	int i = 0;
	for (; argv2[i]; i++)
	{
		(*transfer_num)[i] = argv2[i];
		if (i > MAX_INPUT_LENGTH-1) break;
	}
	(*transfer_num)[i] = '\0';
	
	int res = isCorrectTransferNum(*transfer_num, arg2_len, radix_transfer_num);		
	if ( !res )
	{
		printf("%s\n", "Incorrect SECOND command line argument");
		return 0;
	}

	return 1;
}

int cmd_get_third_arg(const char* argv3, int arg3_len)
{
	int radix_result_num = str_to_int(argv3, arg3_len, DECIMAL);
	if ( !radix_result_num )
	{
		printf("%s\n", "Incorrect THIRD command line argument!");
		return 0;
	}
	if ( (radix_result_num < BINARY || radix_result_num > DECIMAL) && (radix_result_num != HEX) )
	{
		printf("%s\n", "Incorrect THIRD argument range value");
		return 0;
	}

	return radix_result_num;
}
/*																			*/
#endif
