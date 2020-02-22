//
// Created by adi on 15/12/2019.
//

#include "Var.h"
#include "string"
#include "map"
#include <iostream>


using namespace std;

Var::Var(string name1, double val, bool update, string sim1) {

    this->value = val;
    this->sim = sim1;
    this->varName = name1;
    this->varUpdateSim = update;
}

// Symbol Table implementations:
SymbolTable::SymbolTable(map<string, Var *> ptrVarMap1, map<string, Var *> ptrSimMap1) {
    this->simMap = ptrSimMap1;
    this->varMap = ptrVarMap1;
    indexFromXmlToValMap[1] = "instrumentation/airspeed-indicator/indicated-speed-kt";
    indexFromXmlToValMap[2] = "sim/time/warp";
    indexFromXmlToValMap[3] = "controls/switches/magnetos";
    indexFromXmlToValMap[4] = "instrumentation/heading-indicator/offset-deg";
    indexFromXmlToValMap[5] = "instrumentation/altimeter/indicated-altitude-ft";
    indexFromXmlToValMap[6] = "instrumentation/altimeter/pressure-alt-ft";
    indexFromXmlToValMap[7] = "instrumentation/attitude-indicator/indicated-pitch-deg";
    indexFromXmlToValMap[8] = "instrumentation/attitude-indicator/indicated-roll-deg";
    indexFromXmlToValMap[9] = "instrumentation/attitude-indicator/internal-pitch-deg";
    indexFromXmlToValMap[10] = "instrumentation/attitude-indicator/internal-roll-deg";
    indexFromXmlToValMap[11] = "instrumentation/encoder/indicated-altitude-ft";
    indexFromXmlToValMap[12] = "instrumentation/encoder/pressure-alt-ft";
    indexFromXmlToValMap[13] = "instrumentation/gps/indicated-altitude-ft";
    indexFromXmlToValMap[14] = "instrumentation/gps/indicated-ground-speed-kt";
    indexFromXmlToValMap[15] = "instrumentation/gps/indicated-vertical-speed";
    indexFromXmlToValMap[16] = "instrumentation/heading-indicator/indicated-heading-deg";
    indexFromXmlToValMap[17] = "instrumentation/magnetic-compass/indicated-heading-deg";
    indexFromXmlToValMap[18] = "instrumentation/slip-skid-ball/indicated-slip-skid";
    indexFromXmlToValMap[19] = "instrumentation/turn-indicator/indicated-turn-rate";
    indexFromXmlToValMap[20] = "instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    indexFromXmlToValMap[21] = "controls/flight/aileron";
    indexFromXmlToValMap[22] = "controls/flight/elevator";
    indexFromXmlToValMap[23] = "controls/flight/rudder";
    indexFromXmlToValMap[24] = "controls/flight/flaps";
    indexFromXmlToValMap[25] = "controls/engines/engine/throttle";
    indexFromXmlToValMap[26] = "controls/engines/current-engine/throttle";
    indexFromXmlToValMap[27] = "controls/switches/master-avionics";
    indexFromXmlToValMap[28] = "controls/switches/starter";
    indexFromXmlToValMap[29] = "engines/active-engine/auto-start";
    indexFromXmlToValMap[30] = "controls/flight/speedbrake";
    indexFromXmlToValMap[31] = "sim/model/c172p/brake-parking";
    indexFromXmlToValMap[32] = "controls/engines/engine/primer";
    indexFromXmlToValMap[33] = "controls/engines/current-engine/mixture";
    indexFromXmlToValMap[34] = "controls/switches/master-bat";
    indexFromXmlToValMap[35] = "controls/switches/master-alt";
    indexFromXmlToValMap[36] = "engines/engine/rpm";
    // initialize the simPathToValFromSimMap map with the string indexFromXmlToValMap.
    for(int i = 1; i <= 36; i++) {
        simPathToValFromSimMap[indexFromXmlToValMap[i]] = 0;
    }
}


// a test function for printing
void SymbolTable::printXML() {
    for(int i = 1; i <= 36 ; i++) {
        std::cout << simPathToValFromSimMap[indexFromXmlToValMap[i]];
        cout << ",";
    }
    cout << endl;
}

