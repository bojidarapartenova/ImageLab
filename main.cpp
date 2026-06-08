#include <iostream>
#include <sstream>
#include "include/ImageManager.h"
#include "include/MyString.h"

int main()
{
    ImageManager manager;
    std::string line;

    std::cout << "--- Image Processing System ---" << std::endl;
    std::cout << "Available commands: load, add-filter, remove-filter, show-filters, show-all-filters, run, run-all, save, quit" << std::endl;

    while (true)
    {
        std::cout << "\n> ";
        if (!std::getline(std::cin, line))
        {
            break;
        }

        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);
        std::string cmdStr;
        ss >> cmdStr;

        String cmd(cmdStr.c_str());

        if (cmd == "load")
        {
            std::string path;
            bool loaded = false;
            while (ss >> path)
            {
                manager.load(path.c_str());
                loaded = true;
            }
            if (!loaded)
            {
                std::cout << "Error: Missing path for 'load' command." << std::endl;
            }
        }
        else if (cmd == "add-filter")
        {
            std::string imgName, filterType;
            if (ss >> imgName >> filterType)
            {
                int sobelThreshold = -1;
                if (filterType == "sobel")
                {
                    ss >> sobelThreshold;
                }
                manager.addFilter(imgName.c_str(), filterType.c_str(), sobelThreshold);
            }
            else
            {
                std::cout << "Error: Usage: add-filter <image_name> <filter_type>" << std::endl;
            }
        }
        else if (cmd == "remove-filter")
        {
            std::string imgName;
            int fIdx;
            if (ss >> imgName >> fIdx)
            {
                manager.removeFilter(imgName.c_str(), fIdx);
            }
            else
            {
                std::cout << "Error: Usage: remove-filter <image_name> <filter_index>" << std::endl;
            }
        }
        else if (cmd == "show-filters")
        {
            std::string imgName;
            if (ss >> imgName)
            {
                manager.showFilters(imgName.c_str());
            }
            else
            {
                std::cout << "Error: Missing image name for 'show-filters'." << std::endl;
            }
        }
        else if (cmd == "show-all-filters")
        {
            manager.showAllFilters();
        }
        else if (cmd == "run")
        {
            std::string imgName;
            if (ss >> imgName)
            {
                manager.run(imgName.c_str());
            }
            else
            {
                std::cout << "Error: Missing image name for 'run'." << std::endl;
            }
        }
        else if (cmd == "run-all")
        {
            manager.runAll();
        }
        else if (cmd == "save")
        {
            std::string imgName, outName;
            if (ss >> imgName)
            {
                ss >> outName;
                manager.save(imgName.c_str(), outName.c_str());
            }
            else
            {
                std::cout << "Error: Usage: save <image_name> [output_name]" << std::endl;
            }
        }
        else if (cmd == "quit")
        {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else
        {
            std::cout << "Unknown command: " << cmdStr << std::endl;
        }
    }

    return 0;
}
