Pour faire fonctionner le modèle :
	1) Ouvrir un terminal et aller dans le dossier arena (supprimer les dossiers devel et build)
	2) Taper la commande : catkin_make
	3) Taper la commande : gedit ~/.bashrc
	4) Ajouter la ligne suivante à la fin : 
		export GAZEBO_MODEL_PATH=~/projet_turtlebot3/arena/src/arena_gazebo/models:$GAZEBO_MODEL_PATH
		source ~/projet_turtlebot3/arena/devel/setup.bash
	5) Taper la commande : cd /usr/share/gazebo-7/materials
	6) Taper la commande : sudo gedit scripts/gazebo.material
	7) Entrez votre mot de passe et copier ce bout de code à la fin du fichier

	material Gazebo/TextureArene
	{
	  receive_shadows on

	  technique
	  {
	    pass
	    {
	      ambient 0.5 0.5 0.5 1.000000

	      texture_unit
	      {
	        texture arene_test.png
	      }
	    }
	  }
	}

	8) Taper la commande : sudo cp ~/projet_turtlebot3/arena/src/arena_gazebo/materials/textures/arene_test.png textures/
	
Pour lancer le modèle : 
	1) Ouvrir un terminal
	2) Taper la commande : . ~/projet_turtlebot3/arena/devel/setup.bash
	3) Taper la commande : roslaunch arena arena.launch
