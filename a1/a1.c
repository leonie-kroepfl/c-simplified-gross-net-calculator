//------------------------------------------------------------------------------
// a1.c
//
// A small program "Gross-Net Calculator" 
//
// Group: 084
//
// Author: 012311363
//------------------------------------------------------------------------------
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define INVALID_INPUT_MESSAGE "Invalid input!\n" 

const int SV_LIMIT = 5370;
const int INPUT_BUFFER_LIMIT = 1024; 

void printWelcomeMessage(void); 
int checkForValidInput(char input[]);
int getValidGrossSalary(void); 

int main(void)
{
  int gross_salary = getValidGrossSalary(); 
  printf("Input after returning to main: %d\n", gross_salary); 

  //here 

  return 0;
}

//-------------------------------------------functions-----------------------------------------------------------------
void printWelcomeMessage(void)
{
  printf("Your monthly gross income: \n > "); 
  fflush(stdout); 
}

int checkForValidInput(char input[])
{
  // START CITATION
  // Source : Theoretical Session 1
  // Prompt : "Processing the String: Whitespace & Zeros"
  // Link : TC 

  int new_start_of_input = 0; 
  while(isspace(input[new_start_of_input]))
  {
    new_start_of_input++; 
  }

  char *endptr; 
  long valid_input = strtol(input, &endptr, 10); 
  // END CITATION

  if(valid_input <= 0 || valid_input > 5000000)
  {
    return false; 
  }
  return valid_input; 
}


int getValidGrossSalary(void) 
{
  int valid_input_index = false; 
  char input[INPUT_BUFFER_LIMIT]; 
  int valid_input = 0; 

  do
  {
    printWelcomeMessage(); 
    fgets(input, INPUT_BUFFER_LIMIT, stdin); 

    // START CITATION
    // Source : Theoretical Session 1
    // Prompt : "Edge Case: Input Too Long?"
    // Link : TC 

    if(strchr(input, '\n') == NULL)
    {
      int lost_input; 
      while((lost_input = getchar()) != '\n' && lost_input != EOF); 

      printf("%s", INVALID_INPUT_MESSAGE);
      continue; 
    }
    // END CITATION

    valid_input = checkForValidInput(input); 

    if(valid_input == false)
    {
      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }

    valid_input_index = true; 

  } while(valid_input_index != true); 

  return valid_input; 
}

