/**
 * The program take calculate power and logarithm from user inputs
 * @author: Duc Vo 
 * @date: 01/13/2022
 * @version: 1.0
 */

#include <iostream>
using namespace std;

int power(int, int);
// Calculate power
// return 0 if exponent is negative

int myLog(int, int);
// Calculate logarithm
// condition base > 1 and num > 0

/**
 * The program take calculate power and logarithm from user inputs
 */
int main() {
    int base, exp, num;

    cout << "This program calculate power " 
    << "and log from your inputs." << endl;

    cout << "\n========= POWER =========\n";
    cout << "Enter a base: ";
    cin >> base;
    cout << "Enter an exponent: ";
    cin >> exp;

    printf("\n%d to the power of %d is %d\n", base, exp, power(base, exp));

    cout << "\n======== LOGARITHM ========\n";
    cout << "Enter a base: ";
    cin >> base;
    cout << "Enter a number: ";
    cin >> num;

    printf("\nLog of %d in base %d is %d\n\n", num, base, myLog(base, num));

    cout << "Thanks for using the program." << endl;
    
    return 0;
}

int power(int num, int exp) {
    if (exp < 0) return 0;
    if (exp == 0) return 1;
    return num * power(num, exp-1)  ;
}

int myLog(int base, int num) {
    if (base <= 1 ||  num < 0) return -1;
    if (num/base < 1) return 0;
    return 1 + myLog(base, (num/base));
}