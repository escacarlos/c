set(TEST_SOURCES1 ../case.c ../liste_de_cases.c ../file_joueur.c)
add_executable(test_file file_main.cpp ${TEST_SOURCES1})

set(TEST_SOURCES2 ../generateur_nombres_aleatoires.c)
add_executable(test_generateur_nombres generateur_nombres_aleatoires_main.cpp ${TEST_SOURCES2})


set(TEST_SOURCES
        ${PROJECT_SOURCE_DIR}/case.c
        ${PROJECT_SOURCE_DIR}/liste_de_cases.c
        ${PROJECT_SOURCE_DIR}/liste_circulaire_couleur.c
        ${PROJECT_SOURCE_DIR}/file_joueur.c
        ${PROJECT_SOURCE_DIR}/generateur_nombres_aleatoires.c
        ${PROJECT_SOURCE_DIR}/generateur_JeuSE_aleatoire.c
        ${PROJECT_SOURCE_DIR}/jeu_serpent_echelles.c
)
add_executable(test_all file_main.cpp generateur_nombres_aleatoires_main.cpp ${TEST_SOURCES})

#target_include_directories(test_file PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(test_file gtest_main gtest pthread)
target_link_libraries(test_generateur_nombres gtest_main gtest pthread)
target_link_libraries(test_all gtest_main gtest pthread)

include(GoogleTest)
# gtest_discover_tests(test_file test_generateur_nombres test_all)
gtest_discover_tests(test_file)
gtest_discover_tests(test_generateur_nombres)
gtest_discover_tests(test_all)