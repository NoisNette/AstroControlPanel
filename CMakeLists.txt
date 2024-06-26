cmake_minimum_required(VERSION 3.8)
project(astro_control_panel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# include(FetchContent)

# FetchContent_Declare(
#   yaml-cpp
#   GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
#   GIT_TAG master
# )
# FetchContent_GetProperties(yaml-cpp)

# if(NOT yaml-cpp_POPULATED)
#   FetchContent_Populate(yaml-cpp)
#   add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
# endif()

set(YAML_CPP_INSTALL ON CACHE INTERNAL "")
add_subdirectory(yaml-cpp)

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(rviz_default_plugins REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(pluginlib REQUIRED)
find_package(geometry_msgs REQUIRED)

set(${PROJECT_NAME}_headers_to_moc
  include/${PROJECT_NAME}/astro_control_panel.hpp
  include/${PROJECT_NAME}/teleop_section.hpp
  include/${PROJECT_NAME}/info_section.hpp
  include/${PROJECT_NAME}/command_section.hpp
  include/${PROJECT_NAME}/mapping_widget.hpp
  include/${PROJECT_NAME}/localization_widget.hpp
  include/${PROJECT_NAME}/navigation_widget.hpp
)

foreach(header "${${PROJECT_NAME}_headers_to_moc}")
  qt5_wrap_cpp(${PROJECT_NAME}_moc_files "${header}")
endforeach()

set(${PROJECT_NAME}_source_files
  src/astro_control_panel.cpp
  src/teleop_section.cpp
  src/info_section.cpp
  src/command_section.cpp
  src/mapping_widget.cpp
  src/localization_widget.cpp
  src/navigation_widget.cpp
)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_moc_files}
  ${${PROJECT_NAME}_source_files}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_export_include_directories(include)
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rviz_common
  sensor_msgs
  spatz_interfaces
  rviz_ogre_vendor
)

# Link ament packages
ament_target_dependencies(${PROJECT_NAME} rclcpp rviz_common rviz_rendering geometry_msgs)

# Link non ament packages
target_link_libraries(${PROJECT_NAME} Qt5::Widgets yaml-cpp)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${PROJECT_NAME} PRIVATE "${PROJECT_NAME}_BUILDING_LIBRARY")

# prevent pluginlib from using boost
target_compile_definitions(${PROJECT_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  DIRECTORY include/
  DESTINATION include
)

set(BUILD_TESTING false)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
