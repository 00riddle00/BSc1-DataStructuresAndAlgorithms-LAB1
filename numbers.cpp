/*=============================================================================
 | Big Numbers ADT implementation
 +===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Header file with useful debugging macros
#include "dbg.h"
#include "numbers.h"

// Define table as a global variable
Table* table;

void initTable() {
    table = (Table*) malloc(sizeof(Table));
    table->capacity = CHUNK_SIZE;
    table->size = 0;
    table->numbers = (Number**) malloc(CHUNK_SIZE * sizeof(Number*));
    
    for (int i = 0; i < table->capacity; i++) {
        table->numbers[i] = (Number*) calloc(1, sizeof(Number));
    }
}

void saveNumber(Number* number) {
    if (table->size == table->capacity) {
        table->capacity += CHUNK_SIZE;
        table->numbers = (Number**) realloc(table->numbers, table->capacity * sizeof(Number*));

        for (int i = table->size; i < table->capacity; i++) {
            table->numbers[i] = (Number*) calloc(1, sizeof(Number));
        }
    }
    table->numbers[table->size] = number;
    table->size++;
}

void printEntry2(TempNumber* number) {

        if (number->negative) {
            printf("-");
        }

        for (int i = number->digits_whole - 1; i >= 0; i--) {
            printf("%d", number->whole_part[i]);
        }
        printf(".");

        for (int i = 0; i < number->digits_decimal; i++) {
            printf("%d", number->decimal_part[i]);
        }
        printf("\n");
}

void printEntry(Number* number) {

        if (number->negative) {
            printf("-");
        }

        for (int i = number->digits_whole - 1; i >= 0; i--) {
            printf("%d", number->whole_part[i]);
        }
        printf(".");

        for (int i = 0; i < number->digits_decimal; i++) {
            printf("%d", number->decimal_part[i]);
        }
        printf("\n");
}

void printTable() {
    for (int i = 0; i < table->size; i++) {
        printf("[%d] ", i);
        printEntry(table->numbers[i]);
    }
}


char* numToChar(Number* number) {
        char* numArray = (char*) calloc(1, DIGITS * 2 * sizeof(char));
        int index = 0;

        if (number->negative) {
            numArray[0] = '-';
            index++;
        }

        for (int i = number->digits_whole - 1; i >= 0; i--, index++) {
            numArray[index] = number->whole_part[i] + '0';
        }
        numArray[index++] = '.';

        for (int i = 0; i < number->digits_decimal; i++, index++) {
            numArray[index] = number->decimal_part[i] + '0';
        }
        return numArray;
}


void getNumberChar(char* message, char* output)
{

    while (1) {
        printf("%s", message);
        if (scanf("%s", output) == 1 && getchar() == '\n') {
            break;
        } else {
            while (getchar() != '\n')
                ;
            printf("Error: not a string, or too many arguments\n");
        }
    }
}


Number* setNewNumber() {

    Number* num = (Number*) malloc(sizeof(Number));

    num->negative = 0;
    num->digits_whole = 1;
    num->digits_decimal = 1;
    num->whole_part[0] = 0;
    num->decimal_part[0] = 0;

    return num;
}
 



Number* setNumberFromChar(char* numArray) {

    Number* number = (Number*) malloc(sizeof(Number));

    char whole_part[DIGITS];
    char decimal_part[DIGITS];

    int count = 0;
    int error = 0;
    int decimal_pos = 0;

    int start = 0;
    int is_decimal_part = 0;

    number->negative = 0;

    if (numArray[0] == '-') {
        number->negative = 1;
        start++;
    } 

    for (int i = start; i < DIGITS * 2; i++) {

        if(!isdigit(numArray[i])) {
            if (numArray[i] == '.') {
                strncpy(whole_part, numArray+number->negative, count);
                number->digits_whole = count;
                decimal_pos = count;
                count = 0;
                is_decimal_part = 1;
            } else if (numArray[i] == 0) {
                if (is_decimal_part) {
                    strncpy(decimal_part, numArray+decimal_pos+number->negative+1, count);
                    number->digits_decimal = count;
                    break;
                } else {
                    strncpy(whole_part, numArray+number->negative, count);
                    number->digits_whole = count;
                    decimal_pos = count;
                    number->digits_decimal = 0;
                }

            } else {
                error = 1;
                break;
            }
        } else {
            count++;
        }
    }

    /// TODO handle this error
    if(error) {
        printf("Invalid number. Number 0.0 is returned/written\n");
        free(number);
        Number* zero = setNumberFromChar((char*)"0.0");
        return zero;
    }

    for (int i = number->digits_whole - 1; i >= 0; i--) {
        number->whole_part[i] = (int)whole_part[number->digits_whole-1-i] - '0';
    }

    for (int i = 0; i < number->digits_decimal; i++) {
        number->decimal_part[i] = (int)decimal_part[i] - '0';
    }

    fixNumber(number);
    return number;
}


Number* setNumberFromDouble(long double number, int whole_digits, int decimal_digits) {

    char charray[DIGITS];

    sprintf(charray, "%*.*Lf", whole_digits, decimal_digits, number);

    return setNumberFromChar(charray);
}



void assign(Number* num1, Number* num2) {

    num1->digits_whole = num2->digits_whole;
    num1->digits_decimal = num2->digits_decimal;
    num1->negative = num2->negative;

    for (int i = 0; i < num2->digits_decimal; i++) {
        num1->decimal_part[i] = num2->decimal_part[i];
    }
    for (int i = 0; i < num2->digits_whole; i++) {
        num1->whole_part[i] = num2->whole_part[i];
    }
}


void fixNumber(Number* num) {
    if (num->digits_whole == 0) {
        num->digits_whole = 1;
        num->whole_part[0] = 0;
    }
    if (num->digits_decimal == 0) {
        num->digits_decimal = 1;
        num->decimal_part[0] = 0;
    }

    int zeros = 0;

    for (int i = num->digits_whole - 1; i > 0; i--) {
        if (num->whole_part[i] == 0) {
            zeros++;
        } else {
            break;
        }
    }
    num->digits_whole -= zeros;

    zeros = 0;

    for (int i = num->digits_decimal - 1; i > 0; i--) {
        if (num->decimal_part[i] == 0) {
            zeros++;
        } else {
            break;
        }
    }
    num->digits_decimal -= zeros;
}






// this comparison function ignores the sign of the numbers,
// thus it compares the absolute values of the two numbers.
int compare(Number* num1, Number* num2) {
    /*[return values]       [meaning]      */
    /*       1            greater than (>) */
    /*       2            less than (<)    */
    /*       3            equal to (==)    */

    if (num1->digits_whole > num2->digits_whole) {
        return 1;
    } else if (num1->digits_whole < num2->digits_whole) {
        return 2;
    // case for equal number of digits
    } else {
        // compare whole parts
        for (int i = num1->digits_whole-1; i >= 0; i--) {
            if (num1->whole_part[i] > num2->whole_part[i]) {
                return 1;
            } else if (num1->whole_part[i] < num2->whole_part[i]) {
                return 2;
            }
        }

        // compare decimal parts
        for (int i = 0; i < DIGITS; i++) {
            if (num1->decimal_part[i] > num2->decimal_part[i]) {
                return 1;
            } else if (num1->decimal_part[i] < num2->decimal_part[i]) {
                return 2;
            }
        }

        return 3; // the numbers are equal
    }
}

int compareEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 3) {
        return 1;
    } else {
        return 0;
    }
}

int compareNotEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 3) {
        return 0;
    } else {
        return 1;
    }
}

int compareGreaterThan(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 1) {
        return 1;
    } else {
        return 0;
    }
}

int compareLessThan(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 2) {
        return 1;
    } else {
        return 0;
    }
}

int compareGreaterThanOrEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 2) {
        return 0;
    } else {
        return 1;
    }
}

int compareLessThanOrEqual(Number* num1, Number* num2) {
    int cmp = compareNumbers(num1, num2);

    if (cmp == 1) {
        return 0;
    } else {
        return 1;
    }
}




int compareNumbers(Number* num1, Number* num2) {

    int sign1 = num1->negative;
    int sign2 = num2->negative;
    int cmp;

    // both numbers positive
    if (!sign1 && !sign2) {
        cmp = compare(num1, num2);
    // both numbers negative
    } else if (sign1 && sign2) {
        cmp = compare(num2, num1);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        // greater than
        cmp = 1;
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        // less than
        cmp = 2;
    }
    // return values:
    // 1 - greater than
    // 2 - less than
    // 3 - equal
    return cmp;
}

Number *addNumbers(Number* num1, Number* num2) {
    Number* res;
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res = add(num1, num2, 0);
    // both numbers negative
    } else if (sign1 && sign2) {
        res = add(num1, num2, 1);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        res = subtract(num1, num2);
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        res = subtract(num1, num2);
    }

    return res;
}

Number* subtractNumbers(Number* num1, Number* num2) {
    Number* res;
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res =  subtract(num1, num2);
    // both numbers negative
    } else if (sign1 && sign2) {
        res =  subtract(num1, num2);
    // first number is positive, second - negative
    } else if (!sign1 && sign2) {
        res = add(num1, num2, 0);
    // first number is negative, second - positive
    } else if (sign1 && !sign2) {
        res = add(num1, num2, 1);
    }

    return res;
}

Number* multiplyNumbers(Number* num1, Number* num2) {
    Number* res = multiply(num1, num2);
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res->negative = 0;
    // both numbers negative
    } else if (sign1 && sign2) {
        res->negative = 0;
    // one number is positive, another - negative
    } else {
        res->negative = 1;
    }

    return res;
}

