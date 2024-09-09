#ifndef IRISTACCONTROLLER_HPP
#define IRISTACCONTROLLER_HPP

#include "RobotRunner.hpp"
#include "IrisTac.hpp"

class IrisTacController : public RobotController
{
    public:
        IrisTac m_IrisTac;
        IrisTacController():RobotController("IrisTacController"),
        m_IrisTac("IrisTac","/dev/ttyUSB0")
        {};

        void init() override{
        };
};
#endif