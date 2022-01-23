
#include "../Logger/StaticLogger.h"

int main()
{
	StaticLogger::instance.trace("Test");
	return 0;
}