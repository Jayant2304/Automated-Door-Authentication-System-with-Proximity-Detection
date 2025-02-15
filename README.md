# Automated-Door-Authentication-System-with-Proximity-Detection
I configured NodeMCU to set or reset the registration mode of RFID Tags. If we want to
register the RFID tag, NodeMCU is given a pin high input via mobile hotspot. When the pin is
made low and given to NodeMCU, the RFID module will check if the tag being sensed is
registered or not, if it is registered then the stepper motors rotate 90 degrees in clockwise
direction implying opening of the door. If there is no object within 10 cm of the ultrasonic sensor,
then the stepper motor will move 90 degrees in anti-clockwise direction, implying closing of the
door, whereas if there is an object within 10 cm of the sensor then, the door will remain open
