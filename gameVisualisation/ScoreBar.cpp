//
// Created by radamir on 28.04.25.
//

#include "ScoreBar.h"

#include <deque>
#include <iostream>


ScoreBar::ScoreBar(QWidget *parent) {
    setParent(parent);
    setFixedWidth(parent->width());
    backGround = new QLabel(this);
    backGround->setPixmap(QPixmap("/home/radamir/CLionProjects/doubleJumper/requirments/Sprites/Doodle Jump/top-score@2x.png").copy(0,0,backGroundWidth,backGroundHeight));
    backGround->setScaledContents(true);
    backGround->setGeometry(0,0,width(),backGroundHeight);
    setFixedSize(width(), backGroundHeight);
    digitsCoords.resize(10);
    digitsCoords[1] = {636,0,16,34};
    digitsCoords[2] = {653,0,31,34};
    digitsCoords[3] = {684,0,29,34};
    digitsCoords[4] = {712,0,25,34};
    digitsCoords[5] = {736,0,29,34};
    digitsCoords[6] = {766,0,29,34};
    digitsCoords[7] = {797,0,28,34};
    digitsCoords[8] = {826,0,27,34};
    digitsCoords[9] = {851,0,23,34};
    digitsCoords[0] = {876,0,27,34};
}
void ScoreBar::displayScore(int score) {
    std::deque<int> digits;
    if (score == 0) {
        digits.push_front(0);
    }
    while(score > 0) {
        digits.push_front(score % 10);
        score /= 10;
    }
    for (int i =0;i<currentScore.size();i++) {
        delete currentScore[i];
    }
    currentScore.clear();
    currentScore.resize(digits.size());
    int coordinateY = 0;
    int coordinateX = 0;
    for (int i =0;i<digits.size();i++) {
        currentScore[i] = new QLabel(this);
        currentScore[i]->setScaledContents(true);
        currentScore[i]->setPixmap(QPixmap(imagePrefixPath + scoreTilePath).copy(digitsCoords[digits[i]]));
        currentScore[i]->move(coordinateX,coordinateY);
        coordinateX += digitsCoords[digits[i]].width();
        currentScore[i]->show();
    }
}
ScoreBar::~ScoreBar() {
    for (int i =0;i<currentScore.size();i++) {
        delete currentScore[i];
    }
}

