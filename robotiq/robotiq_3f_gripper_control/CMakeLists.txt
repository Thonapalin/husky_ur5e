# http://ros.org/doc/groovy/api/catkin/html/user_guide/supposed.html
cmake_minimum_required(VERSION 2.8.3)
project(robotiq_3f_gripper_control)
find_package(catkin REQUIRED COMPONENTS rospy message_generation roscpp robotiq_ethercat robotiq_3f_gripper_msgs)

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

###################################
## catkin message generation     ##
###################################

catkin_python_setup()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
    CATKIN_DEPENDS rospy message_runtime roscpp robotiq_ethercat
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${robotiq_ethercat_INCLUDE_DIRS}
  ${robotiq_3f_gripper_msgs_INCLUDE_DIRS}
)

add_executable(3f_gripper_node
  src/robotiq_3f_gripper_control/s_model_ethercat_node.cpp
  src/robotiq_3f_gripper_control/s_model_ethercat_client.cpp
)

add_dependencies(3f_gripper_node ${robotiq_3f_gripper_control_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} ${robotiq_3f_gripper_msgs_EXPORTED_TARGETS})

target_link_libraries(3f_gripper_node
   ${robotiq_ethercat_LIBRARIES}
   ${catkin_LIBRARIES}
)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/groovy/api/catkin/html/adv_user_guide/variables.html

install(PROGRAMS nodes/SModelSimpleController.py nodes/SModelStatusListener.py
	nodes/SModelTcpNode.py DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
