#include <vector>
#include <list>
#include <stack>
#include <map>
#include <queue>
#include <iostream>


using namespace std;

//graph
int v = 1000;
int e = 20000;

//adjaceny matrix
vector<vector <int>> adj_mat(v, vector<int>(v));

//adjaceny list
vector<list <int>> adj_list(v);

// depth first search recursive
void dfs(vector<list<int>> &adjaceny_list, vector<bool> &visited, int source)
{
	visited[source] = true;
	//pre visiting
	for (auto itr = adjaceny_list[source].begin(); itr != adjaceny_list[source].end(); itr++)
	{
		if (!visited[*itr])
		{
			// visited[*itr] = true; if the first line in the function code isn't there
			dfs(adjaceny_list, visited, *itr);
		}
	}
	//post
}

//depth first search sequential
void dfs(vector<list<int>> &adjaceny_list, int source)
{
	stack<int> to_be_visited;
	//pre
	to_be_visited.push(source);
	vector <int> visited(adjaceny_list.size());
	visited[source] = true;
	while (!to_be_visited.empty())
	{
		int current_node = to_be_visited.top();
		to_be_visited.pop();
		for (auto itr = adjaceny_list[current_node].begin(); itr != adjaceny_list[current_node].end(); itr++)
		{
			if (!visited[*itr])
			{
				visited[*itr] = true;
				to_be_visited.push(*itr);
			}
		}
	}
	//post
}

//breadth first search
// same implementation as DFS but using queue 
void bfs(vector<list<int>> &adjaceny_list, int source)
{
	queue<int> to_be_visited;
	//pre
	to_be_visited.push(source);
	vector <int> visited(adjaceny_list.size());
	visited[source] = true;
	while (!to_be_visited.empty())
	{
		int current_node = to_be_visited.front();
		to_be_visited.pop();
		for (auto itr = adjaceny_list[current_node].begin(); itr != adjaceny_list[current_node].end(); itr++)
		{
			if (!visited[*itr])
			{
				visited[*itr] = true;
				to_be_visited.push(*itr);
			}
		}
	}
	//post
}

//return a bool that represent if all the vertices are connected or 
// there are a bunch of lone or connected vertices sparse out (متناثرة)
// for undirected graph 
//could be depth or breadth
bool undirected_connected_efficient(vector<list<int>> &adjaceny_list)
{
	stack<int> to_be_visited;
	//pre
	to_be_visited.push(0);
	vector <bool> visited(adjaceny_list.size());//(v) in OMAR AMIN video
	visited[0] = true;
	while (!to_be_visited.empty())
	{
		int current_node = to_be_visited.top();
		to_be_visited.pop();
		for (auto itr = adjaceny_list[current_node].begin(); itr != adjaceny_list[current_node].end(); itr++)
		{
			if (!visited[*itr])
			{
				visited[*itr] = true;
				to_be_visited.push(*itr);
			}
		}
	}
	//post
	for (size_t i = 0; i < visited.size(); i++)
	{
		if (visited[i] == false)return false;
	}
	return true;
}

// is certain(target) node is reachable from another node(source)
//could be depth or breadth
bool is_there_a_way_out(vector<list<int>> &adjaceny_list, int source, int target)
{
	stack<int> to_be_visited;
	//pre
	to_be_visited.push(source);
	vector <bool> visited(adjaceny_list.size());
	visited[source] = true;
	bool found = false;
	while (!to_be_visited.empty()&&!found)
	{
		int current_node = to_be_visited.top();
		if (current_node == target)
		{
			return true;
		}
		to_be_visited.pop();
		for (auto itr = adjaceny_list[current_node].begin(); itr != adjaceny_list[current_node].end(); itr++)
		{
			if (!visited[*itr])
			{
				visited[*itr] = true;
				to_be_visited.push(*itr);
			}
		}
	}
	return false;
}



void main()
{
	printf("hello world !");
	
}