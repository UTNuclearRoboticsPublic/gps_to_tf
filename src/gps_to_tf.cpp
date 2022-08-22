///////////////////////////////////////////////////////////////////////////////
//      Title     : utm_odom.cpp
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

#include <gps_to_tf/gps_to_tf.h>

namespace gps_to_tf
{
GpsToTf::GpsToTf() : nh_(""), private_nh_("~")
{
  fix_sub_ = nh_.subscribe("fix", 1, &GpsToTf::fixCb, this);

  if (!private_nh_.getParam("base_frame", base_frame_)) {
    ROS_FATAL("Base frame parameter not set.");
  }
}

GpsToTf::~GpsToTf() {}

void GpsToTf::fixCb(const sensor_msgs::NavSatFix & msg)
{
  double northing, easting;
  std::string zone;

  gps_common::LLtoUTM(msg.latitude, msg.longitude, northing, easting, zone);

  geometry_msgs::TransformStamped transform;
  transform.header.stamp = ros::Time::now();
  transform.header.frame_id = "utm";
  transform.child_frame_id = base_frame_;
  transform.transform.translation.x = easting;
  transform.transform.translation.y = northing;
  transform.transform.translation.z = msg.altitude;
  transform.transform.rotation.x = 0;
  transform.transform.rotation.y = 0;
  transform.transform.rotation.z = 0;
  transform.transform.rotation.w = 1;

  tf_broadcaster_.sendTransform(transform);
}

}  // namespace gps_to_tf

int main(int argc, char ** argv)
{
  ros::init(argc, argv, "gps_to_tf");

  gps_to_tf::GpsToTf node;
  ros::spin();

  return 0;
}