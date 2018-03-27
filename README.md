# blink
This project consisted of three file(Blink.cpp, Blink.h, blink.ino). 
I made Blink.cpp and Blink.h for library. 
header file(**Blink.h**) has definitions of function and variable for the library: (function: on(int) and off(int), variable: _pin )
source file(**Blink.cpp**) has the actual code: (on(time): turn LED during the time, off(time): off LED during the time )

# Temperature
This project can show me my room temperature and I use Ds18b20 sensor.

# web_float
This project consisted of one file(web_float.js). 
This program provide service that you can save your float data(rounded to two decimal place).
If you want to save your float data, then you write this format(http://163.239.76.215:8080/update?api_key='KEYVALUE'&field1='VALUE')
If you want to show the number of lastest N float data, then you write this format(http://163.239.76.215:8080/get?count=N)) 

# download_db
This project consisted of one file(download_db.js).
This program proivde service that you can save your real sensor data.
THis program have MySQL database that named sensors;
If you want to save your sensor data, then you write this format(ex- http://163.239.76.215:8083/log?device=900&unit=9&type=T&value=99.99&seq=9)
If you want to show the number of sensor data, then you write this format(ex- http://163.239.76.215:8083/download)

