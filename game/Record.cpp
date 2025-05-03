//
// Created by radamir on 03.05.25.
//

#include "Record.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
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
bool Record::operator<(const Record &other) const {
    return this->score < other.score;
}
void Record::save() {
    QJsonObject recordObject;
    recordObject["score"] = score;
    recordObject["playerName"] = playerName;
    recordObject["recordDate"] = recordDate;

    // Читаем существующие записи из файла (если есть)
    QJsonArray recordsArray;
    QFile file("/home/radamir/CLionProjects/doubleJumper/game/records.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray()) {
            recordsArray = doc.array();
        }
        file.close();
    }

    // Добавляем новую запись в массив
    recordsArray.append(recordObject);

    // Записываем обновленный массив обратно в файл
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(recordsArray);
        file.write(doc.toJson());
        file.close();
    }
}
void Record::setScore(int score) {
    this->score = score;
}
void Record::setPlayerName(QString &playerName) {
    this->playerName = playerName;
}
void Record::setRecordDate(QString &recordDate) {
    this->recordDate = recordDate;
}


