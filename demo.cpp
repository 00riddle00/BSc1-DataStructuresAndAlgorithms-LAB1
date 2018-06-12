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

    Number* num1 = setNumberFromChar((char*)"81234812384091238.8901234");

//    Number* num1 = setNumberFromChar((char*)"142922272415189.6313164");

    Number* num2 = setNumberFromChar((char*)"-12380441238423.82431432");

    Number* res;



/* FAIL teritory */
//
//    Number* num1 = setNumberFromChar((char*)"512000000000.0");
//    Number* num1 = setNumberFromChar((char*)"995840.0");
//    Number* num1 = setNumberFromChar((char*)"5350400.0");
//
//    Number* num1 = setNumberFromChar((char*)"76544000000.0");
//    Number* num2 = setNumberFromChar((char*)"362880.0");
//

    Number* num3 = setNumberFromChar((char*)"81234812384091238.8901234");
    Number* num4 = setNumberFromChar((char*)"49521764953695297.25728");


    res = subtractNumbers(num3, num4);
    debug("RES IS");
    printEntry(res);
    assert(strcmp(numToChar(res), "31713047430395941.6328434") == 0 && "subtractNumbers test01 failed");
//
/* // FAIL teritory */


    /* testing arithmetic */
//    res = addNumbers(num1, num2);
//    assert(strcmp(numToChar(res), "81222431942852815.06580908") == 0 && "addNumbers test01 failed");
//
//    res = subtractNumbers(num1, num2);
//    assert(strcmp(numToChar(res), "81247192825329662.71443772") == 0 && "subtractNumbers test01 failed");
//
//    res = multiplyNumbers(num1, num2);
//    assert(strcmp(numToChar(res), "-1005722821235625557767394406067.695067825187088") == 0 && "multiplyNumbers test01 failed");
//
    res = divideNumbers(num1, num2);
    debug("RES");
    printEntry(res);
    assert(strcmp(numToChar(res), "-6561.54419860025807258480133651369799292598220471119087440522753152172937147050145087534158469354169467861073368962805080144763639103815994729925250725392659630057069975612925521735560029401045650694433091") == 0 && "divideNumbers test01 failed");
    /* // testing arithmetic */
//
//    /* testing modulus  (all possible combinations the quotient of two positive/negative numbers */
//    res = modulus(setNumberFromChar((char*)"-20.0"), setNumberFromChar((char*)"-7.0"));
//    assert(strcmp(numToChar(res), "-6.0") == 0 && "modulus test01 failed");
//
//    res = modulus(setNumberFromChar((char*)"4.0"), setNumberFromChar((char*)"17.0"));
//    assert(strcmp(numToChar(res), "4.0") == 0 && "modulus test02 failed");
//
//    res = modulus(setNumberFromChar((char*)"-3.0"), setNumberFromChar((char*)"19.0"));
//    assert(strcmp(numToChar(res), "16.0") == 0 && "modulus test03 failed");
//
//    res = modulus(setNumberFromChar((char*)"-16.0"), setNumberFromChar((char*)"4.0"));
//    assert(strcmp(numToChar(res), "0.0") == 0 && "modulus test04 failed");
//
//    res = modulus(setNumberFromChar((char*)"-16.0"), setNumberFromChar((char*)"3.0"));
//    assert(strcmp(numToChar(res), "2.0") == 0 && "modulus test05 failed");
//
//    res = modulus(setNumberFromChar((char*)"2.0"), setNumberFromChar((char*)"-19.0"));
//    assert(strcmp(numToChar(res), "-17.0") == 0 && "modulus test06 failed");
//
//    res = modulus(setNumberFromChar((char*)"19.0"), setNumberFromChar((char*)"-12.0"));
//    assert(strcmp(numToChar(res), "-5.0") == 0 && "modulus test07 failed");
//
//    res = modulus(setNumberFromChar((char*)"20.0"), setNumberFromChar((char*)"7.0"));
//    assert(strcmp(numToChar(res), "6.0") == 0 && "modulus test08 failed");
//
//    res = modulus(setNumberFromChar((char*)"0.0"), setNumberFromChar((char*)"7.0"));
//    assert(strcmp(numToChar(res), "0.0") == 0 && "modulus test09 failed");
//    /*  // testing modulus */
//
//    /* testing comparison */
//    int cmp;
//
//    cmp = compareEqual(num1, num2);
//    assert(cmp == 0 && "compareEqual test01 failed");
//
//    cmp = compareNotEqual(num1, num2);
//    assert(cmp == 1 && "compareNotEqual test01 failed");
//
//    cmp = compareGreaterThan(num1, num2);
//    assert(cmp == 1 && "compareGreaterThan test01 failed");
//
//    cmp = compareLessThan(num1, num2);
//    assert(cmp == 0 && "compareLessThan test01 failed");
//
//    cmp = compareGreaterThanOrEqual(num1, num2);
//    assert(cmp == 1 && "compareGreaterThanOrEqual test01 failed");
//
//    cmp = compareLessThanOrEqual(num1, num2);
//    assert(cmp == 0 && "compareLessThanOrEqual test01 failed");
//
//    assign(num1, num2);
//    assert(strcmp(numToChar(num1), numToChar(num2)) == 0 && "assign test01 failed");
//    /* // testing comparison */
//
//    /* testing additional functions */
//    int digit;
//    Number* num3 = setNumberFromChar((char*)"123.456");
//
//    digit = getWholeLen(num3);
//    assert(digit == 3 && "getWholeLen test01 failed");
//
//    digit = getDecimalLen(num3);
//    assert(digit == 3 && "getDecimalLen test01 failed");
//
//    digit = getIthDigit(num3, 2);
//    assert(digit == 2 && "getIthDigit test01 failed");
//
//    digit = getIthDigit(num3, -2);
//    assert(digit == 5 && "getIthDigit test02 failed");
//
//    increment(num3);
//    assert(strcmp(numToChar(num3), "124.456") == 0 && "increment test01 failed");
//
//    decrement(num3);
//    assert(strcmp(numToChar(num3), "123.456") == 0 && "increment test01 failed");
//
//    assign(num3, setNumberFromChar((char*)"5.5"));
//    plusEquals(num3, setNumberFromChar((char*)"12.2"));
//    assert(strcmp(numToChar(num3), "17.7") == 0 && "plusEquals test01 failed");
//
//    assign(num3, setNumberFromChar((char*)"5.5"));
//    minusEquals(num3, setNumberFromChar((char*)"6.8"));
//    assert(strcmp(numToChar(num3), "-1.3") == 0 && "minusEquals test01 failed");
//
//    assign(num3, setNumberFromChar((char*)"5.5"));
//    multiplyEquals(num3, setNumberFromChar((char*)"15.6"));
//    assert(strcmp(numToChar(num3), "85.8") == 0 && "multiplyEquals test01 failed");
//
//    assign(num3, setNumberFromChar((char*)"5.5"));
//    divideEquals(num3, setNumberFromChar((char*)"1.1"));
//    assert(strcmp(numToChar(num3), "5.0") == 0 && "divideEquals test01 failed");
//
//    assign(num3, setNumberFromChar((char*)"5.5"));
//    modulusEquals(num3, setNumberFromChar((char*)"1.4"));
//    assert(strcmp(numToChar(num3), "1.3") == 0 && "modulusEquals test01 failed");
//    /* // testing additional functions */
//
//    Number* num4 = setNumberFromChar((char*)"6.0");
//    res = factorial(num4);
//    assert(strcmp(numToChar(res), "720.0") == 0 && "factorial test01 failed");
//
//    Number* num5 = setNumberFromChar((char*)"7.0");
//    res = nextPrime(num5);
//    assert(strcmp(numToChar(res), "11.0") == 0 && "nextPrime test01 failed");
//
//    Number* num6 = setNumberFromChar((char*)"1.1");
//    res = raiseByPow(num6, 2);
//    assert(strcmp(numToChar(res), "1.21") == 0 && "raiseByPow test01 failed");

