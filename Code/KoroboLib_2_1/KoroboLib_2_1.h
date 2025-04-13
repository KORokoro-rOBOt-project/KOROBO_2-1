#ifndef KoroboLib_2_1_h
#define KoroboLib_2_1_h

//motor
#define MOTOR_POWER_MAX 255
#define MOTOR_POWER_MIN 50
#define MOTOR_IN4_PIN 21
#define MOTOR_IN3_PIN 20
#define MOTOR_IN1_PIN 19
#define MOTOR_IN2_PIN 18
#define MOTOR_EN_PIN 22
//mic
#define MIC_PIN 26
#define MIC_PP_DATA_NUM 1000
//ambient light
#define AMBIENT_LIGHT_PIN 27
//eye_info
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define X_EYE_L 30
#define X_EYE_R 85
#define Y_EYE 10
#define EYE_WIDTH 13
#define EYE_HEIGHT 44
#define EYE_AG_FILTER 10
#define EYE_SOUND_FILTER 50
//eye_mode
#define SOUND 2
#define IMU 3
#define LIGHT 5
#define WINK 7
#define ALL 210

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"
#include "string.h"

class KoroboLib_2_1 {
  public:
    KoroboLib_2_1();
    ~KoroboLib_2_1();

    imu::Vector<3> korobo_acc;
    imu::Vector<3> korobo_gyro;
    imu::Vector<3> korobo_mag;

    void begin();
    void Imu_getData();
    int AmbientLight_getData();
    int Mic_getData();
    void Eye(unsigned int num);
    void Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u); 
    void Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u, unsigned int num);
    void Motor(int motor_power_l, int motor_power_r);

  private:
    int SoundAmplitude(int data);
    void Eye_point_size_init();
    void Eye_sound();
    void Eye_imu();
    void Eye_light();
    void Eye_wink();

    int Eye_agx_array[EYE_AG_FILTER] = { 0 };
    int Eye_agy_array[EYE_AG_FILTER] = { 0 };
    int Eye_sound_array[EYE_SOUND_FILTER] = { 0 };

    int sound_amp_temp = 0;
    int mic_val_temp = 0;
    int mic_count;
    int mic_val_min = 0, mic_val_max=0;
    int mic_ans = 0;
    int eye_sound_temp = 0;
    int eye_agx_temp = 0, eye_agy_temp = 0;
    int dX_point = 0, dY_point = 0, dX_size = 0, dY_size = 0;

    bool mic_val_positive = false;

    imu::Vector<3> korobo_acc_temp;
    imu::Vector<3> korobo_gyro_temp;
    imu::Vector<3> korobo_mag_temp;
};

#endif
