#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

bool copyFile(const std::string& source, const std::string& destination)
{
    std::cout << "Copying " << source << " to " << destination << std::endl;

    std::ifstream src(source, std::ios::binary);
    std::ofstream dest(destination, std::ios::binary);
    
    std::istreambuf_iterator<char> beginSrc(src);
    std::istreambuf_iterator<char> endSrc;
    std::ostreambuf_iterator<char> beginDest(dest);
    std::copy(beginSrc, endSrc, beginDest);

    bool success = src && dest;

    src.close();
    dest.close();

    return success;
}

int main() 
{
    std::ifstream userFonts("../txts/userFonts.txt");
    if (userFonts.is_open())
    {
        std::cout << "open" << std::endl;
        std::vector<std::string> fontNames;
        std::string line;
        while (std::getline(userFonts, line))
        {
            fontNames.push_back(std::string(line));
        }
        userFonts.close();

        std::for_each(fontNames.begin(), fontNames.end(),
            [&] (const std::string& name) {
                const std::string sourceDir = std::string("C:/Windows/Fonts/") + name;
                const std::string destDir = std::string("C:/myfonts/") + name;
                std::cout << copyFile(sourceDir, destDir) << std::endl;
            }
        );
    }
}