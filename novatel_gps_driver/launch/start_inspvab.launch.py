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
                    'verbose': True,
                    'publish_novatel_positions': True,
                    'publish_novatel_velocity': False,
                    'publish_novatel_psrdop2': False,
                    'frame_id': '/gps',
                    'loop': True, 
                    'publish_imu_messages': True, 
                    'publish_nmea_messages': False, 
                    'imu_rate': 100.0, # Hz
                    'log_level': 'debug', # 日誌等級爲DEBUG
                }]
            )
        ],
        output='screen',
        # arguments=['--ros-args', '--log-level', 'debug']
    )

    return LaunchDescription([container])
