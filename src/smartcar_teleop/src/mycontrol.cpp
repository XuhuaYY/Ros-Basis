#include <iostream>
#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/ioctl.h> 

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  
using namespace std;
 

//Set KeyValue
#define KEY_W 'w'
#define KEY_S 's'
#define KEY_A 'a'
#define KEY_D 'd'

#define KEY_Z 'z'
#define KEY_X 'x'
 
#define KEY_SPACE_BAR ' '
 
 
 
char GetInput(void);

 
int main(int argc,char **argv)
{
    //关闭缓存区，使从终端接收一个字符不用按回车
    system("stty -icanon"); 
    
    ros::init(argc,argv,"mycontrol");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1); 
    
    geometry_msgs::Twist cmdvel;
    double d_VelSpeed = 0.5f;
    
    //warning word
    cout<<"press q to exit!"<<endl;
    
    
    while(1)
    {
 
        char c = GetInput();
        
        if('q'==c)
        {
            cout<<endl<<"exit now"<<endl;
            exit(0);
        }

        switch(c){
			case KEY_W:	
							cmdvel.linear.x = d_VelSpeed;		
							cmdvel.angular.z = 0;		
							break;
			
			case KEY_S:	
							cmdvel.linear.x = -d_VelSpeed; 	
							cmdvel.angular.z = 0;		
							break;
			case KEY_A:	
							cmdvel.linear.x = 0;		
							cmdvel.angular.z = 1.0f;		
							break;
			case KEY_D:	
							cmdvel.linear.x = 0;		
							cmdvel.angular.z = -1.0f;		
							break;
	
			case KEY_Z: 
							d_VelSpeed += 0.5f;	
							cout<<endl<<"RunSpeed = "<<d_VelSpeed<<endl;	
							break;
			case KEY_X: 
							d_VelSpeed -= 0.5f;	
							cout<<endl<<"RunSpeed = "<<d_VelSpeed<<endl;
							 break;
			
			case KEY_SPACE_BAR:
					    
							cmdvel.linear.x = 0;		
							cmdvel.angular.z = 0;		
							break;
		}
        pub.publish(cmdvel); 
    }
    
    ros::spin();  
    return 0;
    
}




char GetInput()
{
    //fd_set 为long型数组
    //其每个元素都能和打开的文件句柄建立联系
    fd_set rfds;
    struct timeval tv;
    char c = '\0';
 
    //将　rfds数组清零
    FD_ZERO(&rfds);
    //将rfds的第0位置为１，这样fd=1的文件描述符就添加到了rfds中
    //最初　rfds为00000000,添加后变为10000000
    FD_SET(0, &rfds);
    tv.tv_sec = 1;
    tv.tv_usec = 0; //设置等待超时时间
 
    //检测键盘是否有输入
    //由内核根据io状态修改rfds的内容，来判断执行了select的进程哪个句柄可读
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        c = getchar();
 
        return c;
    }
 
    //没有数据返回n
    return 'n';
}
