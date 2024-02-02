cmake_minimum_required(VERSION 3.25)
project(SetLed VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(SetLed
    ./SetLed/main.cpp
    
    ./SetLed/StatusController.cpp
    ./SetLed/StatusController.hpp


    ./common/utility/buffer.cpp
    ./common/utility/buffer.hpp
    ./common/utility/dbgutil.hpp
    ./common/utility/mapfile.cpp
    ./common/utility/mapfile.hpp
    ./common/utility/strutil.hpp
    ./common/utility/timeutil.cpp
    ./common/utility/timeutil.hpp
    

)

if (WIN32)
    target_compile_definitions(SetLed PRIVATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:_DEBUG=1>
        __WINDOWS_DS__
        _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
        _WIN32_WINNT=0x0A00
    )

    target_compile_options(SetLed PRIVATE
        $<$<CONFIG:Release>:/O2>
    )

    target_link_libraries(SetLed
        PUBLIC
            ole32
            dsound
    )
else()
    target_compile_definitions(SetLed PRIVATE
        $<$<CONFIG:Debug>:DEBUG=1>
    )

    target_compile_options(SetLed PRIVATE
        $<$<CONFIG:Release>:-O2>
        -Wno-deprecated-declarations
    )
    if (APPLE)
        target_compile_definitions(SetLed PRIVATE
            __MACOSX_CORE__
        )

        FIND_LIBRARY(COREAUDIO CoreAudio)
        FIND_LIBRARY(COREFOUNDATION CoreFoundation )
        MARK_AS_ADVANCED ( COREAUDIO COREFOUNDATION )

        target_link_libraries(SetLed
            PUBLIC
                pthread
                ${COREAUDIO}
                ${COREFOUNDATION}
        )

    else ()
        target_compile_definitions(SetLed PRIVATE
            __LINUX_ALSA__
        )

        if (BEAGLE)
            target_compile_definitions(SetLed PRIVATE
                BEAGLE
                STATUSLED
            )
        endif (BEAGLE)
    
        target_link_libraries(SetLed
            PUBLIC
                asound
                pthread
        )

    endif (APPLE)
    
endif (WIN32)

target_include_directories(SetLed
    PUBLIC
        ${PROJECT_SOURCE_DIR}/
        ${PROJECT_SOURCE_DIR}/common/
        ${PROJECT_SOURCE_DIR}/thirdparty/
        ${PROJECT_SOURCE_DIR}/thirdparty/asio/
)


