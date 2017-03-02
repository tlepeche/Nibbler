#include <Game.hpp>
#include <Snake.hpp>

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	Game	*game = new Game();
	game->init(); // will call lib->init;

	//test a la con pour verifier la liste des entites 
	for (std::vector<AEntity *>::iterator i = game->getEntities().begin(); i != game->getEntities().end() ; i++)
	{
		std::cout << "type : " << ((*i)->getType() == E_ENTITIES_TYPE::SNAKE ? "Snake" : "Food")
			<< " pos:{" << (*i)->getPos().first << ", " << (*i)->getPos().second << "}" << std::endl;
	}
	game->start();
	return 0;
}
