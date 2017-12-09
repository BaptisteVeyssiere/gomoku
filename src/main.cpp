#include <iostream>
#include "Brain.h"

int	main(void) {
	Gomoku::Brain	brain;

	try {
		if (!brain.run())
			return (1);
	}
	catch (std::exception const & e) {
		std::cerr << "Unknown exception: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}