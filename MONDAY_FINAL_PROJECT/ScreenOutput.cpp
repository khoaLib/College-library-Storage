/*
 * ScreenOutput.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Khoa Pham
 * Platform: Windows 7
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#include "ScreenOutput.h"

//Funtion Prototypes
void displayOneCourse(Course&);
void compareUnique(Course newNodePtr, Course nodePtr, int &result);
void compareSecondary(Course newNodePtr, Course nodePtr, int &result);

/************************************************************
 
 Function clearUno will clear all the stacks of the user by
 pop all the items in the stack( if any), so the user can't
 undo any delete one, unless they delete a new one.
 
 ***********************************************************/

bool ScreenOutput::clearStack(Stack<Course> &stack)
{
    Course noUseItem;
    if (stack.isEmpty())
    {
        //cout << "\n\t*********************************************************************\n"
        //	<< "\t* Deleted Course(s) will be permanently removed out of the database *\n"
        //	<< "\t*********************************************************************" << endl;
        return true;
    }
    else{
        while (!stack.isEmpty())
        {
            stack.pop(noUseItem);
            // Display Deleted Course(s) in reverse order for the purpose of tesing
            // in case there are still deleted Course(s) in stack before user exit the program
            cout << "\nDelete Course left in Undo Delete: " << endl;
            displayOneCourse(noUseItem);
        }
        cout << "\n*********************************************************************\n"
        << "* Deleted Course(s) will be permanently removed out of the database *\n"
        << "*********************************************************************" << endl;
        //cout << "Press any key to end the program." << endl;
    }
    return true;
}

/************************************************************
 
 undoNode function will undo the node that is deleted
 in reverse order. It will print a warning if the stack
 doesn't have anything to undo.
 
 ***********************************************************/


bool ScreenOutput::undoDeleteCourse(BinarySearchTree<Course> *treeUnique,
                                    BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course> &stack, Course& temp)
{
    if (!stack.isEmpty())
    {
        Course* delItem = new Course;
        stack.pop(*delItem);
        temp = (*delItem);	//to know which course get undo
        treeUnique->insert(delItem, compareUnique);
        treeSecondary->insert(delItem, compareSecondary);
        hash->insert(delItem);
        return true;
    }
    else 
        return false;
    
}
