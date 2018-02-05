#include <stdio.h>

int input_deal(char *order)
{ 
    char ch;
    int i = 0;

    while((ch = getchar()) != '\n')
    {
        if(ch == ' ')
	{
	    continue;
	}
	else
	{
	    order[i] = ch;

	    i++;
	}
    }

    order[i] = '\0';

    return 0;
}
