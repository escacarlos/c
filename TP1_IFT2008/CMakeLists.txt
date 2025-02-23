cmake_minimum_required(VERSION 3.10)

# Set the project name
project(JeuSerpentEchelles)

# Specify the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
#-static-libgcc -static-libstdc++ -ggdb")


# Include directories
#include_directories(
#        ${PROJECT_SOURCE_DIR}
#)

# List all the source files
set(SOURCES
        case.c
        liste_de_cases.c
        liste_circulaire_couleur.c
        file_joueur.c
        generateur_nombres_aleatoires.c
        generateur_JeuSE_aleatoire.c
        jeu_serpent_echelles.c
        principal.c
        # tp1_single_file.c
)

# Add the executable target
add_executable(JeuSerpentEchelles ${SOURCES})

enable_testing()

add_subdirectory(tests)


