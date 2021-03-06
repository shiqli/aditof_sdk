/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2019, Analog Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "message_factory.h"
#include <aditof_utils.h>
#include <ros/ros.h>

using namespace aditof;

int main(int argc, char **argv) {

    std::shared_ptr<Camera> camera = initCameraEthernet(argc, argv);
    if (camera.get() == nullptr) {
        ROS_ERROR("initCamera call failed");
        return 0;
    }

    ros::init(argc, argv, "aditof_rviz_node");

    ros::NodeHandle nHandle;
    ros::Publisher frame_pubisher =
        nHandle.advertise<sensor_msgs::PointCloud2>("aditof_pcloud", 100);

    applyNoiseReduction(camera, argc, argv);

    AditofSensorMsg *pclMsg =
        MessageFactory::create(camera, MessageType::sensor_msgs_PointCloud2);

    if (!pclMsg) {
        ROS_ERROR("pointcloud message creation failed");
    }

    while (ros::ok()) {
        dynamic_cast<PointCloud2Msg *>(pclMsg)->FrameDataToMsg(camera);
        pclMsg->publishMsg(frame_pubisher);
    }

    delete pclMsg;

    return 0;
}
