#ifndef CLOG_H_
#define CLOG_H_

#include <string>
#include <fstream>

#define NX_LOG_PATH "nakins.log"

enum class eServeriyLevel {  
  Debug = 1, ///< Informational events most useful for developers to debug application.  
  Fatal = 2, ///< Severe error information that will presumably abort application.  
  Error = 4, ///< Information representing errors in application but application will keep running.  
  Warning = 8, ///< Useful when application has potentially harmful situtaions.  
  Verbose = 16, ///< Information that can be highly useful and vary with verbose logging level.  
  Info = 32, ///< Mainly useful to represent current progress of application.  
  Unknown = 2048 ///< Represents unknown level.
};

class cLog {

public:

    ~cLog();

    void initialize();

    static cLog & getInstance();

    void write(const std::string oMsg);

    void write(const eServeriyLevel oSeverityLevel, const std::string oMsg);

    std::string getServerityName(const eServeriyLevel oSeverityLevel);

    std::string getServerityDescription(const eServeriyLevel oSeverityLevel);

private:

    std::fstream m_oFile;  

    cLog();
    cLog(cLog const&);           
    void operator=(cLog const&);    

    std::string getCurrentTime();

};

#endif // CLOG_H_ 