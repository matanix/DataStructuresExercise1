#include "Graph.h"
#include <string>
#include <iostream>
using namespace std;


int main()
{
	string omri_name = "omri";
	string matan_name = "matan";
	string eidan_name = "eidan";
	string erez_name = "erez";

	Graph<string> graph;

	vector<string> vec;
	Vertex<string> omri(omri_name, vec);
	Vertex<string> matan(matan_name, vec);
	Vertex<string> eidan(eidan_name, vec);
	Vertex<string> erez(erez_name, vec);

	graph.AddVertex(omri, vec);
	vec.push_back(omri_name);
	graph.AddVertex(matan, vec);

	vec.push_back(matan_name);
	graph.AddVertex(eidan, vec);

	vector<string> vec2;
	vec2.push_back(omri_name);
	graph.AddVertex(erez, vec2);

	LinkedList<Vertex<string>> check;

	check = graph.GetElements();

	string res = check.GetAt(0)->GetValue().GetValue();

	cout << "name is : " << res << endl;

	res = check.GetAt(1)->GetValue().GetValue();

	cout << "name is : " << res << endl;

	vector<string> adjRes = check.GetAt(0)->GetValue().GetAllAdj();

	for (std::vector<string>::iterator i = adjRes.begin(); i != adjRes.end(); ++i)
	{
		cout << "omri's adjs name is : " << *i << endl;
	}

	adjRes = check.GetAt(1)->GetValue().GetAllAdj();

	for (std::vector<string>::iterator i = adjRes.begin(); i != adjRes.end(); ++i)
	{
		cout << "matan's adjs name is : " << *i << endl;
	}

	return 0;
}