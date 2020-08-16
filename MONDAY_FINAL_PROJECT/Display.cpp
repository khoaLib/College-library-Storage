/*
 * Display.cpp
 * <Team Project - Group 3>
 *
 * Programmer: Trinh Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Xcode
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#include "Display.h"

//Funtion Prototypes
void displayOneCourse(Course&);
void displayTable(Course&);
void displayTree(Course&);
void reHash(Hash *hash);
void compareUnique(Course newNodePtr, Course nodePtr, int &result);
void compareSecondary(Course newNodePtr, Course nodePtr, int &result);

/************************************************************
 
 Purpose: This function will display the introduction info
 (class info, professor, date submitted, team and member info,
 project info)
 
 ***********************************************************/

void Display::printProjectIntro()
{
    cout <<
    "\t _______________________________________                 ___________________________________________________\n"
    "\t|                                       |               |                                                   |\n"
    "\t|              CIS 22C-02Y              |               |   Unit 1: Team Coordinator - Trinh Nguyen         |\n"
    "\t|            M/W 1:30 - 3:20            |               |   Unit 2: BST Algorithms - Jyn Heng Yu (Henry)    |\n"
    "\t|        Professor Delia Garbacea       |               |   Unit 3: Hash List Algorithms - Tu Nguyen        |\n"
    "\t|         March 20th, 2017              |               |   Unit 4: Screen Output - Khoa Pham               |\n"
    "\t|_______________________________________|               |   Unit 5: File I/O - Jongwook Baik (Tony)         |\n"
    "\t|                                       |               |___________________________________________________|\n"
    "\t|         TEAM 3 - WINTER 2016          |               |                                                   |\n"
    "\t|       DE ANZA COURSE DATABASE         |               |     ~ WELCOME TO THE NEW COURSES SYSTEM OF ~      |\n"
    "\t|  IDE: Visual Studio, Xcode & Eclipse  |               |               ~ DE ANZA COLLEGE ~                 |\n"
    "\t|_______________________________________|               |___________________________________________________|\n";
    
    //COURSE INTRO
    return;
}

/************************************************************
 
 Purpose: This function show the contents of the main menu
 
 ***********************************************************/

void Display::displayMenu()
{
    cout <<
    "\n\t __________________________________\n"
    "\t|                                  |\n"
    "\t|            MAIN MENU             |\n"
    "\t|----------------------------------|\n"
    "\t| A. Add a Course                  |\n"
    "\t| S. Search a Course               |\n"
    "\t| D. Remove a Course               |\n"
    "\t| L. Display Database              |\n"
    "\t| U. Undo delete                   |\n"
    "\t| W. Write data to a file          |\n"
    "\t| M. Show Statistics               |\n"
    "\t| Q. Exit                          |\n"
    "\t|__________________________________|\n";
    
    return;
}

/************************************************************
 
 Purpose: This function displays the menu of the program and
 execute the program according to user input
 
 ***********************************************************/

void Display::ProcessMenu(FileIO IO, BinarySearchTree<Course> *treeUnique,
                          BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    Stack<Course> stack;
    ScreenOutput op;
    string choice;
    do {
        displayMenu();
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        switch (toupper(choice[0]))
        {
            case 'A':   // ADD A COURSE
            {
                InsertManager(treeUnique, treeSecondary, hash);
                break;
            }
            case 'S':   // SEARCH A COURSE
            {
                SearchManager(treeUnique, treeSecondary, hash);
                break;
            }
            case 'D':   // DELETE A COURSE
            {
                DeleteManager(treeUnique, treeSecondary, hash, stack);
                break;
            }
            case 'L':   // DISPLAY DATABASE
            {
                DisplayManager(treeUnique, treeSecondary, hash);
                break;
            }
            case 'U':   // UNDO DELETE
            {
                UndoDeleteManager(treeUnique, treeSecondary, hash, stack);
                break;
            }
            case 'W':   // WRITE DATA TO FILE
            {
                SaveToFile(IO, treeUnique, treeSecondary, hash);
                op.clearStack(stack);
                break;
            }
            case 'M':   // SHOW STATISTICS
            {
                DisplayStatistics(hash);
                break;
            }
            case 'Q':   // EXIT PROGRAM
            {
                //Save to file before exiting
                IO.saveToFile(treeUnique, treeSecondary, hash);
                //When the user selects “Save to file”, the undo stack is cleaned out
                //CLEAR STACK of deleted Courses if there is any
                op.clearStack(stack);
                // User-Interface - A greeting message to user before existing program
                cout << "\n\nThank you for using our services\nGood luck with all your courses!\n";
                //Pause the program ????
                getchar();
                //Exiting Program
                exit(-1);
                break;
            }
                // User-Interface - Have user reenter until getting a valid entry
            default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
                break;
        }
    }while (toupper(choice[0]) != 'Q');
    return;
}


