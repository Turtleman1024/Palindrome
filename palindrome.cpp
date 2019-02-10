#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

bool palindrome(string user_input);
void entrance_message();
void exit_message();

int main(int argc, char const *argv[])
{
	string user_input = "";				//This attribute is used to store user input

	bool exit = false;					//This attribute is used to validate if the user wants to exit

	entrance_message();

	//While the users does not want to exit the program
	while(!exit)
	{
		//Prompt user for a palindrome
		cout << "\nEnter a palindrome: ";
		
		//Get the users input
		getline(cin, user_input);

		//Pass the users input to find if it is a palindrome
		exit = palindrome(user_input);
		
	}
	exit_message();
	return 0;
}

void exit_message()
{
	cout << "\nThank you for using Kenny's Palindrome program\n";
}
void entrance_message()
{
	cout << "Welcome to Kenny's Palindrome finding program\n";
	cout << "\nThis program will find word and number palindromes\n";
	cout << "\nEnter \"Exit\" an anytime to quit program\n";
}
/*
	This method will take the users input string and check whether the uses has entered a
	palidrome or if the user wants to exit.
*/ 
bool palindrome(string user_input)
{
		string user_wants_to_exit = "";						//This attribute is used to check if user wants to exit the program
		bool exit 			      = false;					//This attribute is used to store if the user has selected to exit the program
		bool pally_found 	      = false;					//This attribute is used to store whether or not a palindrome was found
		int  input_string_size    = user_input.size() - 1;	//This attribute is used to store the size of the users input string


		//Iterate through the users input string
		for(int index = 0; index < user_input.size(); index++)
		{
			/*
			//Debug cout that validates the funtion is working correcting by making sure that it is comparing the right elements 
			cout << user_input[index] << " : " << user_input[input_string_size] << endl;
			*/
			if(user_input[index] == user_input[input_string_size])
			{
				pally_found = true;
				input_string_size--;
			}
			else
			{
				pally_found = false;
				break;
			}

		}

		//If the attribute pally_found is true then a palindrome was found
		if(pally_found == true)
			cout << endl <<  "Found: " << user_input << " is a palindrome\n";
		
		//Check if the user wants to exit the program
		else
		{			
			user_wants_to_exit = user_input;
			//Convert the users input string to all upper case and check if it is EXIT
			for(int index = 0; index < user_wants_to_exit.size(); index++)
				user_wants_to_exit[index] = toupper(user_wants_to_exit[index]);

			if(user_wants_to_exit == "EXIT")
			{
				cout << "Palindrome program stopped\n";
				exit = true;
				return (exit = true);
				
			}
			//The user has not entered EXIT and a palindrom was not found
			cout << endl << user_input << " is not a palindrome\n";
			return (exit = false);
		}	
}