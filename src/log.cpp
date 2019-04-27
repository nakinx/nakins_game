#include "log.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

cLog::cLog() {
}

cLog::~cLog() {
    m_oFile.close();
}

cLog & cLog::getInstance() {
    static cLog oLog;
    return (oLog);
}

void cLog::initialize() {
    m_oFile.open(NX_LOG_PATH, std::fstream::in | std::fstream::out | std::fstream::app);
    }

void cLog::write(const std::string oMsg) {
    write(eServeriyLevel::Info, oMsg);
    }

void cLog::write(const eServeriyLevel oSeverityLevel, const std::string oMsg) {
    m_oFile << "[" << getCurrentTime() << "][" << getServerityName(oSeverityLevel) << "] " << oMsg << std::endl;
    m_oFile.flush();    
    }

std::string cLog::getServerityName(const eServeriyLevel oSeverityLevel) {
    switch(oSeverityLevel){
        case eServeriyLevel::Debug : return ("debug");
        case eServeriyLevel::Fatal : return ("fatal");
        case eServeriyLevel::Error : return ("error");
        case eServeriyLevel::Warning : return ("warning");
        case eServeriyLevel::Verbose : return ("verbose");
        case eServeriyLevel::Info : return ("info");
        case eServeriyLevel::Unknown : return ("unknown");
        default : return ("unknown");
    }
}

std::string cLog::getServerityDescription(const eServeriyLevel oSeverityLevel) {
    switch(oSeverityLevel){
        case eServeriyLevel::Debug : return ("Informational events most useful for developers to debug application.");
        case eServeriyLevel::Fatal : return ("Severe error information that will presumably abort application.");
        case eServeriyLevel::Error : return ("Information representing errors in application but application will keep running.");
        case eServeriyLevel::Warning : return ("Useful when application has potentially harmful situtaions. ");
        case eServeriyLevel::Verbose : return ("Information that can be highly useful and vary with verbose logging level.");
        case eServeriyLevel::Info : return ("Mainly useful to represent current progress of application.");
        case eServeriyLevel::Unknown : return ("Unknown level.");
        default : return ("Unknown level.");
    }
}

std::string cLog::getCurrentTime() {    
    std::stringstream oTime;

    auto oCurrentTime = std::chrono::system_clock::now();
    std::time_t oCurrentTimeTT = std::chrono::system_clock::to_time_t(oCurrentTime);
    std::tm oCurrentLT = *std::localtime(&oCurrentTimeTT);
    auto aMilliseconds = (oCurrentTime.time_since_epoch().count() / 1000000) % 1000;

    oTime << std::put_time(&oCurrentLT, "%T") << ":" << aMilliseconds;

    return (oTime.str());
}

