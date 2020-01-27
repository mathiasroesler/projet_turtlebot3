#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import time
import random
import sys

if len(sys.argv) != 2:
	# If the number of arguments is wrong
	print("Usage script.py [rate in s]")
	exit(1)

# List of commandable obstacles and there states
obstacles = ["barriere", "barriere2", "pieton", "pieton2", "feu"]
states = [0, 0, 0, 0, 1] 

while (1):

	obstacle = random.randint(0, len(obstacles)-1) # Obstacle to be updated

	print("Changing state of obstacle", obstacles[obstacle])

	if (obstacle == 0 or obstacle == 1):
	# Barrier obstacle
		if states[obstacle] == 0:
			# Call process and change state
			subprocess.run([obstacles[obstacle], "-o"])
			states[obstacle] = 1
		else:
			subprocess.run([obstacles[obstacle], "-c"])
			states[obstacle] = 0
	
	elif (obstacle == 2 or obstacle == 3):
	# Pedestrian obstacle
		subprocess.run([obstacles[obstacle], "-m"])

	elif obstacle == 4:
	# Traffic light obstacle
		if states[obstacle] == 0:
			# Call process and change state
			subprocess.run([obstacles[obstacle], "-g"])
			states[obstacle] = 1
		else:
			subprocess.run([obstacles[obstacle], "-r"])
			states[obstacle] = 0

	print("State changed")
	time.sleep(int(sys.argv[1])) # Wait to refresh
