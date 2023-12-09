/**
 * @file Particle.h
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the definition of the Particle class.
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "Shape.h"

/**
 * @brief This class represents a Particle.
 * A particle has a name and a trajectory, trajectory includes time and the corresponding position(x,y).
 */
class Particle{
 public:
    void insertTrajectories(float fTimestamp, Point p);
    std::vector<std::pair<float, Point>> getTrajectories();
    void setName(std::string name);
    std::string getName();
 private:
    std::vector<std::pair<float, Point>> mvTrajectories;
    std::string msName;
};


#endif