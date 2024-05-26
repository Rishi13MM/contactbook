#include <iostream>
#include <string>
#include <fstream>

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

    string fileName;
    string idFN;

  public:
    Contact(string, string, string, string);
    void writeCSV(Contact &);
    void setID();
  };

  // Not member function of class
  void createContact();
  bool isFileEmpty(ifstream &);

}

// #########################################################################

cb::Contact::Contact(string fn, string ln, string pn, string em)
{
  id = 0;
  idFN = "id_info.csv";
  fileName = "contacts.csv";
  firstName = fn;
  lastName = ln;
  contactNo = pn;
  email = em;
}

void cb::Contact::writeCSV(Contact &c)
{
  string margedString = to_string(c.id) + "," + c.firstName + "," + c.lastName + "," + c.contactNo + "," + c.email + "\n";

  ofstream fout;

  fout.open(fileName, ios_base::app);
  fout << margedString;
  fout.close();
}

void cb::Contact::setID()
{
  {
    char *read;
    bool isFEmpty = false;

    ifstream fin;
    ofstream fout;

    // check file is empty or not
    fin.open(idFN);
    isFEmpty = cb::isFileEmpty(fin);
    fin.close();

    // write default id -1 if file is empty
    if (isFEmpty)
    {
      fout.open(idFN);
      fout << -1;
      fout.close();
    }

    // code need to run whether file is empty or not
    fin.open(idFN);
    fin.getline(read, INT_MAX - 1);
    id = stoi(read) + 1;
    fin.close();
    // cout << "id: " << id << endl;

    // write id in the csv file
    fout.open(idFN);
    fout << id;
    fout.close();
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
  // c.setID();
  c.writeCSV(c);
}

bool cb::isFileEmpty(ifstream &fin)
{
  fin.seekg(0, ios_base::end);
  return fin.tellg() == 0 ? true : false;
}