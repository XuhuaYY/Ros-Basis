#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>


using namespace std;
void DoingSomething(const std_msgs::String::ConstPtr& msg);


int main(int argc,char **argv){
	ros::init(argc,argv,"Sub");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("Hello_Message",1000,DoingSomething);
	
	ros::spin();
	return 0;
}

void DoingSomething(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heart: [%s]",msg->data.c_str());
}

