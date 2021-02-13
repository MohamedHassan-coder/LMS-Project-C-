#include <iostream>
#include <vector>
#include "LMS.h"


static void list_of_operations();

void proceed(int choice);

void import_export_data();

void import_export_grades();

void modify_grades();

void another_operation();

LMS L_M_S;
bool another = true;

int main() {
    list_of_operations();

    while (another) {
        another_operation();
    }

    return 0;
}

//list all operations to choose between.
void list_of_operations() {
    int choice;
    cout << "Welcome to LMS, please choose an operation number to proceed.(Enter a character to exit)" << endl;
    cout << "\t1- Import/export student data..." << endl;
    cout << "\t2- Import/export student grades..." << endl;
    cout << "\t3- Modify..." << endl;
    cin >> choice;
    if (!cin.fail()) {
        proceed(choice);
    } else {
        cout << "Exiting..." << endl;
    }
}

//direct the user to a method based on his choice on (list_of_operations())
void proceed(int choice) {
    switch (choice) {
        case 1:
            import_export_data();
            break;
        case 2:
            import_export_grades();
            break;
        case 3:
            modify_grades();
            break;
        default:
            int c;
            list_of_operations();
            cin >> c;
            if (!cin.fail()) {
                proceed(c);
            } else {
                break;
            }
    }
}

void import_export_data() {
    int choice;
    cout << "\t1- Import a new student data..." << endl;
    cout << "\t2- Export a student data..." << endl;
    cout << "\t3- Export all students data..." << endl;
    cin >> choice;
    if (cin.fail()) {
        cout << "Exiting..." << endl;
        exit(-1);
    } else {
        switch (choice) {
            case 1:
                L_M_S.import_new_student();
                break;
            case 2:
                L_M_S.export_data();
                break;
            case 3:
                L_M_S.export_all_students();
                break;
            default:
                cout << "Wrong choice, please try again." << endl;
                import_export_data();
        }
    }

}

void import_export_grades() {
    int choice;
    cout << "\t1- Import a new student grades..." << endl;
    cout << "\t2- Export a student grades..." << endl;
    cout << "\t3- Export all students grades..." << endl;
    cin >> choice;
    if (cin.fail()) {
        cout << "Exiting..." << endl;
        exit(-1);
    } else {
        switch (choice) {
            case 1:
                L_M_S.import_new_student_grade();
                break;
            case 2:
                L_M_S.export_grades();
                break;
            case 3:
                L_M_S.export_all_grades();
                break;
            default:
                cout << "Wrong choice, please try again." << endl;
                import_export_data();
        }
    }
}

void modify_grades() {
    int choice;
    cout << "\t1- Normalize..." << endl;
    cout << "\t2- Edit a student grades..." << endl;
    cout << "\t3- Export GPA grades..." << endl;
    cout << "\t4- Statistics..." << endl;
    cout << "\t5- Print a student data and grades..." << endl;
    cin >> choice;
    if (cin.fail()) {
        cout << "Exiting..." << endl;
        exit(-1);
    } else {
        switch (choice) {
            case 1:
                L_M_S.normalize();
                break;
            case 2:
                L_M_S.edit_student_grades();
                break;
            case 3:
                L_M_S.export_all_GPAs();
                break;
            case 4:
                L_M_S.statistics();
                break;
            case 5:
                L_M_S.print_data_grades();
                break;
            default:
                cout << "Wrong choice, please try again." << endl;
                modify_grades();
        }
    }
}

void another_operation() {
    char choice;
    cout << "\n";
    cout << "Do you want to do another operation?(Y/N)" << endl;
    cin >> choice;
    if (!cin.fail()) {
        if (tolower(choice) == 'y') {
            list_of_operations();
        } else if (tolower(choice) == 'n') {
            another = false;
            exit(0);
        }
    } else {
        another = false;
        cout << "Exiting..." << endl;
    }
}
