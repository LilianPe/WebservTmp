#include "Socket/WebservSocket.hpp"
#include "Config/Data/Data.hpp"

#define PORT 4580

int main() {
	// parser index dans server, faire en sorte que les key non valides soient rejetees;
	try {
		// Dans toutes les initialisations, verifier la taille des values pour pas qu'elles contiennent trop ou pas asser d'arguments
		Data d("webservConfig.conf");
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
    // try
    // {
    //     WebservSocket server(PORT);
    //     server.setupSocket();
    //     server.setupPoll();
    //     server.run();
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    return 0;
}
