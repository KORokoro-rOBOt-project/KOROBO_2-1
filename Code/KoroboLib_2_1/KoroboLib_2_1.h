#ifndef KoroboLib_2_1_h
#define KoroboLib_2_1_h

//motor
#define MOTOR_POWER_MAX 255
#define MOTOR_POWER_MIN 50
////main-board ver. ~3.1
#define OLD 0
#define MOTOR_IN4_OLD_PIN 21
#define MOTOR_IN3_OLD_PIN 20
#define MOTOR_IN1_OLD_PIN 19
#define MOTOR_IN2_OLD_PIN 18
#define MOTOR_EN_OLD_PIN 22
////main-board ver. 3.2~
/////motor-driver: TC78H653
#define TC 1
#define MOTOR_IN4_T_PIN 19
#define MOTOR_IN3_T_PIN 18
#define MOTOR_IN1_T_PIN 17
#define MOTOR_IN2_T_PIN 16
#define MOTOR_EN_T_PIN 20
#define MOTOR_MODE_T_PIN 21
/////motor-driver: DRV8835
#define DRV 2
#define MOTOR_IN4_D_PIN 19
#define MOTOR_IN3_D_PIN 18
#define MOTOR_IN1_D_PIN 17
#define MOTOR_IN2_D_PIN 16
#define MOTOR_EN_D_PIN 21
#define MOTOR_MODE_D_PIN 20
//mic
#define MIC_PIN 26
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
//eye_mode
#define SOUND 2
#define IMU 3
#define LIGHT 5
#define ALL 30
//voice
#define I2C_ADDR_PICO 0x2E
#define VOICE_EN_PIN 6
#define VOICE_STATE_PIN 11
//sleep
#define SLEEP_AG_FILTER 1000
//other
#define RC_FILTER 0.8
#define FILTER_SAMPLE 100
//USB接続検出をするGPIOがRaspberry Pi Pico / Raspberry Pi Pico Wとで異なる
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  #define USB_POWER_PIN  66
#else
  #define USB_POWER_PIN 24
#endif

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

    void begin(unsigned int motor_select);
    void Imu_getData();
    int AmbientLight_getData();
    int Mic_getData();
    void Eye(unsigned int num);
    void Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u); 
    void Eye(int dX_point_u, int dY_point_u, int dX_size_u, int dY_size_u, unsigned int num);
    void Motor(int motor_power_l, int motor_power_r);
    void Motor(int motor_power_l, int motor_power_r, bool flug);
    void Move();
    void Voice_send(char Talk[20]);
    void Voice(unsigned int num);
    
    boolean Voice_state();
    boolean Sleep(unsigned int num);

    imu::Vector<3> korobo_acc;
    imu::Vector<3> korobo_gyro;
    imu::Vector<3> korobo_mag;

  private:
    int _SoundAmplitude(int data);
    void _Eye_point_size_init();
    void _Eye_sound();
    void _Eye_imu();
    void _Eye_light();
    void _Eye();
    void _Motor(int motor_power_l, int motor_power_r);

    int Eye_agx_array[EYE_AG_FILTER] = { 0 };
    int Eye_agy_array[EYE_AG_FILTER] = { 0 };
    int Eye_al_array[FILTER_SAMPLE] = { 0 };
    int Voice_d_array[FILTER_SAMPLE] = { 0 };
    int Sleep_array_1[SLEEP_AG_FILTER] = { 1200 };
    int Sleep_array_2[FILTER_SAMPLE] = { 0 };

    int sound_amp_temp = 0;
    int mic_val_temp = 0;
    int mic_count;
    int mic_val_min = 0, mic_val_max=0;
    int mic_ans = 0;
    int eye_sound_temp = 0;
    int eye_agx_temp = 0, eye_agy_temp = 0;
    int eye_al_val_temp = 0;
    int dX_point = 0, dY_point = 0, dX_size = 0, dY_size = 0;
    int voice_mic_temp = 0, voice_light_temp = 0, voice_d_sum_temp = 0;
    int sleep_sum_ave_diff_max = 0;
    int motor_val = 0;
    int motor_in4_pin, motor_in3_pin, motor_in1_pin, motor_in2_pin, motor_en_pin;

    float error_sum_x = 0, error_sum_y = 0;

    bool mic_val_positive = false;
    bool sleep_flag = false;

    imu::Vector<3> korobo_acc_temp;
    imu::Vector<3> korobo_gyro_temp;
    imu::Vector<3> korobo_mag_temp;
};

#endif