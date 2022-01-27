import time
import board
import serial
import adafruit_bh1750
import adafruit_dht
import adafruit_ccs811

i2c = board.I2C()
light_sensor = adafruit_bh1750.BH1750(i2c)
dhtDevice = adafruit_dht.DHT22(board.D18)
ccs811 = adafruit_ccs811.CCS811(i2c)

# print('Running. Press CTRL-C to exit.')

# BH1750
while(True):
    ligh = str(format(light_sensor.lux, '.0f'))
    light = 'l'+ligh
    # print('l' + light)
    f = open("light.txt", "w")
    f.write(ligh)
    f.close()

# CCS811
    while not ccs811.data_ready:
        pass
    co2 = str(ccs811.eco2)
    tvoc = str(ccs811.tvoc)
    co2f = 'c'+co2
    tvocf = 'v'+tvoc

    # print('c' + co2f)
    # print('tv' + tvocf)

    f = open("co2.txt", "w")
    f.write(co2)
    f.close()
    f = open("tvoc.txt", "w")
    f.write(tvoc)
    f.close()

# DHT
    while True:
        try:
            temp = dhtDevice.temperature
            hum = dhtDevice.humidity
            if(temp != None and hum != None):
                temperature = 't'+str(temp)
                humidity = 'h'+str(hum)
                # print('t' + temperature)
                # print('h' + humidity)
                f = open("temperature.txt", "w")
                f.write(str(temp))
                f.close()
                f = open("humidity.txt", "w")
                f.write(str(hum))
                f.close()
                break

        except RuntimeError as error:
            time.sleep(0.5)
            continue
        except Exception as error:
            dhtDevice.exit()
            continue

    with serial.Serial("/dev/ttyUSB0", 9600, timeout=1) as arduino:
        time.sleep(0.1)
        if arduino.isOpen():
            # print("{} connected!".format(arduino.port))
            try:
                    time.sleep(1.5)

                    arduino.write(temperature.encode())
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        # print(answer)
                        arduino.flushInput()

                    arduino.write(humidity.encode())
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        # print(answer)
                        arduino.flushInput()

                    arduino.write(light.encode())
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        # print(answer)
                        arduino.flushInput()

                    arduino.write(co2f.encode())
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        # print(answer)
                        arduino.flushInput()

                    arduino.write(tvocf.encode())
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0:
                        answer=arduino.readline()
                        # print(answer)
                        arduino.flushInput()
            except KeyboardInterrupt:
                print("KeyboardInterrupt has been caught.")