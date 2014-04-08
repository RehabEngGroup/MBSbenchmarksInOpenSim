##

option(BUILD_A04_BRICARD_MECHANISM "Build A04 bricard mechanism example" ON)
if(BUILD_A04_BRICARD_MECHANISM)

    # Define project
    project (A04_BricardMechanism)

    include_directories(${OPENSIM_INCLUDE_DIRS} ${SIMTK_INCLUDE_DIRS})
    include_directories(${SIMULATION_MANAGER_INCLUDE_DIRS})

    ## Create model
    # Identify the cpp file(s) that were to be built
    set(A04_CREATE_MODEL_SOURCE_FILES createModel.cpp)
    set(A04_CREATE_MODEL_HEADER_FILES modelProperties.h)

    source_group("Headers" FILES ${A04_CREATE_MODEL_HEADER_FILES})
    source_group("Sources" FILES ${A04_CREATE_MODEL_SOURCE_FILES})

    add_executable(BricardMechanismCreateModel ${A04_CREATE_MODEL_HEADER_FILES} ${A04_CREATE_MODEL_SOURCE_FILES})
    target_link_libraries(BricardMechanismCreateModel ${OPENSIM_LIBRARIES})

    ## Simulate

    set(A04_SIMULATE_SOURCE_FILES simulate.cpp)

    source_group("Sources" FILES ${A04_SIMULATE_SOURCE_FILES})

    add_executable(BricardMechanismSimulate ${A04_SIMULATE_SOURCE_FILES})
    target_link_libraries(BricardMechanismSimulate simulationManager ${OPENSIM_LIBRARIES})

endif()

