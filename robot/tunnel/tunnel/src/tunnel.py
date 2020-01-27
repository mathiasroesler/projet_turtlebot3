#! /usr/bin/env python

import rospy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist


#================================================#




def clbk_laser(msg):
    #on utilise uniquement deux régions du scan, qui correspondent à l'avant du robot
    regions = {

        'fright':  min(min(msg.ranges[0:30]), 5),

        'fleft':  min(min(msg.ranges[315:360]), 5),       
    }
    take_action(regions)
  

def take_action(regions):
    move=Twist()
    state_description=' ' 
    dist=0.2 #distance de détection 
    angle=1.0 #
    if regions['fleft'] > dist and regions['fright'] > dist:

        state_description = 'case 1 - nothing'

        move.linear.x= -0.3

    elif  regions['fleft'] < dist and regions['fright'] < dist:

        state_description = 'case 2 - front'
        move.linear.x=0 
        move.angular.z = angle

    elif  regions['fleft'] > dist and regions['fright'] < dist:

        state_description = 'case 3 - fright'
        move.linear.x= 0
        move.angular.z = angle

    elif  regions['fleft'] < dist and regions['fright'] > dist:

        state_description = 'case 4 - fleft'
        move.linear.x= 0
        move.angular.z = -angle

    else:
        state_description = 'unknown case'

        rospy.loginfo(regions)
    rospy.loginfo(state_description)
    
    pub.publish(move)
        

rospy.init_node('tunnel')
sub=rospy.Subscriber('/scan', LaserScan, clbk_laser)
pub= rospy.Publisher('/cmd_vel', Twist, queue_size=1)
rospy.spin()
