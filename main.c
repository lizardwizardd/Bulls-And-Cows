#include "Header.h"

void printArray(int *array, int length)
{
	printf("[");
	for (int i = 0; i < length; i++)
	{
		printf("%d ",array[i]);
	}
	printf("]\n");
}

int pow_int(int base, int power)
{
	int result = 1;
	while (power > 0)
	{
		result = result * base;
		power--;
	}
	return result;
}

int checkIntLength(int number, int check_length) // returns 1 if check_length is the number's length, 0 if it's not
{
	if ((number / pow_int(10, check_length) == 0) && (number / pow_int(10, check_length - 1) != 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int printBullsCows(int input_number, int* generated_number, int number_length)
{
	int bulls = 0; 
	int cows = 0;
	int current_digit;
	int digit_input_index = number_length - 1;
	int digit_array_index = number_length - 1;
	while (input_number > 0) { // goes from the last to the first digit of the input number
		current_digit = input_number % 10;
		digit_array_index = number_length - 1;
		while (digit_array_index >= 0)
		{
			if (generated_number[digit_array_index] == current_digit)
			{
				if (digit_array_index == digit_input_index)
				{
					bulls++;
				}
				else 
				{
					cows++;
				}
			}
			digit_array_index--;
		}
		input_number = input_number / 10;
		digit_input_index--;
	}
	if (bulls + cows > 0) { textcolor(YELLOW); }
	if (bulls + cows > number_length / 2) { textcolor(GREEN); }
	printf("Bulls: %d  Cows: %d\n\n", bulls, cows);
	//std::cout << "Bulls: " << bulls << ", Cows: " << cows << "\n\n";
	if (bulls == number_length) { return 1; } // returns 1 if input_number is the generated number
	else { return 0; }
}

void print_title()
{
	gotoxy(30, 1);
	textbackground(BLACK);
	textcolor(LIGHTRED);
	printf_s(" Bulls and Cows ");
	textbackground(BLACK);
	textcolor(LIGHTGRAY);
}

int main()
{
	//SMALL_RECT window;
	setwindow(82, 20);
	//hidecursor();
	print_title();
	gotoxy(5, 4);
	printf_s("Enter 1 to play");
	gotoxy(5, 5);
	printf_s("Enter 2 to learn how to play\n");
	int help = 0;
	while (1)
	{
		gotoxy(5, 7);
		scanf_s("%d", &help);
		clrscr();
		if (help == 2)
		{
			print_title();
			gotoxy(5, 4);
			printf("Try to guess a (2-5)-digit number. All digits in number are different.\n     After each attempt the program prints out the number of 'bulls' and 'cows'.\n");
			printf("\n     'Cows' is the guessed digits that are in a wrong position;\n\n     'Bulls' is the guessed digits that are in the same position\n     as in the number that you have to guess.\n\n");
			printf("\n\n\n\n     Enter any number to continue: ");
			scanf_s("%d", &help);
			clrscr();
			break;
		}
		else
		{
			if (help = 1) { break; }
			else { printf_s("Enter 1 to play or 2 for help"); }
		}
	}

	srand(time(0));
	int current_digit_index = 0; // index of the current digit in the [digits] array
	int next_digit_index;        // index of the next digit in the [available] array
	int available[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int digits[5] = { -1, -1, -1, -1, -1 };
	int available_max_ind = 9;

	next_digit_index = rand() % available_max_ind + 1;          // +1 because zero can't be the first digit
	digits[0] = available[next_digit_index];                    // picking the first digit
	available[next_digit_index] = available[available_max_ind]; // replace the used digit with the last digit
	available_max_ind--;                                        // ignore the last digit 
	current_digit_index++;
 
	next_digit_index = rand() % (available_max_ind + 1);
	digits[1] = available[next_digit_index];                    // picking the second digit
	available[next_digit_index] = available[available_max_ind];
	available_max_ind--;
	current_digit_index++;

	int n = 0;
	print_title();
	gotoxy(5, 4);
	while (1) // defines the length of the generated number
	{
		printf("Enter the length (2 - 5) of a number that will be generated: ");
		scanf_s("%d", &n);
		printf("\n");
		if ( n >= 2 && n <= 5 )
		{
			clrscr();
			print_title();
			printf("\n\nA %d-digit number was generated.\n", n);
			break;
		}
		else
		{
			gotoxy(5, 4);
			printf("You must enter a number in range from 2 to 5.\n\n");
		}
	}

	for (int i = 2; i < n; i++)
	{
		next_digit_index = rand() % (available_max_ind + 1);
		digits[i] = available[next_digit_index];
		available[next_digit_index] = available[available_max_ind];
		available_max_ind--;
		current_digit_index++;
	}

	int attempts = 0;
	int input_number;
	int divide = pow_int(10, n);

	//printArray(digits, 5);
	//printf("Try to guess a %d-digit number. All digits in number are different.\nAfter each attempt the program prints out the number of 'bulls' and 'cows'.\n", n);
	//printf("'Cows' is the guessed digits that are in a wrong position;\n'Bulls' is the guessed digits that are in the same position as in the number that you have to guess.\n\n");
	printf("Enter the number: ");
	while (1)
	{
		scanf_s("%d", &input_number);
		if (checkIntLength(input_number, n) == 1)
		{
			attempts++;
			if (printBullsCows(input_number, digits, n) == 1) // if the input number is the generated number
			{
				printf_s("You've guessed the number! It took you %d attempts.\n\n", attempts);
				printf("\n\n\nEnter any number to quit. ");
				scanf_s("%d", &help);
				break;
			}
		}
		else 
		{
			printf_s("Wrong input. Enter a %d-digit number. First digit can't be 0.\n\n", n);
		}
	}

	return 0;
}