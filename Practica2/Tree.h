#ifndef TREE
#define TREE



#include "p2List.h"
#include "Stack.h"

//#include <stdlib.h>


; template < class Node >
class Tree_Node
{

public:

	Tree_Node<Node>* father;
	p2List<Tree_Node<Node>*> sons;
	Node node_data;



	Tree_Node(const Node& _data){

		node_data = _data;

		father = NULL;
	}

	//Eliminate Sons method
	void Delete_sons(Tree_Node* node)
	{
		p2List_item<Tree_Node*>* item = sons.start;
		for (; item != NULL; item = item->next)
		{
			Tree_Node* child = item->data;

			if (node == child)
			{
				sons.del(item);
				node->father = NULL;
				break;
			}
		}

	}

	//Visit Sons Method
	void Visit_All_Sons(p2List<Tree_Node*>* list)
	{

		list->add(this);

		p2List_item<Tree_Node*>* item = sons.start;

		while (item != NULL)
		{
			Tree_Node* child = item->data;
			child->Visit_All_Sons(list);
			item = item->next;
		}
	}

	//Recursive Methods
	void TreePreOrderRecurisve(p2List<Tree_Node<Node>*>* list)
	{
		list->add(this);

		for (p2List_item<Tree_Node*>* Nodes_child = sons.start; Nodes_child != NULL; Nodes_child = Nodes_child->next)
		{
			Nodes_child->data->TreePreOrderRecurisve(list);
		}
	}

	void TreePostOrderRecurisve(p2List<Tree_Node<Node>*>* list)
	{


		for (p2List_item<Tree_Node*>* Nodes_child = sons.start; Nodes_child != NULL; Nodes_child = Nodes_child->next)
		{
			Nodes_child->data->TreePostOrderRecurisve(list);
		}

		list->add(this);
	}


	void TreeInOrderRecurisve(p2List<Tree_Node<Node>*>* list)
	{
		p2List_item<Tree_Node*>* Nodes_child = sons.start;
		unsigned int middle_num_nodes = sons.count();

		for (unsigned int num = 0; num < middle_num_nodes / 2; ++num)
		{
			Nodes_child->data->TreeInOrderRecurisve(list);
			Nodes_child = Nodes_child->next;
		}

		list->add(this);

		while (Nodes_child != NULL)
		{
			Nodes_child->data->TreeInOrderRecurisve(list);
			Nodes_child = Nodes_child->next;
		}
	}



};

template <class Node>
class Tree
{
public:

	Tree_Node<Node>* root_node;

public:

	//Constructor
	Tree() 
	{ 
		root_node = NULL;
	}


	//Destructor
	~Tree() 
	{   }

	//Recurisve Methods
	void TreePreOrderRecurisve(p2List<Tree_Node<Node>*>* list)const
	{
		root_node->TreePreOrderRecurisve(list);
	}

	void TreePostOrderRecurisve(p2List<Tree_Node<Node>*>* list)const
	{
		root_node->TreePostOrderRecurisve(list);
	}

	void TreeInOrderRecurisve(p2List<Tree_Node<Node>*>* list)const
	{
		root_node->TreeInOrderRecurisve(list);
	}

	//Iterative methods
	void TreePreOrderIterative(p2List <Tree_Node<Node>*>* list)const
	{
		Stack<Tree_Node<Node>*> stack;
		Tree_Node<Node>* node = root_node;

		while (node != NULL)
		{
			list->add(node);

			p2List_item<Tree_Node<Node>*>* Nodes_Children = node->sons.end;
			while (Nodes_Children != NULL)
			{
				stack.PushBack_stack(Nodes_Children->data);
				Nodes_Children = Nodes_Children->prev;
			}

			if (Nodes_Children != NULL)
			{
				node = Nodes_Children->data;
			}
			else
			{
				node = NULL;
			}

			stack.Pop_stack(node);
		}
	}

	void TreePostOrderIterative(p2List <Tree_Node<Node>*>* list)const
	{
		Stack<Tree_Node<Node>*> stack;
		Tree_Node<Node> *node = root_node;


		while (node != NULL || stack.Pop_stack(node))
		{
			p2List_item<Tree_Node<Node>*> *item = node->sons.end;

			if (item != NULL && list->find(item->data) == NULL)
			{
				stack.PushBack_stack(node);
				while (item != NULL)
				{
					stack.PushBack_stack(item->data);
					item = item->prev;
				}

				if (item != NULL)
				{
					node = item->data;
				}
				else
				{
					node = NULL;
				}

			}
			else
			{
				list->add(node);
				node = NULL;
			}
		}

	}

	void TreeInOrderIterative(p2List <Tree_Node<Node>*>* list)
	{
		//I don't know how I can do this method
		//I have tried but I haven't worked
		//However let the unitest of this method in the unistest

	}

	//Add Methods
	Tree_Node<Node>* AddRoot(const Node& data)
	{

		Tree_Node<Node>* newNode = new Tree_Node<Node>(data);
		if (root_node == NULL)
		{
			newNode->father = NULL;
			root_node = newNode;

		}

		else if (root_node != NULL)
		{
			root_node->sons.add(newNode);
			newNode->father = root_node;

		}

		return newNode;
	}


	Tree_Node<Node>* AddChild(const Node& data, Tree_Node<Node>* parent)
	{

		Tree_Node<Node>* newNode = new Tree_Node<Node>(data);

		if (parent == NULL && data == NULL)
		{
			return NULL;
		}

		else if (parent != NULL && data != parent->node_data)
		{
			parent->sons.add(newNode);
			newNode->father = parent;
		}

		else if (data == parent->node_data)
		{
			return NULL;
		}
		return newNode;
	}

	



	//Clear Method
	void Clear(Tree_Node<Node>* nodeToErase = NULL)
	{
		p2List<Tree_Node<Node>*> num_nodes;
		root_node->Visit_All_Sons(&num_nodes);
		Tree_Node<Node>* son;

		if (nodeToErase == NULL)
		{
			p2List_item<Tree_Node<Node>*>* item = num_nodes.start;
			for (; item != NULL; item = item->next)
			{
				son = item->data;

				if (son->father)
					son->father->Delete_sons(son);
			}
		}

		else
		{
			if (nodeToErase->father)
				nodeToErase->father->Delete_sons(nodeToErase);
		}
	}


};

#endif