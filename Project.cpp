#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Number of subjects
const int SUBJECTS = 6;

// Subject names
string subjectNames[SUBJECTS] = {"C/C++", "CN", "DS", "DBMS", "Java", "DAA"};

// Structure to store one student's details
struct Student {
    string roll;
    string name;
    float marks[SUBJECTS];
    int totalClasses;
    int attendedClasses;
};

// Function declarations
void loadData(Student s[], int &n);
void saveData(Student s[], int n);
void addStudent(Student s[], int &n);
void displayAll(Student s[], int n);
void searchStudent(Student s[], int n);
char calculateGrade(float avg);

// ---------------------- MAIN FUNCTION ----------------------
int main() {
    Student s[100];
    int n = 0;
    int choice;

    loadData(s, n); // Load existing data from file

    do {
        cout << "\n===========================================\n";
        cout << "   STUDENT MARKS & ATTENDANCE MANAGEMENT   \n";
        cout << "===========================================\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addStudent(s, n);
            saveData(s, n); // Save every time a new student is added
        } 
        else if (choice == 2)
            displayAll(s, n);
        else if (choice == 3)
            searchStudent(s, n);
        else if (choice == 4)
            cout << "\nExiting program. Data saved to file.\n";
        else
            cout << "\nInvalid choice! Try again.\n";

    } while (choice != 4);

    return 0;
}

// ---------------------- FUNCTION DEFINITIONS ----------------------

// Load data from file
void loadData(Student s[], int &n) {
    ifstream fin("students.txt");
    if (!fin.is_open()) {
        cout << "(No previous records found — starting fresh)\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);

        getline(ss, s[n].roll, ',');
        getline(ss, s[n].name, ',');

        for (int i = 0; i < SUBJECTS; i++)
            ss >> s[n].marks[i], ss.ignore();

        ss >> s[n].totalClasses;
        ss.ignore();
        ss >> s[n].attendedClasses;

        n++;
    }
    fin.close();
    cout << "Loaded " << n << " records from file.\n";
}

// Save data to file
void saveData(Student s[], int n) {
    ofstream fout("students.txt");
    for (int i = 0; i < n; i++) {
        fout << s[i].roll << "," << s[i].name << ",";
        for (int j = 0; j < SUBJECTS; j++)
            fout << s[i].marks[j] << ",";
        fout << s[i].totalClasses << "," << s[i].attendedClasses << "\n";
    }
    fout.close();
}

// Add new student
void addStudent(Student s[], int &n) {
    cout << "\nEnter Roll Number: ";
    cin >> s[n].roll;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s[n].name);

    cout << "\nEnter marks for each subject (out of 20):\n";
    for (int i = 0; i < SUBJECTS; i++) {
        cout << subjectNames[i] << ": ";
        cin >> s[n].marks[i];
    }

    cout << "\nEnter Total Classes Conducted: ";
    cin >> s[n].totalClasses;
    cout << "Enter Classes Attended: ";
    cin >> s[n].attendedClasses;

    cout << "\nStudent added successfully!\n";
    n++;
}

// Display all students
void displayAll(Student s[], int n) {
    if (n == 0) {
        cout << "\nNo student records available!\n";
        return;
    }

    cout << "\n===== ALL STUDENT RECORDS =====\n";
    for (int i = 0; i < n; i++) {
        cout << "\n---------------------------------\n";
        cout << "Name: " << s[i].name << "\n";
        cout << "Roll No: " << s[i].roll << "\n";

        float total = 0;
        for (int j = 0; j < SUBJECTS; j++)
            total += s[i].marks[j];

        float avg = total / SUBJECTS;
        float avgPercent = (avg / 20) * 100;
        char grade = calculateGrade(avgPercent);

        float attendance = 0;
        if (s[i].totalClasses > 0)
            attendance = (s[i].attendedClasses * 100.0) / s[i].totalClasses;

        cout << "Average Marks: " << avg << " / 20\n";
        cout << "Percentage: " << avgPercent << "%\n";
        cout << "Grade: " << grade << "\n";
        cout << "Attendance: " << attendance << "%\n";

        if (attendance < 75)
            cout << "Warning: Low attendance!\n";
    }
}

// Search student
void searchStudent(Student s[], int n) {
    if (n == 0) {
        cout << "\nNo student records to search!\n";
        return;
    }

    string rollSearch;
    cout << "\nEnter Roll Number to Search: ";
    cin >> rollSearch;

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (s[i].roll == rollSearch) {
            found = true;
            cout << "\n===== STUDENT FOUND =====\n";
            cout << "Name: " << s[i].name << "\n";
            cout << "Roll No: " << s[i].roll << "\n";

            cout << "\nMarks (out of 20):\n";
            for (int j = 0; j < SUBJECTS; j++)
                cout << subjectNames[j] << ": " << s[i].marks[j] << "\n";

            float total = 0;
            for (int j = 0; j < SUBJECTS; j++)
                total += s[i].marks[j];

            float avg = total / SUBJECTS;
            float avgPercent = (avg / 20) * 100;
            char grade = calculateGrade(avgPercent);

            float attendance = 0;
            if (s[i].totalClasses > 0)
                attendance = (s[i].attendedClasses * 100.0) / s[i].totalClasses;

            cout << "\nAverage Marks: " << avg << " / 20\n";
            cout << "Percentage: " << avgPercent << "%\n";
            cout << "Grade: " << grade << "\n";
            cout << "Attendance: " << attendance << "%\n";

            if (attendance < 75)
                cout << "Warning: Attendance below 75%!\n";
            break;
        }
    }

    if (!found)
        cout << "\nStudent not found!\n";
}

// Grade calculation
char calculateGrade(float percent) {
    if (percent >= 90) return 'A';
    else if (percent >= 75) return 'B';
    else if (percent >= 60) return 'C';
    else if (percent >= 40) return 'D';
    else return 'F';
}