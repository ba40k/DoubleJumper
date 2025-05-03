//
// Created by radamir on 03.05.25.
//

#include "Record.h"

Record::Record(QString playerName, QString recordDate, int score) {
    this->playerName = playerName;
    this->recordDate = recordDate;
    this->score = score;
}
QString Record::getPlayerName() const {
    return this->playerName;
}
QString Record::getRecordDate() const {
    return this->recordDate;
}
int Record::getScore() const {
    return this->score;
}
