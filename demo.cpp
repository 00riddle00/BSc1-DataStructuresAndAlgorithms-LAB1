/*=============================================================================
 | Program for testing Big Numbers ADT without the user input
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <climits>

// Header file with useful debugging macros
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
    printf("-----------PREPARING FOR LIVE TESTS-----------\n");

    Number *num01 = setNumberFromChar((char *) "100.0");
    res = factorial(num01);
    assert(strcmp(numToChar(res), "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000.0") == 0 && "factorial test01 failed");
    printf("factorial passed\n");

    Number *num02 = setNumberFromChar((char *) "7.0");
    res = nextPrime(num02);
    assert(strcmp(numToChar(res), "11.0") == 0 && "nextPrime test01 failed");
    printf("nextPrime passed\n");

    Number *num03 = setNumberFromChar((char *) "213421342318412384912738132894712.8128374823174812377321");
    res = raiseByPow(num03, 6);
    assert(strcmp(numToChar(res), "94498971652638775929231672647833888771141190540374490793799910241413225365722228670047638705370321438791975293971242620109600173039630619238456992875182844589511986507136169417095017804371947032.203664451869145012957479866119182321453596311449965459940509922047959178153412323810076888179364706154977928824519669175533302959921") == 0 && "raiseByPow test01 failed");
    printf("raiseByPow passed\n");

    Number *num04 = setNumberFromChar((char *) "5.0");
    res = Log(num04);
    setPrecision(res, -100);
    assert(strcmp(numToChar(res), "1.6094379124341003746007593332261876395256013542685177219126478914741789877076577646301338780931796108") == 0 && "Log test01 failed");
    printf("Log passed\n");

    Number *num05 = setNumberFromChar((char *) "20.0");
    res = Sine(num05);
    setPrecision(res, -100);
    assert(strcmp(numToChar(res), "0.9129452507276276543760999838456823012979325837081899563051281147688489193490729760444800496404699762") == 0 && "Sine test01 failed");
    printf("Sine passed\n");

    printf("//---------PREPARING FOR LIVE TESTS-----------\n");
    printf("[All tests have passed successfully]\n");
//    /* // live tests */
}
