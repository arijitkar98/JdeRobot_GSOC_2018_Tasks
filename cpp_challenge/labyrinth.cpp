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

int checkCoordinates( int i, int j, vector<string> labyrinth)
{
    if(i < 0 || j < 0 || i >= labyrinth.size() || j >= labyrinth[0].size())
        return 0;
    return 1;
}

void depthFirstSearch(int x, int y, vector<string> labyrinth, vector<vector<bool> > &visited, vector<string> &pathLabyrinth, int &currentLen)
{
    visited[x][y] = 1;

    int maxLen = 0;

    vector<vector<vector<bool> > > tempVisited;
    vector<vector<string> > tempPathLabyrinth;

    for(int i=0;i<4;i++)
    {
        tempVisited.push_back(visited);
        tempPathLabyrinth.push_back(pathLabyrinth);
    }

    int dirX[] = {-1, 0, 1, 0};
    int dirY[] = { 0,-1, 0, 1};

    for(int i = 0; i < 4; i++)
    {
        int newX = x + dirX[i];
        int newY = y + dirY[i];

        if(checkCoordinates(newX, newY, labyrinth))
        {
            if(visited[newX][newY] == 0)
            {
                int tempLen = 0;    
                depthFirstSearch(newX, newY, labyrinth, tempVisited[i], tempPathLabyrinth[i], tempLen);
            
                if(tempLen > maxLen)
                {
                    pathLabyrinth = tempPathLabyrinth[i];
                    visited = tempVisited[i];
                    maxLen = tempLen;
                }
            }
        }
    }
    
    pathLabyrinth[x][y] = maxLen + '0';
    currentLen = ++maxLen;
}

void findLargestPath(vector<string> &inputLabyrinth, vector<vector<bool> > &visited)
{
    int maxLen = 0;
    vector<string> finalPathLabyrinth;
    vector<vector<bool> > finalVisited = visited;

    for(int i = 0; i < inputLabyrinth.size(); i++)
    {
        for(int j = 0; j < inputLabyrinth[0].size(); j++)
        {
            if(!visited[i][j])
            {
                vector<string> tempPathLabyrinth = inputLabyrinth;
                vector<vector<bool> > tempVisited = visited;
                int currentLen = 0;

                depthFirstSearch(i, j, inputLabyrinth, tempVisited, tempPathLabyrinth, currentLen);

                if(currentLen > maxLen)
                {
                    finalPathLabyrinth = tempPathLabyrinth;
                    maxLen = currentLen;
                    finalVisited = tempVisited;
                }
            }
        }
    }

    cout << maxLen << endl;

    for(int i = 0; i < inputLabyrinth.size(); i++) 
    {
        for(int j = 0; j < inputLabyrinth[0].size(); j++) 
        {
            if(finalPathLabyrinth[i][j] == '#')
                cout << "# ";
            else if(finalPathLabyrinth[i][j] == '.')
                cout << ". ";
            else
            {
                cout<<(static_cast<int>(finalPathLabyrinth[i][j]) - 48)<<' ';
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

	vector<vector<bool> > visited;

	for(int i = 0; i < inputLabyrinth.size(); i++)
	{
		vector<bool> row;
		for(int j=0; j < inputLabyrinth[0].size(); j++)
		{
			if(inputLabyrinth[i][j] == '.')
				row.push_back(0);
			else row.push_back(1);
		}
		visited.push_back(row);
	}

    findLargestPath(inputLabyrinth, visited);

	return 0;
}

