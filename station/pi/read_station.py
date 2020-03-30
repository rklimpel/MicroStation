#!/usr/bin/env python3

import RPi.GPIO as GPIO
import time
import Adafruit_DHT
import requests
import json
from datetime import datetime

pin_led_yellow = 18
pin_led_green = 23

domain = "microstation.damnserver.com"

GPIO.setwarnings(False)
 
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin_led_yellow,GPIO.OUT)
GPIO.setup(pin_led_green,GPIO.OUT)

GPIO.output(pin_led_yellow,True)
GPIO.output(pin_led_green,False)

sensor = Adafruit_DHT.AM2302
pin = 4
humidity_am2302, temperature_am2302 = Adafruit_DHT.read_retry(sensor, pin)

if humidity_am2302 is not None and temperature_am2302 is not None:
    print('DHT22: Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature_am2302, humidity_am2302))
else:
    print('Failed to get reading. Try again!')

sensor = Adafruit_DHT.DHT11
pin = 17
humidity_dht11, temperature_dht11 = Adafruit_DHT.read_retry(sensor, pin)

if humidity_dht11 is not None and temperature_dht11 is not None:
    print('DHT11: Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature_dht11, humidity_dht11))
else:
    print('Failed to get reading. Try again!')

def sent_data(value,sensor,unit,data_type):
    url = "http://" + domain + ":5000/api/v1.0/" + data_type
    timestamp = int(datetime.now().timestamp())
    data_object = {
        "value": round(value,1),
        "station_id": 0,
        "unit": unit,
        "sensor": sensor,
        "timestamp": timestamp
    }
    print(data_object)
    requests.post(url, json = data_object)

sent_data(humidity_am2302,"am2302","%","humidities")
sent_data(temperature_am2302,"am2302","°C","temperatures")
sent_data(humidity_dht11,"dht11","%","humidities")
sent_data(temperature_dht11,"dht11","°C","temperatures")

GPIO.output(pin_led_yellow,False)
GPIO.output(pin_led_green,True)
time.sleep(2)

GPIO.cleanup()