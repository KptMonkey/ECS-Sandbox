cmake_minimum_required(VERSION 3.10)
project(ECS-Sandbox)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES entity.hpp
                 entity_manager.hpp
                 component.hpp
                 component_array.hpp
                 component_manager.hpp
                 manager_manager.hpp
                 system.hpp
                 system_manager.hpp
                 Components/transform.hpp)

add_executable(ECS-Sandbox main.cpp ${SOURCE_FILES})
