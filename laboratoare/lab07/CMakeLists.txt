cmake_minimum_required(VERSION 4.1)
project(lab07)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab07 main.cpp
        utils/CustomVector.h
        domain/Produs.cpp
        domain/Produs.h
        repo/RepoProduse.cpp
        repo/RepoProduse.h
        service/ServiceProduse.cpp
        service/ServiceProduse.h
        ui/UI.cpp
        ui/UI.h
        exceptions/RepositoryException.h
        validators/ProdusValidator.cpp
        validators/ProdusValidator.h
        utils/ProdusComparators.h)

add_executable(tests tests.cpp
        utils/CustomVector.h
        domain/Produs.cpp
        domain/Produs.h
        repo/RepoProduse.cpp
        repo/RepoProduse.h
        service/ServiceProduse.cpp
        service/ServiceProduse.h
        validators/ProdusValidator.cpp
        validators/ProdusValidator.h
        utils/ProdusComparators.h)