#include <ros/ros.h>
#include <fake_ar_publisher/ARMarker.h>
#include <myworkcell/LocalizePart.h>
class Localizer
{
public:
  Localizer(ros::NodeHandle& nh)
  {
    ar_sub_=nh.subscribe<fake_ar_publisher::ARMarker>("ar_pose_marker",1,&Localizer::visionCallback,this);
    server_=nh.advertiseService("localize_part", &Localizer::localizePart,this);
  }
  bool localizePart(myworkcell::LocalizePart::Request& req, myworkcell::LocalizePart::Response& res){
    fake_ar_publisher::ARMarkerConstPtr p = last_msg_;
    if (!p) return false;

    res.pose=p->pose.pose;
    return true;
  }
  void visionCallback(const fake_ar_publisher::ARMarkerConstPtr& msg)
  {
    last_msg_=msg;
  //ROS_INFO_STREAM(last_msg_->pose.pose);
  }
  ros::Subscriber ar_sub_;
  ros::ServiceServer server_;
  fake_ar_publisher::ARMarkerConstPtr last_msg_;
};
int main(int argc, char * argv[]) {
	ros::init(argc, argv, "vision_node");
	ros::NodeHandle nh;
	ROS_INFO("Hello World");
  Localizer localizer(nh);
  ROS_INFO("Vision node starting");
  ros::spin();
}
