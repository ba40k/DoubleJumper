//
// Created by radamir on 16.04.25.
//

#include "gameWidget.h"

#include "../platforms/GreenPlatform.h"
#include<iostream>
#include <QKeyEvent>

#include "../mainwindow.h"
#include "../items/helicopterHat.h"
#include "../items/Jetpack.h"
#include "../items/Spring.h"
#include "../platforms/BlackHole.h"
#include "../platforms/BluePlatform.h"

GameWidget::GameWidget(bool visibleMarkers,QWidget *parent) : game(dynamic_cast<MainWindow*>(parent)->soundOn) {
    currentTheme = new DefaultTheme();
    setParent(parent);
    setFocusPolicy(Qt::StrongFocus); // Разрешаем фокус клавиатуры
    setFocus(); // Захватываем фокус
    game.gameInitialize();
    showScoreMarkers = visibleMarkers;

    prefixPath = "requirments/Sprites/Doodle Jump/";
    backgoundImagePath = "bck@2x.png";
    backgoundLabel = new QLabel(this);
    resize(parent->width(), parent->height());

    backgoundLabel->setScaledContents(true);
    backgoundLabel->setGeometry(QRect(0, 0, parent->width(), parent->height()));

    backgoundLabel->setPixmap(QPixmap(prefixPath + backgoundImagePath));
    scoreBar = new ScoreBar(this);
    auto gamePlatforms = game.getPlatforms();
    platforms.resize(gamePlatforms->size());

    game.getDoubleJumper()->setTheme(currentTheme);

    for (int i = 0; i < gamePlatforms->size(); i++) {
        if (dynamic_cast<BrownPlatform *>((*gamePlatforms)[i])) {
            auto temp = BrownPlatform((*gamePlatforms)[i]->getX(), ((*gamePlatforms)[i]->getY()), imagePath,false);
            temp.setTheme(currentTheme);
            platforms[i] =  temp.getQLabel(this);
        } else if (dynamic_cast<BluePlatform *>((*gamePlatforms)[i])) {
            auto temp = BluePlatform((*gamePlatforms)[i]->getX(), ((*gamePlatforms)[i]->getY()), imagePath);
            temp.setTheme(currentTheme);
            platforms[i] = temp.getQLabel(this);
        } else {
            auto temp = GreenPlatform((*gamePlatforms)[i]->getX(), ((*gamePlatforms)[i]->getY()), imagePath,false);
            temp.setTheme(currentTheme);
            platforms[i] = temp.getQLabel(this);
        }
    }
    visualizeItems();
    timer = new QTimer(this);
    timer->setInterval(deltaTime);
    timer->setSingleShot(false);

    doubleJumperLabel = game.getDoubleJumper()->getLabel(this);

    connect(timer, &QTimer::timeout, this, &GameWidget::update);
    stop();

}

