#include <algorithm>
#include <vector>
#include <string>
#include "include/tinydir.h"
#include <fstream>

typedef std::vector<std::string> Vecstrs;

Vecstrs getUserFonts(const Vecstrs& defaultFonts, const Vecstrs& installedFonts)
{
    Vecstrs userFonts;

    std::for_each(installedFonts.begin(), installedFonts.end(),
        [&] (const std::string& font) {
            if (!std::binary_search(defaultFonts.begin(), defaultFonts.end(), font))
            {
                userFonts.push_back(font);
            }
    });

    return userFonts;
}

int main()
{
    Vecstrs installedFonts;

    tinydir_dir dir;
    tinydir_open(&dir, "C:/Windows/Fonts/");
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);
        if (std::string(file.name) != "." && std::string(file.name) != "..")
        {
            installedFonts.push_back(std::string(file.name));
        }
        tinydir_next(&dir);
    }

    tinydir_close(&dir);

    std::string line;
    Vecstrs defaultFonts;
    std::ifstream file("../txts/default_fonts.txt");
    if (file.is_open())
    {
        while (std::getline (file, line))
        {
            defaultFonts.push_back(line);
        }
        file.close();
    }

    auto userFonts = getUserFonts(defaultFonts, installedFonts);
    std::ofstream userTxt ("../txts/userFonts.txt", std::ofstream::out);
    for_each(userFonts.begin(), userFonts.end(), 
        [&] (const std::string& fontFile) {
            userTxt << fontFile << "\n";
    });

    return 0;
}