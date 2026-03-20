cmake_minimum_required(VERSION 4.0)
project(lab2_4 C)

set(CMAKE_C_STANDARD 11)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

add_executable(lab2_4 main.c
        main.c
        repo.c
        service.c
        tranzactie.c
        ui.c
        vector.c
        test_all.c
)
