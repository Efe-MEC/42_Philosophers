#include "philo.h"

static int	ft_is_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_philo_count(char *philo_number)
{
	if (philo_number[0] == '0')
	{
		printf("Error: Philosopher count can not be 0\n");
		return (0);
	}
	return (1);
}

static int	ft_check_arg_count(int argc)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i <= (argc - 1))
	{
		if (!ft_is_digit(argv[i]))
		{
			printf("Error: Argument is not a number\n");
			return (0);
		}
		i++;
	}
	if (!ft_check_arg_count(argc) || !ft_check_philo_count(argv[1]))
		return (0);
	return (1);
}

void	ft_exit(t_sim **sim)
{
	int	i;

	if (!sim || !(*sim))
		return ;
	if ((*sim)->philos)
		free((*sim)->philos);
	if ((*sim)->forks)
	{
		i = 0;
		while (i < (*sim)->arg.philo_count)
			pthread_mutex_destroy(&(*sim)->forks[i++]);
		free((*sim)->forks);
	}
	if ((*sim)->threads)
	{
		free((*sim)->threads);
	}
	free(*sim);
	*sim = NULL;
}

int	ft_exiterr(char *msg, int err, t_sim **sim)
{
	ft_exit(sim);
	printf("%s\n", msg);
	return (err);
}


static void	ft_init_args(t_sim *sim, int argc, char **argv)
{
	sim->arg.philo_count = ft_atoi(argv[1]);
	sim->arg.time_to_die = ft_atoi(argv[2]);
	sim->arg.time_to_eat = ft_atoi(argv[3]);
	sim->arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->arg.req_eat_count = ft_atoi(argv[5]);
	else
		sim->arg.req_eat_count = -1;
}

static int	ft_init_forks(t_sim *sim)
{
	int				i;
	pthread_mutex_t	*mutexes;

	mutexes = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * sim->arg.philo_count);
	if (!mutexes)
		return (0);
	i = 0;
	while (i < sim->arg.philo_count)
	{
		pthread_mutex_init(mutexes + i, NULL);
		i++;
	}
	sim->forks = mutexes;
	return (1);
}

static void	ft_init_philo(t_sim *sim, pthread_t *thds, int32_t i)
{
	sim->philos[i].id = i + 1;
	sim->philos[i].right = &sim->forks[i];
	sim->philos[i].left = NULL;
	sim->philos[i].th = thds[i];
	sim->philos[i].arg = sim->arg;
	sim->philos[i].sim = sim;
	sim->philos[i].is_first_loop = 1;
	sim->philos[i].last_eating_time = 0;
	sim->philos[i].eaten = 0;
}

static int	ft_init_philos(t_sim *sim)
{
	pthread_t	*thds;
	int32_t		i;

	sim->philos = (t_philo *)malloc(sizeof(t_philo) * sim->arg.philo_count);
	if (!sim->philos)
		return (0);
	thds = (pthread_t *)malloc(sizeof(pthread_t) * sim->arg.philo_count);
	if (!thds)
		return (free(sim->philos), 0);
	sim->threads = thds;
	i = 0;
	while (i < sim->arg.philo_count)
	{
		ft_init_philo(sim, thds, i);
		if (sim->arg.philo_count == 1)
			break ;
		if (i == 0)
			sim->philos[i].left = &sim->forks[sim->arg.philo_count - 1];
		else
			sim->philos[i].left = &sim->forks[i - 1];
		i++;
	}
	return (1);
}

int	ft_init(t_sim **sim, int argc, char **argv)
{
	*sim = (t_sim *)malloc(sizeof(t_sim));
	if (!*sim)
		return (ft_exiterr("Error: Malloc failed\n", 1, NULL));
	ft_init_args(*sim, argc, argv);
	if (!ft_init_forks(*sim))
		return (ft_exiterr("Error: Malloc failed\n", 2, sim));
	if (!ft_init_philos(*sim))
		return (ft_exiterr("Error: Malloc failed\n", 3, sim));
	pthread_mutex_init(&(*sim)->print_mutex, NULL);
	(*sim)->first_philo_count = (*sim)->arg.philo_count;
	pthread_mutex_init(&(*sim)->first_philos_mutex, NULL);
	pthread_mutex_init(&(*sim)->life_mutex, NULL);
	pthread_mutex_init(&(*sim)->eaten_philo_mutex, NULL);
	(*sim)->life_ended = 0;
	(*sim)->eaten_philo_count = 0;
	(*sim)->is_odd_philos = (*sim)->arg.philo_count % 2;
	return (1);
}

void	ft_minus_first_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->first_philos_mutex);
	if (philo->sim->first_philo_count > 0)
		philo->sim->first_philo_count--;
	pthread_mutex_unlock(&philo->sim->first_philos_mutex);
}

bool	ft_is_finish_first(t_philo *philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->sim->first_philos_mutex);
	if (philo->sim->first_philo_count == 0)
		ret = true;
	pthread_mutex_unlock(&philo->sim->first_philos_mutex);
	return (ret);
}

