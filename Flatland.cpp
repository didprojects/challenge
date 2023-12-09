/**
 * @file Flatland.cpp
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the implementation of the Flatland class.
 */

#include "Flatland.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

string decodedata(string nameLine, string dataLine, vector<Point>& vVertices);
string decodedata(string nameLine, string dataLine, vector<float>& vData);

Flatland::Flatland(vector<string>& vsInputData){

    vector<string>::iterator itrBegin = vsInputData.begin();
    vector<string>::iterator itrBeginPartical;
    
    // Create shape areas for the land from the input data
    for(auto it = itrBegin; it != vsInputData.end()-1; it++){
        string curLine = *it;
        string nextLine = *(it+1);
        // Stop when find "PARTICLE" in the line
        if(!insertShape(curLine,nextLine)){
            itrBeginPartical = it;
            break;
        }
    }

    // Create particles for the land from the input data
    for(auto it = itrBeginPartical; it != vsInputData.end(); it++){
        string line = *it;
        insertPartical(line);
    }
}

Flatland::~Flatland(){
    for(auto shape : mvShapes){
        delete shape;
    }
    for(auto particle : mvParticles){
        delete particle;
    }
}

// Generate notification when a particle has entered or left an area by checking if particle is inside or outside of the area
// Write the result into an output file 
// output format:
//    ENTER <time> <particle name> <area name>
//    EXIT <time> <particle name> <area name>
void Flatland::checkIfParticlesInsideAreas(const string sOutFile){
    vector<Output> vOuts;
    for(auto particle : mvParticles){
        for(auto shape : mvShapes){
            vector<pair<float, Point>> trajectory = particle->getTrajectories();
            for(auto it = trajectory.begin(); it != trajectory.end()-1; it++){
                pair<float, Point> tpos1 =*it;       //time1, particle vertex
                pair<float, Point> tpos2 =*(it+1);   //time2, particle vertex

                // Check if a point is inside of a shape
                // true - inside or on the side
                // false - outside
                bool pos1State = false, pos2State = false;
                pos1State = shape->isPointInsideArea(tpos1.second);
                pos2State = shape->isPointInsideArea(tpos2.second);

                // Decide ENTER or EXIT, based on the result of time1 and time2
                Output sOut;
                if(pos1State && !pos2State){
                    sOut.state = "EXIT";
                    sOut.time = tpos2.first;
                    sOut.particleName = particle->getName();
                    sOut.areaName = shape->msAreaName;
                    vOuts.push_back(sOut);
                }
                if(!pos1State && pos2State){
                    sOut.state = "ENTER";
                    sOut.time = tpos2.first;
                    sOut.particleName = particle->getName();
                    sOut.areaName = shape->msAreaName;
                    vOuts.push_back(sOut);
                }
                
            }
        }
    }

    // Sort the result by time
    sort(vOuts.begin(), vOuts.end());

    ofstream fileOut(sOutFile);
    cout<<"\nNotification:"<<endl;
    cout<<endl;
    for(auto out : vOuts){
        cout<<fixed<<setprecision(2)<<out.state<<" "<<out.time<<" "<<out.particleName<<"  "<<out.areaName<<"\n";
        fileOut<<fixed<<setprecision(2)<<out.state<<" "<<out.time<<" "<<out.particleName<<"  "<<out.areaName<<"\n";
    }
    fileOut.close();
}

// Print shape type and shape name
void Flatland::printShapes(){
    cout<<"\nShapes:"<<endl;
    for(auto shape : mvShapes){
        if(shape->mType == RECTANGLE) cout<<"RECTANGLE"<<"  "<<shape->msAreaName<<endl;
        else if(shape->mType == CIRCLE) cout<<"CIRCLE"<<"  "<<shape->msAreaName<<endl;
        else if(shape->mType == TRIANGLE) cout<<"TRIANGLE"<<"  "<<shape->msAreaName<<endl;
        else cout<<"POLYGON"<<"  "<<shape->msAreaName<<endl;
    }
}

// Print particle trajectory
void Flatland::printParticles(){
    cout<<"\nParticles:"<<endl;
    for(auto particle : mvParticles){
        vector<pair<float, Point>> particleTraj = particle->getTrajectories();
        for(auto traj : particleTraj){
            cout<<fixed<<setprecision(2)<<particle->getName()<<"  "<<traj.first<<"  "<<traj.second.pX<<"  "<<traj.second.pY<<endl;
        }
    }
}

