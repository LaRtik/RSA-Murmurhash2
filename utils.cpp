#include "utils.h"

    bigint utils::gcd(bigint a, bigint b)
    {
        while (a != b)
        {
            if (a > b)
            {
                bigint tmp = a;
                a = b;
                b = tmp;
            }
            b = b - a;
        }
        return a;
    }

    bool utils::prime(bigint n)
    {
        for (bigint i = 2; i <= bigint::sqrt(n); i = i + 1)
            if (n % i == 0)
                return false;
        return true;
    }