/************************************************************
 
 Purpose: This function will allow the user to add a
 new Course to the database. It will display an example of
 Course Info, then ask the user to entee all the new
 Course information and then modify the info to its
 appropriate format and then insert the Course to the database.
 After the insertion, if successful, display the new Course,
 if fail, then display error message.
 
 ***********************************************************/

void Display::InsertManager(BinarySearchTree<Course> *treeUnique,
                            BinarySearchTree<Course> *treeSecondary, Hash *&hash)
{
    Course* newCourse = new Course();
    string tempStr;
    
    cout << "\n=================== ADDING A COURSE ====================\n";
    
    //User-Interface - Give user an example of course info for easiser entry
    cout << "\nExample of Course Information: \n"
    << "\t+ Course CRN: 33380 [positive 5-digit number]" << endl
    << "\t+ Course Name: Data Abstraction and Structures" << endl
    << "\t+ Course Code: CIS 22C" << endl
    << "\t+ Course Department: Computer Information Systems" << endl
    << "\t+ Course Professor: Garbacea, Delia-Manuela [last name, first name]" << endl
    << "\nPlease enter New Course Information!\n";
    int count = 0;
    do{
        if (count >= 1)
        {
            cout << "ERROR ==> DUPLICATE Course CRN - This Course CRN " << tempStr << "is already exist in the database!\nPlease enter a non-existed Course CRN!\n";
        }
        cout << "\t+ Course CRN: ";
        tempStr = CRNInputValidation();
        newCourse->setCrn(tempStr);
        count++;
    }while (hash->search(tempStr, *newCourse));
    
    cout << "Thank you! You entered a non-existed CRN.\nPlease proceed with 4 more Course Information for the new Course.\n";
    
    cout << "\t+ Course Name: ";
    tempStr = LineInputModify();
    newCourse->setCourseName(tempStr);
    
    cout << "\t+ Course Code: ";
    tempStr = CourseCodeInputModify();
    newCourse->setCourseCode(tempStr);
    
    cout << "\t+ Course Department: ";
    tempStr = LineInputModify();
    newCourse->setDepartment(tempStr);
    
    cout << "\t+ Course Professor: ";
    tempStr = LineInputModify();
    newCourse->setProfessorName(tempStr);
    
    //Insert new Course to 2 BST and 1 hash table
    treeUnique->insert(newCourse, compareUnique);
    treeSecondary->insert(newCourse, compareSecondary);
    hash->insert(newCourse);
    
    //Rehash to InsertManager.
    FileIO IO;
    if (hash->getLoadFactor() >= 75) {
        IO.reHash(hash);
    }
    
    //User-Interface: Display the information of the Course just got added to the database
    Course course;
    string temp = newCourse->getCrn();
    if (hash->search(temp, course))
    {
        cout << "\nNew Course is successfully added:";
        displayOneCourse(course);
    }
    else
        cout << "Error in Adding New Course\n";
    return;
}

/************************************************************
 
 Purpose: This function will allow the user to search for a
 Course in the database. It will display an menu of
 three options (search by CRN, Name, or return to main menu)
 and execute according to input. It then asks user to target
 to be search and then modify the info to its
 appropriate format. If FOUND, then display all the info,
 if NOT, then display a NOT FOUND message
 
 ***********************************************************/

