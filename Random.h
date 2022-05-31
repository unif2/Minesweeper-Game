#pragma once
#include <random>
class Random
{
	// If x is static, then there is only one instance of the x variable, all instances SHARE this variable.  Access using Random::x
	// Static variables/functions exist for the lifetime of your program
	// Non-static variables require an instance of the class to be made so it can be associated with that instance
	// If you assign x to another variable, val2, then val2 will have that same value x
	// If you x to something else, then val2 will still have the same value as it had before
	// since it's just basic assignment and val2 isn't a pointer.
	static std::mt19937 random;
public:
	// One and only one of this function
	// Static function. We cannot access a non-static variable inside static functions.
	// "this" doesn't exist in static functions
	// Inside a static function, we can only access static variables.
	// Non-static functions can access non-static variables and static variables.
	static int Int(int min, int max);
	static float Float(float min, float max);
};

