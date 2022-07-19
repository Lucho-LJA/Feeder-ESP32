# Feeder-ESP32
The project is about the code to Control a circular feeder with ESP32 and ROS. It is the code of Board, destined to [ESP32 with 38 pins](https://uelectronics.com/producto/esp32-38-pines-esp-wroom-32/) and following the [ESP32 documentation](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/).

## GENERAL DESCRIPTION
The code is used to cominicate with ROS using rosserial_python with ROS distro: Noetic. The project use plataformio framwork and VSCode. All libraries are open source and they have theirs respective licences.

Feeder have the types:
- `FEEDER_2SENSOR_1MOTOR`: It is a circular feeder with 2 sensors: one inductive and other as end of career. the move is a DC motor. The functionality is move one pice of store fed using gravity to other side that is detected with iductive sensor in order to be 
picked up for other cell or robot. Use the driver L298N.
- `FEEDER_LINEAL_CONVEYOR`: It is conveyor with move clock and counter clock. It have a emergency stop button to stop all proceess physically. Use the driver L298N.

## DEPENDECIES
- Platformio (IDE into VSCode recommended)
- VSCode (Used it to upload the programe)
- ESP32 38 pines
- Driver L298N Shield for 1 or 2 motors
- ROS noetic (Ubuntu 20.04)
- python3
- rosserial_python package (to communication with ROS enviroment)

## INSTRUCTIONS
- Clone the repository with:
    ```bash
    git clone --verbose https://github.com/Lucho-LJA/Feeder-ESP32.git
    ```
- Configure the params into the file [CONFIG.H](/include/CONFIG.h)
- Load the code to ESP32
- Run `roscore` and [rosserial_python](#instructions-to-install-and-run-rosserialpython)
- ready

## Instructions to install and run rosserial_python
- update your repositories with: `sudo apt update`
- Install package with: `sudo apt-get install ros-noetic-rosserial`
- run command: `roscore`
- open new terminal and run command: `rosrun rosserial_python serial_node.py _port:=tcp _tcp_port:=<11422>`.
    - `<11422>` must be channge with your `ROS_SERVER_PORT`. eg. `_tcp_port:=1147`.
    - if you want to control with serial o defect values view [Ros Wiki](http://wiki.ros.org/Documentation)
- If you found errors when run the command. Is posible that the package version is other diferent to the normal, so do next:
    - with the terminal or grafic editor open the file: `/opt/ros/noetic/lib/rosserial_python/serial_node.py`.
    - Watch the lines 58 and 59 and verify if this code is there:
    ```python

        tcp_portnum = int(rospy.get_param('/rosserial_embeddedlinux/tcp_port', '11411'))
        fork_server = rospy.get_param('/rosserial_embeddedlinux/fork_server', False)

    ```
    - if you confirmed the above, then the last command isn't usable. there are many solutions, but I did the most easily for me and change the code. However, if you want to resolve it of other way, that is also good. So, I changed the lines 58 and 59 with:
    ```python

    if (rospy.has_param('~tcp_port')):
        tcp_portnum = int(rospy.get_param('~tcp_port', '11411'))
    else:
        tcp_portnum = int(rospy.get_param('/rosserial_embeddedlinux/tcp_port','11411'))
    if (rospy.has_param('~fork_server')):
        fork_server = rospy.get_param('~fork_server')
    else:
        fork_server = rospy.get_param('/rosserial_embeddedlinux/fork_server', False)

    ```
    If you are curious and review the documentation about rosserial python, you should have noticed that the code is the same that other version. If you go to oficial documentation on [github](https://github.com/ros-drivers/rosserial/blob/noetic-devel/rosserial_python/nodes/serial_node.py), you must see better.
- Now, the "serial_node" node is running and if the ESP32 is running too, then the server will recognize it automatically.
- In order to check the communication, run the command `rostopic list` in other terminal and you will can see the topics, that they was created for the ESP32. 

## Common issues
There are some issues indepedence of configuration and some of them are:
- Error: [99-platformio-udev.rules in Linux](https://docs.platformio.org/en/latest/core/installation/udev-rules.html)
```bash
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules
sudo service udev restart
sudo udevadm control --reload-rules
sudo udevadm trigger
```
- Change Monitor serial of platformio
    - Go to file: `platformio.ini`
    - Choose a enviroment and add: `monitor_speed = 115200` 

- When you use several nodes of `rosserial_pyton package` and the name generate a error, you must run the node with diferent node name, example:
```bash
    rosrun rosserial_python serial_node.py __name:=<"name of node"> _port:=tcp _tcp_port:=<port>
```