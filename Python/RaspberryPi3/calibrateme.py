#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import numpy as np
import smbus #FOR the I2C bus

LedPin = 12
sampling_rate = 0.01; #sampling rate in seconds
		     #this value indicates how often we will 
		     #evaluate our function in real time
lux_low = 1000; 


def setup():
    #Set up the I2C bus for the LUX
    # Get I2C bus
	global bus;
	bus = smbus.SMBus(1)
    # TSL2561 address, 0x39(57)
    # Select control register, 0x00(00) with command register, 0x80(128)
    #		0x03(03)	Power ON mode
	bus.write_byte_data(0x39, 0x00 | 0x80, 0x03)
    # TSL2561 address, 0x39(57)
    # Select timing register, 0x01(01) with command register, 0x80(128)
    #		0x02(02)	Nominal integration time = 402ms
	bus.write_byte_data(0x39, 0x01 | 0x80, 0x02)
	time.sleep(0.5);
    #Set up the GPIO modes for PWM
	global p
	GPIO.setmode(GPIO.BOARD)       # Numbers GPIOs by physical location
	GPIO.setup(LedPin, GPIO.OUT)   # Set LedPin's mode is output
	GPIO.output(LedPin, GPIO.LOW)  # Set LedPin to low(0V)

	p = GPIO.PWM(LedPin, 100)     # set Frequence to 1KHz
	p.start(0)                     # Duty Cycle = 0

#supplied f_function
#the value of the function will be mapped to the brightness of the 
#LED
def f_function(currTime):
	val = np.sin(1/3.14*(currTime-3.14));#Notice that I am shifting the function 
				      #So that at t=0, the function value is 0 
	return val; 

def loop():
	#x = range(0,100,sampling_rate);
	#plt.plot(x, f_function(x)); 
	currTime = 0; 
	fmin = -2; fmax = 2; 

	while True:
		#calculate the duty cycle based on the function
		dc = calcDutyCycle(f_function(currTime), fmin, fmax);
		p.ChangeDutyCycle(dc); 
		#print f_function(currTime); 
		#print dc;
		time.sleep(sampling_rate); 
		currTime = currTime+sampling_rate; 
		

#This function calculates the dutyCycle based on the 
#function value
def calcDutyCycle(fval, fmin, fmax):
	dc_0_1 = (fval - fmin)/(fmax-fmin);#this part maps the value of the function
					   #to a value between 0 and 1

	#dc_0_1 = dc_0_1*dc_0_1; #instead of a straight line between 0 and 1
				#we can also try a quadratic line between 0 and 1
				#try changing it to a cubic or a square root and see what feels better
	if dc_0_1 > 1:
		dc_0_1 = 1; 
	if dc_0_1 < 0:
		dc_0_1 = 0; 
	
	return dc_0_1*100;

#Read from the Light sensor
def readExternal():
    # Read data back from 0x0C(12) with command register, 0x80(128), 2 bytes
    # ch0 LSB, ch0 MSB
    data = bus.read_i2c_block_data(0x39, 0x0C | 0x80, 2)
    # Read data back from 0x0E(14) with command register, 0x80(128), 2 bytes
    # ch1 LSB, ch1 MSB
    data1 = bus.read_i2c_block_data(0x39, 0x0E | 0x80, 2)
    # Convert the data
    ch0 = data[1] * 256 + data[0]
    ch1 = data1[1] * 256 + data1[0]
    vis_val = (ch0 - ch1); 
    return vis_val;  
    
    
    #Read from the Light sensor
