#include <algorithm>
#include <iostream>
#include <cstdio>
#include <random>
#include <chrono>
#include <windows.h>
#include <string>
#include "tinydir.h"
#include <unistd.h>

char* directory()
{
    char buffer[500];
    GetModuleFileName(nullptr, buffer, 500);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    std::string str = std::string(buffer).substr(0, pos);
    char *cstr = new char[str.size() + 1];

    std::copy(str.begin(), str.end(), cstr);
    cstr[str.size()] = '\0';

    return cstr;
}

std::mt19937 GEN(std::chrono::high_resolution_clock::now().time_since_epoch().count());
std::uniform_int_distribution<> DIS(33, 126);

std::string randomName(char *extension)
{
    const int NUM_CHARACTERS = 8;
    std::string filename;
    for (int i = 0; i < NUM_CHARACTERS; i++)
    {
        char c = 0;
        do
        {
            c = static_cast<char>(DIS(GEN));
        } while (c == '<' || c == '>' || c == ':' || c == '\"' || c == '/' || c == '\\'
            || c == '|' || c == '?' || c == '*' || c == '.');

        filename.push_back(c);
    }

    return filename.append(".").append(extension);
}

int main() 
{

    std::cout << "This will rename everything in this folder. Press enter to continue." << std::endl;
    std::cin.ignore();

    tinydir_dir dir;
    char* strdir = directory();
    std::cout << strdir << std::endl;
    tinydir_open(&dir, strdir);
    delete[] strdir;

    std::vector<std::string> renamed;
    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        if (!file.is_dir && (std::string(file.name) != std::string("renand.exe")))
        {
            if (!(std::find(renamed.begin(), renamed.end(), std::string(file.name)) != renamed.end()))
            {
                std::string filename = randomName(file.extension);
                renamed.push_back(filename);

                bool success = false;
                int tries = 0;
                do 
                {
                    for (int i = 0; i < tries; i++) { std::cout << '\t'; }

                    std::cout << "Trying to rename: " << file.name 
                              << "\t\tto " << filename << std::endl;
                    success = std::rename(file.name, filename.c_str());
                    success ? tries = 0 : tries++;
                } while (!success);
            }
            
        }
        tinydir_next(&dir);
    }
    tinydir_close(&dir);
}
