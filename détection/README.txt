Préparation de l'environnement:

https://imageai.readthedocs.io/en/latest/

Lancez un terminal et suivez les étapes décrites comme suit:
 
Pour imageai, vous aurez besoin de:
Etape 1:
	Python 3.5.1 ou supérieur, téléchargez Python et pip3 en tapant les commandes ci-dessous:
              		apt-get install python3
			apt-get install python3-pip
Etape 2:
	Tensorflow 1.4.0 ou supérieur, tapez les commandes suivantes
			pip3 install --upgrade tensorflow
			pip3 install tensorflow-gpu==1.13.1
Etape 3:
	Installation de la librairie keras 
    			pip3 install keras
Etape 4:
	Installation de la librairie OpenCv               
			pip3 install opencv-python

Etape 5:
	Installation de la librairie dédiée pour le Deep Learning et Computer Vision
			pip3 install imageai --upgrade



Execution du code:

Partie load Model:
Il faut charger votre modèle une seule fois.
Assurez les bons chemins des deux fichiers "model.h5", "detection_config.json" au sein de votre environnement


Partie exécution du code:
Pour exécuter le code, il faut commencer par charger le modèle en tapant:
			python3 load.py

Pour la partie détection:
Lancez la commande suivante sur le terminal:
			python3 detection.py 