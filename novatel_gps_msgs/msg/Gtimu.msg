# Message from GPGGA NMEA String
# Based on https://docs.novatel.com/OEM7/Content/Logs/GPGGA.htm
std_msgs/Header header

string message_id

int32   gpsweek
float64 gpstime
float64 gx
float64 gy
float64 gz
float64 ax
float64 ay
float64 az
float32 tpr 

