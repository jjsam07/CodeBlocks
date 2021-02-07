#include <iostream>
#include <conio.h> // console input output
#include <string.h>
#include <fstream> // file stream

using namespace std;

typedef struct {
    char name[30];
    char address[50];
    char phone[20];
    int age;
    int service;
    int room_no;
    int bill;
} Patient;

int main_menu();		//to display the main menu
int services();		//to display a list of services
int details();	        //to show details of customer
int rooms();           //to show rooms
int allocate_room(int *, int);
int payment();         //to show balance
int check(int);         //to check room status
int modify(int);       //to modify the record
int deleteRec(int);    //to delete the record
int showBill(int);     //to produce receipt
int verifyRecord();

int main_menu() {
    int choice;
    while(choice!=5) {
        system("cls");
        cout<<"\n\t\t\t\t-------------------------";
        cout<<"\n\t\t\t\t hospital BILLING SYSTEM ";
        cout<<"\n\t\t\t\t      - MAIN MENU -";
        cout<<"\n\t\t\t\t-------------------------";
        cout<<"\n\n\n\t\t\t1.List of Services";
        cout<<"\n\t\t\t2.Customer Details";
        cout<<"\n\t\t\t3.Records";
        cout<<"\n\t\t\t4.Payment";
        cout<<"\n\t\t\t5.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;

    switch(choice) {
            case 1:	services();
                break;
            case 2: details();
                break;
            case 3: rooms();
                break;
            case 4:	payment();
                break;
            case 5: break;
            default: {
                cout<<"\n\n\t\t\tWrong choice.....!!!";
                cout<<"\n\t\t\tPress any key to   continue....!!";
                getch();
            }
        }
    }
    return 0;
}

int services() {
    Patient patient;
    system("cls");
    int room, service;
    ofstream fout("Record.dat", ios::app | ios::binary);

    cout<<"\n List of Services";
    cout<<"\n ----------------------";
    cout<<"\n\n 1.Consultation - P300 (Room No. 1-5) ";
    cout<<"\n 2.Laboratory Services - P400 (Room No. 6-10) ";
    cout<<"\n 3.MRI - P3500 (Room No. 11-15) ";
    cout<<"\n 4.Emergency Room Services - P5000 (Room No. 16-20)" ;
    cout<<"\n 5.Panoramic X-ray - P850 (Room No. 21-25)";
    cout<<"\n Enter the services you want:- ";
    cin>>service;
    //cout<<"\n Choose room number according to services :- ";
    //cin>>r;

    if(allocate_room(&room, service) != 0) {
        cout<<"\n Sorry..!!!This service is fully occupied";
        fout.close();
        getch();
        return 0;
    } else {
        patient.room_no = room;
        if(service == 1) {
            patient.bill = (patient.age >= 60) ? (300.0 * 0.8) : 300;
        }
        else if (service == 2) {
            patient.bill = (patient.age >= 60) ? (400.0 * 0.8) : 400;
        }
        else if (service == 3) {
            patient.bill = (patient.age >= 60) ? (3500.0 * 0.8) : 3500;
        }
        else if (service == 4) {
            patient.bill = (patient.age >= 60) ? (5000.0 * 0.8) : 5000;
        }
        else if (service == 5) {
            patient.bill = (patient.age >= 60) ? (850.0 * 0.8) : 850;
        } else {
            cout << "Invalid option" << endl;
            fout.close();
            getch();
            return 0;
        }
    }
    cout<<" Name: ";
    cin>>patient.name;
    cout<<" Address: ";
    cin>>patient.address;
    cout<<" Phone No: ";
    cin>>patient.phone;
    cout<<" Age: ";
    cin>>patient.age;

    fout.write((char*)&patient, sizeof(patient));
    cout<<"\n The service is now recorded...!!!";
    cout<<"\n Press any key to continue.....!!";

    getch();
    fout.close();
    return 0;
}

int details() {
    Patient patient;
    system("cls");

    ifstream fin("Record.dat", ios::in | ios::binary);
    fin.seekg(10);
    int r;

    cout<<"\n Enter room no. for customer details :- "<<endl;
    cin>>r;

    while(!fin.eof()) {
        fin.read((char*)&patient,sizeof(patient));
        if(patient.room_no==r) {
            system("cls");
            cout<<"\n Customer Details";
            cout<<"\n ----------------";
            cout<<"\n\n Room no: "<<patient.room_no;
            cout<<"\n Name: "<<patient.name;
            cout<<"\n Address: "<<patient.address;
            cout<<"\n Phone no: "<<patient.phone<<endl;
            cout<<"Age: "<<patient.age;
            fin.close();
            getch();
            return 0;
        }
    }

    cout<<"\n Sorry Room no. not found....!!";
    cout<<"\n\n Press any key to continue....!!";\

    getch();
    fin.close();
    return 0;
}

int rooms() {
    Patient patient;
    system("cls");
    ifstream fin("Record.dat", ios::in | ios::binary);
    fin.seekg(10);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    cout << "\n\n Room No.\tName\t\tAddress\t\tPhone No.\tAge\n";

    while(!fin.eof()) {
        fin.read((char *)&patient, sizeof(patient));
        cout << "\n\n " << patient.room_no << "\t\t" << patient.name;
        cout << "\t\t" << patient.address << "\t\t" << patient.phone;
        cout << "\t\t" << patient.age;
    }

    cout <<"\n\n\n\t\t\tPress any key to continue.....!!";
    getch();
    fin.close();
    return 0;
}

