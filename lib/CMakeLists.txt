

include_directories(${OPENSIM_INCLUDE_DIRS} ${SIMTK_INCLUDE_DIRS})

# Identify the cpp file(s) that were to be built
set(SIMULATION_MANAGER_SOURCE_FILES simulationManager.cpp configurationInterpreter.cpp)
set(SIMULATION_MANAGER_HEADER_FILES simulationManager.h configurationInterpreter.h)
source_group("Headers" FILES ${SIMULATION_MANAGER_HEADER_FILES})
source_group("Sources" FILES ${SIMULATION_MANAGER_SOURCE_FILES})

add_library(simulationManager ${SIMULATION_MANAGER_SOURCE_FILES} ${SIMULATION_MANAGER_HEADER_FILES})
target_link_libraries(simulationManager ${OPENSIM_LIBRARIES})

set(SIMULATION_MANAGER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${OPENSIM_INCLUDE_DIRS} ${SIMTK_INCLUDE_DIRS} CACHE STRING "Simulation manager include directories")


