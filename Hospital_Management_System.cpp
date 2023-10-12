#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set>
#include <string>
#include <fstream>

using namespace std;

// The concept of friend function, friend class, operator overloading, inheritance, polymorphism, abstract base class,
// stl (Vector , set , pair), function over-riding and dynamic casting is used in this project.

class Bill;
class Person;
class Patient;
void readFromFile(vector<Person*> &v);
void writeToFile(vector<Person*> &v);
void readFromFile(vector<Patient> &v);
void writeToFile(vector<Patient> &v);
class Person{
public:
    string name;
    string ID;
    Person(){}
    Person(string name,string ID){
        this->name=name;
        this->ID=ID;
    }
    string getID(){
        return ID;
    }
    virtual void resign(){}
    virtual void display() = 0;
    friend class Bill;
};

class Doctor:public Person{
protected:
    string dept;
    string position;
    string qualification;
    int availablehour_start;
    int availablehour_end;
    bool available;
public:
    Doctor(){
        available = true;
    }
    Doctor(string n,string id,string d,string p,string q,int a,int b,bool v):Person(n,id){
        dept=d;
        position=p;
        qualification=q;
        availablehour_start=a;
        availablehour_end=b;
        available=v;
    }
    friend istream &operator >>(istream &in, Doctor &d){
        cout << "Enter Doctor's Name : ";
        in >> d.name;
        cout << "Enter Doctor's ID : ";
        in >> d.ID;
        cout << "Enter department : ";
        in >> d.dept;
        cout << "Enter position : ";
        in >> d.position;
        cout << "Enter qualification : ";
        in >> d.qualification;
        cout << "Enter Doctor's starting hour : ";
        in >> d.availablehour_start;
        cout << "Enter Doctor's ending hour : ";
        in >> d.availablehour_end;
        return in;
    }
    void display(){
        cout << "Name: " << name << endl;
        cout << "ID : " << ID << endl;
        cout << "Department : " << dept << endl;
        cout << "Position : " << position << endl;
        cout << "Qualification : " << qualification << endl << endl;
    }
    void resign(){
        if(available){
            available = false;
            cout << "Doctor has resigned." << endl << endl;
        }
        else{
            cout << "The doctor had already resigned before." << endl << endl;
        }
    }
    bool isavailable(int t){
        if(t>=availablehour_start && t<=availablehour_end){
            return true;
        }
        else{
            return false;
        }
    }
    friend void readFromFile(vector<Person*>& v);
    friend void writeToFile(vector<Person*> &v);
};

class Nurse:public Person{
bool available;
public:
    Nurse(){
        available = true;
    }
    Nurse(string name, string id): Person(name, id){
        available = true;
    }
    friend istream &operator >>(istream &in,Nurse & n){
        cout << "Enter Nurse Name : ";
        in >> n.name;
        cout << "Enter Nurse ID : ";
        in >> n.ID;
        return in;
    }
    void display(){
        cout << "Nurse Name : " << name << endl;
        cout << "Nurse ID : " << ID << endl << endl;
    }
    void resign(){
        if(available){
            available = false;
            cout << "Nurse has resigned." << endl << endl;
        }
        else{
            cout << "The nurse had already resigned before." << endl << endl;
        }
    }
    friend void readFromFile(vector<Person*>& v);
    friend void writeToFile(vector<Person*> &v);
};

class Patient:public Person{
protected:
    string disease;
    string type;
    bool discharged;
    int bill;
    bool bill_paid;
public:
    Person *doctor;
    Patient(){
        discharged=false;
        bill_paid=false;
    }

    friend istream &operator >>(istream &in,Patient &a){
        cout << "Enter Patient Name : ";
        in >> a.name;
        cout << "Enter Patient ID : ";
        in >> a.ID;
        cout << "Enter Disease : ";
        in >> a.disease;
        cout << "Enter patient situation : ";
        in >> a.type;
        return in;
    }

    void discharge(){
        if(discharged){
            cout << "Patient is already discharged." << endl;
        }
        else if(bill_paid == false && bill!=0){
            char c;
            cout << "Please pay your bill." << endl;
            cout << "Amount : " << bill << endl;
            cout << "Press y to pay and n to cancel : ";
            cin >> c;
            if(c=='y'){
                bill_paid=true;
                discharged=true;
                cout << "Patient is discharged." << endl;
                cout << "Thanks for using our system." << endl << endl;
            }
            else{
                cout << "I am sorry. You need to pay first to be discharged." << endl << endl;
            }
        }
        else{
            discharged = true;
            cout << "Patient is discharged." << endl;
        }
    }

