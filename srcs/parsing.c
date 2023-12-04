#include "philo.h"

static bool	contains_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	integer_atoi(char *str)
{
	unsigned long long int	nb;
	int						i;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

bool	is_valid_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!contains_only_digits(av[i]))
			return (msg("%s invalid input: %s: " \
					"not a valid unsigned integer between 0 and 2147483647.\n",
					av[i], false));
		nb = integer_atoi(av[i]);
		if (i == 1 && (nb <= 0 || nb > 200))
			return (msg("%s invalid input: "\
					"there must be between 1 and %s philosophers.\n", "200",
					false));
		if (i != 1 && nb == -1)
			return (msg("%s invalid input: %s: " \
					"not a valid unsigned integer between 0 and 2147483647.\n",
					av[i], false));
		i++;
	}
	return (true);
}