void Display::SearchManager(BinarySearchTree<Course> *treeUnique,
                            BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    string temp;
    Course item, returnedItem;
    int count = 0;
    BinaryNode<Course>* returnedNode = treeSecondary->getRootPtr();
    string choice;
    do{
        cout <<
        "\n\t __________________________________\n"
        "\t|                                  |\n"
        "\t|            SEARCH MENU           |\n"
        "\t|----------------------------------|\n"
        "\t| P. Search Course CRN             |\n"
        "\t| S. Search Course Name            |\n"
        "\t| R. Return to Main Menu           |\n"
        "\t|__________________________________|\n";
        
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        switch (toupper(choice[0]))
        {
            case 'P':
            {
                cout << "Please enter the CRN of the course to search: ";
                temp = CRNInputValidation();
                item.setCourseName(temp);
                if (hash->search(temp, item))
                {
                    cout << "Course CRN " << temp << " is FOUND!" << endl;
                    displayOneCourse(item);
                }
                else
                    cout << "Course with CRN " << temp << " is NOT FOUND!" << endl;
                break;
            }
                
            case 'S':
            {
                cout << "Please enter the Course Name: ";
                temp = LineInputModify();
                item.setCourseName(temp);
                
                if (treeSecondary->getEntry(item, compareSecondary, &returnedNode))
                {
                    count = 1;
                    cout << "\nSEARCHING Course Name...\n";
                    item = *(returnedNode->getItem());
                    displayOneCourse(item);
                    
                    //search for other duplicates
                    returnedNode = returnedNode->getRightPtr();
                    while (treeSecondary->getEntry(item, compareSecondary, &returnedNode))
                    {
                        cout << "\n-----------------------------------------------\n";
                        item = *(returnedNode->getItem());
                        displayOneCourse(item);
                        returnedNode = returnedNode->getRightPtr();
                        count++;
                    }
                    cout << "\n===> FOUND " << count << " match(es).\n";
                }
                else
                {
                    cout << "Course with Name " << temp << " is NOT FOUND" << endl;
                }
                break;
            }
            case 'R':
            {
                //Return to Main Menu
                break;
            }
                // User-Interface - Have user reenter until getting a valid entry
            default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
                break;
        }
    }while (toupper(choice[0]) != 'R');
    return;
}

/************************************************************
 
 Purpose: This function will allow the user to remove a
 Course in the database. It will display an menu of
 two options (remove by CRN, Name, or return to main menu)
 and execute according to input. It then asks user to target
 to be deteled and then modify the info to its appropriate
 format and then search for it in the database. If NOT FOUND,
 then ask again until FOUND. If FOUND, then detele
 the Course and then check whether the Course was deleted
 or not and display a message.
 
 ***********************************************************/

void Display::DeleteManager(BinarySearchTree<Course> *treeUnique,
                            BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course>& stack)
{
    string temp, choice;
    bool remove, resultTree1, resultTree2;
    //bool search;
    //Course* tempItem = new Course("-1", "-1", "-1", "-1", "-1") ;
    
    do {
        cout <<
        "\n\t __________________________________\n"
        "\t|                                  |\n"
        "\t|            DELETE MENU           |\n"
        "\t|----------------------------------|\n"
        "\t| P. Detele by Course CRN          |\n"
        //"\t| S. Detele by Course Name         |\n"
        "\t| R. Return to Main Menu           |\n"
        "\t|__________________________________|\n";
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        
        switch (toupper(choice[0]))
        {
            case 'P':
            {
                cout << "Please enter the Course CRN: ";
                temp = CRNInputValidation();
                Course course;
                course.setCrn(temp);
                
                // DELETE IN TREE 1
                resultTree1 = treeUnique->remove(course, compareUnique);
                // DELETE IN TREE 2
                resultTree2 = treeSecondary->remove(course, compareSecondary);
                // DELETE IN HASH
                remove = hash->remove(temp, course);
                if (remove)
                {
                    if (!hash->search(temp, course))
                    {
                        cout << "Course with CRN " << temp << " is successfully DELETED!\n";
                        stack.push(course);
                    }
                    else
                        cout << "Errors occurs in deleteing Course CRN " << temp << endl;
                }
                else
                    cout << "Course with CRN " << temp << " is NOT FOUND!\n";
                break;
            }
                /*
                 case 'S':
                 {
                 cout << "Please enter the Course Name that you would like to delete: ";
                 temp = LineInputModify();
                 //Input Validation
                 //Search for name
                 //if not found, then ask again until found
                 //if found, then delete
                 //after delete, search again to see if it got deteled or not
                 //and then display a message
                 //treeSecondary->remove(temp);
                 break;
                 }
                 */
            case 'R':
            {
                //Return to Main Menu
                break;
            }
                // User-Interface - Have user reenter until getting a valid entry
            default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
                break;
        }
    }while (toupper(choice[0]) != 'R');
    return;
}


