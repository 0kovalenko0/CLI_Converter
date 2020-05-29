#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>

using namespace std;


struct Parameter {
	string title;
	bool isRequired = false;
};

struct Command {
	string title;
	vector<Parameter> parameters;
	void(*onComand)(map<string, string> parameters);
};

struct CommandExec {
	vector<Command> commands;

	int findParameter(int argc, char** argv, string parameter) {
		for (int i = 2; i < argc; i++) {
			if (parameter == argv[i]) {
				return i;
			}
		}

		return -1;
	}

	void exec(int argc, char** argv) {
		string currentCommand = argv[1]; 

		for (Command cmd : commands) {
			if (cmd.title == currentCommand) {
				map<string, string> parameters;
				
				for (Parameter param : cmd.parameters) {
					int idx = findParameter(argc, argv, param.title);

					if (idx == -1 && param.isRequired) {
						cerr << "Parameter " << param.title << " not found" << endl;
						return; 
					}
					if (idx != -1) {
						parameters.insert(pair<string, string>(param.title, argv[idx + 1])); 
					}
				}

				cmd.onComand(parameters);
			}
		}
	}
};

void convertAction(map<string, string> parameters) {
	
	setlocale(NULL, "Russian");

	double input;
	double result;
	input = atof(parameters.at("-v").c_str());

	if (parameters.at("-m") == "HoursToMiliseconds")
	{
		result = input * 3600000;
		cout << input << " hours = " << result << " milliseconds";
	}
	if (parameters.at("-m") == "HoursToSeconds")
	{
		result = input * 3600;
		cout << input << " hours = " << result << " seconds";
	}
	if (parameters.at("-m") == "SecondsToHours")
	{
		result = input / 3600;
		cout << input << " seconds = " << result << " hours";
	}
	if (parameters.at("-m") == "SecondsToMiliseconds")
	{
		result = input * 1000;
		cout << input << " seconds = " << result << " milliseconds";
	}
	if (parameters.at("-m") == "MilisecondsToHours")
	{
		result = input / 3600000;
		cout << input << " milliseconds = " << result << " hours";
	}
	if (parameters.at("-m") == "MilisecondsToSeconds")
	{
		result = input / 1000;
		cout << input << " milliseconds = " << result << " seconds";
	}
	if (parameters.at("-m") == "KmToSm")
	{
		result = input * 100000;
		cout << input << " kilometers = " << result << " centimeters";
	}
	if (parameters.at("-m") == "KmToMm")
	{
		result = input * 1000000;
		cout << input << " kilometers = " << result << " millimetres";
	}
	if (parameters.at("-m") == "SmToKm")
	{
		result = input / 100000;
		cout << input << " centimeters = " << result << " kilometers";
	}
	if (parameters.at("-m") == "SmToMm")
	{
		result = input * 10;
		cout << input << " centimeters = " << result << " millimetres";
	}
	if (parameters.at("-m") == "MmToKm")
	{
		result = input / 1000000;
		cout << input << " millimetres = " << result << " kilometers";
	}
	if (parameters.at("-m") == "MmToSm")
	{
		result = input / 10;
		cout << input << " millimetres = " << result << " centimeters";
	}

}

int main(int argc, char** argv) {


	Parameter valueParameter;
	valueParameter.title = "-v";
	valueParameter.isRequired = true;

	Parameter modeParameter;
	modeParameter.title = "-m";
	modeParameter.isRequired = true;


	Command convertCommand;
	convertCommand.title = "convert";
	convertCommand.parameters.push_back(valueParameter); 
	convertCommand.parameters.push_back(modeParameter);

	convertCommand.onComand = &convertAction;


	CommandExec exec;
	exec.commands.push_back(convertCommand);
	exec.exec(argc, argv);
	return 0;
}