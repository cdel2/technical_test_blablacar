#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Mower.h"
#include "MowingSimulation.h"
#include "FileReader.h"
#include "Except.h"

#include "direction.h"
#include "action.h"
#include "lawn.h"
#include "position.h"

using namespace std;


int main(int argc, char* argv[]) {
    try {
        if (argc == 1) 
            throw Except("User must specify path to input file in command line argument.");
        if( argc > 2)
            throw Except("Only one argument must be passed to command line.");

        vector<Mower> mowers;
        Lawn lawn;

        FileReader fr(argv[1]);
        fr.read(mowers, lawn);

        MowingSimulation ms(mowers, lawn);
        ms.start();

        ms.printPositions();
    }
    catch (const Except& e) {
        cout << "Error: " << e.what() ;
    }
}