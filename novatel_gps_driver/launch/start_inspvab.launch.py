"""Launch an example driver that communicates using TCP"""

from launch import LaunchDescription
import launch_ros.actions


def generate_launch_description():
    container = launch_ros.actions.ComposableNodeContainer(
        name='novatel_gps_container',
        namespace='',
        package='rclcpp_components',
        executable='component_container',
        composable_node_descriptions=[
            launch_ros.descriptions.ComposableNode(
                package='novatel_gps_driver',
                plugin='novatel_gps_driver::NovatelGpsNode',
                name='novatel_gps',
                parameters=[{
                    'connection_type': 'serial',
                    'device': '/dev/ttyACM0',
                    'serial_baud': 921600,
                    'verbose': True,
                    'publish_novatel_positions': True,
                    'publish_novatel_velocity': False,
                    'publish_novatel_psrdop2': False,
                    'frame_id': '/gps',
                    'loop': True, 
                    'publish_nmea_messages': True,
                    'publish_gtimu': True,
                    'publish_gpfpd': True,
                    'publish_gphpd': True,
                    'frame_id': "gnss_ins",
                    'imu_rate': 100.0, # Hz
                    'log_level': 'debug', # 日誌等級爲DEBUG debug, info, warn, error, fatal
                }]
            )
        ],
        output='screen',
        # arguments=['--ros-args', '--log-level', 'debug']
    )

    return LaunchDescription([container])
