cmake_minimum_required(VERSION 3.18)
project(ZooManager VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE)
  include(${wxWidgets_USE_FILE})
endif()
# sudo apt install nlohmann-json3-dev
find_package(nlohmann_json REQUIRED)
enable_testing()

set(SOURCES
    src/app/zoo_app.cpp
    src/gui/main_frame.cpp
    src/gui/detail_panel.cpp
    src/gui/add_edit.cpp
    src/animals/animal.cpp
    src/app/animal_manager.cpp
    src/animals/bird.cpp
    src/animals/fish.cpp
    src/animals/mammal.cpp
    src/animals/reptile.cpp
    src/animals/amphibian.cpp
)

add_executable(ZooManager ${SOURCES})

target_include_directories(ZooManager PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/animals
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/app
)

target_link_libraries(ZooManager PRIVATE 
    ${wxWidgets_LIBRARIES}
    nlohmann_json::nlohmann_json
)


add_executable(zoo_test
    src/test/zoo_test.cpp
    src/test/catch_amalgamated.cpp

    src/animals/animal.cpp
    src/animals/bird.cpp
    src/animals/fish.cpp
    src/animals/mammal.cpp
    src/animals/reptile.cpp
    src/animals/amphibian.cpp
    src/app/animal_manager.cpp
)

target_include_directories(zoo_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/animals
    ${CMAKE_SOURCE_DIR}/src/app
)

target_link_libraries(zoo_test PRIVATE
    pthread
    nlohmann_json::nlohmann_json
)

add_test(NAME ZooTests COMMAND zoo_test)



