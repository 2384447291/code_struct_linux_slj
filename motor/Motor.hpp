#ifndef MOTOR_HPP
#define MOTOR_HPP

class Motorfeedback;
class Motor 
{
public:
    Motor():controlMode{RELAX_MODE}
    {}

    enum MotorControlModeType
    {
        RELAX_MODE,
        SPD_MODE,
        POS_MODE,   
        TORQUE_MODE,     
    };

    MotorControlModeType controlMode;
    MotorFeedback* pFeedback;
    float speedSet;
    float positionSet;
    float torqueSet;

    bool isMotorOline;
};

class MotorFeedback
{
public:
    bool hasSpeedFdb;
    float speedFdb;
    float lastSpeedFdb;

    bool hasPositionFdb;
    float positionFdb;
    float lastPositionFdb;

    bool hasAccelerationFdb;
    float accelerationFdb;
    float lastAccelerationFdb;

    bool hasTemperatureFdb;
    float temperatureFdb;

    bool hasTorqueFdb;
    float torqueFdb;
    float lastTorqueFdb;

    MotorFeedback():
        hasSpeedFdb(false),
        speedFdb(0.0f),
        lastSpeedFdb(0.0f),

        hasPositionFdb(false),
        positionFdb(0.0f),
        lastPositionFdb(0.0f),

        hasAccelerationFdb(false),
        accelerationFdb(0.0f),
        lastAccelerationFdb(0.0f),

        hasTemperatureFdb(false),
        temperatureFdb(0.0f),

        hasTorqueFdb(false),
        torqueFdb(0.0f),
        lastTorqueFdb(0.0f)
    {
    }
};

#endif