/************************************************************
 
 Purpose: This function will allow the user to view the
 database in different ways. It will display an menu of
 5 options below and execute according to input.
 
 ***********************************************************/

void Display::DisplayManager(BinarySearchTree<Course> *treeUnique,
                             BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    string choice;
    do{
        cout <<
        "\n\t __________________________________________\n"
        "\t|                                          |\n"
        "\t|               DISPLAY MENU               |\n"
        "\t|------------------------------------------|\n"
        "\t| U. Diplay unsorted data                  |\n"
        "\t| P. Display sorted Course CRN data        |\n"
        "\t| S. Display sorted Course Name data       |\n"
        "\t| D. Special display, as an indented list  |\n"
        "\t| R. Return to Main Menu                   |\n"
        "\t|__________________________________________|\n";
        
        cout << "\nYour choice ==> ";
        getline(cin, choice);
        switch (toupper(choice[0]))
        {
            case 'U': // Diplay unsorted data using hash table
            {
                cout << "\t\t\t\t\t\t\t~ "
                "DISPLAY ALL COURSES IN UNSORTED ORDER ~\n";
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                displayHeader();
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                hash->displayConsole(displayTable);
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                break;
            }
            case 'P': // Display sorted Course CRN data using the unique-key tree
            {
                cout << "\t\t\t\t\t\t\t~ "
                "DISPLAY ALL COURSES IN SORTED CRN ORDER ~\n";
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                displayHeader();
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                treeUnique->inOrder(displayTable);
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                break;
            }
            case 'S': // Display sorted Course Name data using the secondary-key tree
            {
                cout << "\t\t\t\t\t\t~ "
                "DISPLAY ALL COURSES IN SORTED COURSE NAME ORDER ~\n";
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                displayHeader();
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                treeSecondary->inOrder(displayTable);
                for (int i = 0; i < TABLE_LENGTH; i++) cout << "-";
                cout << endl;
                break;
            }
            case 'D':   // Special display, as an indented list
            {
                cout << "\t\t\t\t\t\t~ "
                "SPECIAL DISPLAY - DISPLAY ALL COURSES IN "
                "INDENTED LIST IN SORTED CRN ORDER ~\n\n";
                treeUnique->printTreeConsole(displayTree);
                break;
            }
            case 'R':
            {
                //Return to Main Menu
                break;
            }
                // User-Interface - Have user reenter until getting a valid entry
            default: cout << "INVALID ENTRY! -- Please only enter one of the options from the menu.\n";
                break;
        }
    }while (toupper(choice[0]) != 'R');
    return;
}

/************************************************************
 
 Purpose: This function ////
 The user can undo the delete in the reverse order of the
 delete sequence. When the user selects “Save to file”,
 the undo stack is cleaned out (no undo possible unless
 more delete occurs first)
 
 ***********************************************************/

void Display::UndoDeleteManager(BinarySearchTree<Course> *treeUnique,
                                BinarySearchTree<Course> *treeSecondary, Hash *hash, Stack<Course> &stack)
{
    Course temp;
    ScreenOutput op;
    //Undo the delete in the reverse order of the delete sequence
    if (op.undoDeleteCourse(treeUnique, treeSecondary, hash, stack, temp)) {
        cout << "Undo Completed! \n"
        << "This coure below is now back to the data.\n";
        displayOneCourse(temp);
    }
    else { //No undo possible unless more delete occurs first
        cout << "NO more Course deletion has been made!\n";
    }
}

/************************************************************
 
 Purpose: This function will display statistics of hash table
 
 ***********************************************************/

void Display::DisplayStatistics(Hash *hash)
{
    cout << "\n\t   ~ DISPLAY HASH TABLE STATISTIC ~\n\n";
    cout <<
    "\t ___________________________________\n"
    "\t|                                   |\n"
    "\t|            STATISTICS             |\n"
    "\t|-----------------------------------|\n";
    
    
    hash->statistic();
    return;
}


