#include <fstream>
#include "student.h"
#include "LMS.h"
#include <sstream>

using namespace std;

Student::Student() {}

Student::Student(string theCode, string theName, int theAge, char theGender) : code(theCode), name(theName),
                                                                               gender(theGender), age(theAge) {
    Student::code = theCode;
    Student::name = theName;
    Student::age = theAge;
    Student::gender = theGender;
}

Student::Student(string theCode, int mathGrade, int phyGrade, int drawingGrade, int computerGrade, int chemGrade)
        : code(theCode), math_grade(
        mathGrade), phy_grade(phyGrade), drawing_grade(drawingGrade), computer_grade(computerGrade), chem_grade(
        chemGrade) {

    Student::code = theCode;
    Student::math_grade = mathGrade;
    Student::phy_grade = phyGrade;
    Student::drawing_grade = drawingGrade;
    Student::computer_grade = computerGrade;
    Student::chem_grade = chemGrade;
}

Student::Student(string code, string math_Gpa, string phy_Gpa, string draw_Gpa, string comp_Gpa,
                 string chem_Gpa) : code(code), mathGPA(math_Gpa), phyGPA(phy_Gpa), drawGPA(draw_Gpa),
                                    compGPA(comp_Gpa),
                                    chemGPA(chem_Gpa) {
    Student::code = code;
    Student::mathGPA = math_Gpa;
    Student::phyGPA = phy_Gpa;
    Student::drawGPA = draw_Gpa;
    Student::compGPA = comp_Gpa;
    Student::chemGPA = chem_Gpa;
}

string Student::getCode() {
    return code;
}

string Student::getName() {
    return name;
}

int Student::getAge() {
    return age;
}

char Student::getGender() {
    return gender;
}

int Student::getMathGrade() {
    return math_grade;
}

int Student::getPhyGrade() {
    return phy_grade;
}

int Student::getDrawingGrade() {
    return drawing_grade;
}

int Student::getComputerGrade() {
    return computer_grade;
}

int Student::getChemGrade() {
    return chem_grade;
}

string Student::getMathGpa() {
    return mathGPA;
}

string Student::getPhyGpa() {
    return phyGPA;
}

string Student::getDrawGpa() {
    return drawGPA;
}

string Student::getCompGpa() {
    return compGPA;
}

string Student::getChemGpa() {
    return chemGPA;
}

void Student::setMathGrade(int mathGrade) {
    math_grade = mathGrade;
}

void Student::setPhyGrade(int phyGrade) {
    phy_grade = phyGrade;
}

void Student::setDrawingGrade(int drawingGrade) {
    drawing_grade = drawingGrade;
}

void Student::setComputerGrade(int computerGrade) {
    computer_grade = computerGrade;
}

void Student::setChemGrade(int chemGrade) {
    chem_grade = chemGrade;
}


void Student::add_new_student(Student newStudent) {
    fstream file;
    file.open(data_file, ios_base::app);
    LMS lms;
    if (lms.is_file_exists(data_file)) {
        file << newStudent.getCode() << "," << newStudent.getName() << "," << newStudent.getAge() << ","
             << newStudent.getGender() << "\n";
    } else {
        cout << "Error, File doesn't exist" << endl;
    }

    file.close();
}

void Student::add_new_grade(Student newStudent) {
    fstream file;
    file.open(grades_file, ios_base::app);
    LMS lms;
    if (lms.is_file_exists(grades_file)) {
        file << newStudent.getCode() << "," << newStudent.getMathGrade() << "," << newStudent.getPhyGrade() << ","
             << newStudent.getDrawingGrade() << "," << newStudent.getComputerGrade() << "," << newStudent.getChemGrade()
             << "\n";
    } else {
        cout << "Error, File doesn't exist" << endl;
    }

    file.close();
}

void
Student::update_student_grades(string code, int math_grade, int phy_grade, int drawing_grade, int computer_grade,
                               int chemistry_grade) {
    vector<Student> student_v = read_all_grades();
    for (int i = 0; i < student_v.size(); i++) {
        if (student_v[i].getCode() == code) {
            student_v[i].setMathGrade(math_grade);
            student_v[i].setPhyGrade(phy_grade);
            student_v[i].setDrawingGrade(drawing_grade);
            student_v[i].setComputerGrade(computer_grade);
            student_v[i].setChemGrade(chemistry_grade);
        }
    }

    save_updated_grades(student_v);

}

void Student::save_updated_grades(vector<Student> student) {
    ofstream file;
    file.open(grades_file, ios::out);
    file << "student code,Math,Physics ,Drawing,Computer ,Chemistry " << endl;
    for (int i = 0; i < student.size(); i++) {
        file << student[i].getCode() << "," << student[i].getMathGrade() << "," << student[i].getPhyGrade() << ","
             << student[i].getDrawingGrade() << "," << student[i].getComputerGrade() << ","
             << student[i].getChemGrade()
             << endl;
    }
    file.close();
}

vector<Student> Student::read_all_grades() {
    ifstream file;
    file.open(grades_file);
    vector<Student> vector;
    string line;
    string word;

    getline(file, line);//to ignore the first line in the file
    int n = 0;
    string code, math, phy, draw, comp, chem;
    while (getline(file, line)) {
        stringstream s(line);
        while (getline(s, word, ',')) {
            switch (n) {
                case 0:
                    code = word;
                    n++;
                    break;
                case 1:
                    math = word;
                    n++;
                    break;
                case 2:
                    phy = word;
                    n++;
                    break;
                case 3:
                    draw = word;
                    n++;
                    break;
                case 4:
                    comp = word;
                    n++;
                    break;
                case 5:
                    chem = word;
                    Student newStudent(code, atoi(math.c_str()), atoi(phy.c_str()), atoi(draw.c_str()),
                                       atoi(comp.c_str()), atoi(chem.c_str()));
                    vector.push_back(newStudent);
                    n = 0;
                    break;
            }
        }
    }
    file.close();
    return vector;
}

vector<Student> Student::read_all_students() {
    ifstream file;
    file.open(data_file);
    vector<Student> vector;
    string line;
    string word;

    getline(file, line);//to ignore the first line in the file
    int n = 0;
    string code, name, age, gender;
    while (getline(file, line)) {
        stringstream s(line);
        while (getline(s, word, ',')) {
            switch (n) {
                case 0:
                    code = word;
                    n++;
                    break;
                case 1:
                    name = word;
                    n++;
                    break;
                case 2:
                    age = word;
                    n++;
                    break;
                case 3:
                    gender = word;
                    Student newStudent(code, name, atoi(age.c_str()), gender[0]);
                    vector.push_back(newStudent);
                    n = 0;
                    break;
            }
        }
    }
    file.close();
    return vector;
}
