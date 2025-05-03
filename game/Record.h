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
    void save();
    Record(QString playerName, QString recordDate, int score);
    Record() = default;
    int getScore() const;
    QString getPlayerName() const;
    QString getRecordDate() const;
    void setScore(int score);
    void setPlayerName(QString &playerName);
    void setRecordDate(QString &recordDate);
    bool operator<(const Record &other) const;
};



#endif //RECORD_H
