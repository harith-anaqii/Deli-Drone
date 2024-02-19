# Deli-Drone
An ESP32 Drone that carries items here and there😊 


# How does it work? (simplified)



https://github.com/harith-anaqii/Deli-Drone/assets/96841569/7ea8469b-20af-4f05-a2c6-add120b7c4c9




#Proximity Warning System(PWS)
The proximity warning system involves the ultrasonic sensor and the GPS Module. The ultrasonic sensor estimates the Altitude AGL (above ground level) which is the vertical distance between the drone and the ground meanwhile the GPS module estimates the altitude MSL (Mean Sea Level) which is the estimated vertical distance between the drone and the sea using satellites. The proximity warning system works by ** if the distance between the sensor and the ground is less than 30cm, then an alert will be raised by the PWS(an acronym for Proximity Warning System) to the webserver on 192.168.X.X **. Then it's up to the user to either ignore it (for landing) or avoid the ground. 





#GPS Module
The GPS Module which is Neo-6m is used to estimate the position and the MSL altitude. This GPS Module is also used to return to the home point of the drone which is where the drone takes off. There are plans to make an autopilot system but I don't think that is possible with this type of setup. However, if you think this is possible send me a pull request. 



#RTOS 
Of course, all of this is not achievable without the use of a Real Time Operating System (RTOS). This project uses RTOS to manage its tasks since we have to update our GPS location, keep the PWS on during flying, PID controller, Continuously receive input from the webserver, power the motors, keep the drone stable using gyroscope and so on.


#PID Controller
![image](https://github.com/harith-anaqii/Deli-Drone/assets/96841569/94be0122-5db8-4e1a-b12e-65247812df9d)






