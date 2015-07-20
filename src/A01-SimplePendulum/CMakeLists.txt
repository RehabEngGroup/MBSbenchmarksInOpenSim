# Authors: Luca Tagliapietra, Elena Ceseracciu, and Monica Reggiani

option(BUILD_A01_SIMPLE_PENDULUM "Build A01 simple pendlum example" ON)
if(BUILD_A01_SIMPLE_PENDULUM)

    # Define project
    project (A01_SimplePendulum)

    include_directories(${OPENSIM_INCLUDE_DIRS} ${SIMTK_INCLUDE_DIRS})
    include_directories(${SIMULATION_MANAGER_INCLUDE_DIRS})

    ## Create model
    # Identify the cpp file(s) that were to be built
    set(A01_CREATE_MODEL_SOURCE_FILES createModel.cpp)
    set(A01_CREATE_MODEL_HEADER_FILES modelProperties.h)

    source_group("Headers" FILES ${A01_CREATE_MODEL_HEADER_FILES})
    source_group("Sources" FILES ${A01_CREATE_MODEL_SOURCE_FILES})

    add_executable(SimplePendulumCreateModel ${A01_CREATE_MODEL_HEADER_FILES} ${A01_CREATE_MODEL_SOURCE_FILES})
    target_link_libraries(SimplePendulumCreateModel ${OPENSIM_LIBRARIES})

    ## Simulate

    set(A01_SIMULATE_SOURCE_FILES simulate.cpp)

    source_group("Sources" FILES ${A01_SIMULATE_SOURCE_FILES})

    add_executable(SimplePendulumSimulate ${A01_SIMULATE_SOURCE_FILES})
    target_link_libraries(SimplePendulumSimulate simulationManager ${OPENSIM_LIBRARIES})

endif()
