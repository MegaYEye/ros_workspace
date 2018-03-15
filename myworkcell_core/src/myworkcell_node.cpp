#include <ros/ros.h>
#include <myworkcell/LocalizePart.h>


class ScanNPlan {
public:
  ScanNPlan(ros::NodeHandle& nh) {
    vision_client_=nh.serviceClient<myworkcell::LocalizePart>("localize_part");
  }
  void start(const std::string &base_frame) {
    ROS_INFO("Attempting to localize part");
    myworkcell::LocalizePart srv;
    srv.request.base_frame=base_frame;
    ROS_INFO_STREAM("Requesting pose in base frame: " << base_frame);
    if(!vision_client_.call(srv)){
      ROS_ERROR("Could not localize part");
      return;
    }

    ROS_INFO_STREAM("part localized: "<<srv.response);
  }
private:
  ros::ServiceClient vision_client_;


};

int main(int argc, char *argv[]) {
  ros::init(argc,argv,"myworkcell_node");
  ros::NodeHandle nh;
  ros::NodeHandle private_node_handle("~");
  std::string base_frame;
  private_node_handle.param<std::string>("base_frame",base_frame,"world");
  ScanNPlan app(nh);

  ROS_INFO("ScanNPlan node has been initialized");

  ros::Duration(0.5).sleep();
  app.start(base_frame);
  ros::spin();


}
