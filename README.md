Autonomous Sensor-Driven Autonomous Line Following Robot for Real-Time Path Correction

![image](https://github.com/user-attachments/assets/0ea0355d-2070-4212-afcf-62e896c7523c)

🛠️ Tools & Technologies
Microcontroller: Funduino (Arduino Uno-compatible board)

Sensors: Infrared (IR) Obstacle Avoidance Sensors

Power Supply: 9V Battery Pack, Mini560 DC-DC Buck Converter 

Modules: Arduino Sensor Shield V5.0 (for easier sensor and module connections)

Mechanical Components: Front Differential (Salvaged from a toy car)

Development Environment: Arduino IDE

⬜️⬛ Front Sensor Block 

![image](https://github.com/user-attachments/assets/530366cc-4903-488a-b2a9-53adb2f90e85)

The Front Sensor Block is positioned at the front of the line follower and serves as the primary sensing system. At its core is a Funduino (Arduino Uno-compatible board), flanked by infrared (IR) sensors positioned on opposite sides. These IR sensors operate on the principle that lighter surfaces reflect more infrared light, while darker surfaces absorb it.

The robot is programmed to be draw to darker surfaces; when an IR sensor detects minimal reflected light, the robot interprets it as part of the line and steers in that direction. This behavior allows the robot to continuously adjust its path and stay aligned with the dark line on the surface.


⚙️Weighted Logic 

Initially at the beginning at the project, I primarily utilized the funduino sensor as the main sensing unit and hardcoded binary values to operate the robot motions. This was efficient enough to navigate through straight/curved lines. However, it failed at sharp turns; hence, I added extra ir sensors positioned to opposite sides. The approach enabled the robot to navigate through sharp turns more effectively. However, with the hard coded script, the robot failed to stay on course at times and failed to navigate through unique track patterns/obstacles. 

In order to rectify this issue, I sought to include a weighted logic system where each sensor had the respective values:

```
const float leftirsensor_weight = -0.3f;
const float left_weight = -0.1f;
const float centerWeight = 0.0f;
const float right_weight = 0.1f;
const float rightirsensor_weight = 0.3f;
```
Sensors Layout Respective To Weights
![image](https://github.com/user-attachments/assets/00107c2f-55ac-46f7-abd4-28756bd18188)


In which belonged to the respective sensors:

The system works as follows: if multiple sensors do not pick up light from a specific area, the respective sensors weight will be added together and the value will be fed through a function that decides which direction the robot would move. 

This system when tested would prove to be highly efficient by allowing the robot to navigate through sharp turns and unique patterns on the track. 

✏️ Course Layouts 

![image](https://github.com/user-attachments/assets/0af89f95-b868-460c-a2fb-35df76848caf)


Course #1:  [Demo #1: Autonomous Line Following Robot](https://www.youtube.com/watch?v=OqyYif4jq5Q&t=1s)

Course #2:  [Demo #2: Autonomous Line Following Robot](https://youtu.be/u_tEcljQaS0?si=CvnIafdUAzQ-CT-G)

Course #3:  [Demo #3: Autonomous Line Following Robot](https://youtu.be/FmVCL2pEUbI?si=cRp6DwyrxZtuvAr8)


