#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
  int choice;

  cout << endl << "##### ContactBook Project #####" << endl << endl;

  // Options
  cout << "\n\tSelect one option below ";
  cout << "\t1. To create new contact." << endl;
  cout << "\t2. To delete a contact by ID." << endl;
  cout << "\t3. To show a Specific contact by ID." << endl;
  cout << "\t4. To show all contacts." << endl;
  cout << "\t5. Quit." << endl << endl;

  cout << "Enter your choice: ";
  cin >> choice;

  switch (choice)
  {
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  default:
    cout << "Invalid Choice, a choice must be 1,2,3,4 or 5." << endl;
    break;
  }

  return 0;
}