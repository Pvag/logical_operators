/*
  
  Content of the file
  -------------------
  Implemented via code the basic logical operators (AND, XOR, OR, NAND, EQUALS).

  Tests that consider all the different cases are included.


  Author: Paolo Vagnini ( paolondon at gmail dot com )

  Creation Date (MM/DD/YYYY): 12/31/2018 

  Revision Date:

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;
bool not(bool a);
bool xor(bool a, bool b);
bool or(bool a, bool b);
bool and(bool a, bool b);
bool nand(bool a, bool b);
void correct_true(const char test_name[]);
void correct_false(const char test_name[]);
void wrong_true(const char test_name[]);
void wrong_false(const char test_name[]);
bool check_match(bool result, bool expected, char test_name[]);
void test_operator(const bool expected[], char test_name[]);
void report(const bool isValid[], const char test_name[]);
bool equals(bool a, bool b);

// the values are considered in couple, for each iteration in test_operator
const bool values[] = {false, false, false, true, true, false, true, true};

int main(int argc, char *argv[])
{
  const bool expected_AND[4] = {false, false, false, true};
  test_operator(expected_AND, "AND");
  const bool expected_XOR[4] = {false, true, true, false};
  test_operator(expected_XOR, "XOR");
  const bool expected_OR[4] = {false, true, true, true};
  test_operator(expected_OR, "OR");
  const bool expected_NAND[4] = {true, true, true, false};
  test_operator(expected_NAND, "NAND");
  const bool expected_EQUAL[4] = {true, false, false, true};
  test_operator(expected_EQUAL, "EQUAL");

  return EXIT_SUCCESS;
}

// test the function againsts any of the expected couple of values
void test_operator(const bool expected[], char test_name[])
{
  bool isValid[4];
  for (int i = 0; i < 4; i++)
  {
    // TODO find a way to simplify this, avoiding hard-coding the function name
    if (!strcmp(test_name, "AND"))
      isValid[i] = check_match(and(values[2*i], values[2*i+1]), expected[i], test_name);
    else if (!strcmp(test_name, "XOR"))
      isValid[i] = check_match(xor(values[2*i], values[2*i+1]), expected[i], test_name);
    else if (!strcmp(test_name, "OR"))
      isValid[i] = check_match(or(values[2*i], values[2*i+1]), expected[i], test_name);
    else if (!strcmp(test_name, "NAND"))
      isValid[i] = check_match(nand(values[2*i], values[2*i+1]), expected[i], test_name);
    else if (!strcmp(test_name, "EQUAL"))
      isValid[i] = check_match(equals(values[2*i], values[2*i+1]), expected[i], test_name);
    else printf(" ERROR: Test '%s' does not exist !\n", test_name);
  }
  report(isValid, test_name);
}

// check for a match between value given by function and expected value
bool check_match(bool result, bool expected, char test_name[])
{
  bool isValid = true;
  if (result == expected)
  {
    if (expected) correct_true(test_name);
    else correct_false(test_name);
  }
  else
  {
    if (result) wrong_true(test_name);
    else wrong_false(test_name);
    isValid = false;
  }
  return isValid;
}

// print a report for the test
void report(const bool isValid[], const char test_name[])
{
  bool successful = true;
  for (int i = 0; i < 4; i++)
  {
    if (!isValid[i])
    {
      successful = false;
      break;
    }
  }
  if (successful) printf(" * PASSED - test for function: %s\n", test_name);
  else printf(" * NOT PASSED - test for function: %s\n", test_name);
}

void correct_true(const char test_name[])
{
  printf(" . %s test correctly evaluated to true\n", test_name);
}

void correct_false(const char test_name[])
{
  printf(" . %s test correctly evaluated to false\n", test_name);
}

void wrong_true(const char test_name[])
{
  printf(" ! %s test INcorrectly evaluated to true\n", test_name);
}

void wrong_false(const char test_name[])
{
  printf(" ! %s test INcorrectly evaluated to false\n", test_name);
}

// --
// implementation of logical functions - trying to use as less as operators as I can

bool not(bool a)
{
  return nand(a, a);
}

bool xor(bool a, bool b)
{
  return (not(a == b)) ? true : false;
}

bool equals(bool a, bool b)
{
  size_t nbit = sizeof(bool);
  for (int i = 0; i < nbit; i++)
  {
    if (a % 2 != b % 2) return false;
    else
    {
      a = a >> 1; // bit-shifting, here !
      b = b >> 1;
    }
  }
  return true;
}

bool or(bool a, bool b)
{
  if (a) return true;
  if (b) return true;
  else return false;
}

bool and(bool a, bool b)
{
  // if (a == b) return a ? true : false; // basic implementation
  return a ? (a == b) : false; // more ELEGANT implementation !
}

bool nand(bool a, bool b)
{
  return !and(a, b);
}
