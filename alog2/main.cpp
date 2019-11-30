#include "Graph.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct ResVector
{
	string value;
	size_t entry_number = 0;
	size_t finish_number = 0;
};

int GetVertexByString(LinkedList<Vertex<string>> elements, string name, size_t elementsCount)
{
	for (int i = 0; i < elementsCount; ++i)
	{
		if (elements.GetAt(i)->GetValue().GetValue() == name)
		{
			return i;
		}
	}

	return -1;
}

size_t DFS(LinkedList<Vertex<string>> elements, Vertex<string> element,
		   size_t elementNumber, size_t maxElements)
{
	string res = element.GetValue();


	if(element.visited == false)
    {
		int elementPlace = GetVertexByString(elements, res, maxElements);
		elements.GetAt(elementPlace)->GetValue().entry_number = elementNumber;
    	elements.GetAt(elementPlace)->GetValue().visited = true;

    	vector<string> adjRes = element.GetAllAdj();

    	for (std::vector<string>::iterator i = adjRes.begin(); i != adjRes.end(); ++i)
		{
			elementPlace = GetVertexByString(elements, *i, maxElements);

			if(elements.GetAt(elementPlace)->GetValue().visited == true)
			{
				elements.GetAt(elementPlace)->GetValue().finish_number = elementNumber;
				continue;
			}

			return DFS(elements, elements.GetAt(elementPlace)->GetValue(), elementNumber + 1, maxElements) + 1;
		}
    }

    return 0;
}


void TopologicSort(Graph<string>& graph)
{
	cout << "Start TopologicSort with " << graph.GetElementsCount() << " number of elements : " << endl; 

	LinkedList<Vertex<string>> elements = graph.GetElements();
	size_t elementNumber = 0;

	for (int i = 0; i < graph.GetElementsCount(); ++i)
	{
		Vertex<string> element = elements.GetAt(i)->GetValue();
		size_t temp = DFS(elements, element, elementNumber, graph.GetElementsCount());

		elementNumber += temp == 0 ? 1 : temp + 1;  
	}

	ResVector build[graph.GetElementsCount()];

	for (int i = 0; i < graph.GetElementsCount(); ++i)
	{
		Vertex<string> element = elements.GetAt(i)->GetValue();
		build[element.entry_number].value = elements.GetAt(i)->GetValue().GetValue();
		build[element.entry_number].entry_number = element.entry_number;
		build[element.entry_number].finish_number = element.finish_number;
	}

	string registered[graph.GetElementsCount()];
	size_t registeredCounter = 0;

	for (int i = 0; i < graph.GetElementsCount(); ++i)
	{
		if (build[i].finish_number == 0)
		{
			registered[build[i].entry_number - registeredCounter] = build[i].value;
		}
		else
		{
			registered[build[i].finish_number] = build[i].value;
			registeredCounter++;
		}
	}

	for (int i = 0; i < graph.GetElementsCount(); ++i)
	{
		cout << registered[i] << " , ";
	}


	cout << endl << "End TopologicSort" << endl; 
}

int main()
{
	// string omri_name = "omri";
	// string matan_name = "matan";
	// string eidan_name = "eidan";
	// string erez_name = "erez";

	// Graph<string> graph;

	// vector<string> vec;
	// Vertex<string> omri(omri_name, vec);
	// Vertex<string> matan(matan_name, vec);
	// Vertex<string> eidan(eidan_name, vec);
	// Vertex<string> erez(erez_name, vec);

	// graph.AddVertex(omri, vec);
	// vec.push_back(omri_name);
	// graph.AddVertex(matan, vec);

	// vec.push_back(matan_name);
	// graph.AddVertex(eidan, vec);

	// vector<string> vec2;
	// vec2.push_back(omri_name);
	// graph.AddVertex(erez, vec2);

	// LinkedList<Vertex<string>> check;

	// check = graph.GetElements();

	// string res = check.GetAt(0)->GetValue().GetValue();

	// cout << "name is : " << res << endl;

	// res = check.GetAt(1)->GetValue().GetValue();

	// cout << "name is : " << res << endl;

	// vector<string> adjRes = check.GetAt(0)->GetValue().GetAllAdj();

	// for (std::vector<string>::iterator i = adjRes.begin(); i != adjRes.end(); ++i)
	// {
	// 	cout << "omri's adjs name is : " << *i << endl;
	// }

	// adjRes = check.GetAt(1)->GetValue().GetAllAdj();

	// for (std::vector<string>::iterator i = adjRes.begin(); i != adjRes.end(); ++i)
	// {
	// 	cout << "matan's adjs name is : " << *i << endl;
	// }

	// cout << endl << endl;

	// TopologicSort(graph);

	// cout << endl << endl;

	string bdida1_name 						= "bdida1";
	string bdida2_name 						= "bdida2";
	string algo1_name 						= "algo1";
	string algo2_name 						= "algo2";
	string data_structure_name 				= "data_structure";
	string computability_name 				= "computability";
	string computational_models_name 		= "Computational_models"; 
	string introduction_to_Computers_name 	= "Introduction_to_Computers"; 

	Graph<string> graph2;

	vector<string> clean_vec;
	Vertex<string> bdida1(bdida1_name, clean_vec);
	Vertex<string> bdida2(bdida2_name, clean_vec);
	Vertex<string> algo1(algo1_name, clean_vec);
	Vertex<string> algo2(algo2_name, clean_vec);
	Vertex<string> data_structure(data_structure_name, clean_vec);
	Vertex<string> computability(computability_name, clean_vec);
	Vertex<string> computational_models(computational_models_name, clean_vec);
	Vertex<string> introduction_to_Computers(introduction_to_Computers_name, clean_vec);

	graph2.AddVertex(bdida1, clean_vec);
	graph2.AddVertex(introduction_to_Computers, clean_vec);

	vector<string> bdida2Fathers;
	bdida2Fathers.push_back(bdida1_name);
	graph2.AddVertex(bdida2, bdida2Fathers);

	vector<string> dataStructureFathers;
	dataStructureFathers.push_back(introduction_to_Computers_name);
	graph2.AddVertex(data_structure, dataStructureFathers);

	vector<string> algo1Fathers;
	algo1Fathers.push_back(data_structure_name);
	graph2.AddVertex(algo1, algo1Fathers);

	vector<string> algo2Fathers;
	algo2Fathers.push_back(algo1_name);
	algo2Fathers.push_back(bdida2_name);
	graph2.AddVertex(algo2, algo2Fathers);

	vector<string> computational_modelsFathers;
	computational_modelsFathers.push_back(algo1_name);
	graph2.AddVertex(computational_models, computational_modelsFathers);

	vector<string> computabilityFathers;
	computabilityFathers.push_back(algo2_name);
	computabilityFathers.push_back(computational_models_name);
	graph2.AddVertex(computability, computabilityFathers);

	TopologicSort(graph2);

	return 0;
}