Number* divideNumbers(Number* num1, Number* num2) {

    Number* res = divide(num1, num2);
    int sign1 = num1->negative;
    int sign2 = num2->negative;

    // both numbers positive
    if (!sign1 && !sign2) {
        res->negative = 0;
    // both numbers negative
    } else if (sign1 && sign2) {
        res->negative = 0;
    // one number is positive, another - negative
    } else {
        res->negative = 1;
    }

    return res;
}

Number* add(Number* num1, Number* num2, int negative) {

    Number* bigger = setNewNumber();
    Number* smaller = setNewNumber();
    assign(bigger, num1);
    assign(smaller, num2);

    //Number* bigger = num1;
    //Number* smaller = num2;

    if (bigger->digits_decimal < smaller->digits_decimal) {
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
        //assign(bigger, num2);
        //assign(smaller, num1);
    }

    // create result Number and populate it with decimal digits 
    // of the bigger number
    Number* res = (Number*) calloc(1, sizeof(Number));
    for (int i = 0; i < bigger->digits_decimal; i++) {
        res->decimal_part[i] = bigger->decimal_part[i];
    }
    res->digits_decimal = bigger->digits_decimal;

    // part - the part to be transfered to the next sum. 
    //  Ex. 9+5 = 14, 1 then becomes the "part" to be transfered next.
    int carry;

    // add decimal parts
    for (int i = smaller->digits_decimal - 1; i > 0; i--) {
        int result = res->decimal_part[i] + smaller->decimal_part[i];
        carry = 0;
        if (result > 10) {
            carry = 1;
            result %= 10;
        } else if (result == 10) {
            result = 0;
            carry = 1;
        }
        res->decimal_part[i] = result;
        res->decimal_part[i-1] += carry;
    }
    res->decimal_part[0] += smaller->decimal_part[0];

    carry = 0;

    // carry then moves on to be added to the whole part of the number
    if (res->decimal_part[0] >= 10) {
        carry = 1;
        res->decimal_part[0] %= 10;
    } 

    // select number with bigger amount of whole part digits
    if (bigger->digits_whole < smaller->digits_whole) {
        Number temp = *bigger;
        *bigger = *smaller;
        *smaller = temp;
    }

    // copy whole_part to the result struct
    res->digits_whole = bigger->digits_whole + 1;

    for (int i = 0; i < bigger->digits_whole; i++) {
        res->whole_part[i] = bigger->whole_part[i];
    }

    // add whole parts
    for (int i = 0; i < smaller->digits_whole; i++) {
        int result = res->whole_part[i] + smaller->whole_part[i];
        if (i == 0) {
            result += carry;
        }
        carry = 0;
        if (result >= 10) {
            carry = 1;
            result %= 10;
        }
        res->whole_part[i] = result;
        res->whole_part[i+1] += carry;

    }

        // TODO maybe use this implementation, 
        // but move it inside addition for loop
/*        if (i + 1 == smaller->digits_whole) {*/
            //while(1) {
                //if (res->whole_part[i+1] >= 10) {
                    //carry = 1;
                    //res->whole_part[i+1] %= 10;
                    //res->whole_part[i+2] += carry;
                    //if (i+2 == res->digits_whole) {
                        //res->digits_whole++;
                        //breakas = 1;
                        //break;
                    //}
                    //i++;
                    //continue;
                //} else {
                    //break;
                //}
            //}
            //if (breakas) {
                //break;
            //}
        //}
    //fixNumber(res);

    // After adding the whole parts, at the end 
    // such situation might occur that one of the
    // numbers of the sum is equal to 10. Since all
    // the numbers should be 1-digit, this piece
    // of code fixes this error
    for (int i = 0; i < res->digits_whole; i++) {
        if (res->whole_part[i] >= 10) {
            res->whole_part[i] %= 10;
            res->whole_part[i+1] += 1;
            if (i + 1 == res->digits_whole) {
                res->digits_whole++;
            }
        }
    }


    // remove zeroes in the front of the resulting number
    for (int i = res->digits_whole-1; i >= 0; i--) {
        if (res->whole_part[i] == 0) {
            res->digits_whole--;
        } else {
            break;
        }
    }

    // set sign
    res->negative = negative;

    fixNumber(res);
    return res;
}





