//
// Created by Admin on 05/12/2023.
//
#include "main.hpp"

bool Vector::operator==(const Vector &other) const {
    return (this->x==other.x && this->y==other.y);
}

bool Vector::operator!=(const Vector &other) const {
    return !(this->x==other.x && this->y==other.y);
}

Vector Vector::operator+(const Vector &other) const {
    return {this->x+other.x,this->y+other.y};
}

Vector Vector::operator-(const Vector &other) const{
    return {this->x-other.x,this->y-other.y};
}

void Vector::operator+=(const Vector &other) {
    this->x+=other.x;
    this->y+=other.y;
}

void Vector::operator-=(const Vector &other) {
    this->x-=other.x;
    this->y-=other.y;
}

