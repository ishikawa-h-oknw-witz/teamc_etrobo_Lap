#include "PIDController.h"
 
// コンストラクタ
PIDController::PIDController()
    : mKp(0.6),
      mKi(0.0),
      mKd(0.1),
      mIntegral(0),
      mPreviousError(0)
{
}

void PIDController::setGain(float kp, float ki, float kd)
{
    mKp = kp;
    mKi = ki;
    mKd = kd;
}

int PIDController::calculate(int error)
{
    // 積分項更新
    mIntegral += error;
 
    // 微分項計算
    int diff =
        error - mPreviousError;
 
    // PID計算
    int turn =
        mKp * error +
        mKi * mIntegral +
        mKd * diff;
 
    mPreviousError = error;

    return turn;
}