Number* subtract(Number* num1, Number* num2) {

    int negative;
    // compare the two numbers
    int rs = compare(num1, num2);

    Number* first;
    Number* second;

    Number* res = setNewNumber();

    // if first is greater or equal, 
    // subtract second number from the first
    if (rs == 1) {
        negative = 0;

        first = num1;
        second = num2;

    // if first is less than second, 
    // subtract first number from the second
    } else if (rs == 2) {
        negative = 1;

        first = num2;
        second = num1;

    // else if numbers are equal, return zero 
    // (zeroth Number struct)
    } else if (rs == 3) {
        return res;
    }

    // set decimal digits of the result to that of number having
    // more decimal digits
    res->digits_decimal = (first->digits_decimal >= second->digits_decimal) ? first->digits_decimal : second->digits_decimal;

    // copy decimal digits to the result
    for (int i = 0; i < res->digits_decimal; i++) {
        res->decimal_part[i] = first->decimal_part[i];
    }

    // set whole digits of the result to that the bigger number's 
    res->digits_whole = first->digits_whole;
    for (int i = 0; i < res->digits_whole; i++) {
        res->whole_part[i] = first->whole_part[i];
    }

    // set the sign of the result
    res->negative = negative;

    
    /* actual subraction starts   */
    
    // subtract decimal digits
    for (int i = res->digits_decimal - 1; i >= 0; i--) {
        int result = res->decimal_part[i] - second->decimal_part[i];
        if (result < 0) {

            if (i == 0) {
                // borrow the ten (10) from the whole part
                // in case the whole part's number becomes -1,
                // this is then handled when substracting whole digits
                res->decimal_part[i] = result + 10;
                res->whole_part[0]--;
                break;
            }

            // go through the remaining numbers to borrow the needed 
            // ten exponent (10) for subtraction
            for (int j = i-1; j >= 0; j--) {
                res->decimal_part[j] = (res->decimal_part[j] == 0) ? 9 : res->decimal_part[j] - 1; 
                if (res->decimal_part[j] == 9) {
                    if (j == 0) {
                        // borrow the ten (10) from the whole part
                        // in case the whole part's number becomes -1,
                        // this is then handled when substracting whole digits
                        res->whole_part[0]--;
                    }
                    continue;
                } else {
                    break;
                }
            }
            res->decimal_part[i] = result + 10;
        } else {
            res->decimal_part[i] = result;
        }
    }

    // subtract whole digits
    for (int i = 0; i < second->digits_whole; i++) {
        int result = res->whole_part[i] - second->whole_part[i];

        if (result < 0) {

            for (int j = i+1; j < res->digits_whole; j++) {
                res->whole_part[j] = (res->whole_part[j] == 0) ? 9 : res->whole_part[j] - 1;
                if (res->whole_part[j] == 9) {
                    continue;
                } else {
                    break;
                }
            }
            res->whole_part[i] = (result + 10) % 10;
        } else {
            res->whole_part[i] = result;
        }
    }

    fixNumber(res);
    return res;
}




