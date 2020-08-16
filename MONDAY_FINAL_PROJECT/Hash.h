/*
 * Hash.h
 * <Team Project - Group 3>
 *
 * Programmer: Tu Nguyen
 * Platform: Mac OS 10 (Sierra)
 * Main IDE: Visual Studio 2015
 *
 * Lecture: CIS 22C Winter 2017, De Anza College
 * Instructor: Delia Garbacea
 */

#ifndef HASH_H_
#define HASH_H_

#include "HashElem.h"
#include "Hash.h"
#include <iostream>
#include <cmath>
using namespace std;

class Hash {
private:
    HashElem* arrElem;
    int loadFactor, collision, size, numElem;
    
public:
    //Construtors & destructor
    Hash();
    Hash(int s);
    ~Hash();
    
    // Accessors
    int getSize() { return size; };
    int getLoadFactor() { return (numElem * 100) / size; };
    int getNumElem() { return numElem; };
    
    // Required functions
    int badHash(const string key);
    int goodHash(const string key);
    void displayConsole(void visit(Course &));
    void displayOutFile(ostream &out, void visit(ostream &, Course &));
    bool insert(Course*);
    bool remove(string, Course&);
    bool search(string, Course&);
    void statistic();
    Course* traverse();
};

#endif
