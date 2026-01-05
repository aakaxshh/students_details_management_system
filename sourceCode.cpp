#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

struct studentData{                    //struct creates a user defined data type
    string name;                       // name, rollNo, branch etc are data members
    string rollNo;
    string branch;
    string course;
    string emailID;

    void printStudentData() {          // member function
    cout << "\n-----------------------------------------" << endl;
    cout << "Name       : " << name << endl;
    cout << "Roll No    : " << rollNo << endl;
    cout << "Branch     : " << branch << endl;
    cout << "Course     : " << course << endl;
    cout << "Email ID   : " << emailID << endl;
    cout << "-----------------------------------------\n";
    }

};

class studentManagementSystem{          //class declaration
    private:
    vector<studentData> listOfStudents;      //stores student data

    protected:                                // handle i/o reading & writing
    void readStudentRecordFromFile();
    void storeStudentRecordInFile();

    public:                                     // user facing operations
    void mainMenu();
    void addStudentData();
    void displayStudentRecord();
    void searchStudentUsingRollNo();
    void editStudentRecord();
    void deleteStudentRecord();
};

void studentManagementSystem::readStudentRecordFromFile()  {
    ifstream fin("data.txt");
    studentData record;

    if (fin.is_open())  {

        while(  getline(fin, record.name)   && 
                getline(fin, record.rollNo) && 
                getline(fin, record.branch) && 
                getline(fin, record.course) && 
                getline(fin, record.emailID)    )

            listOfStudents.push_back(record);

        fin.close();        
    } else  {
        cout<<"data.txt"<<" file is not found"<<endl;
    }
}

void studentManagementSystem::storeStudentRecordInFile()    {
    ofstream fout("data.txt");
    if (fout.is_open()) {
        
        for(auto record : listOfStudents)   {
            fout<<record.name<<"\n";
            fout<<record.rollNo<<"\n";
            fout<<record.branch<<"\n";
            fout<<record.course<<"\n";
            fout<<record.emailID<<"\n";
        }
        fout.close();
        
    } else {
        cout<<"Error: Unable to open file!"<<endl;
    }
}

void studentManagementSystem::mainMenu() {         //The scope resolution operator (::) tells the compiler that this function belongs to the studentManagementSystem class (it was declared there).
    int choice;
    readStudentRecordFromFile();   // Load existing records

    while (true) {               
        cout << "----------------------------------------------------" << endl;
        cout << "Enter 1 for Add Student" << endl;
        cout << "Enter 2 for Print All Student Records" << endl;
        cout << "Enter 3 for Search Student" << endl;
        cout << "Enter 4 for Edit Student Record" << endl;
        cout << "Enter 5 for Delete Student Record" << endl;
        cout << "Enter 6 for Exit this App" << endl;
        cout << "Enter your Choice: ";
        cin >> choice;

        system("cls"); 

        switch (choice) {
            case 1:
                addStudentData();
                break;
            case 2:
                displayStudentRecord();
                break;
            case 3:
                searchStudentUsingRollNo();
                break;
            case 4:
                editStudentRecord();
                break;
            case 5:
                deleteStudentRecord();
                break;
            case 6:
                storeStudentRecordInFile();  // Save before exiting
                return;  
            default:
                cout << "Enter valid choice" << endl;
        }
    }
}

void studentManagementSystem::addStudentData()  {
    studentData inputData;                         // Creates a local object inputData of type studentData
    cin.ignore();                                  // to clear the input buffer
    cout<<endl<<"--------------------------------"<<endl;
    cout<<"Enter Student Name    : ";
    getline(cin, inputData.name);
    cout<<"Enter Student rollNo  : ";
    getline(cin, inputData.rollNo);
    cout<<"Enter Student branch  : ";
    getline(cin, inputData.branch);
    cout<<"Enter Student course  : ";
    getline(cin, inputData.course);
    cout<<"Enter Student emailId : ";
    getline(cin, inputData.emailID);
    cout<<"--------------------------------"<<endl;
    listOfStudents.push_back(inputData);
}

void studentManagementSystem::displayStudentRecord() {
    if(listOfStudents.empty())  {                               
        cout<<"|----------------------------------|"<<endl;
        cout<<"| Student DataBase Record is Empty |"<<endl;
        cout<<"|----------------------------------|"<<endl;
    } else  {
        int count = 1;
        for(auto Data : listOfStudents) {                      // iterate over the vector
            cout<<"Record No : "<<count++<<endl;               // auto detects the data type of Data which is StudentData
            Data.printStudentData();                           // calls the function from the struct
        }
            
    }
}

void studentManagementSystem::searchStudentUsingRollNo() {
    string rollNo;
    bool found = false;

    cin.ignore();  // safer input clearing
    cout << "Enter Student rollNo : ";
    getline(cin, rollNo);

    if (listOfStudents.empty()) {
        cout << "|----------------------------------|\n";
        cout << "| Student DataBase Record is Empty |\n";
        cout << "|----------------------------------|\n";
        return;
    }

    for (auto& data : listOfStudents) {
        if (data.rollNo == rollNo) {
            data.printStudentData();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "|----------------------------------|\n";
        cout << "| <" << rollNo << "> Student Record not found |\n";
        cout << "|----------------------------------|\n";
    }
}

void studentManagementSystem::editStudentRecord()   {
    string rollNo;
    bool flag = true;
    cin.ignore();
    cout<<"Enter Student rollNo : ";
    getline(cin, rollNo);

    if(listOfStudents.empty())  {
        cout<<"|----------------------------------|"<<endl;
        cout<<"| Student DataBase Record is Empty |"<<endl;
        cout<<"|----------------------------------|"<<endl;
    } else {
        for(int x = 0; x < listOfStudents.size(); x++)

            if(listOfStudents[x].rollNo == rollNo)  {
                cout<<endl<<"--------------------------------"<<endl;
                cout<<"Enter Student Name    : ";
                getline(cin, listOfStudents[x].name);
                cout<<"Enter Student branch  : ";
                getline(cin, listOfStudents[x].branch);
                cout<<"Enter Student emailId : ";
                getline(cin, listOfStudents[x].emailID);
                cout<<"--------------------------------"<<endl;
                flag = false;
                break;
            }

        if(flag)    {
            cout<<"|----------------------------------|"<<endl;
            cout<<"| <"<<rollNo<<"> Student Record not found "<<endl;
            cout<<"|----------------------------------|"<<endl;
        }
    }
}

void studentManagementSystem::deleteStudentRecord() {
    string rollNo;
    bool flag = true;
    cin.ignore();
    cout<<"Enter Student rollNo : ";
    getline(cin, rollNo);

    if(listOfStudents.empty())  {
        cout<<"|----------------------------------|"<<endl;
        cout<<"| Student DataBase Record is Empty |"<<endl;
        cout<<"|----------------------------------|"<<endl;
    } else {
        vector<studentData>::iterator it = listOfStudents.begin();   //Using an iterator is essential here because vector::erase() requires an iterator as an argument.
        for( ; it != listOfStudents.end(); it++)
            if(it->rollNo == rollNo)    {
                it->printStudentData();
                listOfStudents.erase(it);
                cout<<"Deletion is seccuessful"<<endl;
                flag = false;
                break;
            }
        if(flag)    {
            cout<<"|----------------------------------|"<<endl;
            cout<<"| <"<<rollNo<<"> Student Record not found "<<endl;
            cout<<"|----------------------------------|"<<endl;
        }
    }
}



int main() {
    studentManagementSystem sms;
    sms.mainMenu();
    return 0;
}
