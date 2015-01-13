import RPi.GPIO as GPIO
import time

pins = [21, 23, 24, 26]
pulses = [1400.0, 1400.0, 1400.0, 1400.0]
num = 4
p = 1500.0

def testing():
    for i in range(num):
        pulses[i] = p

def setMotor(pin):
    GPIO.setup(pin, GPIO.OUT)

def runMotor(pin, pulse):
    pulse = pulse/1000000
    GPIO.output(pin, 1)
    time.sleep(pulse)
    GPIO.output(pin, 0)
    time.sleep(0.015)

def initMotor(pin):
    for x in range (200):
        runMotor(pin, 1000.0)

def increase(i, pulse):
    pulses[i] = pulse

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
