/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "RouterPipelineStep.hpp"

using namespace Lattice;

RouterPipelineStep::~RouterPipelineStep() {
    delete this->_nextStep;
}

void RouterPipelineStep::setNextStep(RouterPipelineStep *step) {
    delete this->_nextStep;
    this->_nextStep = step;
    if (step) {
        step->_prevStep = this;
    }
}

RouterPipelineStep *RouterPipelineStep::getNextStep() {
    return this->_nextStep;
}

RouterPipelineStep *RouterPipelineStep::getPrevStep() {
    return this->_prevStep;
}
