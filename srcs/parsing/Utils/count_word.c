#include "../../../includes/parsing.h"


int	count_word(char *input)
{
	int	i;
	int	count;
	int	find;

	i = 0;
	count = 0;
	find = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\t' || input[i] == 32)
		{
			find = 0;
		}
		else if (input[i] != '\t' && input[i] != 32)
		{
			if( find == 0)
			{
				count++;
				find = 1;
			}
		} 
		i++;
	}
	return (count);
}
