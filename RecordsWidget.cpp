//
// Created by radamir on 05.05.25.
//

#include "RecordsWidget.h"

#include <qevent.h>

#include "mainwindow.h"
#include <iostream>
#include<thread>
void RecordsWidget::wheelEvent(QWheelEvent *event) {
    // Получаем дельту прокрутки
    QPoint delta = event->angleDelta();

    // Определяем направление прокрутки
    if (!delta.isNull()) {
        // Вертикальная прокрутка
        if (delta.y() != 0) {
            if (delta.y() > 0) {
                wheelShift-=5;

            } else {
                wheelShift+=5;
            }
            wheelShift = std::max(0, wheelShift);
            wheelShift = std::min(wheelShift, (int)recordsLabels.size()* 30);
        }
    }


}
int RecordsWidget::calculateLabelWidth(const QLabel *label, const QString &text) {

        if (!label) return 0;

        // Получаем метрики шрифта из QLabel
        QFontMetrics fontMetrics(label->font());

        // Вычисляем ширину текста
        int textWidth = fontMetrics.horizontalAdvance(text);

        // Получаем отступы содержимого
        QMargins margins = label->contentsMargins();

        // Суммируем ширину текста и отступы
        return textWidth + margins.left() + margins.right();

}


void RecordsWidget::showRecords() {
    for (int i =0 ;i<recordsLabels.size();i++) {
        delete recordsLabels[i];
    }
    recordsLabels.clear();
    int coordY = 200 - wheelShift;
    int coordX = 110;
    auto records = dynamic_cast<MainWindow*>(parent()->parent())->records;
    for (auto it = records->getRecords()->rbegin(); it != records->getRecords()->rend(); it++) {
      //  std::cout<<coordX<<" "<<coordY<<"\n";
        Record record = *it;
        QLabel* nameAndScoreLabel = new QLabel(this);
        nameAndScoreLabel->setGeometry(coordX,coordY,recordWidth,reordHeight);
        nameAndScoreLabel->setText(record.getPlayerName() + " : " + QString::number(record.getScore()));

        QLabel* timeLabel = new QLabel(this);
        timeLabel->setGeometry(coordX,coordY + 50,recordWidth,reordHeight);
        timeLabel->setText(record.getRecordDate());

        QLabel* delimiter = new QLabel(this);
        delimiter->setScaledContents(true);
        delimiter->setGeometry(coordX,coordY + 60 + 60,recordWidth,30);
        delimiter->setPixmap(QPixmap(prefixPath + recordDelimiterPath));
        recordsLabels.push_back(nameAndScoreLabel);
        recordsLabels.push_back(timeLabel);
        recordsLabels.push_back(delimiter);
        delimiter->show();
        timeLabel->show();
        nameAndScoreLabel->show();
        coordY+=reordHeight;

    }
}
void RecordsWidget::showFrame() {
    if (topLabel!=nullptr) {
        delete topLabel;
    }
    if (bottomLabel!=nullptr) {
        delete bottomLabel;
    }
    if (leftLabel!=nullptr) {
        delete leftLabel;
    }
    bottomLabel = new QLabel(this);
    bottomLabel->setScaledContents(true);
    bottomLabel->setPixmap(QPixmap(prefixPath + bottomImagePath));
    bottomLabel->setGeometry(0,850 - 250,640,324);

    leftLabel = new QLabel(this);
    leftLabel->setScaledContents(true);
    leftLabel->setPixmap(QPixmap(prefixPath + leftImagePath));
    leftLabel->setGeometry(0,850 - 250 - 324 - 50,116,398);

    topLabel = new QLabel(this);
    topLabel->setScaledContents(true);
    topLabel->setPixmap(QPixmap(prefixPath + topImagePath));
    topLabel->setGeometry(0,0,640,238);
    bottomLabel->show();
    topLabel->show();
    leftLabel->show();
}
RecordsWidget::RecordsWidget(QWidget *parent){
    setParent(parent);
    setFixedHeight(HEIGHT);
    setFixedWidth(WIDTH);

    fontId = QFontDatabase::addApplicationFont(fontPath);
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    font = new QFont(fontFamilies.at(0), 30);
    setFont(*font);


    backGroundLabel = new QLabel(this);
    backGroundLabel->setScaledContents(true);
    backGroundLabel->setPixmap(QPixmap(prefixPath + backGroundPath));
    backGroundLabel->setGeometry(0,0,WIDTH,HEIGHT);
    showRecords();
    showFrame();

    timer = new QTimer(this);
    timer->setInterval(deltaTime);
    timer->setSingleShot(false);
    //connect(timer,&QTimer::timeout,this,&RecordsWidget::showRecords);
      connect(timer,&QTimer::timeout,this,&RecordsWidget::showFrame);

    timer->start();

}