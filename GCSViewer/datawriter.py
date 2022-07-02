from concurrent.futures import wait
from pymavlink import mavutil
import dronekit as vehicle
import json
import redis as rd
import dronekit_sitl
#connection_string = "127.0.0.1:115200"

sitl = dronekit_sitl.start_default()
connection_string = sitl.connection_string()
try:
     uav = vehicle.connect(connection_string, timeout=30, wait_ready = True)
     db = rd.Redis(host='localhost', port=6379, db=0)
     if db:
          print("Database Connection: OK!")
except Exception:
     print(Exception.args)

print(uav.attitude.roll)
print(uav.attitude.pitch)

flight_data = {
     'att_pitch' : uav.attitude.pitch,
     'att_roll' : uav.attitude.roll,
     'ais' : uav.velocity[0],
     'alt' : uav.location.global_relative_frame.alt,
     'head' : uav.heading,
     'lat' : uav.location.global_relative_frame.lat,
     'lon' : uav.location.global_relative_frame.lon,
     'mode' : uav.mode,
     'turn' : uav.attitude.roll,
     'vspeed' : uav.velocity[1]
     }

db_flight_data = json.dumps(flight_data)



db.set('json_data',db_flight_data)