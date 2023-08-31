cmake_minimum_required(VERSION 3.17)
project(PeterStudent)

set(CMAKE_C_STANDARD 11)

add_executable(PeterStudent main.c)
add_subdirectory(./QuickGame QuickGame)

target_link_libraries(PeterStudent PUBLIC QuickGame)
target_include_directories(PeterStudent PUBLIC QuickGame/include)
target_include_directories(PeterStudent PUBLIC src/)

create_pbp_file(
    TARGET PeterStudent
    TITLE Peter-the-Student_PSP
    ICON_PATH assets/pbpicons/ICON0.png
    BACKGROUND_PATH assets/pbpicons/PIC1.png
    BUILD_PRX ON
)