cmake_minimum_required(VERSION 3.16)
project(PetLife LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt6 REQUIRED COMPONENTS Core Quick Multimedia)

qt_add_executable(PetLife
    main.cpp
    PetStatus.cpp
    PetStatus.h
    resources.qrc
    MusicPlayer.h
    MusicPlayer.cpp
    PetSelectionModel.h
    PetSelectionModel.cpp
)

target_link_libraries(PetLife PRIVATE Qt6::Core Qt6::Quick Qt6::Multimedia)
