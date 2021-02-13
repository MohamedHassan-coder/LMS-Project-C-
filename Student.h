#ifndef LMS_STUDENT_H
#define LMS_STUDENT_H

#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Student {
private:

    string code, name;
    char gender;
    int age;
    int math_grade, phy_grade, drawing_grade, computer_grade, chem_grade;
    string data_file = "studentsData.csv";
    string grades_file = "studentsGrade.csv";

    string mathGPA, phyGPA, drawGPA, compGPA, chemGPA;


    //setters for the grades.
    void setMathGrade(int mathGrade);

    void setPhyGrade(int phyGrade);

    void setDrawingGrade(int drawingGrade);

    void setComputerGrade(int computerGrade);

    void setChemGrade(int chemGrade);

    //save the file after updating the grades (related to _update_student_grades_ method)
    void save_updated_grades(vector<Student> student);

public:
    Student();

    Student(string theCode, string theName, int theAge, char theGender);

    Student(string theCode, int mathGrade, int phyGrade, int drawingGrade, int computerGrade, int chemGrade);

    Student(string code, string math_Gpa, string phy_Gpa, string draw_Gpa, string comp_Gpa,
            string chem_Gpa);

    string getCode();

    string getName();

    int getAge();

    char getGender();

    int getMathGrade();

    int getPhyGrade();

    int getDrawingGrade();

    int getComputerGrade();

    int getChemGrade();

    string getMathGpa();

    string getPhyGpa();

    string getDrawGpa();

    string getCompGpa();

    string getChemGpa();

    void add_new_student(Student newStudent);

    void add_new_grade(Student newStudent);


    //update the student grades by rewriting the file again with the new values
    void update_student_grades(string code, int math_grade, int phy_grade, int drawing_grade, int computer_grade,
                               int chemistry_grade);

    //this method is used to get all grades from the grades file and store it into a vector then return it.
    //note: remember to make one for the data
    vector<Student> read_all_grades();

    vector<Student> read_all_students();

};
#endif //LMS_STUDENT_H

