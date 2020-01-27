 Pour utiliser le modèle de turtlebot3 burger avec une camera
remplacer ces deux fichiers dans le répertoire du package turtlebot3_descriptions:
opt/ros/kinetic/share/turtlebot3_descriptions/urdf
ou
catkin_ws/src/turtlebot3_description/urdf

Dimensions actuelles : 0.008 x 0.015 x 0.015 (m) 

Taille de l'image : 800x800

Pour mieux comprendre le code et le modifier, se référer
à l'explication donnée sur ce lien :

http://gazebosim.org/tutorials?tut=ros_gzplugins#Camera

(Il suffit de supprimer le code en dessous de "!-- Camera --"
dans les deux fichiers pour la retirer)

Visualisation de l'image 

-lancer rviz : 
export TURTLEBOT3_MODEL=burger 

roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch

-cliquer sur "add" puis "Camera" 

-entrer dans les paramètres de la camera 

-mettre le paramètre "Image topic" à "camera1/camera/rgb/image_raw" 

