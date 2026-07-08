#include "DirectionController.h"

DirectionController::DirectionController(
    DistanceCalculator& distanceCalculator,
    IMU& imu,
    Motor& leftMotor,
    Motor& rightMotor)
    : mDistanceCalculator(distanceCalculator),
      mIMU(imu),
      mLeftMotor(leftMotor),
      mRightMotor(rightMotor)
{
}

void DirectionController::move(int distance)
{
    // 距離計測開始

    // 基準角度を記録(リセットしたところを基準の角度とする？)

    // 指定距離到達まで繰り返す

        // 現在角度取得

        // 左右モータ補正

        // 前進

    // 停止
}

void DirectionController::turn(int angle)
{
    // 現在角度取得

    // 目標角度計算

    // 目標角度到達まで旋回

    // 停止
}