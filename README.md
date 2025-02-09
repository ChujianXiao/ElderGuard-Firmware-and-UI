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

## Authors
### Main Contributors to Current Repo
- **Haochen Qin** - Sensor Integration and Wi-Fi Connectivity
- **Chujian Xiao** - UI/UX design

---

## Versions
Current version: **v2.1**

### Version History
- **v1.0** - Implemented system on STM32 Microcontroller, successfully ran UI and connected sensors.

- **v2.0** - Migrated to ESP32 Microcontroller for its on-chip Wi-FI functionality, created seperate folder.

- **v2.1** - Implemented FreeRTOS, seperated tasks for sensors, UI and Wi-Fi. Sensors now read data to global variable, which can be accessed by the UI.



