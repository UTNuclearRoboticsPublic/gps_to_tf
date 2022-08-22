///////////////////////////////////////////////////////////////////////////////
//      Title     : utm_odom.h
//      Platforms : Ubuntu 64-bit
//      Copyright : Copyright© The University of Texas at Austin, 2021. All rights reserved.
//
//          All files within this directory are subject to the following, unless an alternative
//          license is explicitly included within the text of each file.
//
//          This software and documentation constitute an unpublished work
//          and contain valuable trade secrets and proprietary information
//          belonging to the University. None of the foregoing material may be
//          copied or duplicated or disclosed without the express, written
//          permission of the University. THE UNIVERSITY EXPRESSLY DISCLAIMS ANY
//          AND ALL WARRANTIES CONCERNING THIS SOFTWARE AND DOCUMENTATION,
//          INCLUDING ANY WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//          PARTICULAR PURPOSE, AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY
//          THAT MIGHT OTHERWISE ARISE FROM COURSE OF DEALING OR USAGE OF TRADE.
//          NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH RESPECT TO THE USE OF
//          THE SOFTWARE OR DOCUMENTATION. Under no circumstances shall the
//          University be liable for incidental, special, indirect, direct or
//          consequential damages or loss of profits, interruption of business,
//          or related expenses which may arise from use of software or documentation,
//          including but not limited to those resulting from defects in software
//          and/or documentation, or loss or inaccuracy of data of any kind.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <geometry_msgs/TransformStamped.h>
#include <gps_common/conversions.h>
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <tf2_ros/transform_broadcaster.h>

/**
 * Node API
 * 
 * TODO
 */

namespace gps_to_tf
{
class GpsToTf
{
public:
  // basic constructor
  GpsToTf();

  // destructor.
  ~GpsToTf();

private:
  // node handles
  ros::NodeHandle nh_;
  ros::NodeHandle private_nh_;

  // subscribers
  ros::Subscriber fix_sub_;

  // tf broadcaster
  tf2_ros::TransformBroadcaster tf_broadcaster_;

  // class variables
  std::string base_frame_;

  // Callback when a gps fix is received.
  void fixCb(const sensor_msgs::NavSatFix & msg);
};

}  // namespace gps_to_tf