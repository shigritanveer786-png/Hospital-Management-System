#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

/*
    HOSPITAL MANAGEMENT SYSTEM
    Compatible with Dev-C++ 5.11 (C++98)
    Data is stored in text files in the same folder as this program.
*/

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void line() {
    cout << "------------------------------------------------------------\n";
}

void addPatient() {
    ofstream file("patients.txt", ios::app);
    if (!file) {
        cout << "Error: Could not open patients.txt\n";
        return;
    }

    string id, name, age, gender, phone, disease;
    cout << "\n--- ADD PATIENT ---\n";
    cout << "Patient ID: "; getline(cin, id);
    cout << "Patient Name: "; getline(cin, name);
    cout << "Age: "; getline(cin, age);
    cout << "Gender: "; getline(cin, gender);
    cout << "Phone: "; getline(cin, phone);
    cout << "Disease / Problem: "; getline(cin, disease);

    file << id << "|" << name << "|" << age << "|" << gender
         << "|" << phone << "|" << disease << "\n";
    file.close();
    cout << "\nPatient record saved successfully.\n";
}

void viewPatients() {
    ifstream file("patients.txt");
    string record;
    cout << "\n--- ALL PATIENTS ---\n";
    line();
    if (!file) {
        cout << "No patient records found yet.\n";
        return;
    }
    while (getline(file, record)) {
        cout << record << "\n";
    }
    file.close();
    line();
    cout << "Format: ID | Name | Age | Gender | Phone | Disease\n";
}

void searchPatient() {
    ifstream file("patients.txt");
    string id, record;
    bool found = false;
    cout << "\nEnter Patient ID to search: ";
    getline(cin, id);

    if (!file) {
        cout << "No patient records found.\n";
        return;
    }

    while (getline(file, record)) {
        size_t pos = record.find('|');
        if (pos != string::npos && record.substr(0, pos) == id) {
            cout << "\nPatient found:\n" << record << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "Patient ID not found.\n";
}

void addDoctor() {
    ofstream file("doctors.txt", ios::app);
    if (!file) {
        cout << "Error: Could not open doctors.txt\n";
        return;
    }

    string id, name, specialization, phone;
    cout << "\n--- ADD DOCTOR ---\n";
    cout << "Doctor ID: "; getline(cin, id);
    cout << "Doctor Name: "; getline(cin, name);
    cout << "Specialization: "; getline(cin, specialization);
    cout << "Phone: "; getline(cin, phone);

    file << id << "|" << name << "|" << specialization << "|" << phone << "\n";
    file.close();
    cout << "\nDoctor record saved successfully.\n";
}

void viewDoctors() {
    ifstream file("doctors.txt");
    string record;
    cout << "\n--- ALL DOCTORS ---\n";
    line();
    if (!file) {
        cout << "No doctor records found yet.\n";
        return;
    }
    while (getline(file, record)) cout << record << "\n";
    file.close();
    line();
    cout << "Format: ID | Name | Specialization | Phone\n";
}

void addAppointment() {
    ofstream file("appointments.txt", ios::app);
    if (!file) {
        cout << "Error: Could not open appointments.txt\n";
        return;
    }

    string appointmentId, patientId, doctorId, date, time;
    cout << "\n--- BOOK APPOINTMENT ---\n";
    cout << "Appointment ID: "; getline(cin, appointmentId);
    cout << "Patient ID: "; getline(cin, patientId);
    cout << "Doctor ID: "; getline(cin, doctorId);
    cout << "Date (DD-MM-YYYY): "; getline(cin, date);
    cout << "Time: "; getline(cin, time);

    file << appointmentId << "|" << patientId << "|" << doctorId
         << "|" << date << "|" << time << "\n";
    file.close();
    cout << "\nAppointment saved successfully.\n";
}

void viewAppointments() {
    ifstream file("appointments.txt");
    string record;
    cout << "\n--- APPOINTMENTS ---\n";
    line();
    if (!file) {
        cout << "No appointments found yet.\n";
        return;
    }
    while (getline(file, record)) cout << record << "\n";
    file.close();
    line();
    cout << "Format: Appointment ID | Patient ID | Doctor ID | Date | Time\n";
}

void createBill() {
    ofstream file("bills.txt", ios::app);
    if (!file) {
        cout << "Error: Could not open bills.txt\n";
        return;
    }

    string billId, patientId, details;
    double amount;
    cout << "\n--- CREATE BILL ---\n";
    cout << "Bill ID: "; getline(cin, billId);
    cout << "Patient ID: "; getline(cin, patientId);
    cout << "Description: "; getline(cin, details);
    cout << "Amount (PKR): ";
    while (!(cin >> amount) || amount < 0) {
        cout << "Please enter a valid non-negative amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    file << billId << "|" << patientId << "|" << details
         << "|" << fixed << setprecision(2) << amount << "\n";
    file.close();
    cout << "\nBill saved successfully. Amount: PKR "
         << fixed << setprecision(2) << amount << "\n";
}

void viewBills() {
    ifstream file("bills.txt");
    string record;
    cout << "\n--- BILL RECORDS ---\n";
    line();
    if (!file) {
        cout << "No bills found yet.\n";
        return;
    }
    while (getline(file, record)) cout << record << "\n";
    file.close();
    line();
    cout << "Format: Bill ID | Patient ID | Description | Amount (PKR)\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n";
        line();
        cout << "              HOSPITAL MANAGEMENT SYSTEM\n";
        line();
        cout << "1. Add New Patient\n";
        cout << "2. View All Patients\n";
        cout << "3. Search Patient by ID\n";
        cout << "4. Add Doctor\n";
        cout << "5. View All Doctors\n";
        cout << "6. Book Appointment\n";
        cout << "7. View Appointments\n";
        cout << "8. Create Patient Bill\n";
        cout << "9. View Bills\n";
        cout << "0. Exit\n";
        line();
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a menu number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: addDoctor(); break;
            case 5: viewDoctors(); break;
            case 6: addAppointment(); break;
            case 7: viewAppointments(); break;
            case 8: createBill(); break;
            case 9: viewBills(); break;
            case 0: cout << "\nThank you for using Hospital Management System.\n"; break;
            default: cout << "\nInvalid choice. Please select 0 to 9.\n";
        }

        if (choice != 0) pauseScreen();

    } while (choice != 0);

    return 0;
}
