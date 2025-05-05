//
// Created by radamir on 03.05.25.
//

#ifndef RECORDDATABASE_H
#define RECORDDATABASE_H

#include <set>
#include "Record.h"
class RecordDatabase {
private:
    std::set<Record> records;
    void loadFromFile();
public:
    RecordDatabase();
    std::set<Record> *getRecords();
    void insertRecord(Record &record);
};



#endif //RECORDDATABASE_H
