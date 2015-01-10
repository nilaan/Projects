#/usr/bin/python
#from RPIO import PWM
#import RPIO
import time

#Time in MicroSeconds

#List of GPIO
pins = [9, 10, 11, 12]
times = [0, 0, 0, 0]
#pins = TL, TR, BL, BR

'''
def runServo(pin, time):
    motor = PWM.Servo()
    motor.set(pin, time)
    motor.stop_servo(pin)
'''

def runMotor(pin, time):
    RPIO.output(pin, True)
    time = time/1000000
    sleep(time)
    RPIO.output(pin, FALSE)
    sleep(0.02)
    print time

def setMotor(pin):
    RPIO.setup(pin, RPIO.OUT)

#run initMotor any time motor is reset
def initMotor(pin):
    init = 0
    while (init < 200):
	runMotor(pin, 1000)
	init+=1
    print "Motor Initiated"	

def move():
    for i in range(4):
	runMotor(pins[i], times[i])

def up():
    for i in range(4):
	times[i] = 1600

def forward():
    for i in range(4):
	times[i] = 1300

#main

print "Code Initiated"
for pin in pins:
    setMotor(pin)
for pin in pins:
    initMotor(pin)
print "Moving Motors"
start = time.time()
while (time.time() - start < 30 )  
    move()