//    Number* num7 = setNumberFromChar((char*)"5.0");
//    Number* res = Log(num7);
//     FIXME minus in front
//    res->negative = 0;
//    debug("RES IS:");
//    printEntry(res);
//    debug("whole %d", res->digits_whole);
//    debug("decimal %d", res->digits_decimal);
//    setPrecision(res, 100);
//    debug("RES:");
//    printEntry(res);

//    Number* num8 = setNumberFromChar((char*)"20.0");
//    Number* res = Sine(num8);
//    debug("RES IS");
//    printEntry(res);


//        0.91294525072762765437609998384568230129793258370818995630512811476884891934907297604448004964046997


//    Number* num7 = setNumberFromChar((char*)"6969131687242798353909465020576131687242798.3539094650205761316872427983539094650205761316872427983539042946502057613168724279835390946502057613168724279835390946502057613168724279835390946502057613168724279835351440329218106995884773662551440329218106995884773662551440329218106995884773662551440329218106995884773662551440329218106995884773662551440329218106995884773662551440329218106995884773662551440329218107035390946502057613168724279835390946502057613168724279835390946502057613168724279835390946553909465020576");
//    setPrecision(num7, 500);
//    printEntry(num7);
//    setPrecision(num7, 498);
//    printEntry(num7);

//    assert(strcmp(numToChar(res), "1.60943791243410037460075933322618763945392441645116990934027579812967986587305250575502761944300107085461799391278484794984873220804899779999099887005780955438078534098959865804137074063137140476600234956355028790296312826870194396737240455170700703057409925850876415417694733417873054210448814069128743561525350583185004121187666612221313727767425372426517135324691680725874466799947698849089450584509415837894324333238039851168570917328815102714845955034097647778762637477067215324201332177079201406") == 0 && "Log test01 failed");

//    Number* num11 = setNumberFromChar((char*)"1.6094379");
//    setPrecision(num11, 7);
//    debug("RES");
//    printEntry(num11);


//    assert(strcmp(numToChar(res), "1.609437912434100374600759333226187639525601354268517721912647891474178987707657764630133878093179611") == 0 && "Log test01 failed");
//    assert(strcmp(numToChar(res), "1.609437912434100374600759333226187639453924416451169909340275798129679865873052505755027619443001070") == 0 && "Log test01 failed");


//     temp testing

//    Number* num21 = setNumberFromChar((char*)"0.296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296295");
//    Number* num21 = setNumberFromChar((char*)"0.296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296295703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703");
//    Number* num21 = setNumberFromChar((char*)"0.296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296296295703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703703704");
//      Number* num22 = setNumberFromChar((char*)"0.444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444");
//      Number* num22 = setNumberFromChar((char*)"0.444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444");
//    Number* num22 = setNumberFromChar((char*)"0.444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444");
//    setPrecision(num21, 100);
//    printEntry(num21);
//    setPrecision(num22, 100);
//    printEntry(num22);
//    Number* res = multiplyNumbers(num21, num22);
//    res->negative = 0;
//    debug("FINAL");
//    printEntry(res);


//    Number* num31 = setNumberFromChar((char*)"1.53086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419751160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827160493827166419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086419753086");
//    Number* num32 = setNumberFromChar((char*)"0.44444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444");
//
//    Number* res = multiplyNumbers(num31, num32);
//    printEntry(res);



}

