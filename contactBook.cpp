#include <iostream>
#include <fstream>
#include <conio.h>
#include "ContactBook.h"

using namespace std;

int main()
{
  int choice = 10, quit = 0;
  cb::initRemContactIDs();
  cb::createFiles();
  while (quit == 0)
  {
    system("cls");
    cout << endl
         << "##### ContactBook Project #####" << endl;
    // Options
    cout << "\n\tSelect one option below: " << endl;
    cout << "\t1. To create new contact." << endl;
    cout << "\t2. To delete a contact by ID." << endl;
    cout << "\t3. To show a Specific contact by ID." << endl;
    cout << "\t4. To show all contacts." << endl;
    cout << "\t5. Quit." << endl
         << endl;

    cout << "Enter your choice: ";
    cin >> choice;
    cin.clear();
    fflush(stdin);

    cout << endl;
    switch (choice)
    {
    case 1:
      cb::createContact();
      cout << "\n** Contact created & Saved!**" << endl;
      cout << "\nPress any key to continue." << endl;
      getch();
      break;
    case 2:
      cb::deleteContactByID();
      cout << "\nPress any key to continue." << endl;
      getch();
      break;
    case 3:
      cb::showContactByID();
      cout << "\nPress any key to continue." << endl;
      getch();
      break;
    case 4:
      cb::showAllContacts();
      cout << "\nPress any key to continue." << endl;
      getch();
      break;
    case 5:
      quit = 1;
      break;
    default:
      cout << "Invalid Choice, a choice must be 1,2,3,4 or 5." << endl;
      cout << "Press any key to continue." << endl;
      // fflush(stdin);
      getch();
      break;
    }
  }

  cb::saveRemContactIDs();
  return 0;
}
