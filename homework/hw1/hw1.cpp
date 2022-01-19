// AUTHOR: Sample Solution HW1-5041
// FILE: hw1.cpp
// DATE: Insert date
// PURPOSE: This program is used to test the custom designed functions  that
//          calculate power (a number to the power of another number) and  that
//          calculate the log of a number in a given base.
// INPUT:   Prompts from user.
// PROCESS: There are two tests, one to verify power and the other to verify
//          myLog. After the tests, a client program runs, prompting the user
//          for values that will be used to calculate the power and log of the
//          numbers entered.
// OUTPUT:  Prints results of tests and calculations of values entered by user.
#include <iostream>
#include <string>
using namespace std;
// Function:    runProgram
// Purpose:     Calls functions calculatePower() and calculateLog() in a loop.
// Parameters:  None
// Returns:     None
void runProgram();
// Function:    calculatePower
// Purpose:     Prompts user for values for base and exponent, and calculates
//              power using power function.
// Parameters:  None
// Returns:     None
void calculatePower();
// Function:    calculateLog
// Purpose:     Prompts user for values for base and number, and calculates
//              log using myLog function.
// Parameters:  None
// Returns:     None
void calculateLog();
// Function:    power
// Purpose:     Computes num to the exp power
// Parameters:  The number â€“ num, and the exponent â€“ exp
// Returns:     0 if exp is negative; 1 if exp is 0; raise num to the exp
//              power otherwise.
int power(int num, int exp);
// Function:    myLog
// Purpose:     Computes the log of a number to the specified base
// Parameters:  The base â€“ base, and the number â€“ num
// Returns:     a rounded down value of the log of num in the base
int myLog(int base, int num);
// Function:    testTaskOne
// Purpose:     Tests the function power
// Parameters:  None
// Returns:     None
void testTaskOne();
// Function:    testTaskTwo
// Purpose:     Tests the function myLog
// Parameters:  None
// Returns:     None
void testTaskTwo();
int main()
{
    cout << "\n---- HOMEWORK 1 ----" << endl;
    testTaskOne();
    testTaskTwo();
    runProgram();
    return 0;
}
void runProgram()
{
    cout << "\n---- CLIENT PROGRAM ----" << endl;
    char cont = 'Y';
    while (cont == 'Y')
    {
        calculatePower();
        calculateLog();
        cout << "\nWould you like to calculate another log? (Y/N) ";
        string input;
        getline(cin, input);
        cont = input[0];
        cont = toupper(cont);
    }
    cout << "\nExiting homework 1..." << endl;
}

void calculatePower()
{
    bool isInputValid = false;
    while (!isInputValid)
    {
        try
        {
            cout << "\nEnter a base: ";
            string input;
            getline(cin, input);
            // Base can be any integer, so no validation needed
            int base = stoi(input);

            cout << "Enter an exponent: ";
            getline(cin, input);
            // Validation for exponent happens in power(), so no  validation here
            int exp = stoi(input);
            int result = power(base, exp);
            cout << "\n"
                      << base << " to the " << exp << " is " << result
                      << endl;
            isInputValid = true;
        }
        catch (invalid_argument &iae)
        {
            cout << "Please enter a valid integer..." << endl;
            isInputValid = false;
        }
    }
}

void calculateLog()
{
    bool isInputValid = false;
    while (!isInputValid)
    {
        try
        {
            cout << "\n\nEnter a base: ";
            string input;
            getline(cin, input);
            int base = stoi(input);
            cout << "Enter a number: ";
            getline(cin, input);
            int num = stoi(input);
            int result = myLog(base, num);
            cout << "\nLog of " << num << " in base " << base << " is "
                      << result << endl;
            isInputValid = true;
        }
        catch (invalid_argument &iae)
        {
            cout << "Please enter a valid integer..." << endl;
            isInputValid = false;
        }
    }
}
int power(int num, int exp)
{
    if (exp == 0)
        return 1;
    else if (exp > 0)
    {
        int result = 1;
        for (int i = 0; i < exp; i++)
            result *= num;
        return result;
    }
    return 0;
}

int myLog(int base, int num)
{
    if (base > 1 && num > 0)
    { // conditions to perform log
        int result = 0;
        int exp = 0;
        while (result < num)
        {
            int temp = power(base, exp);
            if (temp == num)
                return exp;
            else if (temp > num)
                return --exp;
            result = temp;
            exp++;
        }
    }
    return -1;
}

void testTaskOne()
{
    cout << "\n---- TASK 1 ----" << endl;
    cout << "* Test 1 - 2 power of 2: ";
    int pow = power(2, 2);
    cout << pow << endl;
    cout << "* Test 2 - edge case 2 power of 0: ";
    pow = power(2, 0);
    cout << pow << endl;
    cout << "* Test 3 - edge case 2 power of -2: ";
    pow = power(2, -2);
    cout << pow << endl;
}

void testTaskTwo()
{
    cout << "\n---- TASK 2 ----" << endl;
    cout << "* Test 1 - log of 777 in base 5: ";
    int log = myLog(5, 777);
    cout << log << endl;
    cout << "* Test 2 - log of 3,125 in base 5: ";
    log = myLog(5, 3125);
    cout << log << endl;
    cout << "* Test 3 - edge case log of 1 in base 5: ";
    log = myLog(5, 1);
    cout << log << endl;
    cout << "* Test 4 - edge case log of -2 in base 0: ";

    log = myLog(0, -2);
    cout << log << endl;
    cout << "* Test 5 - edge case log of 777 in base 1: ";
    log = myLog(1, 777);
    cout << log << endl;
}