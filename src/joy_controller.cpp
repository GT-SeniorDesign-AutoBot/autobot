#include <math.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Point.h"
#include <string>

ros::Subscriber joy_sub;
ros::Publisher cmd_vel_pub;

void joy_callback(const sensor_msgs::Joy &joy){
	std_msgs::String result;
	int button_1 = 1;
	button_1 = joy.buttons[5];
	int axe_1 = (int)(joy.axes[1]*100);//forward or backward
	int axe_3 = (int)(joy.axes[3]*100);//turn left or right
	if(button_1 == 1){
		if(axe_1 > 0.0){
			result.data = "A10B10";
		}
		else if(axe_1 < 0.0){
			result.data = "a10b10";
		}
		else if(axe_3 > 0.0){
			result.data = "A10B20";
		}
		else if(axe_3 < 0.0){
			result.data = "A20B10";
		}else{
			result.data = "A00B00";
		}

		cmd_vel_pub.publish(result);
	}
//	float theta = atan2(-1*(msg->x),msg->z);//our model has the opposite coordinates frame with the kinect frame, so negative the x value
//	printf("theta:%f\n",theta);
//	printf("head x %f\n",msg->x);
//	printf("head y %f\n",msg->y);
//	printf("head z %f\n",msg->z);
//	std_msgs::String result;
//	if(fabs(theta) >= 0.5){
//		printf("Out of the range of the kinect\n");
//		result.data = "A00B00";
//		printf("velocity A00 B00\n");
//	} else {
//		if(msg->z <= 1500){
//			printf("in the 1.5m\n");
//			result.data = "A00B00";
//			printf("velocity A00 B00\n");
//		}else{
//			if(fabs(theta) > 0.05){
//				printf("Turn\n");
//				float k=10.0;
//				//float Vmax = 127.0;
//				float Vmax = 15.0;
//				int left_vel = -1 * k*theta + Vmax/2;
//				int right_vel = Vmax/2 + k*theta;
//				char tmp[7];
//				if(left_vel < 16 && right_vel > 16){
//					sprintf(tmp,"A0%xB%x",left_vel, right_vel);
//				}else if(right_vel < 16 && left_vel > 16){
//					sprintf(tmp,"A%xB0%x",left_vel, right_vel);
//				}else if(left_vel < 16 && right_vel < 16){
//					sprintf(tmp,"A0%xB0%x",left_vel, right_vel);
//				}else{
//					sprintf(tmp,"A%xB%x",left_vel, right_vel);
//				}
//				printf("Velocity Command %s\n",tmp);
//				std::string tmp2(tmp);
//				result.data = tmp2;
//			} else {
//				printf("Move Straight\n");
//				result.data = "A15B15";
//				printf("velocity A10 B10\n");
//			}
//		}
//	}
//
//	cmd_vel_pub.publish(result);
}
int main(int argc, char **argv){
	ros::init(argc, argv, "joy_controller");
	ros::NodeHandle nh;
	joy_sub = nh.subscribe("joy",1,joy_callback);
	cmd_vel_pub = nh.advertise<std_msgs::String>("cmd_vel",1);
	ros::Rate loop_rate(60);
	while(ros::ok()){
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}