int allocate_room(int *room, int service) {
    ifstream fin("Record.dat", ios::in | ios::binary);
    fin.seekg(10);
    if ((service < 1) || (service > 5)) {
        fin.close();
        return 1;
    }

    if(verifyRecord() != 0) {
        *room = ((service-1)*5)+1;
        return 0;
    }

    Patient patient;
    int occupied[5] = {0, 0, 0, 0, 0};
    int idx = 0;
    int start = ((service-1)*5);
    int last = (service*5)+1;

    while(!fin.eof()) {
        fin.read((char*)&patient, sizeof(patient));
        if((patient.room_no > start) && (patient.room_no < last)) {
            occupied[idx] = patient.room_no;
            idx++;
        }
    }

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < idx; j++) {
            if (start+1+i == occupied[j]) {
                break;
            } else {
                if (j == idx-1) {
                    *room = start+1+i;
                    fin.close();
                    return 0;
                }
            }
        }
    }

    fin.close();
    return 1;
}

int payment() {
    system("cls");
    int choice,r;
    cout<<"\n EDIT MENU";
    cout<<"\n ---------";
    cout<<"\n\n 1.Modify Customer Record";
    cout<<"\n 2.Delete Customer Record";
    cout<<"\n 3.Produce Receipt";
    cout<<"\n Enter your choice: ";

    cin>>choice;
    system("cls");

    cout<<"\n Enter room no: " ;
    cin>>r;

    switch(choice) {
        case 1:	modify(r);
            break;
        case 2:	deleteRec(r);
            break;
        case 3: showBill(r);
            break;
        default: cout<<"\n Wrong Choice.....!!";
    }
    cout<<"\n Press any key to continue....!!!";

    getch();
    return 0;
}

int check(int r) {
    Patient patient;
    int flag=0;

    ifstream fin("Record.dat", ios::in | ios::binary);
    fin.seekg(10);

    while(!fin.eof()) {
        fin.read((char*)&patient,sizeof(patient));
        if(patient.room_no==r) {
            flag=1;
            break;
        }
    }

    fin.close();
    return(flag);
}

int modify(int r) {
    Patient patient;
    long pos,flag=0;

    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    file.seekg(10);

    while(!file.eof()) {
        pos=file.tellg();
        file.read((char*)&patient,sizeof(patient));
        if(patient.room_no==r) {
            cout<<"\n Enter New Details";
            cout<<"\n -----------------";
            cout<<"\n Name: ";
            cin>>patient.name;
            cout<<" Address: ";
            cin>>patient.address;
            cout<<" Phone no: ";
            cin>>patient.phone;
            cout<<"Age: ";
            cin>>patient.age;
            file.seekg(pos);
            file.write((char*)&patient,sizeof(patient));
            cout<<"\n Record is modified....!!";
            flag=1;
            break;
        }
    }

    if(flag==0)
    cout<<"\n Sorry Room no. not found or vacant...!!";
    file.close();
    return 0;
}

int deleteRec(int r) {
    Patient patient;
    int flag=0;
    char ch;
    ifstream fin("Record.dat", ios::in | ios::binary);
    fin.seekg(10);
    ofstream fout("temp.dat", ios::out | ios::trunc | ios::binary);
    fout.write("RECORD.DAT", 10);

    while(!fin.eof()) {
        fin.read((char*)&patient,sizeof(patient));
        if(patient.room_no==r) {
            cout<<"\n Name: "<<patient.name;
            cout<<"\n Address: "<<patient.address;
            cout<<"\n Phone No: "<<patient.phone;
            cout<<"\n Age: "<<patient.age;
            cout<<"\n\n Do you want to delete this record(y/n): ";
            cin>>ch;
            if(ch=='n') {
                fout.write((char*)&patient,sizeof(patient));
                flag=1;
            }
        } else {
            fout.write((char*)&patient,sizeof(patient));
        }
    }

    fin.close();
    fout.close();

    if(flag==0) {
        cout<<"\n Sorry room no. not found or vacant...!!";
    } else {
        remove("Record.dat");
        rename("temp.dat","Record.dat");
    }
    return 0;
}

int showBill(int r) {
    Patient patient;
    ifstream fin("Record.dat", ios::in | ios::binary);
    fin.seekg(10);

    while(!fin.eof()) {
        fin.read((char*)&patient,sizeof(patient));
        if (patient.room_no == r) {
            cout<<"Your bill = P" << patient.bill;
            fin.close();
            return 0;
        }
    }
    cout<<"\n Sorry room no. not found or vacant...!!\n";
    fin.close();
    return 0;
}

int verifyRecord() {
    char str1[11] = "RECORD.DAT";
    char str2[10] = "";
    fstream file;
    file.open("Record.dat", ios::in | ios::out | ios::binary);
    file.seekg(0);
    file.read(str2, 10);

    if(strcmp(str1, str2) == 0) {
        file.close();
        return 0;
    } else {
        file.close();
        file.open("Record.dat", ios::in | ios::out | ios::binary | ios::trunc);
        file.seekp(0);
        file.write("RECORD.DAT", 10);
        file.close();
        return 1;
    }
    return 0;
}

int main() {
    system("cls");

    cout<<"\n\t\t\t----------------------------";
    cout<<"\n\t\t\t- hospital BILLING SYSTEM -";
    cout<<"\n\t\t\t----------------------------";
    cout<<"\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue....!!";

    getch();

    verifyRecord();
    main_menu();
    return 0;
}
