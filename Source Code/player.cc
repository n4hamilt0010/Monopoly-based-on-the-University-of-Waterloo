#include "player.h"

Player::Player(std::string name, char piece, int balance = 1500, int pos = 0, int turnsInLine = 0, int timsCups = 0) :
    name{name}, piece{piece}, balance{balance}, pos{pos}, turnsInLine{turnsInLine}, timsCups{timsCups} {
        withdraw = false;
    }

Player::~Player() { }

int Player::getBalance() { return balance; }

std::string Player::getName() { return name; }

char Player::getPiece() { return piece; }

int Player::getPos() { return pos; }

int Player::getTurnsInLine() { return turnsInLine; }

int Player::getTimsCups() { return timsCups; }

bool Player::getWithdraw() { return withdraw; }

void Player::setBalance(int setTo) { balance = setTo; }

void Player::setPos(int setTo) { pos = setTo; }

void Player::setTurnsInLine(int setTo) { turnsInLine = setTo; }

void Player::setTimsCups(int setTo) { timsCups = setTo; }

void Player::setWithdraw(bool setTo) { withdraw = setTo; }

void Player::addBalance(int add) { balance += add; }

void Player::subtractBalance(int subtract) { 
        balance -= subtract;
}

void Player::addPos(int roll) { 
    pos += roll;

    if (pos > 39) {
        pos -= 40;
    }
}

void Player::incrementTurnsInLine() { turnsInLine++; }

void Player::incrementTimsCups() { timsCups++; }

void Player::decrementTimsCups() { 
    if (timsCups > 0) {
        timsCups--;
    }
}

