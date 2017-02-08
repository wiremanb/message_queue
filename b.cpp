#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>
#include "shared_info.h"

int main(int argc, char *argv[])
{  
    int  i=0, id=0;
    char userInput[256];
    bool quit = false;
    struct info msg;

    if(argc < 3)
    {
    	std::cout << "[!] -> expected use: ./b <key> <type>" << std::endl;
    	return 1;
    }

    if ((id = msgget((key_t) atoi(argv[1]), IPC_CREAT | 0666  )) < 0 )
    	return 1;
    
    while(!quit)
    {
		if(msgrcv(id, &msg, 256, atoi(argv[2]), IPC_NOWAIT) > 0)
		{
			if(strcmp(msg._txt, "exit")==0)
			{
				quit = true;
				std::cout << "[!] -> Recieved kill from A." << std::endl;
			}
			else 
			{
				std::cout << "Received -> _type: " << msg._type << ", _txt: " << msg._txt << std::endl;
				std::cout << "Message: " << std::flush;
				std::cin.getline(userInput, sizeof(userInput));
				memcpy(&msg._txt[0], userInput, sizeof(userInput));
				if(msgsnd(id, &msg, strlen(msg._txt) + 1, 0 ) < 0)
					return 1;
			}
		}
	}
	msgctl(id, IPC_RMID, 0);
    return 0;
}
