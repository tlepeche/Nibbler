#include <Engine.hpp>

int main(int ac, char **av)
{
	bool debug = false;
	if (ac == 4)
	{
		std::string str(av[1]);
		if (str.compare("-d") == 0)
		{
			debug = true;
			ac = 3;
		}
	}
	if (ac != 3)
	{
		std::cout << "Usage: ./Nibbler [width] [height]" << std::endl;
		return (-1);
	}
	try
	{
		Engine	*engine;
		if (debug)
			engine = new Engine(av[2], av[3], true);
		else
			engine = new Engine(av[1], av[2]);
		engine->init();
		delete engine;
	}
   	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return 0;
}
