### DESCRIPTION

This is a set of C++ macros implementing basic [software contracts](http://weblambdazero.blogspot.com/2013/09/design-by-contract.html).

### INSTALLATION

The software requires no installation, just include the "contract.hpp" file in your source code.

There is also an example application example.cpp which you can build with "make".

### USAGE

Classic design by contract uses a set of preconditions and postconditions to ensure software correctness. Take the following function as an example:

```cpp
// Calculate greatest common divisor of two integers
int gcd(int a, int b)
{
    int result;

    if (b == 0) {
        result = a;
    } else {
        result = gcd(b, a % b);
    }

    return result;
}
```

According to the [definition](http://en.wikipedia.org/wiki/Greatest_common_divisor) "the greatest common divisor of two or more integers (at least one of which is not zero), is the largest positive integer that divides the numbers without a remainder". To make sure that the gcd() function meets the definition we create a **contract**, which says: "if provided arguments are two integers, and at least one of them is not zero, than the result is an integer that divides both numbers without a reminder". We can divide this contract into a precodition ("provided arguments are two integers, and at least one of them is not zero") and a postcondition ("the result is an integer that divides both numbers without a reminder"), which can be written down as follows:

```cpp
// Calculate greatest common divisor of two integers
int gcd(int a, int b)
{
    REQUIRES(a != 0 || b != 0) // precondition
    int result;

    if (b == 0) {
        result = a;
    } else {
        result = gcd(b, a % b);
    }

    ENSURES((a % result == 0) && (b % result == 0)) // postcondition
    return result;
}
```

Conditions within REQUIRES and ENSURES statements must evaluate to true. If they don't, it means that the contract has been broken, and a **contract::exception** is raised.

### TURNING OFF CONSTRAINT CHECKING

If the constraint checking is an issue (for example decreases your code performance) you can turn it off by defining NDEBUG symbol during compilation. It is the very same symbol that is used by C/C++ compilers to control the behavior of the standard assert() macro:

```sh
gcc -DNDEBUG example.cpp
```

### FINAL NOTES

Make sure you don't use a combination of REQUIRES and ENSURES which are mutually dependent, for example:

```cpp
bool prime(int x)
{
    // some code here

    ENSURES(!compound(result))
    return result;
}

bool compound(int x)
{
    // some code here

    ENSURES(!prime(result))
    return result;
}
```

This will lead to cyclic execution of both functions and will result either in infinite loop or stack overflow.
