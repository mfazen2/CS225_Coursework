/**
 * @file main.cpp
 * Contains code to test your recursion, stack, and queue problems.
 */

#include "../src/quackfun.h"
#include "../src/exercises.h"
#include <unistd.h>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

template <typename T>
inline string to_string(const T& value);
template <typename T>
inline string colorize(const T& actual, const T& expected);
string make_red(const string& output);
string make_green(const string& output);

int main()
{
    cout << boolalpha
         << endl; // make true and false print for bools, not 0 and 1

    // Run sumDigits:
    cout << "==== sumDigits ====" << endl;
    cout << "sumDigits(243) = " << colorize(RecursionExercises::sumDigits(243), 9) << endl;
    cout << "expected       = " << 9 << endl;
    cout << "sumDigits(49)  = " << colorize(RecursionExercises::sumDigits(49), 13) << endl;
    cout << "expected       = " << 13 << endl;
    cout << "sumDigits(1)   = " << colorize(RecursionExercises::sumDigits(1), 1) << endl;
    cout << "expected       = " << 1 << endl;
    cout << "sumDigits(0)   = " << colorize(RecursionExercises::sumDigits(0), 0) << endl;
    cout << "expected       = " << 0 << endl << endl;

    // Run triangle:
    cout << "==== triangle ====" << endl;
    cout << "triangle(0) = " << colorize(RecursionExercises::triangle(0), 0) << endl;
    cout << "expected    = " << 0 << endl;
    cout << "triangle(3) = " << colorize(RecursionExercises::triangle(3), 6) << endl;
    cout << "expected    = " << 6 << endl;
    cout << "triangle(6) = " << colorize(RecursionExercises::triangle(6), 21) << endl;
    cout << "expected    = " << 21 << endl << endl;

    // Run sum:
    cout << "==== sum ====" << endl;
    stack<int> s;

    const int n = 16;
    for (int i = 0; i <= n; i++)
        s.push(i);

    stack<int> orig = s;
    cout << "Sum:      " << colorize(QuackFun::sum<int>(s), 136) << endl;
    cout << "Expected: " << 136 << endl;
    if (s == orig)
        cout << "Stack " + make_green("unmodified: :)") << endl;
    else
        cout << "Stack " + make_red("CHANGED: :(") << endl;
    cout << endl;
    // Run isBalanced:
    cout << "==== balance ====" << endl;
    string ss= "()";
    queue<char> qee;

    for (char c : ss)
        qee.push(c);

    cout << QuackFun::isBalanced(qee) << endl;
    cout << "EXPECTED: TRUE" << endl;

    // Run scramble:
    cout << "==== scramble ====" << endl;
    queue<int> q;
    for (int i = 0; i <= 16; i++)
        q.push(i);

    QuackFun::scramble<int>(q);

    int expected[] = {0, 2, 1, 3, 4, 5, 9, 8, 7, 6, 10, 11, 12, 13, 14, 16, 15};
    cout << "Scrambled queue: ";
    for (int i = 0; i <= 16; i++) {
        cout << colorize(q.front(), expected[i]) << ' ';
        q.pop();
    }
    cout << endl;
    cout << "Expected:        0 2 1 3 4 5 9 8 7 6 10 11 12 13 14 16 15 " << endl << endl;

}

template <typename T>
inline string to_string(const T& value)
{
    stringstream ss;
    ss << boolalpha << value;
    return ss.str();
}

template <typename T>
inline string colorize(const T& actual, const T& expected)
{
    if (isatty(STDOUT_FILENO)) {
        if (actual == expected)
            return "\033[32m" + to_string(actual) + "\033[0m";
        else
            return "\033[31m" + to_string(actual) + "\033[0m";
    } else
        return to_string(actual);
}

string make_red(const string& output)
{
    if (isatty(STDOUT_FILENO))
        return "\033[31m" + output + "\033[0m";
    else
        return output;
}

string make_green(const string& output)
{
    if (isatty(STDOUT_FILENO))
        return "\033[32m" + output + "\033[0m";
    else
        return output;
}
