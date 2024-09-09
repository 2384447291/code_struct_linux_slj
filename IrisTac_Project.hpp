#ifndef IRISTAC_PROJECT_HPP
#define IRISTAC_PROJECT_HPP
#include "Ctr_DisplacementStageController.hpp"
#include "Ctr_IrisTacController.hpp"
class IrisTac_Project : public RobotRunner
{
    public:
        IrisTac_Project():RobotRunner(this){}
        DisplacementStageController m_DisplacementStageController;
        //IrisTacController m_IrisTacController;
};

#endif