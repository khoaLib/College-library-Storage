
/*
 * Course.h
 * <Team Project - Group 3>
 *
 * Programmer: Khoa Pham
 * Platform: Windows 7
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include <iostream>
using namespace std;

class Course {
private:
    string crn;
    string courseName;
    string courseCode;
    string department;
    string professorName;

public:
    // Constructor
    Course(string crn, string courseName, string courseCode, string department, string professorName);
    Course();
    // Destructor
    //~Course();
    string getCrn() const;
    string getCourseName() const;
    string getCourseCode() const;
    string getDepartment() const;
    string getProfessorName() const;
    void setCrn(string crn);
    void setCourseName(string courseName);
    void setCourseCode(string courseCode);
    void setDepartment(string department);
    void setProfessorName(string professorName);
};

ostream &operator<<(ostream &strm, const Course &obj);

#endif /* COURSE_H_ */
