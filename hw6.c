/*
* Author: Kenneth Murry
* CptS260 Palindrome
*
* 1) This program will read in a file to a string line by line.
* 2) As the file is being read it will check to make sure the line
*    that is being read does not contain (Uppercase letters, or special characters).
*		i. If the string has one of the above restrictions it will move to the next line in the file.
* 3) If the string does not contain one of the retrictions it will reverse the string
*	 then compare the original string to the reversed string to see if it meets the Palindrome Rule.
* 4) If the strings comparison are the same
*		i.   Print to the screen the a message stating Palindrome was found.
*		ii.  Print the original string to the screen
*		iii. Print the reversed string to the screen
*     
*/

#include <stdio.h>
#include <string.h>

void reversing(char buffer[], char reverse[], int stringLength);

int main(int argc, char const *argv[])
{
	int stringLength = 0;
	int i = 0;
	FILE *fp; 			//Declaring a FILE type pointer calling it fp
	char buffer[64]; 	//Declaring a char array the size of 64 named buffer
	int good = 1;

	fp = fopen("./american-english", "r"); //"./american-english" "./test.txt"

//If the file did not open or does not exist end program
	if (fp == NULL) 
	{
		printf("File did not open\n");
		return 0;	
	}
	else
	{
		while(fgets(buffer, 64, (FILE*)fp) != NULL)
		{
			stringLength = strlen(buffer); //Storing the length of read input
			
			//Checking if ascii value is >=97(a) & <=122(z) or ==10(\n)
			for(i = 0; i < stringLength; i++)
			{
				if((int)buffer[i] >= 97 && (int)buffer[i] <= 122 || (int)buffer[i] == 10)
				{
					good = 1; //If we are in range then good is true				
				}
				else
				{
					good = 0;//If we are not in range then good is false
					break;
				}
			}

			//If line read in passes restriction 
			if(good == 1)
			{
				//Create a new array to store the reverse of the original string	
				char reverse[stringLength + 1];
				reversing(buffer, reverse, stringLength);

				//Loop through the arrays to check for Palindrome Rule
				for (i = 0; i < stringLength; ++i)
				{
					if(buffer[i] == reverse[i] || buffer[i] == '\n' && reverse[i] == '\0')
					{
						good = 1; //If good is 1(true) elements are the same
					}
					else
					{
						good = 0; //If good is 0(false) elements are not the same
						break;
					}
				}

				//If the two strings are the same we have found a Palindrome
				if(good == 1)
				{
					printf("\nPalindrome found!\n");
					printf("Normal String:   %s", buffer); //Print content in buffer(original array)
					printf("Reversed String: %s\n", reverse);//Print content in reverse(Reverse array)

				}
			}
			else if(good == 0)
			{
				//If they are not the same move to the next line of the file
				//DO NOTHING!!
			}
		}

		printf("\nEND OF FILE Reached!\n");
	}
	fclose(fp);
	return 0;
}

//This function will take two arrays and a string length to reverse the first string(buffer)
//and store it in the second array(reverse).
void reversing(char buffer[], char reverse[], int stringLength)
{
	int i = 0;
	int j = stringLength - 1;
	while(i < stringLength)
	{
		reverse[j] = buffer[i];
		i++;
		j--;
	}
	reverse[i] = '\0'; //Need to add the null terminater to the end of the string

	//Since fgets adds a newline(or carries the new line not sure which one) to the end of the string since we are reversing the string need
	//to remove the new line from the first element of the reverse string
	i = 0;
	if(reverse[0] == '\n')
	{
		while(i < stringLength)
		{
			reverse[i] = reverse[i + 1];
			i++;
		}
	}
}