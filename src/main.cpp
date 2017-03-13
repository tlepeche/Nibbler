#include <Engine.hpp>

int main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	try
	{
		Engine		engine(av[1]);
		engine.init();
	}
   	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return 0;
}