Number* multiply(Number* num1, Number* num2) {



    // TODO use setNewNumber here
    // FIXME maybe this makes it crash
    Number* res = (Number*) calloc(1, sizeof(Number));
    // firstly, set the result as a whole part of the resulting number
    // set digits of the result to a maximum possible number after  multiplication
    res->digits_whole = num1->digits_whole + num1->digits_decimal + num2->digits_whole + num2->digits_decimal;

    // two dimensional array used for storing partial products
    // first dimension size - how many numerals does the factor have (the second number)
    // second dimension size - the maximum possible number of digits after multiplication
    // TODO add a[...+1] ??
    int a[num2->digits_whole+num2->digits_decimal][res->digits_whole];
    // initialize two dimensional array with zeroes.
    memset(a, 0, sizeof(a[0][0]) * (num2->digits_whole+num2->digits_decimal) * res->digits_whole);

    // TODO simple assign might be enough
    // populate first factor with both decimal and whole parts of the first
    // number (convert decimal part to whole part) - ie move decimal dot(.) to 
    // the end of the number, or multiply it by 10^n, where n is the number of 
    // decimal digits (digits after the dot).
    Number* n1 = (Number*) calloc(1, sizeof(Number));

    for (int i = num1->digits_decimal - 1, j = 0; i >= 0; i--, j++) {
        n1->whole_part[j] = num1->decimal_part[i];
        n1->digits_whole++;
    }

    for (int i = 0; i < num1->digits_whole; i++) {
        n1->whole_part[i+num1->digits_decimal] = num1->whole_part[i];
        n1->digits_whole++;
    }
    // TODO add this line
//    n1->digits_whole--;

    // populate second factor with both decimal and whole parts of the second
    // number (convert decimal part to whole part) - ie move decimal dot(.) to 
    // the end of the number, or multiply it by 10^n, where n is the number of 
    // decimal digits (digits after the dot).
    Number* n2 = (Number*) calloc(1, sizeof(Number));

    for (int i = num2->digits_decimal - 1, j = 0; i >= 0; i--, j++) {
        n2->whole_part[j] = num2->decimal_part[i];
        n2->digits_whole++;
    }
    for (int i = 0; i < num2->digits_whole; i++) {
        n2->whole_part[i+num2->digits_decimal] = num2->whole_part[i];
        n2->digits_whole++;
    }
    // TODO add this line
//    n2->digits_whole--;




    // FIXME trouble point
    // Set how many decimal numbers the result will contain at most
    int decimal_numbers = num1->digits_decimal + num2->digits_decimal;

    int carry = 0;
    int rc;

    // pos (position) sets how many zeroes there will be before the actual
    // partial product (since each partial product is multiplied by ten
    // in a sense from the point of view of the previous partial product,
    // ie
    //    211
    //    *
    //     52
    //  _____
    //    422
    //  1055  <- differs by the power of ten.
    //
    //  The resulting partial products are then stored in two dimentional
    //  array, with zeros both in front and the back of the number:
    //  
    //  00422
    //  10550
    int pos = 0;

    // long multiplication of numbers, storing each partial product
    // in a two dimensional array
    for (int i = 0; i < n2->digits_whole; i++) {
        pos = i;
        for (int j = 0; j < n1->digits_whole; j++) {
            rc = n2->whole_part[i] * n1->whole_part[j];
            a[i][j+pos] = (rc + carry) % 10;
            carry = (rc+carry) / 10;
        }
        // FIXME if carry == 0 error
        a[i][n1->digits_whole+pos] = carry;
        carry = 0;
    }

    int result = 0;
    carry = 0;


//    debug("HERE");
//    for (int j = 0; j < 500; j++) {
//        printf("%d", a[203][j]);
//    }
//    printf("\n\n500: %d", a[203][500]);
//    printf("\n\n");



    TempNumber* res2 = (TempNumber*) calloc(1, sizeof(TempNumber));
    res2->digits_whole = 0;

    // add all partial products together
    for (int j = 0; j < res->digits_whole; j++) {
        for (int i = 0; i < n2->digits_whole; i++) {
            result += a[i][j];
        }

        result += carry;
        carry = result / 10;
        res2->whole_part[j] = result % 10;
        res2->digits_whole++;
        result = 0;
    }

/* NEW CODE */

    int whole_numbers = res2->digits_whole - decimal_numbers;

    if (decimal_numbers > 500) {
        res->digits_decimal = 500;
        for (int i = res2->digits_whole - 500 - (res2->digits_whole - decimal_numbers), j = 499; i < res2->digits_whole; i++, j--) {
            res->decimal_part[j] = res2->whole_part[i];
        }

        res->digits_whole = whole_numbers;
        for (int i = res2->digits_whole - 1, j = whole_numbers - 1; i > res2->digits_whole - decimal_numbers - 1; i--, j--) {
            res->whole_part[j] = res2->whole_part[i];
        }
    } else {
        res->digits_whole = whole_numbers;

        for (int i = res2->digits_whole-1, j = whole_numbers - 1; i > res2->digits_whole - whole_numbers - 1; i--, j--) {
            res->whole_part[j] = res2->whole_part[i];
        }

        res->digits_decimal = decimal_numbers;
        for (int i = res2->digits_whole-whole_numbers-1, j = 0; i >= 0; i--, j++) {
            res->decimal_part[j] = res2->whole_part[i];
        }

    }







//    if (res2->digits_whole > 500) {
//        res->digits_whole = 500;
//        for (int i = res2->digits_whole - 500, j = 0; i < res2->digits_whole; i++, j++) {
//            res->whole_part[j] = res2->whole_part[i];
//        }
//    }
//    int roundedDigit = res2->whole_part[res2->digits_whole - 500 - 1];
//    if (roundedDigit >= 5) {
//        plusEquals(res, setNumberFromChar((char*)ONE));
//    }

/* // NEW CODE */



    
    // TODO readd this?
/*    // remove zeroes in the front of the resulting number*/
    //for (int i = res->digits_whole-1; i >= 0; i--) {
        //if (res->whole_part[i] == 0) {
            //res->digits_whole--;
        //} else {
            //break;
        //}
    //}

    // move decimal dot to the required place
    // ie convert whole number to a decimal number again

//
//    res->digits_decimal = decimal_numbers;
//    debug("DEC NR: %d", decimal_numbers);
//    for (int i = 0; i < decimal_numbers; i++) {
//        res->decimal_part[i] = res->whole_part[decimal_numbers - 1 - i];
//    }
//    debug("D4");
//    printEntry(res);
//
//
//    for (int i = 0; i < res->digits_whole; i++) {
//        res->whole_part[i] = res->whole_part[decimal_numbers+i];
//    }
//    res->digits_whole -= decimal_numbers;




//    free(n1);
    // FIXME corrupted size
//    free(n2);
    fixNumber(res);
    return res;

}


// additional functions
int getWholeLen(Number* num) {
    if (num->digits_whole == 1 && num->whole_part[0] == 0) {
        return 0;
    } else {
        return num->digits_whole;
    }
}

int getDecimalLen(Number* num) {
    if (num->digits_decimal == 1 && num->decimal_part[0] == 0) {
        return 0;
    } else {
        return num->digits_decimal;
    }
}

// decimal digits are marked by negative indexes
// ex. Number is 12.34
// ex.getIthDigit(0) returns 0 (nothing)
// ex getIthDigit(1) returns 1
// ex getIthDigit(2) returns 2
// ex getIthDigit(-1) returns 3
// ex getIthDigit(-2) returns 4
int getIthDigit(Number* num, int index) {
    if (!index) {
        printf("WARNING: Zeroth index does not exist");
    } else if (index > 0) {
        return num->whole_part[index-1];
    // else if index < 0
    } else {
        return num->decimal_part[-index-1];
    }
}

