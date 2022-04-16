#include "CommandDetails.h"


CommandDetails::CommandDetails() { }

CommandDetails::CommandDetails(ActionType type, std::vector<String> commandWords, int parameterCount, String description)
{
    this->type = type;
    this->commandWords = commandWords;
    this->parameterCount = parameterCount;
    this->parameters = parameters;
    this->description = description;
}
