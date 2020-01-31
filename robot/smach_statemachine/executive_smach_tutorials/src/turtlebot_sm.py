#!/usr/bin/env python
from __future__ import print_function
import rospy
import smach
import time
import roslaunch
import pyzbar.pyzbar as pyzbar
import cv2, cv_bridge, numpy
from sensor_msgs.msg import CompressedImage
from geometry_msgs.msg import Twist
from math import *
from sensor_msgs.msg import LaserScan

#converting images for detection
image_sub = rospy.Subscriber('/raspicam_node/image/compressed',CompressedImage, image_callback,queue_size=1) #subscribing to camera topic
im_bridge=cv_bridge.CvBridge() #creating a bridge object
detected=str() #creating a string a string that will change over the execution of the code
#Dans ce code, "detected" est le résultat de la lecture de QRCODE mais à terme il devra être celui de la detection par reconnaissance de forme
#Cette dernière approche ne modifiera pas la syntaxe actuelle du code puisqu'elle renvoie le nom du panneau detecté

def decode(im) : 
  # Find barcodes and QR codes
    decodedObjects = pyzbar.decode(im) 
  # Get results
    for obj in decodedObjects:
        rospy.loginfo("Data : "+str( obj.data))
        return str(obj.data)
    
def image_callback(msg):
    image = self.bridge.compressed_imgmsg_to_cv2(msg)
    detected = decode(image)
#on pourra ajouter un moyen de rendre le callback intermittent afin de ne pas avoir à traiter toutes les images captées par la camera
# motion control
pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
move = Twist()


# define state suivi
class suivi(smach.State):
    def __init__(self):
        # 'red_light','barrier','speed_limit','tunnel_detected'
        smach.State.__init__(self, outcomes=['stop_sign', 'tunnel_detected'])

    def execute(self, userdata):
	# launch code suivi
	# rospy.init_node('line_follower', anonymous=True)
	    uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
	    roslaunch.configure_logging(uuid)
	    launch = roslaunch.parent.ROSLaunchParent(
	        uuid, ["/home/perel/catkin_ws/src/suivi/launch/suivi.launch"])
	    launch.start()
	    rospy.loginfo('Executing state SUIVI')
	    transition = str(raw_input("Enter an outcome"))
	  
	    if detected == "tunnel":
	         launch.stop()
	         return 'tunnel_detected'
	    if detected == "STOP":
	        launch.stop()
	        return 'stop_sign'


# define state arret
# CBSTATE definition
# @smach.cb_interface(input_keys=[],output_keys=[], outcomes=['time'])
# def arret_cb(user_data):
#	rospy.loginfo('Arret')
#	arret_topic=rospy.Publisher('/cmd_vel',Twist, queue_size=1)
#	msg=Twist()
#	msg.linear.x=0.0
#	msg.angular.z=0.0
#	arret_topic.publish(msg)
#	ros.sleep(5)
#	return 'time'
	# if green_light=True:
	 #   return 'green_light'

# generic state definition
class arret(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['time','green_light'])  # 'green_light'

    def execute(self, userdata):
        rospy.loginfo('Executing state ARRET')
        for i in range(500):
            #move.linear.x = 0.0
            #move.angular.z = 0.0
            #pub.publish(move)
            rospy.sleep(0.01)
        return 'time'
	    if detected="GREEN_LIGHT":
	       return 'green_light'


class tunnel(smach.State):
    def __init__(self):
        smach.State.__init__(self, outcomes=['sortie_tunnel'])

    def execute(self, userdata):
        rospy.loginfo('Executing state TUNNEL')
        # rospy.init_node('tunnel', anonymous=True)
        uuid = roslaunch.rlutil.get_or_generate_uuid(None, False)
        roslaunch.configure_logging(uuid)
        launch = roslaunch.parent.ROSLaunchParent(uuid, ["/home/perel/catkin_ws/src/tunnel/launch/tunnel.launch"])
        launch.start()
        transition = str(raw_input("Enter an outcome"))
        if detected == "SORTIE_TUNNEL":  # moyen d'indiquer qu'on est sorti du tunnel
            launch.stop()
            return 'sortie_tunnel'

# defi: modifier la vitesse de deplacement tout en maintenant le suivi à la détection d'un panneau SPEED_LIMIT
# on utilise un launch file ici et non le script
# pas de nécessitée d'ajouter une classe ralenti
# possibilité de couper la communication entre le noeud line_follower et cmd_vel puis d'écrire  sur cmd_vel et retablir la
# communication
# class ralenti(smach.State):
 #   def __init__(self):
  #      smach.State.__init__(self, outcomes=['speed_limit_false'])

   # def execute(self, userdata):
    # rospy.loginfo('Executing state Ralenti')
	# speed=[0.275,0.25,0.2,0.175,0.15,0.1]
	# for sp in speed
	#     move.linear.x=sp
	#     pub.publish(move)
	# if speed_limit_detected=False
	 #    return 'speed_limit_false'


# main
def main():
    rospy.init_node('turtlebotauto')

    # Create a SMACH state machine
    sm = smach.StateMachine(outcomes=['outcome4', 'outcome5']) #ces transitions sont celles qui interrompent l'execution de la machine à état

    # Open the container
    with sm:
        # Add states to the container
        smach.StateMachine.add('suivi', suivi(),
                               transitions={'stop_sign': 'arret', 'tunnel_detected': 'tunnel'})
        smach.StateMachine.add('arret', arret(),transitions={'time':'suivi','green_light':'suivi'})
        smach.StateMachine.add('tunnel', tunnel(),transitions = {'sortie_tunnel': 'suivi'})
	#smach.StateMachine.add('ARRET', CBState(arret_cb), {'time': 'suivi'})
	# smach.StateMachine.add('ralenti', arret(),
                              # transitions={'speed_limit_false':'suivi'})



    # Execute SMACH plan
    outcome=sm.execute()


if __name__ == '__main__':
    main()
