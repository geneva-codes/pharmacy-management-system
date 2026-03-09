#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Medicine{
    string name;
    float price;
    int stock;
};

Medicine meds[100];
int medCount = 0;
int receiptNo = 1;

void loadMedicines(){

    ifstream file("medicines.txt");

    while(file >> meds[medCount].name >> meds[medCount].price >> meds[medCount].stock){
        medCount++;
    }

    file.close();
}

void saveMedicines(){

    ofstream file("medicines.txt");

    for(int i=0;i<medCount;i++){
        file << meds[i].name << " "
             << meds[i].price << " "
             << meds[i].stock << endl;
    }

    file.close();
}

void viewMedicines(){

    cout << "\n===== MEDICINE INVENTORY =====\n";

    cout << left << setw(5) << "ID"
         << setw(15) << "NAME"
         << setw(10) << "PRICE"
         << setw(10) << "STOCK" << endl;

    cout << "-----------------------------------\n";

    for(int i=0;i<medCount;i++){

        cout << left << setw(5) << i
             << setw(15) << meds[i].name
             << setw(10) << meds[i].price
             << setw(10) << meds[i].stock;

        if(meds[i].stock <= 5)
            cout << "  LOW STOCK";

        cout << endl;
    }
}

void addMedicine(){

    cout << "Medicine Name: ";
    cin >> meds[medCount].name;

    cout << "Price: ";
    cin >> meds[medCount].price;

    cout << "Stock: ";
    cin >> meds[medCount].stock;

    medCount++;

    saveMedicines();

    cout << "Medicine added\n";
}

void deleteMedicine(){

    int id;

    cout << "Enter ID: ";
    cin >> id;

    if(id >= medCount){
        cout << "Invalid ID\n";
        return;
    }

    for(int i=id;i<medCount-1;i++)
        meds[i] = meds[i+1];

    medCount--;

    saveMedicines();

    cout << "Medicine deleted\n";
}

void sellMedicine(){

    float grandTotal = 0;

    cout << "\n========== RECEIPT ==========\n";
    cout << "Receipt No: " << receiptNo << endl;

    while(true){

        int id,qty;

        cout << "\nEnter Medicine ID (-1 to finish): ";
        cin >> id;

        if(id == -1)
            break;

        if(id >= medCount){
            cout << "Invalid ID\n";
            continue;
        }

        cout << "Quantity: ";
        cin >> qty;

        if(qty > meds[id].stock){
            cout << "Not enough stock\n";
            continue;
        }

        float total = qty * meds[id].price;

        meds[id].stock -= qty;

        grandTotal += total;

        ofstream file("sales.txt", ios::app);

        file << receiptNo << " "
             << meds[id].name << " "
             << qty << " "
             << total << endl;

        file.close();

        cout << meds[id].name << " x" << qty
             << " = " << total << endl;
    }

    cout << "\nTOTAL: " << grandTotal << endl;
    cout << "=============================\n";

    receiptNo++;

    saveMedicines();
}

void viewSales(){

    ifstream file("sales.txt");

    int r;
    string name;
    int qty;
    float total;

    cout << "\n===== SALES HISTORY =====\n";

    while(file >> r >> name >> qty >> total){

        cout << "Receipt: " << r << endl;
        cout << "Medicine: " << name << endl;
        cout << "Qty: " << qty << endl;
        cout << "Total: " << total << endl;
        cout << "---------------------\n";
    }

    file.close();
}

int main(){

    loadMedicines();

    string username,password;

    cout << "===== PHARMACY SYSTEM LOGIN =====\n";

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if(!((username=="admin"||username=="cashier") && password=="1234")){
        cout << "Invalid login\n";
        return 0;
    }

    int choice;

    while(true){

        cout << "\n===== PHARMACY MENU =====\n";
        cout << "1 Add Medicine\n";
        cout << "2 View Medicines\n";
        cout << "3 Sell Medicine\n";
        cout << "4 Delete Medicine\n";
        cout << "5 Sales History\n";
        cout << "6 Exit\n";
        cout << "Choice: ";

        cin >> choice;

        if(choice==1)
            addMedicine();

        else if(choice==2)
            viewMedicines();

        else if(choice==3)
            sellMedicine();

        else if(choice==4)
            deleteMedicine();

        else if(choice==5)
            viewSales();

        else if(choice==6)
            break;

        else
            cout << "Invalid choice\n";
    }

    return 0;
}