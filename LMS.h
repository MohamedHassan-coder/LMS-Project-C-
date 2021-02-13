#ifndef LMS_LMS_H
#define LMS_LMS_H

#include <string>
#include <iostream>
#include <vector>
#include "Student.h"
#include <math.h>

using namespace std;

class LMS {

private:
    string data_file = "studentsData.csv";
    string grades_file = "studentsGrade.csv";
    string GPAs_file = "studentsGPA.csv";
    string normalized_grades = "studentsNormalizedGrades.csv";

    //Private methods:

//true --> student exist;
//false --> student not exist
    bool is_student_exist_data_file(string code);

//true --> student exist;
//false --> student not exist
    bool is_student_exist_grades_file(string code);

//this method is used to set default values for a student grades if it's not entered
//this method is related to (_export_new_student_) method
    void continue_adding_new_student(string code);

//over-loaded method for export new student grade;
//this is made to not ask for the grade if i came from adding new student data
    void import_new_student_grade(string code);

//true --> input data are valid
//false --> input data are not valid
    bool check_input_data(string code, string name, int age, char gender);

//true --> input data are valid
//false --> input data are not valid
    bool check_input_grades(int math_grade, int phy_grade, int drawing_grade, int computer_grade,
                            int chem_grade);

//read a student data from the file and return it in a vector
//if the student not exist then the vector will be empty;
    vector<string> get_data(string code);

//read a student grades from the file and return it in a vector
    vector<string> get_grades(string code);

//read all students grades and return it's suitable GPA
    vector<Student> GPAs(vector<Student> students_grades);

//convert the student grade to GPA
    string grades_to_GPA(int grade);

//write the GPA file corresponding to the grades
    void set_GPAs();

//get the statistics for all subjects.
    void math_statistics();

    void physics_statistics();

    void drawing_statistics();

    void computer_statistics();

    void chemistry_statistics();

// returns the normalized math degrees
    vector<float> normalized_math();

// returns the normalized physics degrees
    vector<float> normalized_phy();

// returns the normalized drawing degrees
    vector<float> normalized_draw();

// returns the normalized computer degrees
    vector<float> normalized_comp();

// returns the normalized chemistry degrees
    vector<float> normalized_chem();

// calculate the sum of a (int) vector
    int vector_sum(vector<int> data);

// over-loaded method to vector_sum but with float instead of integers
    float vector_sum(vector<float> data);

    vector<float> x_mu(vector<int> data, float mu);

    vector<float> x_mu_sq(vector<float> x_mu);


public:

    LMS();

//check if the file exists
//true --> file exists
//false --> file not exists
    bool is_file_exists(string file_name);

    void export_data();

//when adding new student data --> adding a new student grade to with default grades 0;
//export new student.
    void import_new_student();

    void export_grades();

    void import_new_student_grade();

    void edit_student_grades();

    void export_all_students();

    void export_all_grades();

    void export_all_GPAs();

    void statistics();

    void normalize();

    void print_data_grades();
};

#endif //LMS_LMS_H
