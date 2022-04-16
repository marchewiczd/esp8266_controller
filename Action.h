#pragma once

#include <Arduino.h>
#include <CommandDescriptions.h>
#include <ActionType.h>
#include <vector>


class Action {
public:
	static void Perform(ActionType type, std::vector<int> parameters = {});

private:
	static void RestartEsp();
	static void PrintHelp();
};
