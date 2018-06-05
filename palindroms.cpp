#include <iostream>
using namespace std;
int LielakaisPalindroms()
{
    int maximum = 0;
    int reiz1, reiz2;
    for (int i = 9999; i >= 1000; i--)
    {
        for (int j = i; j >= 1000; j--)
        {
            int result = i * j;
            if (result < maximum) break;
            int number = result;
            int reverse = 0;
            while (number != 0) //Apgriezam skaitli atradak
            {
                reverse = reverse * 10 + number % 10;
                number /= 10;
            }
            if (result == reverse && result > maximum)
                {
                    reiz1 = j;
                    reiz2 = i;
                    maximum = result;
                }
        }
    }
    cout << reiz1 << "x" << reiz2 << " = ";
    return maximum;
}

int main()
{
    int maximum = 0;
    int reiz1, reiz2;
    for (int i = 9999; i >= 1000; i--)
    {
        for (int j = i; j >= 1000; j--)
        {
            int result = i * j;
            if (result < maximum) break;
            int number = result;
            int reverse = 0;
            while (number != 0) //Apgriezam skaitli atradak
            {
                reverse = reverse * 10 + number % 10;
                number /= 10;
            }
            if (result == reverse && result > maximum)
                {
                    reiz1 = j;
                    reiz2 = i;
                    maximum = result;
                }
        }
    }
    cout << reiz1 << "x" << reiz2 << " = " << maximum;
}
