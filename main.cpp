#include <iostream>
#include "include/ImageManager.h"
#include "include/MyString.h"
#include <cstring>

int main()
{
    ImageManager manager;
    char command[100];

    std::cout << "--- Image Processing System ---" << std::endl;
    std::cout << "Available commands: load, add-filter, remove-filter, show-filters, show-all-filters, run, run-all, save, quit" << std::endl;

    while (true)
    {
        std::cout << "\n> ";
        if (!(std::cin >> command))
            break;

        String cmd(command);

        if (cmd == "load")
        {
            char path[256];
            std::cin >> path;
            manager.load(path);
        }
        else if (cmd == "add-filter")
        {
            char imgName[256], filterType[64];
            std::cin >> imgName >> filterType;
            manager.addFilter(imgName, filterType);
        }
        else if (cmd == "remove-filter")
        {
            char imgName[256];
            int fIdx;
            std::cin >> imgName >> fIdx;
            manager.removeFilter(imgName, fIdx);
        }
        else if (cmd == "show-filters")
        {
            char imgName[256];
            std::cin >> imgName;
            manager.showFilters(imgName);
        }
        else if (cmd == "show-all-filters")
        {
            manager.showAllFilters();
        }
        else if (cmd == "run")
        {
            char imgName[256];
            std::cin >> imgName;
            manager.run(imgName);
        }
        else if (cmd == "run-all")
        {
            manager.runAll();
        }
        else if (cmd == "save")
        {
            char imgName[256], outName[256];
            std::cin >> imgName >> outName;
            manager.save(imgName, outName);
        }
        else if (cmd == "quit")
        {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else
        {
            std::cout << "Unknown command: " << command << std::endl;
            std::cin.ignore(1000, '\n');
        }
    }

    return 0;
}