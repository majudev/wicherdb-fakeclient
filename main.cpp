#include <iostream>
#include <string>
#include <vector>
#include "Database.h"

unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch);

int main(int argc, char * argv[]){
	char buffer[1024];
	size_t pos = 0;
	bool running = true;
	while(running){
        	printf("> ");
        	while(pos < 1024){
			buffer[pos] = getchar();
			if(buffer[pos] == '\n') break;
			++pos;
		}
		buffer[pos] = '\0';
		std::string cmd_full(buffer);
		std::vector<std::string> cmd;
		int cmd_n = split(cmd_full, cmd, ' ');
		if(cmd_n == 1 && cmd[0] == "?"){
			printf("  List of available commands:\n"
			       "  ?\t\t\t- Help\n"
			       "  connect (host) (port)\t- connect to specified host\n"
			       "  login (login) (passwd)\t- login with (login):(password)\n"
			       "  bye\t\t\t- quit the program\n");
		}else if(cmd_n == 1 && cmd[0] == "bye"){
			printf("  Quitting...\n");
			break;
		}else if(cmd_n == 3 && cmd[0] == "connect"){
			bool res = Wicher::Database::getSingleton().conn(cmd[1], atoi(cmd[2].c_str()));
			if(!res) printf("  Error connecting to %s:%s\n", cmd[1].c_str(), cmd[2].c_str());
			else printf("  Success!\n");
		}else if(cmd_n == 3 && cmd[0] == "login"){
			bool res = Wicher::Database::getSingleton().login(cmd[1], cmd[2]);
			if(!res) printf("  Error logging in with credentials %s:%s\n", cmd[1].c_str(), cmd[2].c_str());
			else printf("  Success!\n");
		}else{
			printf("  Unknown command. Type ? for available ones.\n");
		}
		pos = 0;
	}
	/*Wicher::Database::getSingleton().conn("127.0.0.1", 63431);
	if(Wicher::Database::getSingleton().login("null", "null")){
		std::cout << "GUT." << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_types()) << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("M")) << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item("M", "")) << std::endl;
		//std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("M")) << std::endl;
		if(argc == 2){
            ///Creating
		    if(strcmp(argv[1], "-wz") == 0){ ///WZ
                std::vector<int> ids; ids.push_back(1); ids.push_back(1);
                std::vector<std::string> types; types.push_back("M"); types.push_back("K");
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_wz("01/01/01", "Pełesz", "", ids, types)) << std::endl;
		    }
		}else if(argc == 3){
            ///Dropping
            if(strcmp(argv[1], "-droptype") == 0){ ///Type
                if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_type("M")) << std::endl;
                }else if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_type("K")) << std::endl;
                }
		    }else if(strcmp(argv[1], "-dropwz") == 0){ ///WZ
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_wz(Wicher::Toolkit::strtoi(arg))) << std::endl;
            }else if(strcmp(argv[1], "-droppz") == 0){ ///PZ
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_pz(Wicher::Toolkit::strtoi(arg))) << std::endl;
            }else
            ///Creating
            if(strcmp(argv[1], "-item") == 0){ ///Item
                if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item("K", "Generated automatically.")) << std::endl;
                }else if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_item("M", "Generated automatically.")) << std::endl;
                }
            }else if(strcmp(argv[1], "-type") == 0){ ///Type
                if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_type("M", "Materace", "")) << std::endl;
                }else if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_type("K", "Kanadyjki", "")) << std::endl;
                }
		    }else if(strcmp(argv[1], "-pz") == 0){ ///PZ
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::register_pz(Wicher::Toolkit::strtoi(arg), "01/01/01", "Pełesh", "")) << std::endl;
		    }else
		    ///Getting
		    if(strcmp(argv[1], "-wzitems") == 0){
                std::string arg(argv[2]);
                std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_wz_items(Wicher::Toolkit::strtoi(arg))) << std::endl;
		    }
		}else if(argc == 4){
            ///Dropping
		    if(strcmp(argv[1], "-dropitem") == 0){ ///Item
                std::string arg(argv[3]);
                if(strcmp(argv[2], "m") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_item(Wicher::Toolkit::strtoi(arg), "M")) << std::endl;
                }else if(strcmp(argv[2], "k") == 0){
                    std::cout << Wicher::Database::getSingleton().run(Wicher::Database::Query::drop_item(Wicher::Toolkit::strtoi(arg), "K")) << std::endl;
                }
		    }
		}

		std::cout << "Types:\t\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_types()) << std::endl;
		std::cout << "\"M\" Items:\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("M")) << std::endl;
		std::cout << "\"K\" Items:\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_items("K")) << std::endl;
		std::cout << "WZs:\t\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_wzs()) << std::endl;
		std::cout << "PZs:\t\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_pzs()) << std::endl;
		std::cout << "History:\t" << Wicher::Database::getSingleton().run(Wicher::Database::Query::get_history()) << std::endl;
	}*/
	return 0;
}

unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch){
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos ) );

    return strs.size();
}