# Message from GPGGA NMEA String
# Based on https://docs.novatel.com/OEM7/Content/Logs/GPGGA.htm
std_msgs/Header header

string message_id

int32   gpsweek
float64 gpstime
float64 gx  # degree/s
float64 gy  # degree/s
float64 gz  # degree/s
float64 ax  # g
float64 ay  # g
float64 az  # g
float32 tpr 