// TODO optimize
void increment(Number* num) {
    assign(num, addNumbers(num, setNumberFromChar((char*) ONE)));
}

// TODO optimize
void decrement(Number* num) {
    assign(num, subtractNumbers(num, setNumberFromChar((char*) ONE)));
}

void plusEquals(Number* num1, Number* num2) {
    assign(num1, addNumbers(num1, num2));
}

void minusEquals(Number* num1, Number* num2) {
    assign(num1, subtractNumbers(num1, num2));
}

void multiplyEquals(Number* num1, Number* num2) {
    assign(num1, multiplyNumbers(num1, num2));
}

void divideEquals(Number* num1, Number* num2) {
    assign(num1, divideNumbers(num1, num2));
}

void modulusEquals(Number* num1, Number* num2) {
    assign(num1, modulus(num1, num2));
}


// utility functions
int pow(int number, int power) {
    int orig_number = number;
    for (int i = 0; i < power-1; i++) {
        number *= orig_number;
    }
    return number;
}


// converting Number ADT to int
int toInt(Number* num) {
    int int_repr = 0;
    for (int i = num->digits_whole; i > 1; i--) {
        int_repr += num->whole_part[i - 1] * pow(10, (i - 1));
    }
    int_repr += num->whole_part[0];
    return int_repr;
}


Number* getAbsoluteValue(Number* num) {
    // if num > 0
    if (!num->negative) {
        return num;
    // else if num <= 0
    } else {
        Number *ret_num = (Number*) calloc(1, sizeof(Number));
        assign(ret_num, num);
        ret_num->negative = 0;
        return ret_num;
    }
}

Number* getFloorNumber(Number* num) {
    if (num->digits_decimal == 1 && num->decimal_part[0] == 0) {
        return num;
    } else {
        // TODO solve memory leak
        Number* ret_num = (Number*) calloc(1, sizeof(Number));
        assign(ret_num, num);
        ret_num->digits_decimal = 1;
        ret_num->decimal_part[0] = 0;
        return ret_num;
    }
}


int isZero(Number* num) {
    return (!getWholeLen(num) && !getDecimalLen(num));
}

int isInteger(Number* num) {
    return (num->digits_decimal == 1 && num->decimal_part[0] == 0);
}

Number* multiplyByInt(Number* num1, int integer) {

    // init to zero
    //Number* num2 = setNewNumber();
    Number* num2 = (Number*) calloc(1, sizeof(Number));

    while(integer != 0) {
        num2->digits_whole++;
        num2->whole_part[num2->digits_whole-1] = integer % 10;
        integer /= 10;
    }

    return multiply(num1, num2);
}
// // utility functions




// FIXME division works until +-35 digits are put in the result.
// FIXME After that, the program freezes.
// FIXME hence the temporary guard if condition is added to stop 
// FIXME division after the resulting number reaches 35 digits.
Number* divide(Number* num1, Number* num2) {
    int quotient;

    int rs = compare(num1, num2);

    // if first is greater, the quotient will 
    // be greater than 1
    if (rs == 1) {
        quotient = 1;
    // if first is smaller than second, 
    // the quotient will be less than 1
    } else if (rs == 2) {
        quotient = 0;
    // else if numbers are equal, return one 
    } else if (rs == 3) {
        // initalize Number with the value of one
        Number* one = setNumberFromChar((char*) ONE);
        return one;
    }

    Number* res = setNewNumber();

    // initalize Number with the value of one
    Number* one = setNumberFromChar((char*) ONE);

    // initalize Number with the value of ten
    Number* ten = setNumberFromChar((char*) TEN);

    // initalize Number with the value of 0.1
    Number* zero_one = setNumberFromChar((char*) ZERO_ONE);

    Number* tmp = (Number*) calloc(1, sizeof(Number));
    assign(tmp, num1);
    //tmp = num1;

    // set the remainder as the dividend at first
    Number* remainder = num1;

    if (!quotient) {
        one = multiply(one, zero_one);
        tmp = multiply(tmp, ten);
        remainder = multiply(remainder, ten);
    }

    // sets how many times the divisor is subtracted from remainder
    // ie sets the whole number = remainder / divisor
    int counter = 0;

    // run the long division loop
    while (1) {
        tmp = subtract(tmp, num2);
        // if remainder is not yet divided into equal parts or does
        // not yet become negative, continue the division
        if ((tmp->digits_whole > 1 || tmp->whole_part[0] != 0) && !(tmp->negative)) {
            res = add(res, one, 0);
            counter++;
            continue;
        // stop if the remainder becomes equal to zero (ie becomes divided
        // into equal parts
        } else if (isZero(tmp)) {
            res = add(res, one, 0);
            counter++;
            free(one);
            free(ten);
            free(zero_one);
            return res;
        } else {
            // if the divisor (second number) is greater than the remainder,
            // multiply the remainder by ten and continue the division loop.
            if (counter == 0) {
                // tmp becomes remainder again
                assign(tmp, remainder);

                // the remainder is multiplied by ten
                tmp = multiply(tmp, ten);
                remainder = multiply(remainder, ten);

                // enter a zero to the result, which means that the remainder
                // was smaller than the divisor
                
                // TODO ar nereiktu pirma digits_decimal++ padaryti?
                if (res->digits_decimal > 1) {
                    res->decimal_part[(res->digits_decimal)++] = 0;
                }
                one = multiply(one, zero_one);

                continue;
            }
            // FIXME temporary guard, else the program stops running 
            // FIXME (gets stuck)
            if (res->digits_decimal >= 200) {
                free(one);
                free(ten);
                free(zero_one);
                fixNumber(res);
                return res;
            }
            // get the new remainder (remainder -= divisor * (remainder / divisor))
            //
            //
            remainder = subtract(remainder, multiplyByInt(num2, counter));

            //one->decimal_part[one->digits_decimal-1] = 0;
            //one->decimal_part[(one->digits_decimal)++] = 1;
            one = multiply(one, zero_one);
            counter = 0;

            // tmp becomes remainder again
            assign(tmp, remainder);

            remainder = multiply(remainder, ten);
            tmp = multiply(tmp, ten);

        }
    }

    free(one);
    free(ten);
    free(zero_one);
    fixNumber(res);
    return res;
}


