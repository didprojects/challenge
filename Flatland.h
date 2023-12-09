/**
 * @file Flatland.h
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the definition of the Flatland class.
 */

#ifndef FLATLAND_H
#define FLATLAND_H

#include "Shape.h"
#include "Particle.h"

struct Output{
    std::string state;
    float time;
    std::string particleName;
    std::string areaName;
    bool operator < (const Output& rhs) const {
        return time < rhs.time;
    }
};

/**
 * @brief This class represents a Flatland.
 * A flat land has multiple areas(in different shapes), and multiple particles moving on the land.
 */
class Flatland{
 public:
    Flatland(std::vector<std::string>& vsInputData);
    ~Flatland();
    void checkIfParticlesInsideAreas(const std::string sOutFile);
    void printShapes();
    void printParticles();
 private:
    bool insertShape(std::string sNameLine, std::string sDataLine);
    void insertPartical(std::string sLine);
    std::vector<Shape*> mvShapes;
    std::vector<Particle*> mvParticles;
};

#endif