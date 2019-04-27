#include <iostream>
#include <locale>

#include "log.h"
#include "engine.h"

int main (int argc, char *argv[]) {

    // Set the locale of a application based on system definitions.
    std::locale::global(std::locale(""));    

    // Set default configuration for the log file.
    cLog::getInstance().initialize();

    cLog::getInstance().write("Stating nakinx game.");

    cEngine oEngine;

    oEngine.initialize();
    oEngine.loop();

    return (0);
}


