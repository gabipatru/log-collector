/*
 * log_item.cpp
 *
 *  Created on: 23 Jan 2019
 *      Author: Gabi
 */

/**
 * Log Item
 */
LogItem::LogItem()
{
    this->type = "";
    this->subType = "";
    this->path = "";
    this->line = 0;
    this->createdAt = "";
}

LogItem::LogItem( STRINGCLASS type, STRINGCLASS subType, STRINGCLASS path, unsigned long int line, STRINGCLASS createdAt )
{
    this->type = type;
    this->subType = subType;
    this->path = path;
    this->line = line;
    this->createdAt = createdAt;
}

bool LogItem::operator==( bool compare )
{
    if ( compare == true ) {
        if ( this->getPath().length() == 0
                && this->getSubType().length() == 0
                && this->getType().length() == 0
                && this->getLine() == 0
                && this->getCreatedAt().length() == 0) {
            return false;
        } else {
            return true;
        }
    } else {
        if ( this->getPath().length() == 0
                && this->getSubType().length() == 0
                && this->getType().length() == 0
                && this->getLine() == 0
                && this->getCreatedAt().length() == 0) {
            return true;
        } else {
            return false;
        }
    }
}

void LogItem::setType( STRINGCLASS type )
{
    this->type = type;
}

STRINGCLASS LogItem::getType()
{
    return this->type;
}

void LogItem::setSubType( STRINGCLASS subType )
{
    this->subType = subType;
}

STRINGCLASS LogItem::getSubType()
{
    return this->subType;
}

void LogItem::setPath( STRINGCLASS path )
{
    this->path = path;
}

STRINGCLASS LogItem::getPath()
{
    return this->path;
}

void LogItem::setLine( unsigned long int line )
{
    this->line = line;
}

unsigned long int LogItem::getLine()
{
    return this->line;
}

void LogItem::setCreatedAt( STRINGCLASS date )
{
    this->createdAt = date;
}

STRINGCLASS LogItem::getCreatedAt()
{
    return this->createdAt;
}

int LogItem::Validate()
{
    if ( this->getType().length() == 0 ) {
        return 0;
    }
    if ( this->getSubType().length() == 0 ) {
        return 0;
    }
    if ( this->getPath().length() == 0 ) {
        return 0;
    }

    return 1;
}


/**
 * Log List
 */
LogList::LogList()
{
    this->pNext = NULL;
}

void LogList::setItem( LogItem Item )
{
    this->Item = Item;
}

LogItem LogList::getItem()
{
    return this->Item;
}

void LogList::setNextPointer( PLOGLIST pItem )
{
    this->pNext = pItem;
}

PLOGLIST LogList::getNextPointer()
{
    return this->pNext;
}


/**
 * Log Chain
 */
LogChain::LogChain()
{
    this->pHead = NULL;
    this->pCurrent = NULL;
}

void LogChain::CreateItem( LogItem Item )
{
    PLOGLIST pNewListItem = new LogList;

    // copy the data
    pNewListItem->setItem( Item );

    // if the head is null, this will be the first item
    if ( this->pHead == NULL ) {
        this->pHead = pNewListItem;
        this->pCurrent = pNewListItem;
    } else {
        this->pCurrent->setNextPointer( pNewListItem );
        this->pCurrent = pNewListItem;
    }
}

void LogChain::CreateItem( STRINGCLASS type, STRINGCLASS subType, STRINGCLASS path, unsigned long int line, STRINGCLASS date )
{
    LogItem Item;

    Item.setType( type );
    Item.setSubType( subType );
    Item.setPath( path );
    Item.setLine( line );
    Item.setCreatedAt( date );

    this->CreateItem( Item );
}

void LogChain::Reset()
{
    this->pCurrent = this->pHead;
}

int LogChain::hasCurrentItem()
{
    if ( this->pCurrent != NULL ) {
        return true;
    }
    return false;
}

LogItem LogChain::getCurrentItem()
{
    return this->pCurrent->getItem();
}

LogItem LogChain::getCurrentItemAndInc()
{
    LogItem Item;

    if ( this->pCurrent != NULL ) {
        Item = this->pCurrent->getItem();
        this->pCurrent = this->pCurrent->getNextPointer();
    }

    return Item;
}
