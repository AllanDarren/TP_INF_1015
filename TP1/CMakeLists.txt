cmake_minimum_required(VERSION 3.10)
project(exercices_TP1)

set(CMAKE_CXX_STANDARD 17)

# Exécutable pour exo1.cpp
add_executable(exercies_TP1 Main.cpp)

add_executable(exo1 exo1.cpp
        exo1.cpp
        exo1.cpp)
add_executable(exo2 exo2.cpp
        exo2.cpp)
#add_executable(exo3 exo3.cpp)
#add_executable(exo4 exo4.cpp)
#add_executable(exo5 exo5.cpp)
add_executable(exo3 exo3.cpp)
add_executable(exo4 exo4.cpp)
add_executable(exo5 exo5.cpp)
add_executable(exo6 exo6.cpp)
add_executable(back_a_sable ../../back_à_sable/back_a_sable.cpp
        ../../back_à_sable/class_et_autres.h)
add_executable(main Main.cpp)
