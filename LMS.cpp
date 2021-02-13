#include "LMS.h"
#include <string>
#include <vector>
#include <fstream>
#include "Student.h"

using namespace std;

LMS::LMS() = default;

bool LMS::is_file_exists(string file_name) {
    ifstream file;
    file.open(file_name);
    if (file.is_open()) {
        file.close();
        return true;
    } else {
        return false;
    }
}

bool LMS::is_student_exist_data_file(string code) {
    if (get_data(code).empty()) {
        return false;
    } else {
        return true;
    }
}

bool LMS::is_student_exist_grades_file(string code) {
    if (get_grades(code).empty()) {
        return false;
    } else {
        return true;
    }
}

vector<string> LMS::get_data(string code) {
    vector<string> record;
    //4-fields for: code ,name ,age ,gender.
    string field_1, field_2, field_3, field_4;

    ifstream file;
    file.open(data_file);

    bool field_found = false;

    while (!field_found && getline(file, field_1, ',')) {

        getline(file, field_2, ',');
        getline(file, field_3, ',');
        getline(file, field_4, '\n');

        if (field_1 == code) {
            field_found = true;
            record.push_back(field_1);
            record.push_back(field_2);
            record.push_back(field_3);
            record.push_back(field_4);
        }
    }
    file.close();
    return record;
}

vector<string> LMS::get_grades(string code) {
    vector<string> record;
    //6-fields for: code ,math_grade ,phy_grade ,draw_grade,com_grade,chem_grade.
    string field_1, field_2, field_3, field_4, field_5, field_6;

    ifstream file;
    file.open(grades_file);

    bool field_found = false;

    while (!field_found && getline(file, field_1, ',')) {
        getline(file, field_2, ',');
        getline(file, field_3, ',');
        getline(file, field_4, ',');
        getline(file, field_5, ',');
        getline(file, field_6, '\n');

        if (field_1 == code) {
            field_found = true;
            record.push_back(field_1);
            record.push_back(field_2);
            record.push_back(field_3);
            record.push_back(field_4);
            record.push_back(field_5);
            record.push_back(field_6);
        }
    }
    file.close();
    return record;
}

