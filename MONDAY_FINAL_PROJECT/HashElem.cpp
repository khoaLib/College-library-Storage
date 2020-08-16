/*
 * HashElem.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Tu Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#include "Course.h"
#include "HashElem.h"
#include <iostream>

using namespace std;

// Constructor
HashElem::HashElem() {
    this->item = 0;
    flag = 0;
}

// Overload Constructors
HashElem::HashElem(Course* item) {
    this->item = item;
    flag = 0;
}

// setItem set the value of object Course
void HashElem::setItem(Course * c) {
    item = c;
}

// setItemToNull set the value of all variables to -1
void HashElem::setItemToNull() {
    (*item).setCrn("-1");
    (*item).setCourseName("-1");
    (*item).setCourseCode("-1");
    (*item).setDepartment("-1");
    (*item).setProfessorName("-1");
}

ostream &operator<<(ostream &strm, HashElem& obj){
    strm << obj.getItem();
    return strm;
}
