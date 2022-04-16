#include "CommandParser.h"


bool CommandParser::parse(String command, std::vector<CommandDetails> CommandDetailsList, CommandDetails& outputDetails)
{
    std::vector<String> splitCommand = Split(command);

    if (splitCommand.size() == 0)
        return false;

    if (FindFirstMatch(CommandDetailsList, splitCommand, outputDetails))
        return true;

    return false;
}

bool CommandParser::FindFirstMatch(std::vector<CommandDetails> commandDetails, std::vector<String> splitCommand, CommandDetails& outputDetails)
{
    std::vector<int> parameters;

    for (int i = 0; i < commandDetails.size(); i++)
        if (commandDetails[i].commandWords.size() + commandDetails[i].parameterCount == splitCommand.size())
            if (TryMatchCurrentDetails(commandDetails[i], splitCommand, commandDetails[i].parameters)) {
                outputDetails = commandDetails[i];
                return true;
            }

    return false;
}

bool CommandParser::TryMatchCurrentDetails(CommandDetails& commandDetails, std::vector<String> splitCommand, std::vector<int>& parameters)
{
    int cmdCount = commandDetails.commandWords.size();

    for (int j = 0; j < cmdCount; j++)
        if (commandDetails.commandWords[j] != splitCommand[j])
            return false;

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

std::vector<String> CommandParser::Split(String command)
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
