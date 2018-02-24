/*
			JdeRobot GSOC 2018
			C++ Programming Task
			Submitted By - Arijit Kar (arijitkar98)
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

void depthFirstSearch(int x, int y, vector<string> &labyrinth, vector<vector<bool> > &visited1, int &currentLen)
{
    for(int i = -1; i < 2; i++) 
    {
    	for(int j = -1; j < 2; j++)
    	{
    		if(abs(i) + abs(j) == 1)
    		{
        		int x1 = x + i;
        		int y1 = y + j;
        		if(x1 >= 0 && x1 < labyrinth.size() && y1 >=0  && y1 < labyrinth[0].size() && labyrinth[x1][y1] == '.' && visited1[x1][y1] == false) 
        		{
            		visited1[x1][y1] = true;
            		currentLen = currentLen + 1;
            		depthFirstSearch(x1, y1, labyrinth, visited1, currentLen);
        		}
        	}
        }
    }
}

void finalDFS(int x, int y, vector<string> &labyrinth, vector<vector<bool> > &visited1, int &currentLen)
{
    labyrinth[x][y] = currentLen + '0';

    for(int i = -1; i < 2; i++) 
    {
        for(int j = -1; j < 2; j++)
        {
            if(abs(i) + abs(j) == 1)
            {
                int x1 = x + i;
                int y1 = y + j;
                if(x1 >= 0 && x1 < labyrinth.size() && y1 >=0  && y1 < labyrinth[0].size() && labyrinth[x1][y1] == '.' && visited1[x1][y1] == false) 
                {
                    visited1[x1][y1] = true;
                    currentLen = currentLen + 1;
                    finalDFS(x1, y1, labyrinth, visited1, currentLen);
                }
            }
        }
    }
}

void findLargestPath(int rows, int cols, vector<string> &inputLabyrinth, vector<string> &outputLabyrinth, vector<vector<bool> > &visited1, vector<vector<bool> > &visited2)
{
    int maxLen = 0;
    int currentLen;
    int startX, startY;
    for(int i = 0; i < rows; i++) 
    {
        for( int j = 0; j < cols; j++) 
        {
            if(inputLabyrinth[i][j] != '#' && visited1[i][j] == false)
            {
                currentLen = 1;
                visited1[i][j] = true;
                depthFirstSearch(i ,j, inputLabyrinth, visited1, currentLen);

                if(currentLen > maxLen) 
                {
                    maxLen = currentLen;
                    startX = i;
                    startY = j;
                }
            }
        }
    }

    currentLen = 1;
    visited2[startX][startY] = true;
    finalDFS(startX, startY, outputLabyrinth, visited2, currentLen);

    cout << currentLen << endl;
    for(int i = 0; i < rows; i++) 
    {
        for(int j = 0; j < cols; j++) 
        {
        	if(outputLabyrinth[i][j] == '#')
        		cout << "# ";
        	else if(outputLabyrinth[i][j] == '.')
        		cout << ". ";
        	else
        	{
            	cout<<(static_cast<int>(outputLabyrinth[i][j]) - 49)<<' ';
        	}
        }
        cout<<endl;
    }
}

int main(int argc, char* argv[])
{
	ifstream file(argv[1]);	
	string a;
	vector<string> matrix;
	while(getline(file,a))
	{
		matrix.push_back(a);
	}
	vector<string> inputLabyrinth(matrix);

	vector<string> outputLabyrinth = inputLabyrinth;

    int rows = inputLabyrinth.size();
    int cols = inputLabyrinth[0].size();

    vector<vector<bool> > visited1,visited2;

    for(int i = 0; i < rows; i++)
    {
        vector<bool> row;
        visited1.push_back(row);
        visited2.push_back(row);

        for(int j = 0; j < cols; j++)
        {
            visited1[i].push_back(false);
            visited2[i].push_back(false);
        }
    }

    findLargestPath(rows,cols,inputLabyrinth,outputLabyrinth,visited1,visited2);

	return 0;
}