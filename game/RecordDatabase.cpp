//
// Created by radamir on 03.05.25.
//

#include "RecordDatabase.h"

#include<iostream>
#include "Record.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
void RecordDatabase::loadFromFile() {
        QFile file("/home/radamir/CLionProjects/doubleJumper/game/records.json");
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("Could not open records.json");
            return;
        }

        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);

        if (doc.isNull() || !doc.isArray()) {
            qWarning("Invalid JSON format in records.json");
            return;
        }

        QJsonArray jsonArray = doc.array();
        records.clear();

        for (const QJsonValue &value : jsonArray) {
            if (value.isObject()) {
                QJsonObject obj = value.toObject();
                Record record;
                record.setScore(obj["score"].toInt());
                QString tempName = obj["playerName"].toString();
                record.setPlayerName(tempName);
                QString tempDate = obj["recordDate"].toString();
                record.setRecordDate(tempDate);
                records.insert(record);
            }
        }
}
RecordDatabase::RecordDatabase() {
    std::cout<<"!";
    loadFromFile();
}
void RecordDatabase::insertRecord(Record &record) {
    if (records.find(record) == records.end()) {
        record.save();
        records.insert(record);
    }

}
std::set<Record> *RecordDatabase::getRecords() {
    return &records;
}