    void display(){
        cout << "Name: " << name << endl;
        cout << "ID : " << ID << endl;
        cout << "Disease : " << disease << endl;
        cout << "Case : " << type << endl << endl;
    }
    friend class Bill;
    friend void readFromFile(vector<Patient>&v);
    friend void writeToFile(vector<Patient>&v);
};

class Bill{
public:
    static void calculate_bill(Patient *p){
        vector<pair<string, int>> tests = {
            make_pair("Blood Test", 500),
            make_pair("X-ray", 600),
            make_pair("CT-Scan", 1500),
            make_pair("MRI", 1300),
            make_pair("ECG", 1600),
            make_pair("ETT", 1800),
            make_pair("Urine Test", 1200),
            make_pair("Radiotherapy", 2500)
        };

        int testCount = (rand() % (tests.size()-1)) +1;
        set<int> patTest;

        for(int i = 0; patTest.size()!=testCount; i++){
            patTest.insert(rand() % tests.size());
        }
        cout << "ALL TEst : " << endl;
        int bill = 0;
        for(auto i: patTest){
            cout << tests[i].first << " : " << tests[i].second << endl;
            bill += tests[i].second;
        }
        int visit;
        if(p->type=="Serious"){
            visit = 6000;
        }
        else if(p->type=="Care-needed"){
            visit = 6000;
        }
        else{
            visit = 2000;
        }
        cout << "Doctor bill : " << visit << endl;
        bill += visit;
        cout << "Total : " << bill << endl;
        char c;
        p->bill = bill;
        cout << "Do you want to pay now?" << endl;
        cout << "y/n Please give input : " << endl;
        cin >> c;
        if(c=='y'){
            cout << "Your bill is paid." << endl << endl;
            p->bill_paid = true;
        }
        else{
            cout << "Please pay your bill before discharge." << endl << endl;
        }
    }
};

class Hospital{
protected:
    string H_name;
    string H_address;
public:
    vector<Patient> patients;
    vector<Person *> staffs;

    Hospital() {}
    Hospital(string H_name, string H_address){
        this->H_name = H_name;
        this->H_address = H_address;
    }

    void registerpatient(){
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "A patient is being admitted in the hospital.\t Please fill out the following information.\n\n";
        Patient p;
        cin >> p;
        Bill::calculate_bill(&p);
        patients.push_back(p);
    }

    void patientdetails(){
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "Checking a patient's details : \n\n";
        string id;
        cout << "Enter patient ID: ";
        cin >> id;
        for(auto p:patients){
            if(p.getID() == id ){
                p.display();
            }
        }
    }

    void add_doctor(){
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "A doctor is now joining the hospital.\t Please fill out the following information.\n\n";
        Doctor *d = new Doctor();
        cin >> *d;
        staffs.push_back(d);
    }

    void add_nurse(){
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "A nurse is now joining the hospital.\t Please fill out the following information.\n\n";
        Nurse *n = new Nurse;
        cin >> *n;
        staffs.push_back(n);
    }

    void releasepatient(){
        string id;
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "Releasing a patient .\t Please fill out the following information.\n\n";
        cout << "Enter patient ID to discharge: ";
        cin >> id;
        for(auto p:patients){
            if(p.getID() == id ){
                p.discharge();
            }
        }
    }

    void remove_doctor(){
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "A doctor is now resigning from the hospital .\t Please fill out the following information.\n\n";
        string id;
        cout << "Enter doctor ID to resign: ";
        cin >> id;
        int c = 0;
        for(auto s:staffs){
            if(s->getID() == id && typeid(*s) == typeid(Doctor)){
                s->resign();
                c++;
            }
            
        }
        if(c==0){
            cout << "The id does not exist in the system." << endl << endl;
        }
    }

    void remove_nurse(){
        string id;
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        cout << "A nurse is now resigning from the hospital .\t Please fill out the following information.\n\n";
        cout << "Enter nurse ID to resign: ";
        cin >> id;
        int c =  0;
        for(auto s:staffs){
            if(s->getID() == id && typeid(*s) == typeid(Nurse)){
                s->resign();
                c++;
            }
        }
        if(c==0){
            cout << "The id does not exist in the system." << endl << endl;
        }
    }

    void available_doctor(){
        cout << "****************************************************\n";
        cout << "|\t\tKhulna City Hospital\t\t|\n";
        cout << "****************************************************\n\n";
        int t,i=1;
        cout << "Enter the time of appointment : " << endl << endl;
        cin >> t;
        cout << "All the available doctors are : " << endl << endl;
        for(auto s:staffs){
            if(typeid(*s) == typeid(Doctor)){
                 if((dynamic_cast<Doctor*>(s))->isavailable(t)){
                    cout << "Doctor " << i << " : " << endl << endl;
                    s->display();
                    i++;
                 }
            }

        }
        if(i == 1){
            cout << "The is no doctor available for the required time." << endl << endl;
        }
    }

