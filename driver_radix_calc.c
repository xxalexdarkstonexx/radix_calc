#include "radix_calc.h"

int main(int argc, char** argv)
{
	char radix_trans_buf[MAX_FIRST_ARG_LENGTH+1] = "";
	int radix_transfer_num = 0;
	char transfer_num[MAX_INPUT_LENGTH+1] = "";
	char radix_res_buf[MAX_THIRD_ARG_LENGTH+1] = "";
	int radix_result_num = 0;


	if ( argc < MAX_PROGRAM_ARGS )
	{
		printf("%s", "Incorrect program usage!\n"
				     "Please, use following notation:\n"
					 "<program_name> <radix_tranfer_num> <transfer_number> <radix_result_num>\n"
					 "<> - necessery parameters\n\n\n"
			  );

		switch ( argc )
		{
			case 1:
				radix_transfer_num = input_get_first_arg(&radix_trans_buf, MAX_FIRST_ARG_LENGTH+1);
				printf("Your FIRST argument is: %d\n", radix_transfer_num);

				
				input_get_second_arg(&transfer_num, radix_transfer_num);
				printf("Your SECOND argument is: %s\n", transfer_num);
			

				radix_result_num = input_get_third_arg(&radix_res_buf, MAX_THIRD_ARG_LENGTH+1);
				printf("Your THIRD argument is: %d\n", radix_result_num);
				break;
			case 2:
				;int arg1_len = str_len(argv[1]);
				radix_transfer_num = cmd_get_first_arg(argv[1], arg1_len);
				if ( !radix_transfer_num )
					return 0;
				printf("Your FIRST argument is: %d\n", radix_transfer_num);
				

				input_get_second_arg(&transfer_num, radix_transfer_num);
				printf("Your SECOND argument is: %s\n", transfer_num);

				
				radix_result_num = input_get_third_arg(&radix_res_buf, MAX_THIRD_ARG_LENGTH+1);
				printf("Your THIRD argument is: %d\n", radix_result_num);
				break;
			case 3:
				arg1_len = str_len(argv[1]);
				radix_transfer_num = cmd_get_first_arg(argv[1], arg1_len);
				if ( !radix_transfer_num )
					return 0;
				printf("Your FIRST argument: %d\n", radix_transfer_num);


				int arg2_len = str_len(argv[2]);
				if ( !cmd_get_second_arg(&transfer_num, argv[2], arg2_len, radix_transfer_num))
					return 0;
				printf("Your SECOND argument: %s\n", transfer_num);
				

				radix_result_num = input_get_third_arg(&radix_res_buf, MAX_THIRD_ARG_LENGTH+1);
				printf("Your THIRD argument is: %d\n", radix_result_num);
				break;
		}
	}
	else
	{
		int arg1_len = str_len(argv[1]);
		radix_transfer_num = cmd_get_first_arg(argv[1], arg1_len);
		if ( !radix_transfer_num )
			return 0;
		printf("Your FIRST argument: %d\n", radix_transfer_num);

		
		int arg2_len = str_len(argv[2]);
		if ( !cmd_get_second_arg(&transfer_num, argv[2], arg2_len, radix_transfer_num))
			return 0;
		printf("Your SECOND argument: %s\n", transfer_num);



		int arg3_len = str_len(argv[3]);
		radix_result_num = cmd_get_third_arg(argv[3], arg3_len);
		if ( !radix_result_num )
			return 0;
		printf("Your THIRD argument: %d\n", radix_result_num);
	}

	
	int length_transfer_num = str_len(transfer_num);
	char* result_num;
	result_num = Transfer(radix_transfer_num, transfer_num, length_transfer_num, radix_result_num);
	if ( result_num == NULL )
	{
		printf("%s\n", "Internal error has occured!\nMemory to string \"result_num\" didn't allocate!");
		return 0;
	}

	/*int i = 0;
	while (result_num[i])
		i++;
	printf("i = %d\n", i);
	

	printf("%s", "result_num = ");
	for (i = 0; result_num[i]; i++ )
		printf("%d ", result_num[i]);
	printf("%d\n", result_num[i]);*/

	printf("%s in (%d) is %s in (%d)\n", transfer_num, radix_transfer_num, result_num, radix_result_num);

	free(result_num);

	return 0;
}
