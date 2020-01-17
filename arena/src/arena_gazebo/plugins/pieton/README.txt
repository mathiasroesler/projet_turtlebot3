README pour le plugin du piéton

Objectif :
	Donner une vitesse linéaire au piéton dans la simulation Gazebo

Utilisation :
	1) Lancer le monde à l'aide de la commande :
		 roslaunch arena arena.launch
	2) Modifier la position de la barrière avec la commande :
		rostopic pub -1 /pieton/pieton_velocity std_msgs/Float32 0.1

Le dernier chiffre de la commande est la vitesse du piéton en m/s.

Modification du plugin :
	Pour modifier le plugin il faut éditer le fichier pieton_plugin.cc
	Une fois les modifications effectuées, il faut aller dans le répertoire
	build et utiliser la commande suivante :
		cmake ../ && make
	S'il n'y a pas d'erreur il faut déplacer la libraire en utilisant
	la commande suivante :
		cp *.so ../../lib

Tips :
	Le plugin ne fonctionnait pas au niveau graphique en utilisant roslaunch
	la solution était de rendre l'objet statique en changeant l'argument de
	false à true dans le fichier arena.world

