# Work-Conditions-Monitoring-Device

To use project you need to:

1. Upload "arduino_WorkConditionsMonitoringDevice.ino" to your Arduino Nano microcontroller.

2. On Raspberry Pi 0:
   1. Change Raspberry Pi configuration:
    `$ sudo raspi-config`
    Select `3 Interface Options` -> `P5 I2C` -> `<YES>`
    Select `3 Interface Options` -> `P6 Serial Port` -> `<YES>`
    Select `3 Interface Options` -> `P8 Remote GPIO` -> `<YES>`
   2. Run python script "python_WorkConditionsMonitoringDevice.py"
    `$ python3 python_WorkConditionsMonitoringDevice.py`

3. To run user interface:
   1. Run Node-Red
   `$ node-red start`
   2. Go to `http://\{rpi-hostname\}:1880`
   3. Import flow "flow_WorkConditionsMonitoringDevice.json"
   4. Deploy flow
   5. User interface is on `http://\{rpi-hostname\}:1880/ui`