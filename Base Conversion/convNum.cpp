//CSC16 Assignment#1

#include <iostream>
#include <cmath>
using namespace std;

//Function returns Length of Number user has inputed
int count(int num)
{
	int total = 0;
	if (num < 0)
		total = 1;
	while(num)
	{
		num/=10;
		total++;		
	}
	return total;
}

//Function converts number into base 10
//Inputs are array of digits, # of digits, and base of number
int conv(int numarr[], int numofdigits, int numbase)
{
	int convResult = 0;
	numofdigits--;
	for(int i = numofdigits; i >= 0; i--)
	{
		if(i > 0)
		{
			convResult += (numarr[i] * pow(numbase,i));
		}
		else
		{
			convResult += numarr[i];
		}
	}
	return convResult;
}

int main()
{
	//Requesting the number to conver and the base of that number
	int number;
	int base;
	cout<<"Enter the Base of your Number"<<endl;
	cin>>base;
	cout<<"Enter the Number you want to convert"<<endl;
	cin>>number;

	//How many digits are in the number that the user entered
	int Digits = count(number);
	cout<<"Number of Digits in X: "<<Digits<<endl;

	//Start an array and input every digit into that array
	int lArray[Digits];
	for(int i = 0; i <= (Digits - 1); i++)
	{
		lArray[i]=number%10;
		number/=10;
	}

	//call the converter function and export the results
	int result = conv(lArray,Digits,base);
	cout<<"Conversation Result: "<<result<<endl;
}
