random-renamer
==============

random-renamer is a small utility that renames all files in the executable's directory to a random $NUM character name. Names are a random string of characters, and preserve the file extension.

## Exploring

The source for random-renamer is found in this directory.
* ```renand.cpp``` - Gets a list of all files in the directory where ```renand.exe``` was run. Generates random names and renames all files (not including sub-directories) in the directory.

## Dependencies
#### Platform agnostic
* **[tinydir](https://github.com/cxong/tinydir)** - Used to get a list of all files in a given directory.

#### Platform dependent
* ```Windows.h``` - This header was included for the function ```GetModuleFileName()``` which gets the directory in which the executable was run on Windows. Replace this function with the proper function in your operating system.

## Usage
#### Downloading
To download, simply

	$ todo

#### Building
Run

	$ make

You must have g++.

#### Running

	$ cd bin
	$ cp renand [directory to rename files]
	$ cd [directory]
	$ renand

**Warning**: This program will rename all files in the working directory except for the executable, and there is no built-in way to revert this. Perhaps I'll add this functionality later. Use with caution, and don't be enter-happy.

## Future plans

I'll make it possible to revert the renamed files back to the original names.

## License

The MIT License (MIT)

Copyright (c) 2014 Leon Cheung

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