    void take_appointment(){
        string patient_id;
        string id;
        Patient *pat;
        cout << "Enter Patient ID : ";
        cin >> patient_id;
        cout << "Enter Doctor's ID : ";
        cin >> id;
        for(auto p:patients){
            if(p.getID() == id ){
                pat=&p;
            }
            else{
                cout << "Please register patient first." << endl << endl;
                return;
            }
        }
        for(auto s:staffs){
            if(s->getID() == id && typeid(*s) == typeid(Doctor)){
                pat->doctor = s;
                s->display();
                cout << "The patient has been appointed." << endl << endl;
            }
            else{
                cout << "The id does not exist in the system." << endl << endl;
            }
        }
    }
};

void readFromFile(vector<Person*>& v) {
    ifstream fileD("Doctor.txt"), fileN("Nurse.txt");
    if (fileD){
        while (!fileD.eof()) {
            Doctor * d = new Doctor() ;
            fileD >>  d->name >> d->ID >> d->qualification >> d->available >> d->availablehour_end >> d->availablehour_start >> d->dept >> d->position;
            if(d->name == "") break;
            v.push_back(d);
        }
    }
    if (fileN){
        while (!fileN.eof()) {
            Nurse * n = new Nurse();
            fileN >> n->name >> n->ID;
            if(n->name == "") break;
            v.push_back(n);
        }
    }
    fileD.close();
    fileN.close();
}

void readFromFile(vector<Patient>&v) {
    ifstream fileP("Patient.txt");
    while(!fileP.eof()){
            Patient p;
            fileP >> p.name >> p.ID >> p.disease >> p.type;
            if(p.name == "") break;
            v.push_back(p);
        }
}

void writeToFile(vector<Person*> &v) {
    ofstream fileD("Doctor.txt"), fileN("Nurse.txt");

    for (auto i:v) {
        Nurse *n = dynamic_cast<Nurse*> (i);
        Doctor *d = dynamic_cast<Doctor*> (i);
         
        if (n!=0) {
            fileN << n->name<<endl;
            fileN << n->ID<<endl;
        }
        else{
            fileD << d->name<<endl;
            fileD << d->ID<<endl;
            fileD << d->qualification<<endl;
            fileD << d->available<<endl;
            fileD << d->availablehour_end<<endl;
            fileD << d->availablehour_start<<endl;
            fileD << d->dept<<endl;
            fileD << d->position<<endl;
        }
    }
    fileD.close();
    fileN.close();
}

void writeToFile(vector<Patient> &v) {
    ofstream fileP("Patient.txt");

    for (auto i:v) {
    fileP << i.name << endl;
    fileP << i.ID << endl;
    fileP << i.disease << endl;
    fileP << i.type << endl;
}
    fileP.close();
}

int main()
{
    Hospital h;
    readFromFile(h.patients);
    readFromFile(h.staffs);
    while(1){
        int input;
        cout << "****************************************************\n";
        cout << "\t\tKhulna City Hospital\n";
        cout << "****************************************************\n\n";
        cout << "1. To admit a patient\n";
        cout << "2. To release a patient\n";
        cout << "3. Take appointment from a doctor\n";
        cout << "4. Show all the doctors available\n";
        cout << "5. To check patient details\n";
        cout << "6. Add a doctor\n";
        cout << "7. Remove a doctor\n";
        cout << "8. Add a nurse\n";
        cout << "9. Remove a nurse\n";
        cout << "0. To close the program\n";
        cout << "Please give input : ";
        cin >> input;
        if(input == 1){
            h.registerpatient();
        }
        else if(input == 2){
            h.releasepatient();
        }
        else if(input == 3){
            h.take_appointment();
        }
        else if(input == 4){
            h.available_doctor();
        }
        else if(input == 5){
            h.patientdetails();
        }
        else if(input == 6){
            h.add_doctor();
        }
        else if(input == 7){
            h.remove_doctor();
        }
        else if(input == 8){
            h.add_nurse();
        }
        else if(input == 9){
            h.remove_nurse();
        }
        else if(input == 0){
            cout << "Thanks for using our system." << endl;
            break;
        }
        else{
            cout << "Wrong input. Pleae give input again." << endl;
        }
    }
    writeToFile(h.patients);
    writeToFile(h.staffs);
    return 0;
}