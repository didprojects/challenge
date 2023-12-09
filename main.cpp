/**
 * @file main.cpp
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the main process for trimbleflatlandchallenge task.
 */

#include "Shape.h"
#include "Flatland.h"
#include "Particle.h"
#include <iostream>
#include <fstream>

using namespace std;

bool readInputFile(const string filePath, vector<string>& vsData);

int main(int argc, char* argv[]){
    string inputPath = "";
    string printCmd = "";
    if(argc < 2){
        cout<<endl<< "Usage: ./main path_to_input_file"<<endl;
        return 1;
    }
    inputPath = argv[1];

    if(argc >= 3){
        printCmd =  argv[2];
    }

    // Read input test data
    vector<string> vsInputData;
    bool isOpen = readInputFile(inputPath,vsInputData);
    if(!isOpen){
        cout<<"Unable to open file!\n";
        return 1;   
    }

    Flatland flatland(vsInputData);

    // Print shape area and particle information in the flat land (for test)
    if(printCmd == "-p"){
        flatland.printShapes();    
        flatland.printParticles();
    }
    
    // Check if particles enter or exit an area, and output the result
    string outFile = "output.txt";
    flatland.checkIfParticlesInsideAreas(outFile);

    cout<<"\nOutput file name: "<<outFile<<endl;
    
    return 0;
}

bool readInputFile(const string filePath,vector<string>& vsData){
    ifstream fs(filePath);
    
    if(!fs.is_open()) return false;

    string line;
    while(getline(fs,line)){

        // Ignore blank lines or lines beginning with a '#'
        if(line.empty() || line[0] == '#'){
            continue;
        } 

        // Erase trailing white-spaces
        line.erase(line.find_last_not_of( "\t\n\r" ) + 1);

        vsData.push_back(line);
    }

    fs.close();

    return true;
}

