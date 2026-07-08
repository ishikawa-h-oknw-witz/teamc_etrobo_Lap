#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController
{
public:
    PIDController();
    
    void setGain(float kp, float ki, float kd);
    
    int calculate(int error);
 
private:
    float mKp;
    float mKi;
    float mKd;
 
    float mIntegral;
 
    int mPreviousError;
};
 
#endif