#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
namespace cb
{
  class Contact
  {
  private:
    int id;
    string firstName;
    string lastName;
    string contactNo;
    string email;

  public:
    static string fileName;
    static string idFN;
    Contact(string, string, string, string);
    void writeCSV(Contact &);
    void setID();
  };

  string Contact::fileName = "contacts.csv";
  string Contact::idFN = "id_info.csv";

  // Not member function of class
  void createContact();
  bool isFileEmpty(fstream &);
  bool isFileEmpty(ofstream &);
  void showAllContacts();
  void showContactByID();

}

// #########################################################################

cb::Contact::Contact(string fn, string ln, string pn, string em)
{
  id = 1;
  firstName = fn;
  lastName = ln;
  contactNo = pn;
  email = em;
}

void cb::Contact::writeCSV(Contact &c)
{
  string margedString = to_string(c.id) + "," + c.firstName + "," + c.lastName + "," + c.contactNo + "," + c.email + "\n";

  fstream file;

  file.open(fileName, ios_base::app | ios_base::in);
  if (file.is_open())
  {
    if (cb::isFileEmpty(file))
    {
      string headerStr = "ID,FirstName,LastName,PhoneNo.,EmailID\n";
      file << headerStr;
    }

    file << margedString;
    file.close();
  }
  else
  {
    cout << "Something went wrong! Cannot open the file." << endl;
  }
}

void cb::Contact::setID()
{
  string readStr;
  fstream file;

  file.open(idFN, ios_base::in | ios_base::out);
  if (file.is_open())
  {
    if (cb::isFileEmpty(file))
    {
      file << id;
    }
    else
    {
      getline(file, readStr);
      file.seekg(0, ios_base::beg);
      id = stoi(readStr) + 1;
      file << id;
    }

    file.close();
  }
  else
  {
    cout << "Something went wrong! Cannot open the file." << endl;
  }
}

void cb::createContact()
{
  int id;
  string fn;
  string ln;
  string em;
  string pn;

  cout << "Enter first name: ";
  cin >> fn;

  cout << "Enter last name: ";
  cin >> ln;

  cout << "Enter contact no: ";
  cin >> pn;

  cout << "Enter contact email id: ";
  cin >> em;

  cb::Contact c = cb::Contact(fn, ln, pn, em);
  c.setID();
  c.writeCSV(c);
}

bool cb::isFileEmpty(fstream &file)
{
  bool isEmpty;
  file.seekg(0, ios_base::end);
  isEmpty = file.tellg() == 0 ? true : false;

  // reset read position
  file.seekg(0, ios_base::beg);
  return isEmpty;
}

void cb::showAllContacts()
{

  string fname = "contacts.csv";
  string readStr;
  int i = 1;

  fstream fin;
  fin.open(fname);

  if (!(cb::isFileEmpty(fin)))
  {
    while (!(fin.eof()))
    {
      if (i == 1)
      {
        i++;
        getline(fin, readStr);
        continue;
      }

      getline(fin, readStr, ',');
      if (readStr.empty())
        continue;
      cout << "##########################################\n";
      cout << "|" << setw(15) << "ID: " << setw(25) << readStr << "|" << endl;

      getline(fin, readStr, ',');
      cout << "|" << setw(15) << "First Name: " << setw(25) << readStr << "|" << endl;

      getline(fin, readStr, ',');
      cout << "|" << setw(15) << "Last Name: " << setw(25) << readStr << "|" << endl;

      getline(fin, readStr, ',');
      cout << "|" << setw(15) << "Phone No: " << setw(25) << readStr << "|" << endl;

      getline(fin, readStr, '\n');
      cout << "|" << setw(15) << "Email ID: " << setw(25) << readStr << "|" << endl;

    cout << "##########################################\n\n";
    }
  }
  else
  {
    cout << "Their is no contact avaiable!" << endl;
  }

  fin.close();
}

void cb::showContactByID()
{
  string readStr;
  int id;
  printf("Enter the contact id: ");
  cin >> id;

  fstream file;
  file.open(Contact::fileName, ios_base::in | ios_base::out);

  if (file.is_open())
  {
    if (!(cb::isFileEmpty(file)))
    {
      getline(file, readStr);
      while (!(file.eof()))
      {
        getline(file, readStr, ',');

        if (empty(readStr))
        {
          cout << "contact with id '" << id << "' not found!" << endl;
          continue;
        }

        if (stoi(readStr) == id)
        {
          cout << "\n##########################################\n";

          cout << "|" << setw(15) << "ID: " << setw(25) << readStr << "|" << endl;

          getline(file, readStr, ',');
          cout << "|" << setw(15) << "First Name: " << setw(25) << readStr << "|" << endl;

          getline(file, readStr, ',');
          cout << "|" << setw(15) << "Last Name: " << setw(25) << readStr << "|" << endl;

          getline(file, readStr, ',');
          cout << "|" << setw(15) << "Phone no: " << setw(25) << readStr << "|" << endl;

          getline(file, readStr, '\n'); // default dlt is \n
          cout << "|" << setw(15) << "Email ID: " << setw(25) << readStr << "|" << endl;

          cout << "##########################################\n\n";
          break;
        }
        else
        {
          getline(file, readStr);
        }
      }
    }
    file.close();
  }
}
