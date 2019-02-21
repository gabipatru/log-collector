/*
 * log_item.h
 *
 *  Created on: 23 Jan 2019
 *      Author: Gabi
 */

#ifndef SRC_LOG_ITEM_H_
#define SRC_LOG_ITEM_H_

class LogItem {
private:
    /**
     * The log type, eg apache2
     */
    STRINGCLASS type;

    /**
     * The log subtype, eg access, error
     */
    STRINGCLASS subType;

    /**
     * Location of the log file on the disk
     */
    STRINGCLASS path;

public:
    /**
     * The default constructor
     */
    LogItem();

    /**
     * Construct with type and path
     */
    LogItem( STRINGCLASS, STRINGCLASS );

    /**
     * Construct with type, subtype and path
     */
    LogItem( STRINGCLASS, STRINGCLASS, STRINGCLASS );

    /**
     * Overload operator != to allow comparisons with bools
     */
    bool operator==( bool );

    /**
     * Setter and Getter for Type
     */
    void setType( STRINGCLASS );
    STRINGCLASS getType();

    /**
     * Setter and Getter for subType
     */
    void setSubType( STRINGCLASS );
    STRINGCLASS getSubType();

    /**
     * Setter and Getter for Path
     */
    void setPath( STRINGCLASS );
    STRINGCLASS getPath();

    /**
     * Check if all fields are valid
     */
    int Validate();
};

typedef class LogItem* PLOGITEM;

class LogList
{
private:
    LogItem Item;
    LogList *pNext;

public:
    /**
     * Default Constructor
     */
    LogList();

    /**
     * Getter and Setter for Item
     */
    void setItem( LogItem );
    LogItem getItem();

    /**
     * Set the next item in the list
     */
    void setNextPointer( LogList* );
    LogList *getNextPointer();
};

typedef class LogList* PLOGLIST;

class LogChain
{
private:
    PLOGLIST pHead, pCurrent;

public:
    /**
     * Default constructor
     */
    LogChain();

    /**
     * Create an item
     */
    void CreateItem( LogItem );
    void CreateItem( STRINGCLASS, STRINGCLASS, STRINGCLASS );

    /**
     * Set the current item to the head
     */
    void Reset();

    /**
     * Check if the currect item is valid
     */
    int hasCurrentItem();

    /**
     * Get the current item
     */
    LogItem getCurrentItem();

    /**
     * Get the current item and go to next one
     */
    LogItem getCurrentItemAndInc();
};

class LogChain LogItems;

#include "constant.h"

#include "log_item.cpp"

#endif /* SRC_LOG_ITEM_H_ */
