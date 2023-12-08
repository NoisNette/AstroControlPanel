cmake_minimum_required(VERSION 3.8)
project(astro_control_panel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(rviz_common REQUIRED)
find_package(rviz_rendering REQUIRED)
find_package(rviz_ogre_vendor REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(pluginlib REQUIRED)

set(astro_control_panel_headers_to_moc
  include/astro_control_panel/astro_control_panel.hpp
)

foreach(header "${astro_control_panel_headers_to_moc}")
  qt5_wrap_cpp(astro_control_panel_moc_files "${header}")
endforeach()

set(astro_control_panel_source_files
  src/astro_control_panel.cpp
)

add_library(astro_control_panel SHARED
  ${astro_control_panel_moc_files}
  ${astro_control_panel_source_files}
)

target_include_directories(astro_control_panel PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_export_include_directories(include)
ament_export_targets(astro_control_panel HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rviz_common
  sensor_msgs
  spatz_interfaces
  rviz_ogre_vendor
)

# Link ament packages
ament_target_dependencies(${PROJECT_NAME} rclcpp rviz_common rviz_rendering)

# Link non ament packages
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(astro_control_panel PRIVATE "astro_control_panel_BUILDING_LIBRARY")

# prevent pluginlib from using boost
target_compile_definitions(${PROJECT_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)

install(
  TARGETS astro_control_panel
  EXPORT astro_control_panel
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