void GameWidget::update() {
    if (game.isGameEnded() && blackHoleAnimationTicks > 0 && game.getFinalBlackHole() != nullptr) {
        //timer->stop();
        playBlackHoleAnimation();
        --blackHoleAnimationTicks;
        return;
    }
    if (game.isGameEnded() && (blackHoleAnimationTicks == 0 || game.getFinalBlackHole() == nullptr)) {
        timer->stop();
        loseDialog = new LoseDialog(this, game.getScore());
        loseDialog->setModal(true);
        loseDialog->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
        loseDialog->show();
        return;
    }
    int shift = game.getShift();
    visualizeItems();
    if (showScoreMarkers) {
        visualizeScoreMarkers();
    }
    game.gameStateUpdate(deltaTime, leftArrowPressed, rightArrowPressed);
    auto gamePlatforms = game.getPlatforms();
    //  std::cout<<platforms.size()<<'\n';
    for (int i = 0; i < platforms.size(); i++) {
        delete platforms[i];
    }

    platforms.clear();
    platforms.resize(gamePlatforms->size());
    for (int i = 0; i < gamePlatforms->size(); i++) {
        if (dynamic_cast<BrownPlatform *>((*gamePlatforms)[i])) {
            dynamic_cast<BrownPlatform *>((*gamePlatforms)[i])->setAnimationCounter(
                dynamic_cast<BrownPlatform *>((*gamePlatforms)[i])->getAnimationCounter() + 1);
            auto temp = BrownPlatform((*gamePlatforms)[i]->getX(), (*gamePlatforms)[i]->getY() + shift, imagePath,false);
            temp.setTheme(currentTheme);
            if (dynamic_cast<BrownPlatform *>((*gamePlatforms)[i])->isBroken()) {
                temp.setBroken();
            }
            temp.setAnimationCounter(dynamic_cast<BrownPlatform *>((*gamePlatforms)[i])->getAnimationCounter());
            platforms[i] = temp.getQLabel(this);
        } else if (dynamic_cast<GreenPlatform *>((*gamePlatforms)[i])) {
            auto otherTemp = GreenPlatform((*gamePlatforms)[i]->getX(), (*gamePlatforms)[i]->getY() + shift, imagePath,false);
            otherTemp.setTheme(currentTheme);
            platforms[i] =  otherTemp.getQLabel(this);
        } else if (dynamic_cast<BlackHole *>((*gamePlatforms)[i])) {
            auto otherTemp = BlackHole((*gamePlatforms)[i]->getX(), (*gamePlatforms)[i]->getY() + shift, imagePath,false);
            otherTemp.setTheme(currentTheme);
            platforms[i] = otherTemp.getQLabel(this);
        } else {
            auto otherTemp =BluePlatform((*gamePlatforms)[i]->getX(), (*gamePlatforms)[i]->getY() + shift, imagePath);
            otherTemp.setTheme(currentTheme);
            platforms[i] =  otherTemp.getQLabel(this);
        }
        platforms[i]->show();
    }

    doubleJumperLabel->setPixmap(game.getDoubleJumper()->getLabel(this)->pixmap());
    doubleJumperLabel->move(game.getDoubleJumperX(), game.getDoubleJumperY() + shift);
    doubleJumperLabel->raise();
    if (currentScoreTick % scoreUpdateTick == 0) {
        scoreBar->displayScore(game.getScore());
    }

    if (game.getHatPointer() != nullptr) {
        if (currentHatLabel != nullptr) {
            delete currentHatLabel;
        }
        currentHatLabel = game.getHatPointer()->getQLabel(this);
        currentHatLabel->move(currentHatLabel->x(), currentHatLabel->y() + game.getShift());
        currentHatLabel->show();
    } else {
        if (currentHatLabel != nullptr) {
            delete currentHatLabel;
            currentHatLabel = nullptr;
        }
    }
    if (game.getJetpackPointer() != nullptr) {
        if (currentJetpackLabel != nullptr) {
            delete currentJetpackLabel;
        }
        currentJetpackLabel = game.getJetpackPointer()->getQLabel(this);
        currentJetpackLabel->move(currentJetpackLabel->x(), currentJetpackLabel->y() + game.getShift());
        currentJetpackLabel->show();
    } else {
        if (currentJetpackLabel != nullptr) {
            delete currentJetpackLabel;
            currentJetpackLabel = nullptr;
        }
    }
    scoreBar->raise();
    ++currentScoreTick;
}

void GameWidget::stop() {
    timer->stop();
    stopped = true;
}

void GameWidget::run() {
    timer->start();
    stopped = false;
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            if (game.getDoubleJumper()->getOrintation() == 1) {
                game.getDoubleJumper()->changeOrintation();
            }
            leftArrowPressed = true;


            break;
        case Qt::Key_Right:
            rightArrowPressed = true;
            if (game.getDoubleJumper()->getOrintation() == 0) {
                game.getDoubleJumper()->changeOrintation();
            }
            break;

        default:
            QWidget::keyPressEvent(event); // передаём остальные события родителю
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Left:
            leftArrowPressed = false;
            break;
        case Qt::Key_Right:
            rightArrowPressed = false;
            break;

        default:
            QWidget::keyPressEvent(event); // передаём остальные события родителю
    }
}

void GameWidget::visualizeItems() {
    auto gameItems = game.getItems();
    for (int i = 0; i < items.size(); i++) {
        delete items[i];
    }
    items.clear();
    items.resize(gameItems->size());
    for (int i = 0; i < gameItems->size(); i++) {
        gameItems->at(i)->setTheme(currentTheme);
        if (dynamic_cast<Spring *>((*gameItems)[i])) {
            items[i] = dynamic_cast<Spring *>((*gameItems)[i])->getQLabel(this);
            items[i]->move(items[i]->x(), items[i]->y() + game.getShift());
            items[i]->show();
        } else if (dynamic_cast<HelicopterHat *>((*gameItems)[i])) {
            items[i] = dynamic_cast<HelicopterHat *>((*gameItems)[i])->getQLabel(this);
            items[i]->move(items[i]->x(), items[i]->y() + game.getShift());
            items[i]->show();
        } else if (dynamic_cast<Jetpack *>((*gameItems)[i])) {
            items[i] = dynamic_cast<Jetpack *>((*gameItems)[i])->getQLabel(this);
            items[i]->move(items[i]->x(), items[i]->y() + game.getShift());
            items[i]->show();
        }
    }
}

