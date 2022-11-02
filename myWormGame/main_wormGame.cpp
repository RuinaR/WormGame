#include "wormGame.h"

int main(void)
{
	Init();
	while (TRUE)
	{
		Title();
		Game();
	}

	return 0;
}