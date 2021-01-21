#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>

#define CELL_W 187
#define CELL_H 328

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

int main()
{
	ifstream fs;
	ofstream ofs;
	ofs.open("output.txt", ios::out);
	fs.open("scene4.txt");
	int id = 0;
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
			if (line == "") continue;
			if (line[0] == '#')
			{
				id = 0;
				ofs << line;
			}
			else
			{
				vector<string> tokens = split(line);
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
				int top = int(bboxTop / CELL_H);
				int left = int(bboxLeft / CELL_W);
				int right = ceil(bboxRight / CELL_W);
				int bottom = ceil(bboxBottom / CELL_H);

				ofs << left << "\t" << top << "\t" << right << "\t" << bottom << "\t";
			}
			ofs << "\n";
		}
	}
	fs.close();
	ofs.close();
	return 0;
}

