#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

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
    static string remIDsFN;
    Contact(string, string, string, string);
    void writeCSV(Contact &);
    void setID();
  };

  string Contact::fileName = "contacts.csv";
  string Contact::idFN = "id_info.csv";
  string Contact::remIDsFN = "remContactIDs.csv";

  // Not member function of class
  void createContact();
  bool isFileEmpty(fstream &);
  bool isFileEmpty(ofstream &);
  void showAllContacts();
  void showContactByID();
  void deleteContactByID();
  void saveRemContactIDs();
  void initRemContactIDs();
  string remNewLineChar(string);
  void createFiles();

  vector<int> remContactIDs;
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
  vector<string> lines;
  string readline;
  string margedString = to_string(c.id) + "," + c.firstName + "," + c.lastName + "," + c.contactNo + "," + c.email + "\n";

  ifstream fin;
  fin.open(Contact::fileName);

  if (fin.is_open())
  {
    while (!(fin.eof()))
    {
      getline(fin, readline);
      lines.push_back(readline);
    }
    fin.close();

    lines.pop_back();
  }

  fstream file;

  file.open(fileName, ios_base::out | ios_base::in);
  if (file.is_open())
  {
    if (cb::isFileEmpty(file) && lines.size() < 1)
    {
      string headerStr = "ID,FirstName,LastName,PhoneNo.,EmailID\n";
      file << headerStr;
      file << margedString;
    }
    else
    {
      for (int i = 0; i < lines.size(); i++)
      {
        if (c.id == i)
        {
          file << margedString;
        }
        else
        {
          file << lines[i] << endl;
        }
      }

      if (c.id > lines.size() - 1)
      {
        file << margedString;
      }
    }

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
  bool isRemContactIDs = remContactIDs.size() > 0;
  sort(remContactIDs.begin(), remContactIDs.end());
  // sort the vector in accending order

  file.open(idFN, ios_base::in | ios_base::out);
  if (file.is_open())
  {
    if (isRemContactIDs)
    {
      id = remContactIDs[0];
      remContactIDs.erase(remContactIDs.begin()); // remove the first element
    }

    if (cb::isFileEmpty(file))
    {
      file << id;
    }
    else
    {
      getline(file, readStr);
      file.seekg(0, ios_base::beg);
      id = isRemContactIDs ? id : stoi(readStr) + 1;
      file << (isRemContactIDs ? stoi(readStr) : stoi(readStr) + 1);
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
      if (empty(readStr))
        continue;
      else if (empty(remNewLineChar(readStr)))
      {
        fin.close();
        cout << "Their is no contact avaiable!" << endl;
        return;
      }

      cout << "##########################################\n";
      cout << "|" << setw(15) << "ID: " << setw(25) << stoi(readStr) << "|" << endl;

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
        readStr = remNewLineChar(readStr);

        if (empty(readStr) || readStr == "\n")
        {
          cout << "\ncontact with id '" << id << "' not found!" << endl;
          continue;
        }
        // cout<<readStr<<"readstr"<<endl;

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

          cout << "##########################################\n";
          break;
        }
        else
        {
          getline(file, readStr);
        }
      }
    }
    else
    {
      cout << "\ncontact with id '" << id << "' not found!" << endl;
    }
    file.close();
  }
}

void cb::deleteContactByID()
{
  vector<string> lines;
  string readline;
  int id;
  cout << "Enter the id which you want to delete: ";
  cin >> id;

  ifstream fin;
  fin.open(Contact::fileName);

  if (fin.is_open())
  {
    while (!(fin.eof()))
    {
      getline(fin, readline);
      lines.push_back(readline);
    }

    lines.pop_back();

    fin.close();

    if ((id > (lines.size() - 1)) || id < 1 || lines.size() == 0 || count(remContactIDs.begin(), remContactIDs.end(), id))
    {
      cout << "\nID No. '" << id << "' not found" << endl;
      fin.close();
      return;
    }
  }
  else
  {
    cout << "\nSomething went wrong! cannot open the file." << endl;
    return;
  }

  ofstream fout;
  fout.open(Contact::fileName);

  if (fout.is_open())
  {

    for (int i = 0; i < lines.size(); i++)
    {
      if (id == i)
      {
        remContactIDs.push_back(id);
        fout << endl;
      }
      else
      {
        fout << lines[i] << endl;
      }
    }
    cout << "\nContact with id '" << id << "' is deleted!" << endl;
  }
  else
  {
    cout << "\nSomething went wrong! cannot open the file." << endl;
  }
  fout.close();
}

void cb::saveRemContactIDs()
{

  ofstream fout;
  fout.open(Contact::remIDsFN);

  if (fout.is_open())
  {
    for (int i = 0; i < remContactIDs.size(); i++)
    {
      fout << remContactIDs[i] << endl;
    }

    fout.close();
  }
  else
  {
    cout << "Something went wrong! cannot open the file." << endl;
  }
}

void cb::initRemContactIDs()
{
  string readline;
  ifstream fin;
  fin.open(Contact::remIDsFN);

  if (fin.is_open())
  {
    while (!(fin.eof()))
    {
      getline(fin, readline);
      if (empty(readline))
        continue;
      remContactIDs.push_back(stoi(readline));
    }

    fin.close();
  }
  else
  {
    cout << "Something went wrong! cannot open the file." << endl;
  }
}

string cb::remNewLineChar(string str)
{
  string newStr = "";

  for (int i = 0; i < str.size(); i++)
  {
    char ch = str[i];
    if (!(ch == '\n'))
      newStr += ch;
  }

  return newStr;
}

void cb::createFiles()
{
  ofstream file;
  file.open(Contact::fileName, ios_base::app);
  file.close();

  file.open(Contact::idFN, ios_base::app);
  file.close();

  file.open(Contact::remIDsFN, ios_base::app);
  file.close();
}