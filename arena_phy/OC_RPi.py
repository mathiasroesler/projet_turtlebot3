import serial
import time
import os
# A changer avec  ls /dev/tty* et prendre ttyACM0
ser = serial.Serial('/dev/ttyACM0', 9600)
print("CTRL + C pour arreter")

while True :
		print("CTRL + C pour arreter \n")
		print("\t \t \t GESTION DES OBJETS CONNECTES \n")
		print("\t \t \t ---------------------------- \n")
		msg=int(input("1- VERT | \t  2- ROUGE | \t  3- OUVERTURE  | \t 4-FERMETURE \n"))
		os.system("clear")
		ser.write(str(msg))