static int	ft_monitor(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->eaten_philo_mutex);
	if (philo->sim->eaten_philo_count >= philo->sim->arg.philo_count)
		return (0);
	pthread_mutex_unlock(&philo->sim->eaten_philo_mutex);
	pthread_mutex_lock(&philo->sim->print_mutex);
	pthread_mutex_lock(&philo->sim->life_mutex);
	if (ft_get_time(&philo->sim) - philo->last_eating_time
		>= (uint64_t) philo->arg.time_to_die)
	{
		printf("%lu %d %s\n", ft_get_time(&philo->sim), philo->id,
			ft_get_status(DIED));
		return (0);
	}
	pthread_mutex_unlock(&philo->sim->print_mutex);
	pthread_mutex_unlock(&philo->sim->life_mutex);
	return (1);
}

static void	*ft_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_think_one_odd(philo);
	while (1)
	{
		if (philo->is_first_loop)
		{
			if (philo->id % 2 == 1)
			{
				if (ft_eat(philo))
					return (NULL);
			}
			else
			{
				if (ft_think(philo))
					return (NULL);
			}
			philo->is_first_loop = 0;
		}
		if (ft_is_finish_first(philo))
			if (ft_eat(philo))
				return (NULL);
	}
	return (NULL);
}

static void	ft_start(t_sim **sim)
{
	int	i;

	i = 0;
	(*sim)->start_time = ft_get_time(sim);
	while (i < (*sim)->arg.philo_count)
	{
		pthread_create(&(*sim)->philos[i].th, NULL,
			ft_loop, &(*sim)->philos[i]);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < (*sim)->arg.philo_count)
		{
			if (ft_monitor(&(*sim)->philos[i]) != 1)
			{
				ft_exit(sim);
				return ;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	if (!ft_check_args(argc, argv))
		return (0);
	if (!ft_init(&sim, argc, argv))
		return (0);
	ft_start(&sim);
}

void	ft_think_one_odd(t_philo *philo)
{
	pthread_detach(philo->th);
	if (philo->sim->is_odd_philos && philo->id == 1)
	{
		ft_think(philo);
		philo->is_first_loop = 0;
	}
}

bool	ft_think(t_philo *philo)
{
	if (philo->is_first_loop)
		ft_minus_first_philo(philo);
	return (ft_print_status(philo, THINKING));
}

bool	ft_sleep_think(t_philo *philo)
{
	if (ft_print_status(philo, SLEEPING))
		return (true);
	ft_usleep(&philo->sim, philo->arg.time_to_sleep);
	return (ft_think(philo));
}

static void	ft_life_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->life_mutex);
	philo->last_eating_time = ft_get_time(&philo->sim);
	philo->eaten++;
	pthread_mutex_lock(&philo->sim->eaten_philo_mutex);
	if (philo->eaten == philo->arg.req_eat_count)
		philo->sim->eaten_philo_count++;
	pthread_mutex_unlock(&philo->sim->eaten_philo_mutex);
	pthread_mutex_unlock(&philo->sim->life_mutex);
}

bool	ft_eat(t_philo *philo)
{
	if (philo->right == NULL || philo->left == NULL)
		return (true);
	if (philo->eaten == philo->arg.req_eat_count)
		return (true);
	pthread_mutex_lock(philo->right);
	if (ft_print_status(philo, TAKING_FORK))
		return (pthread_mutex_unlock(philo->right), true);
	pthread_mutex_lock(philo->left);
	if (ft_print_status(philo, TAKING_FORK))
		return (pthread_mutex_unlock(philo->right),
			pthread_mutex_unlock(philo->left), true);
	if (philo->is_first_loop)
		ft_minus_first_philo(philo);
	if (ft_print_status(philo, EATING))
		return (pthread_mutex_unlock(philo->right),
			pthread_mutex_unlock(philo->left), true);
	ft_life_eating(philo);
	ft_usleep(&philo->sim, philo->arg.time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (ft_sleep_think(philo));
}

char	*ft_get_status(t_status status)
{
	if (status == EATING)
		return ("is eating");
	else if (status == SLEEPING)
		return ("is sleeping");
	else if (status == THINKING)
		return ("is thinking");
	else if (status == DIED)
		return ("died");
	else if (status == TAKING_FORK)
		return ("has taken a fork");
	else
		return (NULL);
}

bool	ft_print_status(t_philo *philo, t_status status)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->sim->print_mutex);
	printf("%lu %d %s\n", ft_get_time(&philo->sim), philo->id,
		ft_get_status(status));
	if (philo->eaten == philo->arg.req_eat_count)
		ret = true;
	pthread_mutex_unlock(&philo->sim->print_mutex);
	return (ret);
}


int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	uint64_t	nb;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

uint64_t	ft_get_time(t_sim **sim)
{
	int	time;

	gettimeofday(&(*sim)->tv, NULL);
	time = ((*sim)->tv.tv_sec * 1000) + ((*sim)->tv.tv_usec / 1000)
		- (*sim)->start_time;
	return (time);
}

void	ft_usleep(t_sim **sim, uint64_t time)
{
	uint64_t		last;
	struct timespec	req;

	last = ft_get_time(sim) + time;
	while (ft_get_time(sim) < last)
	{
		req.tv_sec = 0;
		req.tv_nsec = 100000;
		nanosleep(&req, NULL);
	}
}
