#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>

#define CELL_W 187
#define CELL_H 328

#define MIN_CELL_W	1	
#define MAX_CELL_W	2
#define MIN_CELL_H	1
#define MAX_CELL_H	1

using namespace std;

vector<string> split(string line, string delimeter = "\t")
{
	vector<string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}

int DetectCell_Size(int Map, int min_range, int max_range, int Screen)
{
	int cell_Min = floor((min_range * Map) / Screen);
	int cell_Max = floor((max_range * Map) / Screen);

	int avg = (cell_Min + cell_Max) / 2;

	return floor(Map / avg);
}

int main()
{
	int mapW;
	int mapH;
	int screenW;
	int screenH;
	int cellW;
	int cellH;
	ifstream fs;
	ofstream ofs;
	ofs.open("output.txt", ios::out);
	fs.open("scene1.txt");
	int id = 0;
	int section;
	if (fs.fail())
	{
		cout << "Load file scene fail";
	}
	else
	{
		cout << "Load File Thanh cong";
		char str[1024];
		while (fs.getline(str, 1024))
		{
			string line(str);
			if (line == "[MAP_INFOR]")
			{
				section = 0;
				ofs << line << "\n";
				continue;
			}
			if (line == "[OBJECTS]")
			{
				section = 1;
				ofs << line <<"\n";
				continue;
			}

			
			if (line == "") continue;
			if (line[0] == '#')
			{
				id = 0;
				ofs << line;
			}
			else
			{
				vector<string> tokens = split(line);
				if (section == 0)
				{
					mapW = atoi(tokens[0].c_str());
					mapH = atoi(tokens[1].c_str());
					screenW = atoi(tokens[2].c_str());
					screenH = atoi(tokens[3].c_str());
					cellW = DetectCell_Size(mapW, MIN_CELL_W, MAX_CELL_W, screenW);
					cellH = DetectCell_Size(mapH, MIN_CELL_H, MAX_CELL_H, screenH);
					ofs << cellW << "\t" << cellH << "\n";

				}
				else
				{
					int bboxLeft, bboxTop, bboxRight, bboxBottom;
					id++;
					ofs << id << "\t";
					ofs << line << "\t";
					int amountX = atoi(tokens[4].c_str());
					int amountY = atoi(tokens[5].c_str());
					bboxLeft = atoi(tokens[1].c_str());
					bboxTop = atoi(tokens[2].c_str());

					bboxRight = bboxLeft + amountX * 16;
					bboxBottom = bboxTop + amountY * 16;
					//ofs << bboxLeft << "\t" << bboxTop << "\t" << bboxRight << "\t" << bboxBottom << "\t";

					//Done export file + BBOX
					int top = int(bboxTop / cellH);
					int left = int(bboxLeft / cellW);
					int right = ceil(bboxRight / cellW);
					int bottom = ceil(bboxBottom / cellH);

					ofs << left << "\t" << top << "\t" << right << "\t" << bottom << "\t";
				}
			}
			ofs << "\n";
		}
	}
	fs.close();
	ofs.close();
	return 0;
}

