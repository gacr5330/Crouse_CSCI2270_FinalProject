#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Conversations
{
	private:


	string description;

	// A vector of choices outputted.
	vector<string> choices;

	public:

	int startConversation()
	{
		cout << description << endl;

		// Output and number the choices
		for(int i = 0; i < this->choices.size(); ++i)
		{
			cout << i+1 << ": " << this->choices[i] << endl;
		}

		int input = -1;

		// read input from cin until a valid option is given
		while(true)
		{
			cin >> input;

			if(input >= 0 && input <= choices.size())
			{
				return input;
			}
		}

		return 0;
	}

	Conversations(string description, vector<string> choices)
	{
		this->description = description;
		this->choices = choices;
	}

	Conversations()
	{
	}
};

#endif /* DIALOGUE_HPP */
