#source ~/ucla_ws/src/ucla_husky/ucla_husky_bringup/scripts/setup.bash

#--Dual-Arm----
#export HUSKY_URDF_EXTRAS=$(catkin_find husky_ur_description urdf/husky_dual_ur5_e_description.urdf.xacro --first-only)



#--Single-Arm--
#export HUSKY_URDF_EXTRAS=$(catkin_find husky_ur_description urdf/husky_ur5_e_description.urdf.xacro --first-only)
# roslaunch ucla_husky_bringup simulation.launch


##--Single-Arm With Gripper--
export HUSKY_URDF_EXTRAS=$(catkin_find husky_ur_description urdf/husky_ur5_e_gripper_description.urdf.xacro --first-only)
# roslaunch ucla_husky_bringup_gripper simulation.launch
