##

option(BUILD_A05_FLYBALL_GOVERNOR "Build A05 flyball governor example" ON)
if(BUILD_A05_FLYBALL_GOVERNOR)

    # Define project
    project (A05_FlyballGovernor)

    include_directories(${OPENSIM_INCLUDE_DIRS} ${SIMTK_INCLUDE_DIRS})
    include_directories(${SIMULATION_MANAGER_INCLUDE_DIRS})

    ## Create model
    # Identify the cpp file(s) that were to be built
    set(A05_CREATE_MODEL_SOURCE_FILES createModel.cpp)
    set(A05_CREATE_MODEL_HEADER_FILES modelProperties.h)

    source_group("Headers" FILES ${A05_CREATE_MODEL_HEADER_FILES})
    source_group("Sources" FILES ${A05_CREATE_MODEL_SOURCE_FILES})

    add_executable(FlyballGovernorCreateModel ${A05_CREATE_MODEL_HEADER_FILES} ${A05_CREATE_MODEL_SOURCE_FILES})
    target_link_libraries(FlyballGovernorCreateModel ${OPENSIM_LIBRARIES})

    ## Simulate

    set(A05_SIMULATE_SOURCE_FILES simulate.cpp)

    source_group("Sources" FILES ${A05_SIMULATE_SOURCE_FILES})

    add_executable(FlyballGovernorSimulate ${A05_SIMULATE_SOURCE_FILES})
    target_link_libraries(FlyballGovernorSimulate simulationManager ${OPENSIM_LIBRARIES})

endif()

