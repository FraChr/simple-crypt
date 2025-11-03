#include <getopt.h>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>


#include <unistd.h>

#include "ArgsHandler.h"


int main(const int argc, char *argv[]) {

    /*static option long_options[] = {
        {"arg", no_argument, 0, 'a'},
        {"barg", required_argument, 0, 'b'},
        {0,0,0,0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "ab:", long_options, &option_index))!= -1) {
        switch (opt) {
            case 'a':
                std::cout << "testing" << std::endl;
                break;
            case 'b':
                std::cout << "testing2" << std::endl;
        }
    }*/

    ArgsHandler argsHandler;
    argsHandler.Handle(argc, argv);

    /*const auto args = std::vector<std::string>(argv + 1, argv + argc);
    crypto app;
    app.run(args);*/
    return 0;
}
