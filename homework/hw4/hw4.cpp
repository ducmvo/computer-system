// AUTHOR: Duc Vo
// FILE: hw2.cpp
// DATE: 02/23/2022
// PURPOSE: This program allows user to enter name-score pairs, sort the scores
//          in ascending order and calculates the average score
// INPUT:   Prompts from user.
// PROCESS: the program prompts user for the number of test scores,
//          then let user input eacg student name/score.
//          Once all the scores are entered. The program sorts, calculate average scores
//           and prints out the result to the screen.
// OUTPUT:  Prints sorted students name/score and average score

#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

template <typename T>
void swap(T, int, int);
// Function:    swap
// Purpose:     swap two values in an array
// Parameters:  array pointer, indexes of swap values
// Returns:     None

void sort(string *, short *, int);
// Function:    sort
// Purpose:     sort scores and names in ascending order
// Parameters:  students names, scores array pointers and size
// Returns:     None

double getAverage(short *, int);
// Function:    getAverage
// Purpose:     calculate the average scores of all students
// Parameters:  scores array pointer, size of array
// Returns:     the average score

void printResult(string *, short *, int);
// Function:    printResult
// Purpose:     print student names/scores and average scores
// Parameters:  scores/names array pointers, size of array
// Returns:     none

string getName(string name = "");
// Function:    getName
// Purpose:     get student name from user input or passed in param
// Parameters:  student name (optional)
// Returns:     student name

short getScore(long score = -1);
// Function:    getScore
// Purpose:     get student score from user input or passed in param
// Process:     if the input score is negative or greater than 100, score will
//              be returned as default maximum or minimum value
// Parameters:  student score (optional)
// Returns:     student score

void runProgram(bool test = false);
// Function:    runProgram
// Purpose:     run the program or run test the program
// Process:     if the input is true, the program will run test with predefined input
//              otherwise the run the main program with user input
// Parameters:  test boolean
// Returns:     none

int main()
{
    bool test = true;
    runProgram(test);
    runProgram();
    return 0;
}

template <typename T>
void swap(T *arr, int i, int j)
{
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void sort(string *names, short *scores, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (scores[j] < scores[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
        {
            swap<short>(scores, minIndex, i);
            swap<string>(names, minIndex, i);
        };
    }
}

double getAverage(short *scores, int size)
{
    double avg = 0;
    for (int i = 0; i < size; i++)
        avg += scores[i];
    return avg / size;
}

void printResult(string *names, short *scores, int size)
{
    cout << left << setw(15) << "Name"
         << "Score" << endl;

    for (int i = 0; i < size; i++)
        cout << left << setw(15) << names[i] << scores[i] << endl;

    cout << "\nAverage score: " << setprecision(2) << fixed
         << getAverage(scores, size) << endl;
}

string getName(string name)
{
    if (name == "")
        getline(cin, name);
    return name;
}

short getScore(long score)
{
    if (score == -1)
    {
        cin >> score;
        cin.ignore(100, '\n');
    }
    const short MIN = 0, MAX = 100;
    if (score > MAX)
        return MAX;
    if (score < MIN)
        return MIN;
    return score;
}

void runProgram(bool test)
{
    string *names;
    short *scores;
    int size;

    if (test)
    {
        size = 5;
        const double expectedAvg = 95.80;

        const string testNames[] = {"King", "Lewis", "Goss", "Green", "Clinton"};
        const short testScores[] = {100, 90, 98, 95, 96};

        string expectedSortedNames[] = {"Lewis", "Green", "Clinton", "Goss", "King"};
        short expectedSortedScores[] = {90, 95, 96, 98, 100};

        names = new string[size];
        scores = new short[size];

        for (int i = 0; i < size; i++)
        {
            names[i] = getName(testNames[i]);
            scores[i] = getScore(testScores[i]);
        }
        cout << "=== TEST SORT ===\n";
        sort(names, scores, size);

        bool pass = true;
        for (int i = 0; i < size; i++)
        {
            if (scores[i] != expectedSortedScores[i] || names[i] != expectedSortedNames[i])
                pass = false;
        }
        cout << "PASSED: " << (pass ? "TRUE" : "FALSE") << endl;

        double avg = getAverage(scores, size);
        cout << "=== TEST AVERAGE ===\n"
             << setprecision(2) << fixed << avg << "/"
             << setprecision(2) << fixed << expectedAvg << endl;
        cout << "PASSED: " << (avg == expectedAvg ? "TRUE" : "FALSE") << endl;

        cout << "=== TEST GET SCORE ===\n";
        cout << "input negative | score: " << getScore(-10) << "/0" << endl;
        cout << "input greater than 100 | score: " << getScore(100) << "/100" << endl;
        cout << "input maximum short | score: " << getScore(SHRT_MAX) << "/100" << endl;
    }
    else
    {
        cout << "\n ==== WELCOME TO AVERAGE SCORES PROGRAM! ====\n"
             << endl;
        cout << "How many test scores will you enter? ";
        cin >> size;
        cin.ignore(100, '\n');

        names = new string[size];
        scores = new short[size];

        for (int i = 0; i < size; i++)
        {
            cout << "\nEnter student " << (i + 1) << "’s last name: ";
            names[i] = getName();
            cout << "Enter that student’s test score: ";
            scores[i] = getScore();
        }

        sort(names, scores, size);

        cout << "\nThe test scores in ascending order, and their average, are: \n\n";
        printResult(names, scores, size);
    }

    delete[] names;
    delete[] scores;
}