/************************************************************
 
 Purpose: This function write data of 2 BST and hash table
 to file
 
 ***********************************************************/

void Display::SaveToFile(FileIO IO, BinarySearchTree<Course> *treeUnique,
                         BinarySearchTree<Course> *treeSecondary, Hash *hash)
{
    cout << "======> WRITE DATA TO FILE \"" << outFileName << "\"!\n";
    IO.saveToFile(treeUnique, treeSecondary, hash);
    return;
}


/************************************************************
 
 Purpose: This function will display a header of a table
 
 ***********************************************************/

void Display::displayHeader()
{
    cout << setw(12) << left  << "| CRN"
    << setw(57) << left << "| COURSE NAME"
    << setw(17) << left << "| COURSE CODE"
    << setw(40) << left << "| DEPARTMENT"
    << setw(29) << left << "| PROFESSOR"  << right << "|" << endl;
    return;
}

/************************************************************
 
 Purpose: This function will display information of an Course
 It will be used for displaying a single Course for
 a better presentaion.
 
 ***********************************************************/

void displayOneCourse(Course& anItem)
{
    cout << "\nCourse CRN: " << anItem.getCrn() << endl
    << "Course Name: " << anItem.getCourseName() << endl
    << "Course Code: " << anItem.getCourseCode() << endl
    << "Course Department: " << anItem.getDepartment() << endl
    << "Course Professor: " << anItem.getProfessorName() << endl;
    return;
}

/************************************************************
 
 Purpose: This function will display information of an Course
 It will be used for displaying table for all Courses for a
 better presentaion.
 
 ***********************************************************/

void displayTable(Course& anItem)
{
    cout  << "| " << setw(10) << left << anItem.getCrn()
    << "| "<< setw(55) << left << anItem.getCourseName()
    << "| "<< setw(15) << left << anItem.getCourseCode()
    << "| "<< setw(38) << left << anItem.getDepartment()
    << "| "<< setw(27) << left << anItem.getProfessorName()
    << right << "|" << endl;
    return;
}

/************************************************************
 
 Purpose: This function will display information of an Course
 It will be used for displaying a indented tree for a
 better presentaion.
 
 ***********************************************************/

void displayTree(Course& anItem)
{
    cout  << anItem.getCrn() << " ------ "
    << anItem.getCourseName() << " ------ "
    << anItem.getCourseCode() << " ------ "
    << anItem.getDepartment() << " ------ "
    << anItem.getProfessorName() << endl << endl;
    return;
}

/************************************************************
 
 Purpose: This function validate user input in order to get
 a valid Course CRN (a 5-digit numnber)
 
 ***********************************************************/

string Display::CRNInputValidation()
{
    string input;
    int crn;
    int count = 0;
    do
    {
        if (count > 0)
            cout << "Please enter a valid 5-digit number Course CRN: ";
        getline(cin, input);
        crn = stoi(input);
        count++;
    }while (crn < 0 || crn > 100000);
    return input;
}

/************************************************************
 
 Purpose: This function will modify the user input of
 Course Name + Department and Professor Name by capitalizing
 the first letter of every word to be used for the insertion,
 search and deletion of a course
 Ex: Input: data structures ---> Modify: Data Structures
 Input: computer information systems ---> Modify: Computer Information Systems
 Input: garbarcea, delia-manuela ---> Modify: Garbacea, Delia-Manuela
 
 ***********************************************************/

string Display::LineInputModify()
{
    string input;
    getline(cin, input);
    input[0] = toupper(input[0]);
    for (int i = 0; i <= (int) input.length(); i++)
    {
        if (input[i] == ' ' || input[i] == '-' || input[i] == '(' || input[i] == ':')
        {
            input[i+1] = toupper(input[i+1]);
        }
    }
    return input;
}

/************************************************************
 
 Purpose: This function will modify the uder input of
 Course Code by capitalizing every letters in the string to
 be used for the insertion, search and deletion of a course
 Ex: Input: cis 22c ---> Modify: CIS 22C
 
 ***********************************************************/

string Display::CourseCodeInputModify()
{
    string input;
    getline(cin, input);
    input[0] = toupper(input[0]);
    for (int i = 0; i < (int) input.length(); i++)
    {
        if (isalpha(input[i]))
            input[i] = toupper(input[i]);
    }
    return input;
}

