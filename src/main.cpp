#include <Engine.hpp>

int main(int ac, char **av)
{
	bool debug = false;
	bool multi = false;
	if (ac == 4)
	{
		if (av[1][0] == '-')
		{
			std::string str(av[1]);
			if (str.find('d') != std::string::npos)
			{
				debug = true;
				ac = 3;
			}
			if (str.find('m') != std::string::npos)
			{
				multi = true;
				ac = 3;
			}
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
		if (debug || multi)
			engine = new Engine(av[2], av[3], debug, multi);
		else
			engine = new Engine(av[1], av[2], debug, multi);
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
