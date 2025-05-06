//
// Created by radamir on 06.05.25.
//

#include "Theme.h"
QString Theme::getBackgroundImagePath() {
    return backgroundImagePath;
}
QString Theme::getJetpackImagePath() {
    return jetpackImagePath;
}
QString Theme::getPropellerImagePath() {
    return propellerImagePath;
}
QString Theme::getThemePreviewPath() {
    return themePreviewPath;
}
QString Theme::getGameTileImagePath() {
    return gameTileImagePath;
}
QString Theme::getLeftOrientedImagePath() {
    return leftOrientedImagePath;
}
QString Theme::getRightOrientedImagePath() {
    return rightOrientedImagePath;
}
QString Theme::getScoreBarImagePath() {
    return scoreBarImagePath;
}
QString Theme::getLeftOrientedHoppedImagePath() {
    return leftOrientedHoppedImagePath;
}
QString Theme::getRightOrientedHoppedImagePath() {
    return rightOrientedHoppedImagePath;
}


DefaultTheme::DefaultTheme() {
    backgroundImagePath = "bck@2x.png";
    leftOrientedImagePath = "lik-left@2x.png";
    rightOrientedImagePath = "lik-right@2x.png";
    leftOrientedHoppedImagePath = "lik-left-odskok@2x.png";
    rightOrientedHoppedImagePath = "lik-right-odskok@2x.png";
    gameTileImagePath = "game-tiles@2x.png";
    jetpackImagePath = "jetpack@2x.png";
    propellerImagePath = "propeller@2x.png";
    scoreBarImagePath = "top-score@2x.png";
    themePreviewPath = "default-preview@2x.png";
}
UnderwaterTheme::UnderwaterTheme() {
    backgroundImagePath = "underwater-bck@2x.png";
    leftOrientedImagePath = "underwater-left@2x.png";
    rightOrientedImagePath = "underwater-right@2x.png";
    leftOrientedHoppedImagePath = "underwater-left-odskok@2x.png";
    rightOrientedHoppedImagePath = "underwater-right-odskok@2x.png";
    gameTileImagePath = "game-tiles-underwater@2x.png";
    jetpackImagePath = "jetpack-underwater@2x.png";
    propellerImagePath = "propeller-underwater@2x.png";
    scoreBarImagePath = "underwater-top-score@2x.png";
    themePreviewPath = "underwater-preview@2x.png";
}
HaloweenTheme::HaloweenTheme() {
    backgroundImagePath = "doodlestein-bck@2x.png";
    leftOrientedImagePath = "doodlestein-left@2x.png";
    rightOrientedImagePath = "doodlestein-right@2x.png";
    leftOrientedHoppedImagePath = "doodlestein-left-odskok@2x.png";
    rightOrientedHoppedImagePath = "doodlestein-right-odskok@2x.png";
    gameTileImagePath = "game-tiles-halloween@2x.png";
    jetpackImagePath = "jetpack-doodlestein@2x.png";
    propellerImagePath = "propeller-doodlestein@2x.png";
    scoreBarImagePath = "halloween-top-score@2x.png";
    themePreviewPath = "doodlestein-preview@2x.png";
}
SpaceTheme::SpaceTheme() {
    backgroundImagePath = "space-bck@2x.png";
    leftOrientedImagePath = "space-left@2x.png";
    rightOrientedImagePath = "space-right@2x.png";
    leftOrientedHoppedImagePath = "space-left-odskok@2x.png";
    rightOrientedHoppedImagePath = "space-right-odskok@2x.png";
    gameTileImagePath = "game-tiles-space@2x.png";
    jetpackImagePath = "jetpack-space@2x.png";
    propellerImagePath = "propeller-space@2x.png";
    scoreBarImagePath = "space-top-score@2x.png";
    themePreviewPath = "space-preview@2x.png";
}

