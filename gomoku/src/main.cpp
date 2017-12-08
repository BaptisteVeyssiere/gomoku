#include "Brain.h"

int	main(void) {
	Brain	brain;

	try {
		if (!brain.tun())
			return (1);
	}
	catch (std::exception const & e) {
		std::cerr << "Unknown exception: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}