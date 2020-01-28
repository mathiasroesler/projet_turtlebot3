#!/usr/bin/env python



 
import rospy, cv2, cv_bridge, numpy
from sensor_msgs.msg import CompressedImage
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from math import *

class Listener:

	def __init__(self):
		
		
		#cv2.namedWindow("window", 1)
		#self.string=String()
		#Subscriber pour la camera
		#self.string_sub=rospy.Subscriber('chatter',String, self.callback,queue_size=1)
		self.string=String()
		self.d= None
		#publisher pour les moteurs
		self.cmd_vel_pub = rospy.Publisher('/cmd_vel',Twist, queue_size=1)
		self.string_sub=rospy.Subscriber('chatter',String,self.callback,queue_size=1)
		#self.tist = Twist()
	
	def callback(self, msg):
		
		self.d=msg
		print(self.d.data)
		#self.string=msg
		
class Follower:

	def __init__(self):
		self.i=0
		self.bridge = cv_bridge.CvBridge()
		#cv2.namedWindow("window", 1)
		#self.string=String()
		#Subscriber pour la camera
		#self.string_sub=rospy.Subscriber('chatter',String, self.callback,queue_size=1)
		self.image_sub = rospy.Subscriber('/camera1/camera/rgb/image_raw/compressed',
			CompressedImage, self.image_callback,queue_size=1)
		#publisher pour les moteurs
		self.twist = Twist()
		self.cmd_vel_pub = rospy.Publisher('/cmd_vel',Twist, queue_size=1)
		
	
	def image_callback(self, msg):

		image = self.bridge.compressed_imgmsg_to_cv2(msg)
		cv2.imwrite('image.png',image)
		
		#self.i=self.i+1
		#lower_yellow = numpy.array([-10, 245, 145])
		#upper_yellow= numpy.array([ 10, 265, 225])
		lower_yellow = numpy.array([-10, -10, 183])
		upper_yellow= numpy.array([ 10,  10, 263])

		hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
		kernel=numpy.ones((5,5),numpy.uint8)
		mask = cv2.inRange(hsv, lower_yellow, upper_yellow)
		mask = cv2.bitwise_and(image, image, mask=mask)		
		
		
		erosion=cv2.erode(mask,kernel,iterations=3)
		dilation=cv2.dilate(erosion,kernel,iterations=2)
		cv2.imwrite('image99.png',dilation)
		mask = cv2.cvtColor(dilation, cv2.COLOR_BGR2GRAY)	
		#dilation=[int(numpy.floor(w/5)):int(numpy.floor(4*w/5)),0:h]
		h, w, d = image.shape
		search_top = h/2
		search_bot = 3*h/4
		numpy.floor(search_top)
		numpy.floor(search_bot)
		#search_left = w/4+25
		#search_right = 2.5*w/4-90 
		#numpy.floor(search_left)
		#numpy.floor(search_right)

                #dilation=dilation[0:h, int(search_left):int(search_right)]
# dilation=dilation[0:h, int(search_left):int(search_right)]
		#cv2.imwrite('mask1.png',dilation)
		mask[0:int(search_bot), 0:w] = 0
		#image[ int(search_bot):h,0:w] = 0
		#hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
		#mask = cv2.inRange(hsv, lower_yellow, upper_yellow)
		#kernel=numpy.ones((5,5),numpy.uint8)
		#erosion=cv2.erode(mask,kernel,iterations=1)
		#dilation=cv2.dilate(erosion,kernel,iterations=2)
		#mask[0:int(numpy.floor(search_top)), 0:w] = 0
		#mask[int(numpy.floor(search_bot)):h, 0:w] = 0
		#cv2.imwrite('ia'+str(self.i)+'.png',mask)		
		
		#h,w=mask.shape
		p=w/2
		
		
			
		M = cv2.moments(mask)
		#rospy.loginfo("erreur"+str(M['m00']))
		if M['m00'] > 0:
			cx = int(M['m10']/M['m00'])
			cy = int(M['m01']/M['m00'])
			#cv2.circle(image, (cx, cy), 20, (0,0,255), -1)
			#cv2.circle(image, (w/2, cy), 20, (0,255,0), -1)
			
			#cv2.circle(image, (w/2, h-20), 20,(255,0,0),-1)	#point 				d'origine pour mesurer l'angle		
			#Vect_po = (cx-w/2, cy-(h-20))
			#angle = atan2(Vect_po(1),Vect-po(0))-pi/2
			#k2=1
			#print(angle)
			
		        #cv2.imwrite('image.png',image)
			'''y=[]
			for k in range(len(x)): 
   			 	 
				y.append(cx-x[k])
			'''
			err = cx-p
			
	
			#rospy.loginfo("erreur"+str(err))
			self.twist.linear.x = 0.015
			
			  
			self.twist.angular.z= - float(err) / 100
			#self.twist.angular.z = k2*tan(angle)*abs(self.twist.linear.x) #loi de 				commande avec l'angle
			
			#self.twist.linear.x = 0
			#self.twist.angular.z = 0
			#self.twist.linear.x = 0.05
			#print(cx,p)
			#rospy.loginfo("rotation"+str(self.twist.angular.z))
		
		
		self.cmd_vel_pub.publish(self.twist)

		
rospy.init_node('line_follower')
follower = Follower()
#listener = Listener()

			

rospy.Rate(10)
rospy.spin()
