//Copyright © 2024 Charles Kerr. All rights reserved.

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "utility/strutil.hpp"
#include "StatusController.hpp"

using namespace std::string_literals ;

int main(int argc, const char * argv[]) {
    auto exitcode = EXIT_SUCCESS ;
    StatusController statusController ;
    try {
        if (argc != 3) {
            throw std::runtime_error("Invalid arguments, must be: led (all,connect,run,show,play) state (flash,on,off") ;
        }
        auto led = util::lower(std::string(argv[1])) ;
        auto state =  util::lower(std::string(argv[2]));
        if (led != "all" && led != "connect" && led != "run"  && led != "show"  && led != "play") {
            throw std::runtime_error("Invalid led, must be one of: all,connect,run,show,play ");
        }
        if (state != "flash" && state != "on" && state != "off" ){
            throw std::runtime_error("Invalid led, must be one of: all,connect,run,show,play ");
        }
        auto ledstate = LEDInfo::OFF ;
        if ( state == "flash") {
            ledstate = LEDInfo::FLASH ;
        }
        else if (state == "on") {
            ledstate = LEDInfo::ON ;
        }
        else if ( state == "off") {
            ledstate = LEDInfo::OFF ;
        }
        if (led == "all") {
            statusController.setState(LEDInfo::RUN, ledstate, true) ;
            statusController.setState(LEDInfo::CONNECT, ledstate, true) ;
            statusController.setState(LEDInfo::SHOW, ledstate, true) ;
            statusController.setState(LEDInfo::PLAY, ledstate, true) ;
        }
        else if (led == "run"){
            statusController.setState(LEDInfo::RUN, ledstate, true) ;
        }
        else if (led == "connect"){
            statusController.setState(LEDInfo::CONNECT, ledstate, true) ;
        }
        else if (led == "show"){
            statusController.setState(LEDInfo::SHOW, ledstate, true) ;
        }
        else if (led == "play"){
            statusController.setState(LEDInfo::PLAY, ledstate, true) ;
        }
    }
    catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        exitcode = EXIT_FAILURE ;

    }
    catch(...) {
        std::cerr << "Unknown error!" << std::endl;
        exitcode = EXIT_FAILURE ;
    }
    return 0;
}
