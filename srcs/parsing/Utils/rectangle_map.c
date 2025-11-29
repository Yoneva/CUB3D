#include "../../../includes/parsing.h"


void	counting(char **map, int *rows, int *max_len)
{
	int	len;

	while (map[*rows])
	{
		len = ft_strlen(map[*rows]);
		if (len > *max_len)
			*max_len = len;
		(*rows)++;
	}
}

char	**normalize_map(char **map, int max_len, int rows)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	j = 0;
	new_map = malloc((rows + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	while (i < rows)
	{
		int len = ft_strlen(map[i]);
		new_map[i] = malloc(max_len + 1);
		if (!new_map[i])
		{
			for (int k = 0; k < i; k++)
				free(new_map[k]);
			return (free(new_map), NULL);
		}
		ft_strlcpy(new_map[i], map[i], max_len + 1);
		j = len;
		while (j < max_len)
		{
			new_map[i][j] = ' ';
			j++;
		}
		new_map[i][max_len] = '\0';
		i++;
	}
	new_map[rows] = 0;
	return (new_map);
}

// int main()
// {
// 	char *map[] = {
//     "1111111111111111110111111",
//     "1000000000110000000000001",
//     "1011000001110000000000001",
//     "1001000000000000000000001",
//     "111111111011000001110000000000001",
//     "100000000011000001110111111111111",
//     "11110111111111011100000010001",
//     "11110111111111011101010010001",
//     "11000000110101011100000010001",
//     "10000000000000001100000010001",
//     "10000000000000001101010010001",
//     "11000001110101011111011110N0111",
//     "11110111 1110101 101111010001",
//     "11111111 1111111 111111111111",
//     NULL
// };

// char **square_map = normalize_map(map, 0, 0);

// // print to verify
// for (int i = 0; square_map[i]; i++)
//     printf("%s\n", square_map[i]);

// }