void GameWidget::playBlackHoleAnimation() {
    dynamic_cast<BlackHole *>(game.getFinalBlackHole())->playSound();
    int blackHoleX = game.getFinalBlackHole()->getX();
    int blackHoleY = game.getFinalBlackHole()->getY();
    int blackHoleWidth = game.getFinalBlackHole()->getWidth();
    int blackHoleHeight = game.getFinalBlackHole()->getHeight();
    int blackHoleCenterX = blackHoleX + blackHoleWidth;
    int blackHoleCenterY = blackHoleY + blackHoleHeight / 2;

    int doubleJumperX = game.getDoubleJumperX();
    int doubleJumperY = game.getDoubleJumperY();
    int doubleJumperWidth = game.getDoubleJumper()->getWidth();
    int doubleJumperHeight = game.getDoubleJumper()->getHeight();
    int doubleJumperCenterX = doubleJumperX + doubleJumperWidth / 2;
    int doubleJumperCenterY = doubleJumperY + doubleJumperHeight / 2;

    int distanseX = blackHoleCenterX - doubleJumperCenterX;
    int distanseY = blackHoleCenterY - doubleJumperCenterY;

    int deltaX = distanseX / blackHoleAnimationTicks;
    int deltaY = distanseY / blackHoleAnimationTicks;
    //   std::cout<<blackHoleCenterX<<' '<<blackHoleCenterY<<' '<<doubleJumperCenterX<<' '<<doubleJumperCenterY<<' '<<deltaX<<' '<<deltaY<<' '<<blackHoleAnimationTicks<<std::endl;
    game.getDoubleJumper()->setCoordinateX(game.getDoubleJumper()->getCoordinateX() + deltaX);
    game.getDoubleJumper()->setCoordinateY(game.getDoubleJumper()->getCoordinateY() + deltaY);
    doubleJumperLabel->setGeometry(doubleJumperLabel->x() + deltaX, doubleJumperLabel->y() + deltaY,
                                   doubleJumperLabel->width() - 3, doubleJumperLabel->height() - 3);
    if (currentHatLabel != nullptr) {
        currentHatLabel->setGeometry(currentHatLabel->x() + deltaX, currentHatLabel->y() + deltaY,
                                     currentHatLabel->width() - 3, currentHatLabel->height() - 3);
    }
    if (currentJetpackLabel != nullptr) {
        currentJetpackLabel->setGeometry(currentJetpackLabel->x() + deltaX, currentJetpackLabel->y() + deltaY,
                                         currentJetpackLabel->width() - 3, currentJetpackLabel->height() - 3);
    }
}

GameWidget::~GameWidget() {

    delete doubleJumperLabel;
    if (currentJetpackLabel != nullptr) {
        delete currentJetpackLabel;
    }
    if (currentHatLabel != nullptr) {
        delete currentHatLabel;
    }
    for (auto pointer: platforms) {
        delete pointer;
    }
    for (auto pointer: items) {
        delete pointer;
    }
    // game.End();
}

int GameWidget::calculateLabelWidth(const QLabel *label, const QString &text) {
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

void GameWidget::visualizeScoreMarkers() {
    for (int i = 0; i < scoreMarkers.size(); i++) {
        delete scoreMarkers[i];
        delete scoreMarkerNames[i];
    }
    // bestScore = (850 - cord)/3
    // 3 * bestScore = 850 - cord
    //
    scoreMarkers.clear();
    scoreMarkerNames.clear();
    auto recordsStorage = dynamic_cast<MainWindow*>(parent())->records->getRecords();
    for (auto pointer: *recordsStorage) {
        int recordCoord = 850 - pointer.getScore() * 3;
        recordCoord += game.getShift();
      //  std::cout << recordCoord << '\n';
        if (recordCoord <= 850 && recordCoord >= 0) {
            QLabel *label = new QLabel(this);
            label->setScaledContents(true);
            label->setPixmap(QPixmap(prefixPath + scoreMarkerImagePath));
            label->setGeometry(640 - 80, recordCoord, 80, 40);
            scoreMarkers.push_back(label);
            QLabel *nameLabel = new QLabel(this);
            int reqWidth = calculateLabelWidth(nameLabel,pointer.getPlayerName());
            nameLabel->setScaledContents(true);
            nameLabel->setGeometry(640 - reqWidth, recordCoord - 25, reqWidth, 40);
            nameLabel->setText(pointer.getPlayerName());
            nameLabel->show();
            scoreMarkerNames.push_back(nameLabel);

            label->show();
        }
    }
}
void GameWidget::changeScoreMarkersVisibility() {
    showScoreMarkers = !showScoreMarkers;
}
void GameWidget::setTheme(Theme *theme) {
    game.getDoubleJumper()->setTheme(theme);
    currentTheme = theme;
    backgoundImagePath = theme->getBackgroundImagePath();
    backgoundLabel->setPixmap(QPixmap(prefixPath + backgoundImagePath));
}
