//
// Created by radamir on 03.05.25.
//

#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record {
    private:
    QString playerName;
    QString recordDate;
    int score;
    public:
    Record(QString playerName, QString recordDate, int score);
    int getScore() const;
    QString getPlayerName() const;
    QString getRecordDate() const;
};



#endif //RECORD_H
