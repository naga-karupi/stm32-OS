cmake_minimum_required(VERSION 3.14)

project(stm32_os CXX)

add_library(system src/generator.cpp src/task.cpp)
target_compile_options(system PUBLIC -fcoroutines -Wall -O2)
target_compile_features(system PUBLIC cxx_std_20)
target_include_directories(system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(${PROJECT_NAME}-SYSTEM-TEST)
  add_executable(${PROJECT_NAME}-system-googletest test/system-gtest.cpp src/generator.cpp src/task.cpp)
  target_compile_features(${PROJECT_NAME}-system-googletest PUBLIC cxx_std_20)
  target_compile_options(${PROJECT_NAME}-system-googletest PUBLIC -fcoroutines -Wall -O2)
  target_link_libraries(${PROJECT_NAME}-system-googletest gtest_main gtest pthread)
  target_include_directories(${PROJECT_NAME}-system-googletest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

  add_test(NAME system_test COMMAND system)
  enable_testing()
endif()
