#!/usr/bin/env python




import rospy, cv2, cv_bridge, numpy
from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist

class Follower:

	def __init__(self):
		
		self.bridge = cv_bridge.CvBridge()
		cv2.namedWindow("window", 1)
		
		#Subscriber pour la camera
		self.image_sub = rospy.Subscriber('/camera/rgb/image_raw',
			Image, self.image_callback)
		#publisher pour les moteurs
		self.cmd_vel_pub = rospy.Publisher('/cmd_vel',
			Twist, queue_size=1)
		
		self.twist = Twist()

	def image_callback(self, msg):

		image = self.bridge.imgmsg_to_cv2(msg,desired_encoding='bgr8')
		hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
		
		#Etendu de la couleur voulu (bleue par defaut)
		#lower_red = numpy.array([160,20,70])    #Decommenter pour suivre la couleur rouge
		#upper_red = numpy.array([190,255,255])
		lower = numpy.array([101,50,38])
		upper = numpy.array([110,255,255])
		
		#Mask de la couleur voulu		
		mask = cv2.inRange(hsv, lower_yellow, upper_yellow)
		
		#elimination des zones non interessante dans le mask 
		h, w, d = image.shape
		search_top = 3*h/4
		search_bot = 3*h/4 + 20
		mask[0:search_top, 0:w] = 0
		mask[search_bot:h, 0:w] = 0

		M = cv2.moments(mask)
		#Calcul du centre de la zone d'interet ( l'asservissement se fait sur la coordonnées X vue que c'est l'orientation qu'on commande		
		if M['m00'] > 0:
			cx = int(M['m10']/M['m00'])
			cy = int(M['m01']/M['m00'])
			cv2.circle(image, (cx, cy), 20, (0,0,255), -1)
	
			err = cx - w/2
			self.twist.linear.x = 0.2
			self.twist.angular.z = -float(err) / 80  #80 ici les le gain Kp, je l'ai defini arbitrairement pour le moment
			self.cmd_vel_pub.publish(self.twist)
		cv2.imshow("window", image)
		cv2.waitKey(3)

rospy.init_node('line')
follower = Follower()
rospy.spin()
