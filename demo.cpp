/*=============================================================================
 | Program for testing Big Numbers ADT without the user input
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Header file with useful debugging macros
#include "dbg.h"
#include "numbers.h"


int main() {

    Number *num1 = setNumberFromChar((char *) "81234812384091238.8901234");
    Number *num2 = setNumberFromChar((char *) "-12380441238423.82431432");

    Number *res;

    /* testing arithmetic */
    res = addNumbers(num1, num2);
    assert(strcmp(numToChar(res), "81222431942852815.06580908") == 0 && "addNumbers test01 failed");

    res = subtractNumbers(num1, num2);
    assert(strcmp(numToChar(res), "81247192825329662.71443772") == 0 && "subtractNumbers test01 failed");

    res = multiplyNumbers(num1, num2);
    assert(strcmp(numToChar(res), "-1005722821235625557767394406067.695067825187088") == 0 &&
           "multiplyNumbers test01 failed");

    res = divideNumbers(num1, num2);
    assert(strcmp(numToChar(res), "-6561.54419860025807258480133651369799292598220471119087440522753152172937147050145087534158469354169467861073368962805080144763639103815994729925250725392659630057069975612925521735560029401045650694433091") == 0 && "divideNumbers test01 failed");
    /* // testing arithmetic */

    /* testing modulus  (all possible combinations the quotient of two positive/negative numbers */
    res = modulus(setNumberFromChar((char *) "-20.0"), setNumberFromChar((char *) "-7.0"));
    assert(strcmp(numToChar(res), "-6.0") == 0 && "modulus test01 failed");

    res = modulus(setNumberFromChar((char *) "4.0"), setNumberFromChar((char *) "17.0"));
    assert(strcmp(numToChar(res), "4.0") == 0 && "modulus test02 failed");

    res = modulus(setNumberFromChar((char *) "-3.0"), setNumberFromChar((char *) "19.0"));
    assert(strcmp(numToChar(res), "16.0") == 0 && "modulus test03 failed");

    res = modulus(setNumberFromChar((char *) "-16.0"), setNumberFromChar((char *) "4.0"));
    assert(strcmp(numToChar(res), "0.0") == 0 && "modulus test04 failed");

    res = modulus(setNumberFromChar((char *) "-16.0"), setNumberFromChar((char *) "3.0"));
    assert(strcmp(numToChar(res), "2.0") == 0 && "modulus test05 failed");
//
    res = modulus(setNumberFromChar((char*)"2.0"), setNumberFromChar((char*)"-19.0"));
    assert(strcmp(numToChar(res), "-17.0") == 0 && "modulus test06 failed");

    res = modulus(setNumberFromChar((char*)"19.0"), setNumberFromChar((char*)"-12.0"));
    assert(strcmp(numToChar(res), "-5.0") == 0 && "modulus test07 failed");

    res = modulus(setNumberFromChar((char *) "20.0"), setNumberFromChar((char *) "7.0"));
    assert(strcmp(numToChar(res), "6.0") == 0 && "modulus test08 failed");

    res = modulus(setNumberFromChar((char *) "0.0"), setNumberFromChar((char *) "7.0"));
    assert(strcmp(numToChar(res), "0.0") == 0 && "modulus test09 failed");
    /*  // testing modulus */

    /* testing comparison */
    int cmp;

    cmp = compareEqual(num1, num2);
    assert(cmp == 0 && "compareEqual test01 failed");

    cmp = compareNotEqual(num1, num2);
    assert(cmp == 1 && "compareNotEqual test01 failed");

    cmp = compareGreaterThan(num1, num2);
    assert(cmp == 1 && "compareGreaterThan test01 failed");

    cmp = compareLessThan(num1, num2);
    assert(cmp == 0 && "compareLessThan test01 failed");

    cmp = compareGreaterThanOrEqual(num1, num2);
    assert(cmp == 1 && "compareGreaterThanOrEqual test01 failed");

    cmp = compareLessThanOrEqual(num1, num2);
    assert(cmp == 0 && "compareLessThanOrEqual test01 failed");

    assign(num1, num2);
    assert(strcmp(numToChar(num1), numToChar(num2)) == 0 && "assign test01 failed");
    /* // testing comparison */

    /* testing additional functions */
    int digit;
    Number *num3 = setNumberFromChar((char *) "123.456");

    digit = getWholeLen(num3);
    assert(digit == 3 && "getWholeLen test01 failed");

    digit = getDecimalLen(num3);
    assert(digit == 3 && "getDecimalLen test01 failed");

    digit = getIthDigit(num3, 2);
    assert(digit == 2 && "getIthDigit test01 failed");

    digit = getIthDigit(num3, -2);
    assert(digit == 5 && "getIthDigit test02 failed");

    increment(num3);
    assert(strcmp(numToChar(num3), "124.456") == 0 && "increment test01 failed");

    decrement(num3);
    assert(strcmp(numToChar(num3), "123.456") == 0 && "increment test01 failed");

    assign(num3, setNumberFromChar((char *) "5.5"));
    plusEquals(num3, setNumberFromChar((char *) "12.2"));
    assert(strcmp(numToChar(num3), "17.7") == 0 && "plusEquals test01 failed");

    assign(num3, setNumberFromChar((char *) "5.5"));
    minusEquals(num3, setNumberFromChar((char *) "6.8"));
    assert(strcmp(numToChar(num3), "-1.3") == 0 && "minusEquals test01 failed");

    assign(num3, setNumberFromChar((char *) "5.5"));
    multiplyEquals(num3, setNumberFromChar((char *) "15.6"));
    assert(strcmp(numToChar(num3), "85.8") == 0 && "multiplyEquals test01 failed");

    assign(num3, setNumberFromChar((char *) "5.5"));
    divideEquals(num3, setNumberFromChar((char *) "1.1"));
    assert(strcmp(numToChar(num3), "5.0") == 0 && "divideEquals test01 failed");

    assign(num3, setNumberFromChar((char *) "5.5"));
    modulusEquals(num3, setNumberFromChar((char *) "1.4"));
    assert(strcmp(numToChar(num3), "1.3") == 0 && "modulusEquals test01 failed");
    /* // testing additional functions */

    /* live tests */
    Number *num4 = setNumberFromChar((char *) "6.0");
    res = factorial(num4);
    assert(strcmp(numToChar(res), "720.0") == 0 && "factorial test01 failed");
    debug("factorial ok");

    Number *num5 = setNumberFromChar((char *) "7.0");
    res = nextPrime(num5);
    assert(strcmp(numToChar(res), "11.0") == 0 && "nextPrime test01 failed");
    debug("nextPrime ok");

    Number *num6 = setNumberFromChar((char *) "1.1");
    res = raiseByPow(num6, 2);
    assert(strcmp(numToChar(res), "1.21") == 0 && "raiseByPow test01 failed");
    debug("raiseByPow ok");
    /* // live tests */

//    Number *num7 = setNumberFromChar((char *) "5.0");
//    res = Log(num7);
//    setPrecision(res, 100);
//    assert(strcmp(numToChar(res), "1.609437912434100374600759333226187639525601354268517721912647891474178987707657764630133878093179611") == 0 && "Sine test01 failed");
//    debug("Log ok");
//
//    Number *num8 = setNumberFromChar((char *) "20.0");
//    res = Sine(num8);
//    setPrecision(res, 100);
//    assert(strcmp(numToChar(res), "0.9129452507276276543760999838456823012979325837081899563051281147688489193490729760444800496404699762") == 0 && "Sine test01 failed");
//    debug("Sine ok");

}
