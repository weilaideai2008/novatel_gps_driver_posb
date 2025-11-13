# Message from GPHPD NMEA String
std_msgs/Header header

string message_id

int32   gpsweek
float64 gpstime
float32 heading
float32 pitch
float32 track
float64 latitude
float64 longitude
float64 altitude
float32 ve
float32 vn
float32 vu
float32 baseline
int16   nsv1
int16   nsv2
uint8   status
# 0：初始化
# 1：粗对准
# 2：精对准
# 3：GPS定位
# 4：GPS定向
# 5：RTK定位
# 8：纯惯性
# 9：零速校正
# B：差分定向
# C：动态对准
