Pour faire fonctionner le modèle :
	1) Ouvrir un terminal et aller dans le dossier arena
	2) Taper la commande : catkin_make
	3) Taper la commande : . devel/setup.bash (Ne pas oublier le point)
	4) Taper la commande : gedit ~/.bashrc
	5) Ajouter la ligne suivante à la fin : export GAZEBO_MODEL_PATH=~/projet_turtlebot3/arena/src/arena_gazebo/models:$GAZEBO_MODEL_PATH
	6) Taper la commande : cd /usr/share/gazebo-7/materials
	7) Taper la commande : sudo gedit scripts/gazebo.material
	8) Entrez votre mot de passe et copier ce bout de code à la fin du fichier

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

	9) Taper la commande : sudo cp ~/projet_turtlebot/arena/src/arena_gazebo/materials/textures/arene_test.png textures/
	
Pour lancer le modèle : 
	1) Ouvrir un terminal
	2) Taper la commande : . ~/projet_turtlebot3/arena/devel/setup.bash
	3) Taper la commande : roslaunch arena arena.launch
