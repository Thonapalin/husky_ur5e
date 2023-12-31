// Copyright (c) 2016, Toyota Research Institute. All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef S_MODEL_ROS_H
#define S_MODEL_ROS_H

#include <ros/ros.h>
#include <std_srvs/Trigger.h>
#include <robotiq_3f_gripper_control/SModel_robot_input.h>
#include <robotiq_3f_gripper_control/SModel_robot_output.h>
#include <robotiq_3f_gripper_control/s_model_api.h>
#include <dynamic_reconfigure/server.h>
#include <robotiq_3f_gripper_control/SModelConfig.h>

namespace robotiq_3f_gripper_control
{
class SModelROS
{
public:
    SModelROS(ros::NodeHandle& nh,
                  boost::shared_ptr<robotiq_3f_gripper_control::SModelAPI> driver, std::vector<std::string> joint_names,
                  ros::Duration desired_update_freq);

    void publish();

    bool handleInit(std_srvs::TriggerRequest &req, std_srvs::TriggerResponse &resp);
    bool handleReset(std_srvs::TriggerRequest &req, std_srvs::TriggerResponse &resp);
    bool handleHalt(std_srvs::TriggerRequest &req, std_srvs::TriggerResponse &resp);
    bool handleEmergRelease(std_srvs::TriggerRequest &req, std_srvs::TriggerResponse &resp);
    bool handleShutdown(std_srvs::TriggerRequest &req, std_srvs::TriggerResponse &resp);

    void handleReconfigure(robotiq_3f_gripper_control::SModelConfig &config, uint32_t level=0);

    void handleRawCmd(const robotiq_3f_gripper_control::SModel_robot_output::ConstPtr &msg);

    void updateConfig(const robotiq_3f_gripper_control::SModelConfig &config);
    void getCurrentConfig(robotiq_3f_gripper_control::SModelConfig &config);

private:
    ros::NodeHandle nh_;
    boost::shared_ptr<robotiq_3f_gripper_control::SModelAPI> driver_;

    //! Services
    ros::ServiceServer init_srv_;
    ros::ServiceServer reset_srv_;
    ros::ServiceServer halt_srv_;
    ros::ServiceServer emerg_release_srv_;
    ros::ServiceServer shutdown_srv_;

    //! Topics
    ros::Publisher input_status_pub_;
    ros::Subscriber output_sub_;

    //! Settings
    ros::Duration desired_update_freq_;

    //! Reconfigure
    typedef dynamic_reconfigure::Server<robotiq_3f_gripper_control::SModelConfig> ReconfigureServer;
    boost::shared_ptr<ReconfigureServer> reconfigure_;
    boost::recursive_mutex reconfigure_mutex_;
    robotiq_3f_gripper_control::SModelConfig config_;

    robotiq_3f_gripper_control::SModel_robot_input input_status_msg_;

};
} //end namespace robotiq_3f_gripper_control

#endif // S_MODEL_ROS_H
