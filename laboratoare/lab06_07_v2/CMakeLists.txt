cmake_minimum_required(VERSION 4.1)
project(lab06_07_v2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab06_07_v2 main.cpp
        domain/produs.cpp
        domain/produs.h
        ui/ui.cpp
        ui/ui.h
        repo/repo.cpp
        repo/repo.h
        service/utils.cpp
        service/utils.h
        service/service.cpp
        service/service.h
)



add_executable(tests tests/teste.cpp
        domain/produs.cpp
        domain/produs.h
        ui/ui.cpp
        ui/ui.h
        repo/repo.cpp
        repo/repo.h
        service/utils.cpp
        service/utils.h
        service/service.cpp
        service/service.h
)