Number* modulus(Number* num1, Number* num2) {

    if (isZero(num1)) {
        Number* zero = setNewNumber();
        return zero;
    } else if (isZero(num2)) {
        printf("ERROR: Division from zero in modulus expression!\n");
        exit(1);
    }


    // compare absolute values. return whether num1 > num2
    int cmp_abs = compareNumbers(getAbsoluteValue(num1), getAbsoluteValue(num2));

    // if the absolute values of numbers are equal, return zero
    if (cmp_abs == 3) {
        Number *zero = setNewNumber();
        return zero;
    }

    // shows if num1 > num2 (value=1) or vice a versa (value=0)
    int cmp_gt;


    /* Finding which number is bigger, based on which absolute value
     * is bigger and either the number is positive or negative
     * (this saves computation time by avoiding another full comparison
     * between numbers) */

    // if |num1| > |num2|
    if (cmp_abs == 1) {
        // if num1 > 0
        if (!num1->negative) {
            // num1 > num2
            cmp_gt = 1;
        // else if num1 < 0
        } else {
            // num1 < num2
            cmp_gt = 0;
        }
    // else if |num1| < |num2|
    } else if (cmp_abs == 2) {
        // if num2 > 0
        if (!num2->negative) {
            // num1 < num2
            cmp_gt = 0;
        // else if num2 < 0
        } else {
            // num1 > num2
            cmp_gt = 1;

        }
    }

    // if num1 < num2
    if (cmp_gt == 0) {
        // if num2 < 0
        if (num2->negative) {
            Number* ret_num = modulus(getAbsoluteValue(num1), getAbsoluteValue(num2));
            ret_num->negative = 1;
            return ret_num;
        // else if num2 > 0
        } else {
            // if num1 > 0
            if (!num1->negative) {
                return num1;
            }
            // else if |num1| < |num2|
            else if (cmp_abs == 2) {
               return subtractNumbers(num2, getAbsoluteValue(num1)) ;
            }
            // else if |num1| > |num2|
            else if(cmp_abs == 1) {
                // if |num1|/num2 is integer
                if (isInteger(divideNumbers(getAbsoluteValue(num1), num2))) {
                    Number* zero = setNewNumber();
                    return zero;
                // else, if the quotient is not an integer
                } else {
                    Number* one = setNumberFromChar((char*) ONE);
                    // return |(floor(|num1|/num2)+1)*num2| - |num1|
                    return subtractNumbers(getAbsoluteValue(multiplyNumbers(addNumbers(getFloorNumber(divideNumbers(getAbsoluteValue(num1), num2)), one), num2)), getAbsoluteValue(num1));
                }
            }
        }
    // else if num1 > num2
    } else if (cmp_gt == 1) {
        // if num2 < 0
        if (num2->negative) {
            // if num1 > 0
            if (!num1->negative) {
                // if |num1| < |num2|
                if (cmp_abs == 0) {
                    return addNumbers(num1, num2);
                // else if |num1| > |num2|
                } else {
                    Number *one = setNumberFromChar((char *) ONE);
                    Number *ret_num = addNumbers(multiplyNumbers(getFloorNumber(addNumbers(getAbsoluteValue(divideNumbers(num1, num2)), one)), num2), num1);
                    ret_num->negative = 1;
                    return ret_num;
                }
            }
            // else if num1 < 0
            else {
                // ret_num = -(modulus(|num1|,|num2|)
                // FIXME inf recursion
                Number* ret_num = modulus(getAbsoluteValue(num1), getAbsoluteValue(num2));
                ret_num->negative = 1;
                return ret_num;
            }
        // else if num2 > 0
        } else {
            //return num1 - floor(num1/num2)*num2
            return subtractNumbers(num1, multiply(getFloorNumber(divideNumbers(num1, num2)), num2));
        }
    }

}

