#include "app.h"
#include "kernel.h"
#include "LineTracer.h"
#include "PIDController.h"
#include "DistanceCalculator.h"
#include "Motor.h" 
#include "ForceSensor.h" 
#include "ColorSensor.h"

/* SPIKE-RTのシリアル（Bluetooth含む）API */
#include <syssvc/serial.h>

/* SPIKE Bluetooth制御API */
#include <spike/hub/bluetooth.h>

#include <stdio.h>
#include <string.h>

#include "Clock.h"

struct Section {
    int distance;
    int speed;
    float kp;
    float ki;
    float kd;
};

//{走行距離(mmまで), 走行速度, 比例ゲイン, 積分ゲイン, 微分ゲイン}
Section sections[] = {
    {600, 100, 0.6, 0.0, 0.2}, //区間１　直進　約60cm
    {900, 70, 0.6, 0.0, 0.4},  //区間２　緩やかなカーブ　約30cm
    {1400, 100, 0.8, 0.0, 0.2},   //区間３　直進　約50cm
    {1700, 70, 0.6, 0.0, 0.4},  //区間４　緩やかなカーブ　約30cm
    {2100, 100, 0.5, 0.0, 0.2},  //区間５　直進　約40cm
    {2600, 70, 0.6, 0.0, 0.4}, //区間６　緩やかなカーブ　約30cm
    {4400, 70, 0.5, 0.0, 0.4},  //区間７　蛇行　約180cm
    {5400, 100, 0.6, 0.0, 0.4}   //区間８　直進　約100cm
};

/**
 * Bluetooth初期化処理
 * - serial_opn_por(2)でBluetoothシリアルを開く
 * - 接続されるまで待機する
 */
static void init_bluetooth()
{
    bool connected = false;

    /* Bluetoothシリアルをオープン
     * → これにより内部でadvertisingが開始される */
    serial_opn_por(2);

    /* PCなどと接続されるまで待機 */
    while (!connected) {
        hub_bluetooth_is_connected(&connected);

        /* 100ms待機（CPU負荷軽減） */
        tslp_tsk(100 * 1000);
    }
}

/**
 * 距離データをBluetoothへ送信
 * 送信フォーマット: DIST,xxx\n
 */
static void send_distance(int32_t distance)
{
    char buffer[64];

    /* 数値をCSV形式の文字列に変換 */
    int len = snprintf(
        buffer,
        sizeof(buffer),
        "DIST,%ld\n",
        (long)distance
    );

    /* Bluetoothポート(2)へ送信 */
    serial_wri_dat(2, buffer, len);
}

/**
 * 距離データをBluetoothへ送信
 * 送信フォーマット: DIST,xxx\n
 */
static void send_color(int32_t color)
{
    char buffer[64];

    /* 数値をCSV形式の文字列に変換 */
    int len = snprintf(
        buffer,
        sizeof(buffer),
        "COLOR,%ld\n",
        (long)color
    );

    /* Bluetoothポート(2)へ送信 */
    serial_wri_dat(2, buffer, len);
}

void main_task(intptr_t exinf)
{

    /* インスタンス生成 */
    Motor leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true);
    Motor rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);
    ForceSensor forceSensor(EPort::PORT_D);
    ColorSensor colorSensor(EPort::PORT_E);
    Clock clock;

    PIDController pidController;
    LineTracer lineTracer(leftWheel, rightWheel, colorSensor, pidController);
    DistanceCalculator distanceCalculator(leftWheel, rightWheel);

    /* Bluetooth初期化＆接続待ち */
    //init_bluetooth();

    /* 初期化 */
    int currentSection = 0;
    bool measuring = false;

    lineTracer.setBaseSpeed(
        sections[0].speed);

    pidController.setGain(
        sections[0].kp,
        sections[0].ki,
        sections[0].kd);

    while (!forceSensor.isTouched()); 
    while (true)
    {
        //テスト用
        if (forceSensor.isTouched())
        {
            // ボタンを離すまで待つ（チャタリング防止）
            while (forceSensor.isTouched())
            {
                tslp_tsk(10000);
            }

            if (!measuring)
            {
                // 1回目：計測開始
                distanceCalculator.reset();
                measuring = true;
            }
            else
            {
                leftWheel.stop();
                rightWheel.stop();
                break;
            }
        }

        if (measuring){
            //区間指定走行用
            int distance = distanceCalculator.getDistance();

            if (currentSection < 7 && distance >= sections[currentSection].distance) {

                currentSection++;

                lineTracer.setBaseSpeed(
                    sections[currentSection].speed);

                pidController.setGain(
                    sections[currentSection].kp,
                    sections[currentSection].ki,
                    sections[currentSection].kd);
            }

            /* Bluetoothへ送信 */
            //send_distance(distanceCalculator.getDistance());
            //send_color(colorSensor.getReflection());

            lineTracer.run();

            //HSV取得
            ColorSensor::HSV hsv;
            colorSensor.getHSV(hsv);
            if (hsv.h >= 200 && hsv.h <= 260 &&     //青検知範囲
                hsv.s >= 50 &&
                hsv.v >= 20)
            {
                leftWheel.stop();
                rightWheel.stop();
                break;
            }
        }
    }
    ext_tsk(); 
}
