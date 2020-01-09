Pour faire fonctionner le modèle :
	1) Ouvrir un terminal et aller dans le dossier arena (supprimer les dossiers devel et build)
	2) Taper la commande : catkin_make
	3) Taper la commande : gedit ~/.bashrc
	4) Ajouter la ligne suivante à la fin : 
		export GAZEBO_MODEL_PATH=~/projet_turtlebot3/arena/src/arena_gazebo/models:$GAZEBO_MODEL_PATH
		source ~/projet_turtlebot3/arena/devel/setup.bash
	5) Taper la commande : . ~/projet_turtlebot3/arena/devel/setup.bash

REMARQUE : La suite présente les étapes pour lancer le modèle. Il est nécessaire d'avoir executé les commandes de la partie
11.[ROS] Simulation du tutoriel Robotis.
(lien : http://emanual.robotis.com/docs/en/platform/turtlebot3/simulation/#turtlebot3-simulation-using-fake-node) 

Pour lancer le modèle : 
	a) Ouvrir un terminal
	b) Taper la commande : roslaunch arena arena.launch

Si vous obtenez un message le message d'erreur suivant :
[arena.launch] is neither a launch file in package [arena] nor is [arena] a launch file name
The traceback for the exception was written to the log file

Effectuez de nouveau les étapes 1 à 5






http://gazebosim.org/tutorials?cat=install&tut=install_ubuntu&ver=7.0#Alternativeinstallation:step-by-step

