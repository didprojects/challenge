/**
 * @file Particle.cpp
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the implementation of the Particle class.
 */

#include "Particle.h"
        
void Particle::insertTrajectories(float fTimestamp, Point p){
    mvTrajectories.push_back(std::make_pair(fTimestamp, p));
}

std::vector<std::pair<float, Point>> Particle::getTrajectories(){
    return mvTrajectories;
}

void Particle::setName(std::string name){
    msName = name;
}
std::string Particle::getName(){
    return msName;
}
