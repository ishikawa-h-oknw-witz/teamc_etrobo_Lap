#ifndef DIRECTION_CONTROLLER_H
#define DIRECTION_CONTROLLER_H

#include "DistanceCalculator.h"
#include "IMU.h"
#include "Motor.h"

using namespace spikeapi;

class DirectionController
{
public:

    DirectionController(
        DistanceCalculator& distanceCalculator,
        IMU& imu,
        Motor& leftMotor,
        Motor& rightMotor);

    void move(int distance);

    void turn(int angle);

private:

    DistanceCalculator& mDistanceCalculator;

    IMU& mIMU;

    Motor& mLeftMotor;

    Motor& mRightMotor;
};

#endif