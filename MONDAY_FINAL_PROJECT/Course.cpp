/*
 * Course.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Khoa Pham
 * Platform: Windows 7
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#include "Course.h"

/******************************************************
 *               Overload   Constructor               *
 ******************************************************/
Course::Course(string crn, string courseName, string courseCode, string department, string professorName) {
    this->crn = crn;
    this->courseName = courseName;
    this->courseCode = courseCode;
    this->department = department;
    this->professorName = professorName;
}

/******************************************************
 *                 Default Constructor                *
 ******************************************************/
Course::Course() {
    this->crn = "";
    this->courseName = "";
    this->courseCode = "";
    this->department = "";
    this->professorName = "";
}

/********************* Accessors **********************
 * Member functions that allow access to data members *
 ******************************************************/

// getCrn and returns crn
string Course::getCrn() const {
    return crn;
}

// getCourseName gets the value of courseName and returns courseName
string Course::getCourseName() const {
    return courseName;
}

// getCourseCode gets the value of courseCode and returns courseCode
string Course::getCourseCode() const {
    return courseCode;
}

// getDepartment gets the value of department and returns department
string Course::getDepartment() const {
    return department;
}

// getProfessorNamee gets the value of professorName and returns professorName
string Course::getProfessorName() const {
    return professorName;
}

/********************** Mutators **********************
 *   Member functions that allow for modification of  *
 *   the data members                                 *
 ******************************************************/

// setCrn sets the value of the member variable crn
void Course::setCrn(string crn) {
    this->crn = crn;
}

// setCourseName sets the value of the member variable courseName
void Course::setCourseName(string courseName) {
    this->courseName = courseName;
}

// setCourseCode sets the value of the member variable courseCode
void Course::setCourseCode(string courseCode) {
    this->courseCode = courseCode;
}

// setDepartment sets the value of the member variable department
void Course::setDepartment(string department) {
    this->department = department;
}

// setProfessorName sets the value of the member variable professorName
void Course::setProfessorName(string professorName) {
    this->professorName = professorName;
}

/******************************************************
 *           Class template for output stream         *
 ******************************************************/
ostream &operator<<(ostream &strm, const Course &obj)
{
    strm << obj.getCrn() << "\t\t"
    << obj.getCourseName() << "\t\t"
    << obj.getCourseCode() << "\t\t"
    << obj.getDepartment() << "\t\t"
    << obj.getProfessorName() << endl;
    return strm;
}
