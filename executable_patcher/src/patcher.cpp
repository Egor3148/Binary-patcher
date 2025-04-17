#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../inc/patcher.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::fstream;

int patch(const char* content, int size, std::string file_to_patch, std::string file_patched)
{
	ifstream fin(file_to_patch, std::ios::binary | std::ios_base::in);
	fstream fout(file_patched, std::ios::binary | std::ios_base::out);

	if (!fin)
	{
		return 1;
	}
	else if (!fout)
	{
		return 2;
	}

	// FSM identifier data 
	// (used to identify patching buffer start and end)
	char start_states[3] = { '<', 's', 't' };
	char end_states[3] = { 's', 't', '>' };
	char state = 0;

	bool bufferFound = false;	// Specifies if the patching buffer was found
	bool limit = false;			// Specifies if patching finished because of exceeding buffer limit

	char buf;
	
	while (fin.read(&buf, sizeof(buf)))
	{
		fout.write(&buf, sizeof(buf));
		if (buf == start_states[state])
		{
			++state;
			if (state == 3)	// Tag recognized, buffer start identified
			{
				bufferFound = true;

				// Buffer writing
				int i = 0;
				state = 0;
				
				while (i < size)
				{
					fin.read(&buf, sizeof(buf));
					if (buf == end_states[state])
					{
						++state;
						if (state == 3)	// Buffer end identified, stop writing
						{
							limit = true;
							break;
						}
					}
					else
					{
						state = 0;
					}

					fout.write(&content[i], sizeof(content[i]));
					++i;
				}

				if (limit)
				{
					fout.seekg(fout.tellg() - std::streamoff(2));
					fout << "st>";
				} else
				{
					fin.read(&buf, sizeof(buf));
					fin.read(&buf, sizeof(buf));
					fin.read(&buf, sizeof(buf));

					//for (short j = 0; j < 3; ++j)
					//{
					//	fout.write(&end_states[i], sizeof(end_states[i]));
					//}
					fout << "st>";

				}

			}
		}
		else
		{
			state = 0;
		}
	}

	fin.close();
	fout.close();

	if (!bufferFound)
	{
		return 3;
	}
	else if (limit)
	{
		return 4;
	}
	else
	{
		return 0;
	}
}

void signFile(const std::string& filename) {
	std::string cmd = "signtool sign /fd sha256 /a \"" + filename + "\"";
	system(cmd.c_str());
}
