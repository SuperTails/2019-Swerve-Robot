#include "SwerveModule.h"
#include <frc/smartdashboard/SmartDashboard.h>

SwerveModule::SwerveModule(int driveMotorId, int pivotMotorId, int pivotSensorId, double zeroAngle) :
    m_driveMotor(driveMotorId, rev::CANSparkMax::MotorType::kBrushless),
    m_pivotMotor(pivotMotorId),
    m_pivotSensor(pivotSensorId),
    m_pivotController(1.6, 0.0, 0.0, &m_pivotSensor, &m_pivotMotor),
    m_zeroAngle(zeroAngle)
{
    m_pivotController.SetContinuous(true);
    m_pivotController.SetInputRange(0.0, 5.0);
    m_pivotController.SetOutputRange(-1.0, 1.0);
    m_pivotController.SetEnabled(true);

    m_pivotController.SetSetpoint(m_zeroAngle / 360.0 * 5.0);
}

void SwerveModule::Set(double speed, double angle) {
    angle += m_zeroAngle;

    angle -= std::floor(angle / 360.0) * 360.0;

    m_driveMotor.Set(speed);

    frc::SmartDashboard::PutNumber("Swerve Error " + std::to_string(m_driveMotor.GetDeviceId()), m_pivotController.GetError() / 5.0 * 360.0);

    m_pivotController.SetSetpoint(angle / 360.0 * 5.0);
}

double SwerveModule::getAngle() const {
    return m_pivotSensor.GetVoltage() * 360.0 / 5.0;
}