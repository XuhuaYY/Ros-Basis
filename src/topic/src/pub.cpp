#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
using namespace std;

int main(int argc,char **argv){
	
	//01
	//for(int i=0;i<argc;i++){
	//	cout<<argv[i]<<endl;
	//}
	
	//02
	//char a[] = {0};
	//sprintf(a,"%s",argv[1]);
	//switch(a[0]){
	//	case '0':cout<<"hello"<<endl;break;
	//	case '1':cout<<"goodbye"<<endl;break;
	//	
	//}
	
	//03
	ros::init(argc,argv,"Pub");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<std_msgs::String>("Hello_Message",1000);
	
	ros::Rate lp_rate(10);
	while(ros::ok()){
		std_msgs::String msg;
		std::stringstream ss;
		ss<<"Hello ros melodic";
		msg.data = ss.str();
		pub.publish(msg);
		
		ros::spinOnce();
		lp_rate.sleep();
	}
	return 0;
	
}

