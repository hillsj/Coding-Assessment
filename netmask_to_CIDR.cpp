// Name: Justin Hills
// Charter Communications: Programming Assessment
// 1. Dotted Quad Netmask to CIDR Bits

// NOTE TO HIRING STAFF: I chose this problem of the four on the assessment because I was inadequate
//                       with the networking questions that were asked during the technical phone
//                       interview, regarding IP Addresses and bits. Before starting this assignment
//                       I brushed up on these areas to better understand IP Addresses, subnet masks,
//                       and how to calculate CIDR bits.


#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


/*--------------------------------------------------------------------------------/
/                          FUNCTION: NETMASK_TO_BITS()                            /
/ This function accepts a string and validates that the string accurately         /
/ represents a dotted quad netmask. If the string does not follow the correct     /
/ format of a dotted quad netmask, the function returns an int of -1. Otherwise,  /
/ it converts the netmask to CIDR bits as an int and returns that int.            /
/--------------------------------------------------------------------------------*/

int netmask_to_bits(char *netmask)
{
	// Variables
	int num, cidr = 0;
	int dots = 0;
	int spaces = 0;
	int num1, num2, num3, num4 = 0;
	int bits;
	string octet1, octet2, octet3, octet4 = "";
	string subnet = "";
	char *octet = NULL;
	char *next_token = NULL;
	const char *delim = ".";


	// Check that netmask doesn't exceed maximum possible number of characters
	if (sizeof(netmask) > 15)
	{
		return -1;
	}

	// Check that netmask begins with a number
	if (netmask[0] < '0' || netmask[0] > '9')
	{
		return -1;
	}

	// Check that netmask only contains numbers and exactly three dots
	for (int i = 0; netmask[i] != '\0'; i++)
	{
		if (netmask[i] < '0' || netmask[i] > '9')
		{
			if (netmask[i] != '.')
				return -1;
			else
				// Check if dots are consecutive
				if (netmask[i + 1] < '0' || netmask[i + 1] > '9')
					return -1;
				else
					dots += 1;
		}
	}

	if (dots != 3)
		return -1;
	

	// Begin parsing netmask for first octet
	octet = strtok_s(netmask, delim, &next_token);

	num = stoi(octet);
	if (num < 128 || num > 255)
		return -1;

	// String to hold netmask with octets separated by spaces
	subnet = octet;


	// Finish parsing netmask for remaining octets, cast the strings to ints,
	// and verify that each octet is a number no larger than 255
	for (int j = (sizeof(netmask) - subnet.length()); j != sizeof(netmask); j++)
	{
		octet = strtok_s(NULL, delim, &next_token);

		num = stoi(octet);

		if (num < 0 || num > 255)
			return -1;

		subnet = subnet + " " + octet;
	}


	// Store each octet in a separate string
	for (size_t k = 0; k < subnet.length(); k++)
	{
		if (subnet[k] == ' ')
			spaces += 1;

		while (spaces == 0)
		{
			octet1 += subnet[k];
			break;
		}
		
		while (spaces == 1)
		{
			octet2 += subnet[k];
			break;
		}

		while (spaces == 2)
		{
			octet3 += subnet[k];
			break;
		}

		while (spaces == 3)
		{
			octet4 += subnet[k];
			break;
		}
	}

	// Convert each octet to an int
	num1 = stoi(octet1);
	num2 = stoi(octet2);
	num3 = stoi(octet3);
	num4 = stoi(octet4);

	// Validate netmask
	if ((num1 < num2 || num2 < num3 || num3 < num4) || (num1 < 255 && num2 > 0) || (num2 < 255 && num3 > 0) || (num3 < 255 && num4 > 0))
		return -1;

	// Calculate CIDR bits from each octet number
	bits = 128;

	// First Octet
	while (num1 > 0)
	{
		if ((num1 - bits) > 0)
		{
			cidr += 1;
			num1 -= bits;
		}

		if (num1 == bits)
		{
			cidr += 1;
			num1 = 0;
			bits = 0;
			break;
		}

		bits = bits / 2;
	}

	bits = 128;

	// Second Octet
	while (num2 > 0)
	{
		if ((num2 - bits) > 0)
		{
			cidr += 1;
			num2 -= bits;
		}

		if (num2 == bits)
		{
			cidr += 1;
			num2 = 0;
			bits = 0;
			break;
		}

		bits = bits / 2;
	}

	bits = 128;

	// Third Octet
	while (num3 > 0)
	{
		if ((num3 - bits) > 0)
		{
			cidr += 1;
			num3 -= bits;
		}

		if (num3 == bits)
		{
			cidr += 1;
			num3 = 0;
			bits = 0;
			break;
		}

		bits = bits / 2;
	}

	bits = 128;

	// Fourth Octet
	while (num4 > 0)
	{
		if ((num4 - bits) > 0)
		{
			cidr += 1;
			num4 -= bits;
		}

		if (num4 == bits)
		{
			cidr += 1;
			num4 = 0;
			bits = 0;
			break;
		}

		bits = bits / 2;
	}


	return cidr;
}


int main()
{
	// Test input

	char subnet1[] = "255.255.252.0";
	char subnet2[] = "255.1.2.3";
	char subnet3[] = "252.0.0.0";
	char subnet4[] = "255.148.0.0";
	char subnet5[] = "45.0.0.0";
	char subnet6[] = "Hello, World!";
	char subnet7[] = "";
	char subnet8[] = "255.255.255.168";
	cout << "Subnet Mask 1  |  CIDR: " << netmask_to_bits(subnet1) << endl;
	cout << "Subnet Mask 2  |  CIDR: " << netmask_to_bits(subnet2) << endl;
	cout << "Subnet Mask 3  |  CIDR: " << netmask_to_bits(subnet3) << endl;
	cout << "Subnet Mask 4  |  CIDR: " << netmask_to_bits(subnet4) << endl;
	cout << "Subnet Mask 5  |  CIDR: " << netmask_to_bits(subnet5) << endl;
	cout << "Subnet Mask 6  |  CIDR: " << netmask_to_bits(subnet6) << endl;
	cout << "Subnet Mask 7  |  CIDR: " << netmask_to_bits(subnet7) << endl;
	cout << "Subnet Mask 8  |  CIDR: " << netmask_to_bits(subnet8) << endl;

	return 0;
}

