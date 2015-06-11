// designed for use on a Raspberry Pi MicroController
import RPi.GPIO as GPIO
import time

// list of pins at which motors are connected
pins = [21, 23, 24, 26]
// default pulse values
pulses = [1400.0, 1400.0, 1400.0, 1400.0]
// count of number of motors currently attached
num = 4
// used for testing purposes - allows for easy change in pulses[]
p = 1500.0

// allows immediate change of pulse values implemented to all motors of Quad
def testing():
    for i in range(num):
        pulses[i] = p

// initiation of Controller pins
def setMotor(pin):
    GPIO.setup(pin, GPIO.OUT)

// pulse width modulation output
def runMotor(pin, pulse):
    pulse = pulse/1000000
    GPIO.output(pin, 1)
    time.sleep(pulse)
    GPIO.output(pin, 0)
    time.sleep(0.015)

// initial callobration of all motors
def initMotor(pin):
    for x in range (200):
        runMotor(pin, 1000.0)

// increase / decrease motor speed based on desired pulse 
def increase(i, pulse):
    pulses[i] = pulse

// shutdown all motors by setting speed to 0
def shutdown():
    for i in range(num):
        pulses[i] = 0.0


GPIO.setmode(GPIO.BOARD)
print "Board Initiated"

print "Motors Initiating.."
for pin in pins:
    setMotor(pin)

for pin in pins:
    initMotor(pin)
print "Motors Initiated" 

// implemented to run for 20 seconds
count = 0
start = time.time()
while (time.time() - start <= 20):
    if (time.time() - start > 10):
        if (count == 0):
            testing()
            count+=1
    for i in range(num):
        runMotor(pins[i], pulses[i])
print "Motors ShutDown"
GPIO.cleanup()
