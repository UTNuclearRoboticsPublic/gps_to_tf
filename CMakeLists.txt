cmake_minimum_required(VERSION 3.0.2)
project(gps_to_tf)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  gps_common
  sensor_msgs
  tf2_ros
  geometry_msgs
)

catkin_package(
  LIBRARIES
  CATKIN_DEPENDS
  roscpp
  gps_common
  sensor_msgs
  tf2_ros
  geometry_msgs
  DEPENDS
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(gps_to_tf src/gps_to_tf.cpp)
target_link_libraries(gps_to_tf ${catkin_LIBRARIES})