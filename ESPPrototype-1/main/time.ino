#include <NTPClient.h>
#include <time.h>

//Time offset: UTC-4
const long utcOffsetInSeconds = -4 * 3600;

//Variable to detect if the time is set already
bool timeSet = false;
//Detect new minute to change time
int lastMinute = -1;

//NTP client setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org",utcOffsetInSeconds, 60000);  //UTC-4 time, 60s update (we'll only use it once)

void setSystemTime(){
  //Check if WiFi is connected first
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Unable to get time, WiFi not connected.");
    return;
  }

  //Initialize NTP and fetch time
  timeClient.begin();
    while (!timeClient.update()){
        timeClient.forceUpdate();
    }
  Serial.println("Time from NTP: " + timeClient.getFormattedTime());

  //Setup system time with in-built RTC
  time_t rawTime = timeClient.getEpochTime();
  struct timeval tv = { .tv_sec = rawTime };
  settimeofday(&tv, nullptr);

  timeSet = true;
}

//Function to update the time UI
void updateUI_time(lv_timer_t *timer){
  if (timeSet){
    //Use system RTC to get current time
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
    } else {
      if (timeinfo.tm_min != lastMinute){
        lastMinute = timeinfo.tm_min;

        char timeStr[16];
        strftime(timeStr, sizeof(timeStr), "%H:%M", &timeinfo);
        lv_label_set_text(ui_Time, timeStr);
      } 
    }
  }
}