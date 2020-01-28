# Gestion des Objets Connectés de l'ARENE

## 1) Se connecter à la RaspberryPi de l'arène :
```bash
ssh pi@192.168.0.233
mdp:raspberry
```
## 2) se positionner sur le répertoire du code Arduino à uploader et téléverser :
- Objets Connectès contrôlés avec Boutons
	```bash
	cd /home/pi/Arduino/OC_Boutons/
	```
- Objets Connectès contrôlés avec la RPi
	```bash
	cd /home/pi/Arduino/OC_RPi/
	```
## 3) Téléverser du Script Arduino :
Lancer le Makefile :
```bash
make
```
Uploader le Script correspondant :
```bash
make upload
```

## 4.1) Commander avec la RPi
lancer le code python qui gère les commandes de la Raspberry ( A ne faire que  dans le cas d'un contrôle avec la RPi ) :
```bash
	cd 
	python OC_RPi.py
``` 
## 4.2) Commander avec les boutons
Pour les Boutons, Il n'as pas de code à lancer. Il faut commander directement avec les boutons du BreadBoard


