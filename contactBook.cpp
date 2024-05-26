#include <iostream>
#include <fstream>
#include <conio.h>
#include "ContactBook.h"

using namespace std;

void createContact();

int main()
{
  int choice,quit=0;

while(quit==0){
  system("cls");
  cout << endl << "##### ContactBook Project #####" << endl;
  // Options
  cout << "\n\tSelect one option below: "<<endl;
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
    cb::createContact();
    cout<<"** Contact created & Saved!**"<<endl;
    cout<<"Press any key to continue."<<endl;
    getch();
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
  quit=1;
    break;
  default:
    cout << "Invalid Choice, a choice must be 1,2,3,4 or 5." << endl;
    cout << "Press any key to continue." << endl;
    getch();
    break;
  }

}
  return 0;
}
