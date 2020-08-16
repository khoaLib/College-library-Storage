/*
 * ScreenOutput.h
 * <Team Project - Group 3>
 *
 * Programmer: Khoa Pham
 * Platform: Windows 7
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#ifndef _SCREEN_OUTPUT_
#define _SCREEN_OUTPUT_
#include "Display.h"
#include "BinarySearchTree.h"
#include "Hash.h"
#include "Course.h"
#include "Display.h"
#include "BinaryNode.h"
#include "BinaryTree.h"
#include "Stack.h"
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
#define TABLE_LENGTH 156


class ScreenOutput
{
private:
    
public:
    
    // Undo detele the deleted Course
    bool undoDeleteCourse(BinarySearchTree<Course>*, BinarySearchTree<Course>*, Hash*, Stack<Course>&, Course&);
    // option "Save to file", clear all stack, and the user can't undo
    bool clearStack(Stack<Course>&);
    
};
#endif
