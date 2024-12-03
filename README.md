# Elderly Health Monitoring Smartwatch

### Overview

This project focuses on developing a **smartwatch** designed primarily for **monitoring elderly health**, with additional fitness tracking features. The smartwatch collects real-time health data, such as heart rate, body temperature, and step count, to provide timely insights and reminders for elderly users. Users can monitor their health through a connected mobile app, which also provides health suggestions based on the collected data.

---

## Features

### Health Monitoring:
- Real-time tracking of **heart rate**, **body temperature**, and **step count**.
- Periodic health summaries for users to review their daily activity and overall well-being.
- Monitoring of **UV radiation** (coming soon).

### Fitness Tracking:
- Basic fitness tracking including step count and activity duration.
- Integration with mobile app to provide exercise suggestions based on activity levels.

### Alerts & Notifications:
- Alerts for abnormal health conditions, such as irregular heart rate or high body temperature.
- Customizable reminders for medication, hydration, and exercise.
- Notifications delivered through **SMS** and **mobile app**.

### Mobile App Integration:
- Real-time data sync with a companion mobile app (iOS/Android).
- Display of real-time health data and historical trends.
- Health advice generated based on data trends and user activity.

---

### How to use docker?

docker build -t lvgl .

docker run -it --rm -e DISPLAY=YourOwnIP:0 -e XDG_RUNTIME_DIR=/tmp -v /tmp/.X11-unix:/tmp/.X11-unix lvgl

*Make sure to change the IP to your host device for the docker run command

IMPORTANT: Install VcXsrv

1. Set the display number to 0

2. Start no client

3. Disable access control
