#Minimalna wersja cmake konieczna do zbudowania tego projektu
cmake_minimum_required(VERSION 3.15)

#Parametry konfiguracyjne platformy programistycznej i flagi kompilatora
set(CMAKE_CXX_COMPILER g++)#g++ jako kompilator C++
set(CMAKE_C_COMPILER gcc)#gcc jako kompilator C
set(CMAKE_CXX_STANDARD 11)#Standard C++ 11, bez tego parametru g++ uĹźyje wartoĹci domyĹlnej. Dla g++ od wersji 6 jest to C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)#OkreĹlony wyĹźej standard C++ jest wymagany

#Profil debug i maksymalny poziom debug info g3 oraz format debug info na dwarf-4 (musi byÄ gdb w wersji 7). BUILD_TYPE moĹźe byÄ ustawiony na:
#empty,
#Debug,
#Release,
#RelWithDebInfo
#MinSizeRel
#Ustawiono dodatkowo flagi debug generujÄce informacjÄ dla debuggera
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")

#Ustaw nazwÄ projektu i jÄzyk na C++
project(CinemaProject)
enable_language(CXX)

find_package(Boost 1.65 COMPONENTS unit_test_framework system filesystem program_options date_time REQUIRED)
link_directories($(Boost_LIBRARY_DIR))

include_directories(
        include
        ${Boost_INCLUDE_DIRS})


#W specjalnym pliku compile_commands.json moĹźna podejrzeÄ wszystkie operacje kompilatora wraz z parametrami,
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)


#uwzglÄdnij podprojek znajdujÄcy siÄ w podkatalogu program. Musi byÄ w nim pliki CMakeLists.txt
add_subdirectory(program)

add_subdirectory(library)

set (CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra  -Werror")

#WĹÄczenie testĂłw powoduje pojawienie siÄ celu test w makefiles
enable_testing()
