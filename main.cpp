#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printVec(vector<vector<int> >& vec)
{
	for (unsigned i = 0; i < vec.size(); i++)
	{
		for(unsigned j = 0; j < vec[i].size(); j++)
			cout << vec[i][j] << " ";
		cout << endl;
	}
}

void maxAndMin(vector<vector<int> >& vec, int &maxH, int &maxW, int &minW)
{
	maxH = 0;
	maxW = 0;
	minW = INT_MAX;
	for(unsigned i = 0; i < vec.size(); i++)
	{
		if(vec[i][1] > maxH)
			maxH = vec[i][1];
		if(vec[i][0] + vec[i][2] > maxW)
			maxW = vec[i][0] + vec[i][2];
		if(vec[i][0] < minW)
			minW = vec[i][0];
	}
}

void makeLines(vector< vector<int> >& vec, vector<vector<int> >& area)
{
	for (unsigned i = 0; i < vec.size(); i++)
	{
		vector<pair<int, int>> temp;

		temp.push_back(make_pair(vec[i][0], 0));
		temp.push_back(make_pair(vec[i][0], vec[i][1]));
		temp.push_back(make_pair(vec[i][0] + vec[i][2], vec[i][1]));
		temp.push_back(make_pair(vec[i][0] + vec[i][2], 0));

		for (int j = 0; j <= vec[i][1]; j++)
			area[vec[i][0]][j]++;
		for (int j = vec[i][0]; j <= vec[i][0]+vec[i][2]; j++)
			area[j][vec[i][1]]++;
		for (int j = vec[i][1]; j >= 0; j--)
			area[vec[i][0]+vec[i][2]][j]++;
		
	}
}

void findPoints(vector<vector<int> >& area, vector<pair<int, int>>& points, int maxW, int minW)
{
	int ver = 1, hor = 0;
	int px = minW, py = 0;
	points.push_back(make_pair(px, py));
	
	while(1)
	{
		if(px == maxW && py == 0)
		{
			points.push_back(make_pair(px, py));
			break;
		}

		if (ver == 1)
		{
			if(area[px][py] == 1)
				py++;
			else
			{
				if (area[px][py+1] == 0)
				{
					points.push_back(make_pair(px, py));
					ver = 0;
					hor = 1;
					px++;
				}

				else
					py++;
			}
		}

		if (hor == 1)
		{
			if (area[px][py] == 0 && py == 0)
				px++;
			
			else if(area[px][py] == 1)
			{
				if(area[px-1][py] != 0)
					px++;
				else
				{
					points.push_back(make_pair(px, py));
					ver = 1;
					hor = 0;
					py++;
				}
			}
			else
			{
				if(area[px+1][py] != 0 && area[px][py+1] == 0 && area[px][py-1] != 0)
				{
					if(area[px][py] == 1)
					{
						points.push_back(make_pair(px, py));
						px++;
					}
					else
						px++;
				}

				else if((area[px+1][py] != 0 && area[px][py-1] != 0) || (area[px+1][py] == 0 && area[px][py-1] == 0) || 
					(area[px+1][py] != 0 && area[px][py-1] == 0))
				{
					points.push_back(make_pair(px, py));
					ver = 1;
					hor = 0;
					py++;
				}

				else if(area[px+1][py] == 0 && area[px][py+1] == 0)
				{
					points.push_back(make_pair(px, py));
					ver = -1;
					hor = 0;
					py--;
				}
			}
		}

		if (ver == -1)
		{
			if(area[px][py] == 1)
			{
				if (py != 0)
					py--;
				else
				{
					points.push_back(make_pair(px, py));
					ver = 0;
					hor = 1;
					px++;
				}
			}

			else
			{
				points.push_back(make_pair(px, py));
				ver = 0;
				hor = 1;
				px++;
			}
		}
	}
}

int main()
{
	int maxH = 0, maxW = 0, minW = 0;
	vector<vector<int> > buildings, area;
	vector<pair<int, int>> points;
	vector<int> values;
	ifstream in("girdi.txt");
    int data;
    while(in >> data)
        values.push_back(data);

    in.close();

	for (unsigned i = 0; i < values.size(); i += 3)
	{
		vector<int> vec;
		vec.push_back(values[i]);
		vec.push_back(values[i+1]);
		vec.push_back(values[i+2]);
		buildings.push_back(vec);
	}

	maxAndMin(buildings, maxH, maxW, minW);

	for (int i = 0; i <= maxW+1; i++)
	{
		vector <int> vec;
		for (int j = 0; j <= maxH+1; j++)
			vec.push_back(0);
		area.push_back(vec);
	}


	makeLines(buildings, area);
	findPoints(area, points, maxW, minW);

	for(unsigned i = 0; i < points.size (); i++)
	{
		if(i != points.size()-1)
    		cout << "(" << points[i].first << ", " << points[i].second << ")" << ", "; 
		else
			cout << "(" << points[i].first << ", " << points[i].second << ")"; 
	}

	return 0;
}
