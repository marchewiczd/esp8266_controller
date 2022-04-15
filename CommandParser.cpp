#include "CommandParser.h"


bool CommandParser::parse(String command, std::vector<CmdDetails> cmdDetailsList, CmdDetails& outputDetails)
{
    std::vector<String> splitCommand = split(command);

    if (splitCommand.size() == 0)
        return false;

    if (findFirstMatch(cmdDetailsList, splitCommand, outputDetails))
        return true;

    return false;
}

bool CommandParser::findFirstMatch(std::vector<CmdDetails> commandDetails, std::vector<String> splitCommand, CmdDetails& outputDetails)
{
    std::vector<int> parameters;

    for (int i = 0; i < commandDetails.size(); i++) {
        if (commandDetails[i].commandWords.size() + commandDetails[i].parameterCount == splitCommand.size()) {
            if (tryMatchCurrentDetails(commandDetails[i], splitCommand, commandDetails[i].parameters)) {
                outputDetails = commandDetails[i];
                return true;
            }
        }
    }

    return false;
}

bool CommandParser::tryMatchCurrentDetails(CmdDetails& commandDetails, std::vector<String> splitCommand, std::vector<int>& parameters)
{
    int cmdCount = commandDetails.commandWords.size();

    for (int j = 0; j < cmdCount; j++) {
        if (commandDetails.commandWords[j] != splitCommand[j]) {
            return false;
        }
    }

    for (int j = cmdCount; j < cmdCount + commandDetails.parameterCount; j++) {
        try {
            int param = std::stoi(splitCommand[j].c_str());
            parameters.push_back(param);
        }
        catch (std::invalid_argument const& ex) {
            parameters.erase(parameters.begin(), parameters.end());
            return false;
        }
    }

    return true;
}

std::vector<String> CommandParser::split(String command)
{
    std::vector<String> commandWords(1);
    int currentListPosition = 0;

    for (int i = 0; i < command.length(); i++) {

        if (command[i] == ' ') {
            currentListPosition++;
            commandWords.push_back("");
        }
        else
            commandWords[currentListPosition] += command[i];
    }

    return commandWords;
}

CmdDetails::CmdDetails()
{
}

CmdDetails::CmdDetails(CmdType type, std::vector<String> commandWords, int parameterCount)
{
    this->type = type;
    this->commandWords = commandWords;
    this->parameterCount = parameterCount;
    this->parameters = parameters;
}