// Decode input data and create shapes, insert shape into mvShapes
bool Flatland::insertShape(string nameLine, string dataLine){
    vector<Point> vertices;
    vector<float> data;

    if(nameLine.find("RECTANGLE") != std::string::npos){
        Rectangle *rect = new Rectangle;
        rect->mType = RECTANGLE;
        string sAreaName = decodedata(nameLine,dataLine,vertices);
        rect->msAreaName = sAreaName;
        for(auto vertex : vertices){
            rect->insertVertex(vertex);
        }
        mvShapes.push_back(rect);
    }else if(nameLine.find("TRIANGLE") != std::string::npos){
        Triangle *triangle = new Triangle;
        triangle->mType = TRIANGLE;
        string sAreaName = decodedata(nameLine,dataLine,vertices);
        triangle->msAreaName = sAreaName;
        for(auto vertex : vertices){
            triangle->insertVertex(vertex);
        }
        mvShapes.push_back(triangle);
    }else if(nameLine.find("CIRCLE") != std::string::npos){
        Circle *circle = new Circle;
        circle->mType = CIRCLE;
        string sAreaName = decodedata(nameLine,dataLine,data);
        circle->msAreaName = sAreaName;
        Point center;
        center.pX = data[0];
        center.pY = data[1]; 
        
        circle->setCenter(center);
        circle->setRadius(data[2]);
        mvShapes.push_back(circle);
    }else if(nameLine.find("POLYGON") != std::string::npos){
        Polygon *polygon = new Polygon;
        polygon->mType = POLYGON;
        string sAreaName = decodedata(nameLine,dataLine,vertices);
        polygon->msAreaName = sAreaName;
        for(auto vertex : vertices){
            polygon->insertVertex(vertex);
        }
        mvShapes.push_back(polygon);
    }else if(nameLine.find("PARTICLE") != std::string::npos){
        return false;
    }
    return true;
}

// Decode input data and create particles, insert particle into mvParticles
void Flatland::insertPartical(string line){
    if(line.find("PARTICLE") != std::string::npos){
        Particle *particle = new Particle;
        stringstream sstr(line);
        string s;
        
        getline(sstr, s, ' ');
        getline(sstr, s, ' ');
        particle->setName(s);
        mvParticles.push_back(particle);
    }else if(line[0] == 'T'){
        stringstream sstr(line);
        string s;
        getline(sstr, s, ' ');
        getline(sstr, s, ' ');    
        float time = stof(s);    
        for(auto particle : mvParticles){
            getline(sstr, s, ' ');
            stringstream ss(s);
            Point pt;
            getline(ss, s, ',');
            pt.pX = stof(s);
            getline(ss, s, ',');
            pt.pY = stof(s);
            particle->insertTrajectories(time,pt);
        }
    }
}

// Extract vertex data based on if rectangle, triangle, polygon has recognised in the current line
string decodedata(string sNameLine, string sDataLine, vector<Point>& vertices){
    stringstream ssCur(sNameLine);
    string sAreaName;
    string s;
    
    getline(ssCur, s, ' ');
    getline(ssCur, s);

    sAreaName = s;
    
    stringstream ssNext(sDataLine);
    vector<string> vsNext;
    while(getline(ssNext, s, ' ')) {
        vsNext.push_back(s);
    }
    for(string sdt : vsNext){
        stringstream ssData(sdt);
        Point vertex;
        getline(ssData,s,',');
        vertex.pX = stof(s);
        getline(ssData,s);
        vertex.pY = stof(s);
        vertices.push_back(vertex);
    }
    return sAreaName;
}

// Extract center, radius of a circle
string decodedata(string sNameLine, string sDataLine, vector<float>& vfData){
    stringstream ssCur(sNameLine);
    string sAreaName;
    string s;
    
    getline(ssCur, s, ' ');
    getline(ssCur, s);

    sAreaName = s;

    stringstream ssNext(sDataLine);
    vector<string> vsNext;
    while(getline(ssNext, s, ' ')) {
        vsNext.push_back(s);
    }

    stringstream ssData(vsNext[0]);
    getline(ssData,s,',');
    float px = stof(s);
    vfData.push_back(px);
    getline(ssData,s);
    float py = stof(s);
    vfData.push_back(py);
    
    float radius = stof(vsNext[1]);
    vfData.push_back(radius);
    
    return sAreaName;
}
