#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function Prototypes
int romanToDecimal(char *roman);
void performArithmeticOperation(char *inputFile, char *outputFile);
void decimalToWords(int num, char *output);
void convertToWords(int n, char *result);

// Main Function
int main() {
    // Input and output file names
    char inputFile[] = "binary.txt";
    char outputFile[] = "Output.txt";

    // Perform the arithmetic operation
    performArithmeticOperation(inputFile, outputFile);

    printf("Program executed successfully. Check '%s' for results.\n", outputFile);
    return 0;
}

// Function to Convert Roman Numerals to Decimal
int romanToDecimal(char *roman) {
    int value = 0, prev = 0, current = 0;

    // Map Roman numerals to their decimal equivalents
    for (int i = strlen(roman) - 1; i >= 0; i--) {
        switch (toupper(roman[i])) {
            case 'I': current = 1; break;
            case 'V': current = 5; break;
            case 'X': current = 10; break;
            case 'L': current = 50; break;
            case 'C': current = 100; break;
            case 'D': current = 500; break;
            case 'M': current = 1000; break;
            default: current = 0; // Non-Roman numeral character
        }

        // Subtract if current is less than previous, else add
        if (current < prev)
            value -= current;
        else
            value += current;

        prev = current;
    }
    return value;
}

// Function to Perform Arithmetic Operations on Input File
void performArithmeticOperation(char *inputFile, char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (!in || !out) {
        printf("Error: Unable to open file(s).\n");
        return;
    }

    char roman1[20], roman2[20], operator;
    while (fscanf(in, "%s %c %s", roman1, &operator, roman2) != EOF) {
        int num1 = romanToDecimal(roman1);
        int num2 = romanToDecimal(roman2);
        int result = 0;
        char wordResult[500] = "";

        // Perform the arithmetic operation
        switch (operator) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            default: fprintf(out, "Invalid operator: %c\n", operator); continue;
        }

        // Convert result to words
        decimalToWords(result, wordResult);
        fprintf(out, "%d %c %d = %s\n", num1, operator, num2, wordResult);
    }

    fclose(in);
    fclose(out);
}

// Function to Convert a Decimal Number to Words
void decimalToWords(int num, char *output) {
    if (num < 0) {
        strcat(output, "Negative ");
        num = -num;
    }

    if (num == 0) {
        strcat(output, "Zero");
        return;
    }

    convertToWords(num, output);
}

// Recursive Helper Function to Convert Numbers to Words
void convertToWords(int n, char *result) {
    // Arrays to store words for units, tens, and teens
    char *units[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                     "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                     "Seventeen", "Eighteen", "Nineteen"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    // Handle billions place
    if (n >= 1000000000) {
        convertToWords(n / 1000000000, result);
        strcat(result, " Billion ");
        n %= 1000000000;
    }

    // Handle millions place
    if (n >= 1000000) {
        convertToWords(n / 1000000, result);
        strcat(result, " Million ");
        n %= 1000000;
    }

    // Handle thousands place
    if (n >= 1000) {
        convertToWords(n / 1000, result);
        strcat(result, " Thousand ");
        n %= 1000;
    }

    // Handle hundreds place
    if (n >= 100) {
        strcat(result, units[n / 100]);
        strcat(result, " Hundred ");
        n %= 100;
    }

    // Handle tens and units
    if (n >= 20) {
        strcat(result, tens[n / 10]);
        strcat(result, " ");
        strcat(result, units[n % 10]);
    } else if (n > 0) {
        strcat(result, units[n]);
    }
}
