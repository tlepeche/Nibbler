#include <Engine.hpp>

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	/*	Game	*game = new Game();
		game->init(); // will call lib->init;

	//test a la con pour verifier la liste des entites 
	for (std::vector<AEntity *>::iterator i = game->getEntities().begin(); i != game->getEntities().end() ; i++)
	{
	std::cout << "type : " << ((*i)->getType() == E_ENTITIES_TYPE::SNAKE ? "Snake" : "Food")
	<< " pos:{" << (*i)->getPos().first << ", " << (*i)->getPos().second << "}" << std::endl;
	}
	game->start();*/
	if (ac != 2)
		return (-1);
	try
	{
		Engine		engine(av[1]);

		engine.init();
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return 0;
}
