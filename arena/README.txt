Pour faire fonctionner le modèle :
	1) Ouvrir un terminal et aller dans le dossier arena
	2) Taper la commande : catkin_make
	3) Taper la commande : . devel/setup.bash (Ne pas oublier le point)
	4) Taper la commande : gedit ~/.bashrc
	5) Ajouter la ligne suivante à la fin : export GAZEBO_MODEL_PATH=~/projet_turtlebot3/arena/src/arena_gazebo/models:$GAZEBO_MODEL_PATH
	
Pour lancer le modèle : 
	1) Ouvrir un terminal
	2) Taper la commande : . ~/projet_turtlebot3/arena/devel/setup.bash
	3) Taper la commande : roslaunch arena arena.launch