def readExternalNew(V):
    # Read data back from 0x0C(12) with command register, 0x80(128), 2 bytes
    # ch0 LSB, ch0 MSB
    data = bus.read_i2c_block_data(0x39, 0x0C | 0x80, 2)
    # Read data back from 0x0E(14) with command register, 0x80(128), 2 bytes
    # ch1 LSB, ch1 MSB
    data1 = bus.read_i2c_block_data(0x39, 0x0E | 0x80, 2)
    # Convert the data
    ch0 = data[1] * 256 + data[0]
    ch1 = data1[1] * 256 + data1[0]
    vis_val = (ch0 - ch1); 
    
    #new
    print "%f,%f"
    a_ret = vis_val - (Res_a*V*V+Res_b*V + Res_c);
    bac = (Res_b*Res_b-4.0*(Res_c - a_ret)*Res_a);
    
    if bac < 0.0
    	rel = 0.0;
    else:
    	val_ret_a = (-Res_b+np.sqrt(Res_b*Res_b-4.0*(Res_c-a_ret)*Res_a))/(2.0*Res_a);
    	val_ret_b = (-Res_b-np.sqrt(Res_b*Res_b-4.0*(Res_c-a_ret)*Res_a))/(2.0*Res_a);
    	rel = max(val_ret_a,val_ret_b,0,0);
    return rel;  
    
#Nagumo program
def fitzhughNagumo():
    #time step
    tstep = 0.01;
    #initial values of v and w
    v = 2.0; 
    w = 0.0; 
    I_ext = 0; 
    tc = 1.0;
    #parameters
    a = 1; b = 0.0; c = 0.8;
    eps = 10;
    #time scale used to shift the model
    t_sc = 10; 
    #end of parameters 
    fmin = -2; fmax = 2; 
    while(True):
        #calculate how long it takes to do the computation
        #and substract that time from the sleep time 
        #in case the computation takes a long time
        t_start = time.time();
        #calculate the rate of change
        I_ext = readExternalNew(v);
        dv = t_sc*(v - v**3/3 - w + I_ext)
        dw = t_sc*(1.0/eps*(a*v+b-c*w));
        #calculate the value of v based on the rate of change
        v = v+tstep*dv; 
        w = w+tstep*dw;     
        #now calculate the dc associated with the current v
        dc = calcDutyCycle(v, fmin, fmax);
        t_end = time.time();
        #change the duty cycle
        p.ChangeDutyCycle(dc); 
        #sleep for sampling time
        time.sleep(sampling_rate-(t_end-t_start)); 
        

        
#Calibration code
def calibrate():
    f_min = -2.0;
    f_max = 2.0; 
    
    #set my LED to a certain value
    fval = [-2.0, -1.0, 0.0, 1.0, 2.0];
    
    #store the bs in arrays 
    b_array = []; 
    A_array = [[4, -2, 1], [1, -1, 1], [0, 0, 1], [1,1,1], [4,2,1]]; 
    for vals in fval:
        dc = calcDutyCycle(vals, f_min, f_max)
        #set the LED to the particular light level
        p.ChangeDutyCycle(dc); 
        #read the sensor value
        time.sleep(1); 
        s_val = readExternal();
        b_array.append(s_val);
        print "%f, %f, %f" % (vals, s_val, dc);
        time.sleep(1);
    #flash flash flash after calibration
    p.ChangeDutyCycle(10);
    time.sleep(0.5);
    p.ChangeDutyCycle(40);
    time.sleep(0.5);
    p.ChangeDutyCycle(60);
    time.sleep(0.5);
    p.ChangeDutyCycle(100);
    time.sleep(0.5);    
    p.ChangeDutyCycle(0);
    #start solving the least square (AT*A)\(AT*b)
    Res = np.linalg.lstsq(A_array,b_array);
    global Res_a; 
    global Res_b; 
    global Res_c; 
    
    Res_a = Res[0][0];
    Res_b = Res[0][1];
    Res_c = Res[0][2];
    
    print "a=%f, b=%f, c=%f" %(Res_a, Res_b, Res_c); 
    
def destroy():
	p.stop()
	GPIO.output(LedPin, GPIO.HIGH)    # turn off all leds
	GPIO.cleanup()

if __name__ == '__main__':     # Program start from here
	setup()
	try:
		#loop()
		#fitzhughNagumo();
        calibrate();
        time.sleep(10); 
        fitzhughNagumo();
	except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
		destroy()