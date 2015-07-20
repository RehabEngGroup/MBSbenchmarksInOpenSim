# Authors: Luca Tagliapietra, Elena Ceseracciu, and Monica Reggiani

option(BUILD_A03_ANDREWS_MECHANISM "Build A03 Andrew's Mechanism example" ON)
if(BUILD_A03_ANDREWS_MECHANISM)

    # Define project
    project (A03_AndrewsMechanism)

    include_directories(${OPENSIM_INCLUDE_DIRS} ${SIMTK_INCLUDE_DIRS})
    include_directories(${SIMULATION_MANAGER_INCLUDE_DIRS})

    ## Create model
    # Identify the cpp file(s) that were to be built
    set(A03_CREATE_MODEL_SOURCE_FILES createModel.cpp)
    set(A03_CREATE_MODEL_HEADER_FILES modelProperties.h)

    source_group("Headers" FILES ${A03_CREATE_MODEL_HEADER_FILES})
    source_group("Sources" FILES ${A03_CREATE_MODEL_SOURCE_FILES})

    add_executable(AndrewsMechanismCreateModel ${A03_CREATE_MODEL_HEADER_FILES} ${A03_CREATE_MODEL_SOURCE_FILES})
    target_link_libraries(AndrewsMechanismCreateModel ${OPENSIM_LIBRARIES})

    ## Simulate

    set(A03_SIMULATE_SOURCE_FILES simulate.cpp)
    set(A03_SIMULATE_HEADER_FILES DcMotorPIDController.h)

    source_group("Headers" FILES ${A03_SIMULATE_HEADER_FILES})
    source_group("Sources" FILES ${A03_SIMULATE_SOURCE_FILES})

    add_executable(AndrewsMechanismSimulate ${A03_SIMULATE_SOURCE_FILES} ${A03_SIMULATE_HEADER_FILES})
    target_link_libraries(AndrewsMechanismSimulate simulationManager ${OPENSIM_LIBRARIES})

endif()
