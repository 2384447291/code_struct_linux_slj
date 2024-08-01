#ifndef IRISTAC_HPP
#define IRISTAC_HPP
#include "DisplacementStageController.hpp"
class IrisTac : public RobotRunner
{
    public:
        IrisTac():RobotRunner(this){}
        DisplacementStageController m_DisplacementStageController;
};

#endif