/* functions to be tested */
Number* factorial(Number* num) {
    int numToInt = toInt(num);

    Number* one = setNumberFromChar((char*) ONE);
    Number* ret_num = setNewNumber();
    Number* diff = setNewNumber();
    assign(diff, one);
    assign(ret_num, num);

    for (int i = 1; i < numToInt-1; i++) {
        diff = multiplyByInt(one, i);
        multiplyEquals(ret_num, subtractNumbers(num, diff));
    }
    return ret_num;
}

int isPrime(Number* num) {
    printEntry(num);
    if (compareEqual(num, setNumberFromChar((char*)"2.0"))) {
        return 1;
    }
    if (isZero(modulus(num, setNumberFromChar((char *) "2.0")))) {
        return 0;
    }
    for (Number*i = setNumberFromChar((char *) "3.0"); compareLessThanOrEqual(multiplyNumbers(i, i), num); plusEquals(i, setNumberFromChar((char *) "2.0"))) {
        if (isZero(modulus(num, i))) {
            return 0;
        }
    }
    return 1;
}

Number* nextPrime(Number* num) {
    if (num->negative || isZero(num)) {
        return setNumberFromChar((char *) "2.0");
    } else {
        num = getFloorNumber(num);
        printEntry(num);
        Number *diff = setNumberFromChar((char *) ONE);

        while (!isPrime(addNumbers(num, diff))) {
            plusEquals(diff, setNumberFromChar((char *) ONE));
            printEntry(diff);
        }

        return addNumbers(num, diff);
    }
}


Number* raiseByPow(Number* num, int power) {
    Number* ret_val = setNewNumber();
    assign(ret_val, num);

    Number* orig_num = setNewNumber();
    assign(orig_num, num);

    for (int i = 0; i < power-1; i++) {
        multiplyEquals(ret_val, orig_num);
    }
    return ret_val;
}

Number* Log(Number* num) {
    // TODO add validation for negative input
    Number *step = setNewNumber();
    Number *one = setNumberFromChar((char *) ONE);

    Number *powe = setNumberFromChar((char *) ONE);

    Number *y = setNewNumber();
    Number *z = divideNumbers(addNumbers(num, one), subtractNumbers(num, one));
    Number *ret_num = setNewNumber();

    step = divideNumbers(raiseByPow(subtractNumbers(num, one), 2), raiseByPow(addNumbers(num, one), 2));

    int count = 0;
    while (count < 300) {
        debug("%d", count);
        multiplyEquals(z, step);
        assign(y, multiplyNumbers(divideNumbers(one, powe), z));
        plusEquals(ret_num, y);
        plusEquals(powe, setNumberFromChar((char *) "2.0"));

        count++;
    }
    multiplyEquals(ret_num, setNumberFromChar((char*)"2.0"));
    return ret_num;
}

// this operation is irreversible!
void setPrecision(Number* num, int precision) {
    Number *ten = setNumberFromChar((char *) "10.0");
    // TODO case when higher precision is added (?)
    // TODO check precision for negative values and zero
    // TODO wrap num->digits_whole in a variable
    // TODO fixNumber might be needed
    if (num->digits_whole >= precision) {
        if (num->digits_whole > precision) {
            int last_index = num->digits_whole - precision;
            int rounded_index = last_index - 1;
            if (num->whole_part[rounded_index] < 5) {
                for (int i = rounded_index; i >= 0; i--) {
                    num->whole_part[i] = 0;
                }
                // else if num->whole_part[rounded_index >= 5)
            } else {
                Number *roundingTens = raiseByPow(ten, rounded_index + 1);
                Number *numberToBeSubtracted = setNewNumber();
                assign(numberToBeSubtracted, num);
                numberToBeSubtracted->digits_whole = rounded_index + 1;
                Number *numberToAddWhenRounding = subtractNumbers(roundingTens, numberToBeSubtracted);
                plusEquals(num, numberToAddWhenRounding);
            }
        }
        // FIXME memory leak
        num->digits_decimal = 1;
        num->decimal_part[0] = 0;
    } else if (num->digits_whole < precision) {
        Number* ShiftedComma = multiplyNumbers(num, raiseByPow(ten, num->digits_decimal));
        setPrecision(ShiftedComma, precision);
        divideEquals(ShiftedComma, raiseByPow(ten, num->digits_decimal));
        // TODO do without ShiftedComma variable
        assign(num, ShiftedComma);
    }
}



void freeTable() {
    for (int i = 0; i < table->capacity; i++) {
        free(table->numbers[i]);
    }
    free(table->numbers);
    free(table);
}