void LMS::export_data() {
    if (is_file_exists(data_file)) {
        ifstream file;
        file.open(data_file);
        string code;
        cout << "Enter the student ID..." << endl;
        cin >> code;
        cout << endl;
        if (is_student_exist_data_file(code)) {
            vector<string> data = get_data(code);
            cout << "\t\tStudent data\n" << "\t\t------------" << endl;
            cout << "\tCode: " << data[0] << endl;
            cout << "\tName: " << data[1] << endl;
            cout << "\tAge: " << data[2] << endl;
            cout << "\tGender: " << data[3] << endl;
        } else {
            cout << "student not found, try another code..." << endl;
            export_data();
        }
        file.close();
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

void LMS::import_new_student() {
    string code, name;
    int age;
    char gender;
    if (is_file_exists(data_file)) {
        cout << "Enter the data of the new student..." << endl;
        cout << "Code:";
        cin >> code;
        cout << endl;
        if (!is_student_exist_data_file(code)) {
            cout << "\t\tAdd new student" << endl;
            cout << "\t\t---------------" << endl;
            cout << "\tCode:" << code << endl;
            cout << "\tName:";
            getline(cin >> ws, name);
            cout << "        Age:";
            cin >> age;
            cout << "\t Gender:";
            cin >> gender;
            if (check_input_data(code, name, age, gender)) {
                Student newStudent_data(code, name, age, gender);
                newStudent_data.add_new_student(newStudent_data);
                continue_adding_new_student(code);
            } else {
                cout << "Error, Please check the validity of the inputs..." << endl;
                import_new_student();
            }
        } else {
            cout << "Student already exists, try again..." << endl;
            import_new_student();
        }
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

bool LMS::check_input_data(string code, string name, int age, char gender) {
    bool code_check = code.empty();
    bool name_check = name.empty();
    bool age_check = (age <= 0);
    bool gender_check = tolower(gender) == 'm' || tolower(gender) == 'f';
    if (!code_check && !name_check && !age_check && gender_check) {
        return true;
    }
    return false;
}

bool LMS::check_input_grades(int math_grade, int phy_grade, int drawing_grade, int computer_grade,
                             int chem_grade) {

    bool math_check = math_grade >= 0 && math_grade <= 100;
    bool phy_check = phy_grade >= 0 && phy_grade <= 100;
    bool draw_check = drawing_grade >= 0 && drawing_grade <= 100;
    bool comp_check = computer_grade >= 0 && computer_grade <= 100;
    bool chem_check = chem_grade >= 0 && chem_grade <= 100;

    if (math_check && phy_check && draw_check && comp_check && chem_check) {
        return true;
    }
    return false;
}

void LMS::export_grades() {
    if (is_file_exists(grades_file)) {
        string code;
        ifstream file;
        cout << "Enter the student ID..." << endl;
        cout << "Code:";
        cin >> code;
        cout << endl;
        file.open(grades_file);
        if (is_student_exist_data_file(code)) {
            vector<string> data = get_grades(code);
            cout << "\t\tStudent grades\n" << "\t\t--------------" << endl;
            cout << "\tCode: " << data[0] << endl;
            cout << "\tMath: " << data[1] << endl;
            cout << "\tPhysics: " << data[2] << endl;
            cout << "\tDrawing: " << data[3] << endl;
            cout << "\tComputer: " << data[4] << endl;
            cout << "\tChemistry: " << data[5] << endl;
        } else {
            cout << "student not found, try another code..." << endl;
            export_grades();
        }

        file.close();
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

void LMS::import_new_student_grade() {
    string code;
    int math, phy, drawing, computer, chem;
    if (is_file_exists(grades_file)) {
        cout << "Enter the Code of the new student..." << endl;
        cout << "Code:";
        cin >> code;
        cout << endl;
        if (is_student_exist_data_file(code)) {
            vector<string> data = get_grades(code);
            if (!is_student_exist_grades_file(code)) {
                cout << "\t\tAdd new student grades" << endl;
                cout << "\t\t----------------------" << endl;
                cout << "\tCode:" << code << endl;
                cout << "\tMath grade:";
                cin >> math;
                cout << "        Physics grade:";
                cin >> phy;
                cout << "        Drawing grade:";
                cin >> drawing;
                cout << "        Computer grade:";
                cin >> computer;
                cout << "        Chemistry grade:";
                cin >> chem;
                if (check_input_grades(math, phy, drawing, computer, chem)) {
                    Student st(code, math, phy, drawing, computer, chem);
                    st.add_new_grade(st);
                    set_GPAs();
                    normalize();
                } else {
                    cout << "Error, Please check the validity of the inputs..." << endl;
                    import_new_student_grade();
                }
            } else {
                cout << "Student already exist and has grades, Do you mean modify student grades?" << endl;
                edit_student_grades();
            }
        } else {
            cout << "There is no data for this student, Please add data for this student first..." << endl;
            LMS::import_new_student();
        }

    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

void LMS::import_new_student_grade(string code) {
    int math, phy, drawing, computer, chem;
    if (is_file_exists(grades_file)) {
        cout << "\t\tAdd new student grades" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "\tCode:" << code << endl;
        cout << "\tMath grade:";
        cin >> math;
        cout << "        Physics grade:";
        cin >> phy;
        cout << "        Drawing grade:";
        cin >> drawing;
        cout << "        Computer grade:";
        cin >> computer;
        cout << "        Chemistry grade:";
        cin >> chem;
        if (check_input_grades(math, phy, drawing, computer, chem)) {
            Student newStudent(code, math, phy, drawing, computer, chem);
            newStudent.add_new_grade(newStudent);
            set_GPAs();
            normalize();
        } else {
            cout << "\n";
            cout << "Error, Please check the validity of the inputs..." << endl;
            import_new_student_grade(code);
        }
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

void LMS::continue_adding_new_student(string code) {
    char choice;
    cout << "Do you want to add grades for this student?(Y/N)" << endl;
    cin >> choice;
    if (tolower(choice) == 'y') {
        import_new_student_grade(code);
    }
}

void LMS::edit_student_grades() {
    string code;
    int math, phy, draw, computer, chem;
    Student newStudent;
    cout << "Enter the code of the student..." << endl;
    cout << "Code:";
    cin >> code;
    cout << "\n";
    vector<string> old_student_grades = get_grades(grades_file);
    if (is_student_exist_data_file(code)) {
        cout << "\t\tEdit a student grades" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "\tCode:" << code << endl;
        cout << "\tMath grade:";
        cin >> math;
        cout << "        Physics grade:";
        cin >> phy;
        cout << "        Drawing grade:";
        cin >> draw;
        cout << "        Computer grade:";
        cin >> computer;
        cout << "        Chemistry grade:";
        cin >> chem;
        if (check_input_grades(math, phy, draw, computer, chem)) {
            newStudent.update_student_grades(code, math, phy, draw, computer, chem);
            set_GPAs();
            normalized_math();
        } else {
            cout << "Input grades are not valid, please try again..." << endl;
            edit_student_grades();
        }
    } else {
        cout << "Student is not existed, try again..." << endl;
        edit_student_grades();
    }

}

void LMS::export_all_students() {
    Student student;
    if (is_file_exists(data_file)) {
        vector<Student> students_data = student.read_all_students();
        for (int i = 0; i < students_data.size(); i++) {
            cout << "Student No:" << i + 1 << endl;
            cout << "\tName:" << students_data[i].getName() << endl;
            cout << "\tCode:" << students_data[i].getCode() << endl;
            cout << "\tAge:" << students_data[i].getAge() << endl;
            cout << "\tGender:" << students_data[i].getGender() << endl;
            cout << "----------------------" << endl;
        }
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

void LMS::export_all_grades() {
    Student student;
    if (is_file_exists(grades_file)) {
        vector<Student> students_data = student.read_all_grades();
        for (int i = 0; i < students_data.size(); i++) {
            cout << "Student No:" << i + 1 << endl;
            cout << "\tCode:" << students_data[i].getCode() << endl;
            cout << "\tMath grade:" << students_data[i].getMathGrade() << endl;
            cout << "\tPhysics grade:" << students_data[i].getPhyGrade() << endl;
            cout << "\tDrawing grade:" << students_data[i].getDrawingGrade() << endl;
            cout << "\tComputer grade:" << students_data[i].getComputerGrade() << endl;
            cout << "\tChemistry grade:" << students_data[i].getChemGrade() << endl;
            cout << "----------------------" << endl;
        }
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

string LMS::grades_to_GPA(int grade) {
    if (grade >= 90) {
        return "A";
    } else if (grade >= 85 && grade < 90) {
        return "B+";
    } else if (grade >= 80 && grade < 85) {
        return "B";
    } else if (grade >= 75 && grade < 80) {
        return "C+";
    } else if (grade >= 70 && grade < 75) {
        return "C";
    } else if (grade >= 65 && grade < 70) {
        return "D+";
    } else if (grade >= 60 && grade < 65) {
        return "D";
    } else {
        return "F";
    }
}

vector<Student> LMS::GPAs(vector<Student> students_grades) {
    vector<Student> vector;
    string code, mathGPA, phyGPA, drawGPA, compGPA, chemGPA;

    for (int i = 0; i < students_grades.size(); i++) {
        code = students_grades[i].getCode();
        mathGPA = grades_to_GPA(students_grades[i].getMathGrade());
        phyGPA = grades_to_GPA(students_grades[i].getPhyGrade());
        drawGPA = grades_to_GPA(students_grades[i].getDrawingGrade());
        compGPA = grades_to_GPA(students_grades[i].getComputerGrade());
        chemGPA = grades_to_GPA(students_grades[i].getChemGrade());
        vector.push_back(Student(code, mathGPA, phyGPA, drawGPA, compGPA, chemGPA));
    }

    return vector;
}

void LMS::set_GPAs() {
    Student student;
    vector<Student> vector = GPAs(student.read_all_grades());
    ofstream file;
    file.open(GPAs_file, ios::out);
    file << "student code,Math GPA,Physics GPA,Drawing GPA,Computer GPA,Chemistry GPA " << endl;
    for (int i = 0; i < vector.size(); i++) {
        file << vector[i].getCode() << "," << vector[i].getMathGpa() << "," << vector[i].getPhyGpa() << ","
             << vector[i].getDrawGpa() << "," << vector[i].getCompGpa() << ","
             << vector[i].getChemGpa()
             << endl;
    }
    file.close();
}

void LMS::export_all_GPAs() {

    Student student;
    if (is_file_exists(GPAs_file)) {
        vector<Student> vector = GPAs(student.read_all_grades());
        for (int i = 0; i < vector.size(); i++) {
            cout << "Student No:" << i + 1 << endl;
            cout << "\tCode:" << vector[i].getCode() << endl;
            cout << "\tMath GPA:" << vector[i].getMathGpa() << endl;
            cout << "\tPhysics GPA:" << vector[i].getPhyGpa() << endl;
            cout << "\tDrawing GPA:" << vector[i].getDrawGpa() << endl;
            cout << "\tComputer GPA:" << vector[i].getCompGpa() << endl;
            cout << "\tChemistry GPA:" << vector[i].getChemGpa() << endl;
            cout << "----------------------" << endl;
        }
    } else {
        cout << "Error, File doesn't exist" << endl;
    }

}

void LMS::math_statistics() {
    Student student;
    vector<Student> students_GPAs = GPAs(student.read_all_grades());
    int students_num = students_GPAs.size();
    float array[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //[A,B+,B,C+,C,D+,D,F]
    float statistics[8] = {0, 0, 0, 0, 0, 0, 0, 0};


    for (int i = 0; i < students_num; i++) {
        string gpa = students_GPAs[i].getMathGpa();
        if (gpa == "A") {
            array[0]++;
        } else if (gpa == "B+") {
            array[1]++;
        } else if (gpa == "B") {
            array[2]++;
        } else if (gpa == "C+") {
            array[3]++;
        } else if (gpa == "C") {
            array[4]++;
        } else if (gpa == "D+") {
            array[5]++;
        } else if (gpa == "D") {
            array[6]++;
        } else if (gpa == "F") {
            array[7]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        statistics[i] = (array[i] / (float) students_num) * 100;
    }
    cout.precision(3);
    cout << statistics[0] << "% of the students got A" << endl;
    cout << statistics[1] << "% of the students got B+" << endl;
    cout << statistics[2] << "% of the students got B" << endl;
    cout << statistics[3] << "% of the students got C+" << endl;
    cout << statistics[4] << "% of the students got C" << endl;
    cout << statistics[5] << "% of the students got D+" << endl;
    cout << statistics[6] << "% of the students got D" << endl;
    cout << statistics[7] << "% of the students got F" << endl;
}

void LMS::physics_statistics() {
    Student student;
    vector<Student> students_GPAs = GPAs(student.read_all_grades());
    int students_num = students_GPAs.size();
    float array[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //[A,B+,B,C+,C,D+,D,F]
    float statistics[8] = {0, 0, 0, 0, 0, 0, 0, 0};


    for (int i = 0; i < students_num; i++) {
        string gpa = students_GPAs[i].getPhyGpa();
        if (gpa == "A") {
            array[0]++;
        } else if (gpa == "B+") {
            array[1]++;
        } else if (gpa == "B") {
            array[2]++;
        } else if (gpa == "C+") {
            array[3]++;
        } else if (gpa == "C") {
            array[4]++;
        } else if (gpa == "D+") {
            array[5]++;
        } else if (gpa == "D") {
            array[6]++;
        } else if (gpa == "F") {
            array[7]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        statistics[i] = (array[i] / (float) students_num) * 100;
    }

    cout.precision(3);
    cout << statistics[0] << "% of the students got A" << endl;
    cout << statistics[1] << "% of the students got B+" << endl;
    cout << statistics[2] << "% of the students got B" << endl;
    cout << statistics[3] << "% of the students got C+" << endl;
    cout << statistics[4] << "% of the students got C" << endl;
    cout << statistics[5] << "% of the students got D+" << endl;
    cout << statistics[6] << "% of the students got D" << endl;
    cout << statistics[7] << "% of the students got F" << endl;

}

void LMS::drawing_statistics() {
    Student student;
    vector<Student> students_GPAs = GPAs(student.read_all_grades());
    int students_num = students_GPAs.size();
    float array[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //[A,B+,B,C+,C,D+,D,F]
    float statistics[8] = {0, 0, 0, 0, 0, 0, 0, 0};


    for (int i = 0; i < students_num; i++) {
        string gpa = students_GPAs[i].getDrawGpa();
        if (gpa == "A") {
            array[0]++;
        } else if (gpa == "B+") {
            array[1]++;
        } else if (gpa == "B") {
            array[2]++;
        } else if (gpa == "C+") {
            array[3]++;
        } else if (gpa == "C") {
            array[4]++;
        } else if (gpa == "D+") {
            array[5]++;
        } else if (gpa == "D") {
            array[6]++;
        } else if (gpa == "F") {
            array[7]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        statistics[i] = (array[i] / (float) students_num) * 100;
    }

    cout.precision(3);
    cout << statistics[0] << "% of the students got A" << endl;
    cout << statistics[1] << "% of the students got B+" << endl;
    cout << statistics[2] << "% of the students got B" << endl;
    cout << statistics[3] << "% of the students got C+" << endl;
    cout << statistics[4] << "% of the students got C" << endl;
    cout << statistics[5] << "% of the students got D+" << endl;
    cout << statistics[6] << "% of the students got D" << endl;
    cout << statistics[7] << "% of the students got F" << endl;

}

void LMS::computer_statistics() {
    Student student;
    vector<Student> students_GPAs = GPAs(student.read_all_grades());
    int students_num = students_GPAs.size();
    float array[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //[A,B+,B,C+,C,D+,D,F]
    float statistics[8] = {0, 0, 0, 0, 0, 0, 0, 0};


    for (int i = 0; i < students_num; i++) {
        string gpa = students_GPAs[i].getCompGpa();
        if (gpa == "A") {
            array[0]++;
        } else if (gpa == "B+") {
            array[1]++;
        } else if (gpa == "B") {
            array[2]++;
        } else if (gpa == "C+") {
            array[3]++;
        } else if (gpa == "C") {
            array[4]++;
        } else if (gpa == "D+") {
            array[5]++;
        } else if (gpa == "D") {
            array[6]++;
        } else if (gpa == "F") {
            array[7]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        statistics[i] = (array[i] / (float) students_num) * 100;
    }

    cout.precision(3);
    cout << statistics[0] << "% of the students got A" << endl;
    cout << statistics[1] << "% of the students got B+" << endl;
    cout << statistics[2] << "% of the students got B" << endl;
    cout << statistics[3] << "% of the students got C+" << endl;
    cout << statistics[4] << "% of the students got C" << endl;
    cout << statistics[5] << "% of the students got D+" << endl;
    cout << statistics[6] << "% of the students got D" << endl;
    cout << statistics[7] << "% of the students got F" << endl;

}

void LMS::chemistry_statistics() {
    Student student;
    vector<Student> students_GPAs = GPAs(student.read_all_grades());
    int students_num = students_GPAs.size();
    float array[8] = {0, 0, 0, 0, 0, 0, 0, 0}; //[A,B+,B,C+,C,D+,D,F]
    float statistics[8] = {0, 0, 0, 0, 0, 0, 0, 0};


    for (int i = 0; i < students_num; i++) {
        string gpa = students_GPAs[i].getChemGpa();
        if (gpa == "A") {
            array[0]++;
        } else if (gpa == "B+") {
            array[1]++;
        } else if (gpa == "B") {
            array[2]++;
        } else if (gpa == "C+") {
            array[3]++;
        } else if (gpa == "C") {
            array[4]++;
        } else if (gpa == "D+") {
            array[5]++;
        } else if (gpa == "D") {
            array[6]++;
        } else if (gpa == "F") {
            array[7]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        statistics[i] = (array[i] / (float) students_num) * 100;
    }

    cout.precision(3);
    cout << statistics[0] << "% of the students got A" << endl;
    cout << statistics[1] << "% of the students got B+" << endl;
    cout << statistics[2] << "% of the students got B" << endl;
    cout << statistics[3] << "% of the students got C+" << endl;
    cout << statistics[4] << "% of the students got C" << endl;
    cout << statistics[5] << "% of the students got D+" << endl;
    cout << statistics[6] << "% of the students got D" << endl;
    cout << statistics[7] << "% of the students got F" << endl;

}

void LMS::statistics() {

    cout << "\t\tMath" << endl;
    cout << "\t\t----" << endl;
    math_statistics();
    cout << "\n";
    cout << "\t\tPhysics" << endl;
    cout << "\t\t-------" << endl;
    physics_statistics();
    cout << "\n";
    cout << "\t\tDrawing" << endl;
    cout << "\t\t-------" << endl;
    drawing_statistics();
    cout << "\n";
    cout << "\t\tComputer" << endl;
    cout << "\t\t--------" << endl;
    computer_statistics();
    cout << "\n";
    cout << "\t\tChemistry" << endl;
    cout << "\t\t---------" << endl;
    chemistry_statistics();
    cout << "\n";

}

void LMS::normalize() {
    ofstream file;
    Student student;
    vector<Student> students_grades = student.read_all_grades();

    if (is_file_exists(normalized_grades)) {
        file.open(normalized_grades, ios::out);
        vector<float> math = normalized_math();
        vector<float> physics = normalized_phy();
        vector<float> drawing = normalized_draw();
        vector<float> computer = normalized_comp();
        vector<float> chemistry = normalized_chem();
        file << "student code,Math,Physics,Drawing,Computer,Chemistry " << endl;
        for (int i = 0; i < math.size(); i++) {
            file << students_grades[i].getCode() << "," << math[i] << "," << physics[i] << ","
                 << drawing[i] << "," << drawing[i] << "," << computer[i] << ","
                 << chemistry[i] << endl;
        }

        file.close();
    } else {
        cout << "Error, File doesn't exist" << endl;
    }
}

vector<float> LMS::normalized_math() {
    Student student;
    vector<float> normalized_grades;
    vector<Student> students_grades = student.read_all_grades();
    vector<int> math_grades;
    float n = students_grades.size(); // number of the students
    for (int i = 0; i < n; i++) {
        math_grades.push_back(students_grades[i].getMathGrade());
    }
    float muo = (float) vector_sum(math_grades) / n;

    float sigma = sqrt(vector_sum(x_mu_sq(x_mu(math_grades, muo))) / n);

    for (int i = 0; i < n; ++i) {
        normalized_grades.push_back(((float) math_grades[i] - muo) / sigma);
    }

    return normalized_grades;
}

vector<float> LMS::normalized_phy() {
    Student student;
    vector<float> normalized_grades;
    vector<Student> students_grades = student.read_all_grades();
    vector<int> phy_grades;
    float n = students_grades.size(); // number of the students
    for (int i = 0; i < n; i++) {
        phy_grades.push_back(students_grades[i].getPhyGrade());
    }
    float muo = (float) vector_sum(phy_grades) / n;

    float sigma = sqrt(vector_sum(x_mu_sq(x_mu(phy_grades, muo))) / n);

    for (int i = 0; i < n; ++i) {
        normalized_grades.push_back(((float) phy_grades[i] - muo) / sigma);
    }

    return normalized_grades;
}

vector<float> LMS::normalized_draw() {
    Student student;
    vector<float> normalized_grades;
    vector<Student> students_grades = student.read_all_grades();
    vector<int> drawing_grades;
    float n = students_grades.size(); // number of the students
    for (int i = 0; i < n; i++) {
        drawing_grades.push_back(students_grades[i].getDrawingGrade());
    }
    float muo = (float) vector_sum(drawing_grades) / n;

    float sigma = sqrt(vector_sum(x_mu_sq(x_mu(drawing_grades, muo))) / n);

    for (int i = 0; i < n; ++i) {
        normalized_grades.push_back(((float) drawing_grades[i] - muo) / sigma);
    }

    return normalized_grades;
}

vector<float> LMS::normalized_comp() {
    Student student;
    vector<float> normalized_grades;
    vector<Student> students_grades = student.read_all_grades();
    vector<int> comp_grades;
    float n = students_grades.size(); // number of the students
    for (int i = 0; i < n; i++) {
        comp_grades.push_back(students_grades[i].getComputerGrade());
    }
    float muo = (float) vector_sum(comp_grades) / n;

    float sigma = sqrt(vector_sum(x_mu_sq(x_mu(comp_grades, muo))) / n);

    for (int i = 0; i < n; ++i) {
        normalized_grades.push_back(((float) comp_grades[i] - muo) / sigma);
    }

    return normalized_grades;
}

vector<float> LMS::normalized_chem() {
    Student student;
    vector<float> normalized_grades;
    vector<Student> students_grades = student.read_all_grades();
    vector<int> chem_grades;
    float n = students_grades.size(); // number of the students
    for (int i = 0; i < n; i++) {
        chem_grades.push_back(students_grades[i].getChemGrade());
    }
    float muo = (float) vector_sum(chem_grades) / n;

    float sigma = sqrt(vector_sum(x_mu_sq(x_mu(chem_grades, muo))) / n);

    for (int i = 0; i < n; ++i) {
        normalized_grades.push_back(((float) chem_grades[i] - muo) / sigma);
    }

    return normalized_grades;
}

int LMS::vector_sum(vector<int> data) {
    int sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum;
}

float LMS::vector_sum(vector<float> data) {
    float sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum;
}

vector<float> LMS::x_mu(vector<int> data, float mu) {
    vector<float> z;
    for (int i = 0; i < data.size(); i++) {
        z.push_back((float) data[i] - mu);
    }
    return z;
}

vector<float> LMS::x_mu_sq(vector<float> x_mu) {
    vector<float> v;

    for (int i = 0; i < x_mu.size(); i++) {
        v.push_back(pow(x_mu[i], 2));
    }

    return v;
}

void LMS::print_data_grades() {
    string code;
    Student student;
    vector<string> data;
    vector<string> grades;
    cout << "Enter the student code:";
    cin >> code;
    cout << endl;
    if (is_student_exist_data_file(code) && is_student_exist_grades_file(code)) {
        data = get_data(code);
        grades = get_grades(code);
        cout << "Student's basic information and grades:" << endl;
        cout << "\tCode:" << data[0] << endl;
        cout << "\tName:" << data[1] << endl;
        cout << "\tAge:" << data[2] << endl;
        cout << "\tGender:" << data[3] << endl;
        cout << "\tMath grade:" << grades[1] << "(" << grades_to_GPA(atoi(grades[1].c_str())) << ")" << endl;
        cout << "\tPhysics grade:" << grades[2] << "(" << grades_to_GPA(atoi(grades[2].c_str())) << ")" << endl;
        cout << "\tDrawing grade:" << grades[3] << "(" << grades_to_GPA(atoi(grades[3].c_str())) << ")" << endl;
        cout << "\tComputer grade:" << grades[4] << "(" << grades_to_GPA(atoi(grades[4].c_str())) << ")" << endl;
        cout << "\tChemistry grade:" << grades[5] << "(" << grades_to_GPA(atoi(grades[5].c_str())) << ")" << endl;
    } else {
        cout << "Student is not exist ,please try another code..." << endl;
    }

}
