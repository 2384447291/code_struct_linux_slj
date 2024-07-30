#include "DisplacementStageController.hpp"
class IrisTac : public RobotRunner
{
    public:
        IrisTac():RobotRunner(this){}
        DisplacementStageController m_DisplacementStageController;
};