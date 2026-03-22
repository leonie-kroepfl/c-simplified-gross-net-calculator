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

const int INPUT_BUFFER_LIMIT = 1024; 
const int FAMILY_BONUS = 100; 

const int SV_LIMIT_FOR_0 = 460;
const double SV_RATE_UNTIL_460 = 0.00;
const int SV_LIMIT_FOR_15 = 1733;
const double SV_RATE_UNTIL_1733 = 0.15;
const int SV_LIMIT_FOR_16 = 1891;
const double SV_RATE_UNTIL_1891 = 0.16;
const int SV_LIMIT_FOR_17 = 2049;
const double SV_RATE_UNTIL_2049 = 0.17;
const double SV_RATE_ABOVE_2049 = 0.18;

const double LST_LIMIT_FOR_20 = 1000.00; 
const double LST_RATE_UNTIL_1000 = 0.00; 
const double LST_LIMIT_FOR_30 = 1500.00; 
const double LST_RATE_UNTIL_1500 = 0.20; 
const double LST_LIMIT_FOR_40 = 2500.00; 
const double LST_RATE_UNTIL_2500 = 0.30; 
const double LST_LIMIT_FOR_50 = 5000.00; 
const double LST_RATE_UNTIL_5000 = 0.40; 
const double LST_RATE_ABOVE_5000 = 0.50; 



void printWelcomeMessage(void); 
int checkForValidInput(char input[]);
int getValidGrossSalary(void); 
double calculationOfSocialSecurityContribution(double gross_salary); 
double formulaOfCalculations(double calculation_basis, double calculation_rate);
double calculationOfIncomeTax(float gross_salary_after_deducting_sv); 
void printFamilyBonusQuestion(void); 
bool checkFamilyBonus(void); 
double calculationWithFamilyBonus(double lst_amount); 
void printSummary(double gross_salary, double sv_amount, double lst_amount);


int main(void)
{
  double gross_salary = getValidGrossSalary(); 
  double sv_amount = calculationOfSocialSecurityContribution(gross_salary); 
  double gross_salary_after_deducting_sv = gross_salary - sv_amount; 
  double lst_amount = calculationOfIncomeTax(gross_salary_after_deducting_sv); 

  if(checkFamilyBonus() == true)
  {
    lst_amount = calculationWithFamilyBonus(lst_amount); 
  }
  printSummary(gross_salary, sv_amount, lst_amount);
  //here 

  return 0; 
}

//-------------------------------------------functions-----------------------------------------------------------------
void printSummary(double gross_salary, double sv_amount, double lst_amount)
{
  printf("Gross:\t\t%12.2f\n", gross_salary);
  printf("SV:\t\t%14.2f\n", sv_amount);
  printf("LSt:\t\t%14.2f\n", lst_amount);
  printf("Net:\t\t%14.2f\n", (gross_salary - sv_amount - lst_amount));
}

double calculationWithFamilyBonus(double lst_amount)
{
  if(lst_amount >= FAMILY_BONUS)
  {
    lst_amount -= FAMILY_BONUS; 
  }
  else
  {
    lst_amount = 0.00; 
  }

  return lst_amount; 
} 

bool checkFamilyBonus(void)
{
  char input; 

  while(1)
  {  
    printFamilyBonusQuestion();
    int amount_of_converted_input = scanf("%c", &input); 
    printf("\n%d\n", amount_of_converted_input); 

    if(amount_of_converted_input != 1)
    {
      int lost_integer; 
      
      while((lost_integer = getchar()) != EOF && lost_integer != '\n')
      {
        continue; 
      }

      printf("%s", INVALID_INPUT_MESSAGE);
      continue;
    }

    switch (input)
    {
    case 'y':
      return true; 
      break;
    case 'Y':
      return true;
      break; 
    case 'n':
      return false; 
      break;
    case 'N':
      return false;
      break;
    default:
      printf("%s", INVALID_INPUT_MESSAGE); 
      break;
    }
  }
}

void printFamilyBonusQuestion(void)
{
  printf("Children is household?: \n > "); 
  fflush(stdout); 
}

double calculationOfIncomeTax(float gross_salary_after_deducting_sv)
{
  double lst_amount = 0.00; 
  double lst_basis = gross_salary_after_deducting_sv; 
  double lst_rate = 0.00; 

  if(lst_basis > LST_LIMIT_FOR_50)
  {
    lst_rate = LST_RATE_ABOVE_5000; 
    lst_amount += formulaOfCalculations((lst_basis - LST_LIMIT_FOR_50), lst_rate); 
    lst_basis = LST_LIMIT_FOR_50; 
  }

  if(lst_basis > LST_LIMIT_FOR_40)
  {
    lst_rate = LST_RATE_UNTIL_5000; 
    lst_amount += formulaOfCalculations((lst_basis - LST_LIMIT_FOR_40), lst_rate); 
    lst_basis = LST_LIMIT_FOR_40; 
  }

  if(lst_basis > LST_LIMIT_FOR_30)
  {
    lst_rate = LST_RATE_UNTIL_2500; 
    lst_amount += formulaOfCalculations((lst_basis - LST_LIMIT_FOR_30), lst_rate); 
    lst_basis = LST_LIMIT_FOR_30; 
  }

  if(lst_basis > LST_LIMIT_FOR_20)
  {
    lst_rate = LST_RATE_UNTIL_1500; 
    lst_amount += formulaOfCalculations((lst_basis - LST_LIMIT_FOR_20), lst_rate); 
    lst_basis = LST_LIMIT_FOR_20; 
  }

  return lst_amount; 
}

double calculationOfSocialSecurityContribution(double gross_salary) 
{
  double sv_amount = 0.00; 
  double sv_basis = gross_salary; 
  double sv_rate = 0.00; 
  sv_rate = (gross_salary <= SV_LIMIT_FOR_0) ? SV_RATE_UNTIL_460 : 
            (gross_salary <= SV_LIMIT_FOR_15) ? SV_RATE_UNTIL_1733 :
            (gross_salary <= SV_LIMIT_FOR_16) ? SV_RATE_UNTIL_1891 :
            (gross_salary <= SV_LIMIT_FOR_17) ? SV_RATE_UNTIL_2049 : 
            SV_RATE_ABOVE_2049; 

  sv_amount = formulaOfCalculations(sv_basis, sv_rate); 
  return sv_amount; 
}

double formulaOfCalculations(double calculation_basis, double calculation_rate)
{
  double calculation_amount = calculation_basis * calculation_rate; 
  return calculation_amount; 
}

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

