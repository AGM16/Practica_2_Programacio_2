#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Practica Quadtree/p2DynArray.h"
#include "../Practica Quadtree/p2List.h"
#include "../Practica Quadtree/Stack.h"
#include "../Practica Quadtree/Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		

		//-----------------------------------------------

		//CLASS TREE

		//-----------------------------------------------

		/*
		             -------Tree-------

		                     A
		               ______________
		              |      |       |
		              B      C       D
		                   __|__     |
		                  |     |    H
		                  E     F    |
		                       _|_   J
		                      |   |
		                      G   H
		*/

		//-------------------------------------------------
		//Method Add

		TEST_METHOD(TreeAddRootNode_And_childs_of_rootnode)
		{

			Tree<char> tree;
			Tree_Node<char>* father_1;

			//Rootnode
			father_1 = tree.AddRoot('A');

			//First sons of Rootnode
			tree.AddRoot('B');
			tree.AddRoot('C');
			tree.AddRoot('D');

			p2List<Tree_Node<char>*> list;

			tree.root_node->Visit_All_Sons(&list);

			//Rootnode
			Assert::AreEqual((char)list[0]->node_data, 'A');
			Assert::AreEqual((char)list[1]->node_data, 'B');
			Assert::AreEqual((char)list[2]->node_data, 'C');
			Assert::AreEqual((char)list[3]->node_data, 'D');

			//If I eliminate the childs only rest the rootnode
			tree.Clear();
			p2List<Tree_Node<char>*> list_2;
			tree.root_node->Visit_All_Sons(&list_2);

			Assert::AreEqual((int)list_2.count(), 1);

		}

		TEST_METHOD(TreeAdd_child)
		{

			Tree<char> tree;
			Tree_Node<char>* father_1;

			//Rootnode
			father_1 = tree.AddRoot('A');

			//Sons of Rootnode
			father_1 = tree.AddChild('D', father_1);
			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			p2List<Tree_Node<char>*> list;

			tree.root_node->Visit_All_Sons(&list);

			//Rootnode
			Assert::AreEqual((char)list[0]->node_data, 'A');
			Assert::AreEqual((char)list[1]->node_data, 'D');
			Assert::AreEqual((char)list[2]->node_data, 'I');
			Assert::AreEqual((char)list[3]->node_data, 'J');

		}


		//--------------------------------------------------
		//Recursive Methods

		TEST_METHOD(TreePreOrderRecursive)
		{

			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);


			p2List<Tree_Node<char>*> list;

			tree.TreePreOrderRecurisve(&list);



			Assert::AreEqual((char)list[0]->node_data, 'A');
			Assert::AreEqual((char)list[1]->node_data, 'B');
			Assert::AreEqual((char)list[2]->node_data, 'C');
			Assert::AreEqual((char)list[3]->node_data, 'E');
			Assert::AreEqual((char)list[4]->node_data, 'F');
			Assert::AreEqual((char)list[5]->node_data, 'G');
			Assert::AreEqual((char)list[6]->node_data, 'H');
			Assert::AreEqual((char)list[7]->node_data, 'D');
			Assert::AreEqual((char)list[8]->node_data, 'I');
			Assert::AreEqual((char)list[9]->node_data, 'J');


		}

		TEST_METHOD(TreePostOrderRecursive)
		{
			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			p2List<Tree_Node<char>*> list;

			tree.TreePostOrderRecurisve(&list);


			Assert::AreEqual((char)list[0]->node_data, 'B');
			Assert::AreEqual((char)list[1]->node_data, 'E');
			Assert::AreEqual((char)list[2]->node_data, 'G');
			Assert::AreEqual((char)list[3]->node_data, 'H');
			Assert::AreEqual((char)list[4]->node_data, 'F');
			Assert::AreEqual((char)list[5]->node_data, 'C');
			Assert::AreEqual((char)list[6]->node_data, 'J');
			Assert::AreEqual((char)list[7]->node_data, 'I');
			Assert::AreEqual((char)list[8]->node_data, 'D');
			Assert::AreEqual((char)list[9]->node_data, 'A');



		}

		TEST_METHOD(TreeInOrderRecursive)
		{
			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			p2List<Tree_Node<char>*> list;

			tree.TreeInOrderRecurisve(&list);


			Assert::AreEqual((char)list[0]->node_data, 'B');
			Assert::AreEqual((char)list[1]->node_data, 'A');
			Assert::AreEqual((char)list[2]->node_data, 'E');
			Assert::AreEqual((char)list[3]->node_data, 'C');
			Assert::AreEqual((char)list[4]->node_data, 'G');
			Assert::AreEqual((char)list[5]->node_data, 'F');
			Assert::AreEqual((char)list[6]->node_data, 'H');
			Assert::AreEqual((char)list[7]->node_data, 'D');
			Assert::AreEqual((char)list[8]->node_data, 'I');
			Assert::AreEqual((char)list[9]->node_data, 'J');

		}



		//--------------------------------------------------
		//Iteartive Methods

		TEST_METHOD(TreePreOrderIterative)
		{

			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			p2List<Tree_Node<char>*> list;

			tree.TreePreOrderIterative(&list);

			Assert::AreEqual((char)list[0]->node_data, 'A');
			Assert::AreEqual((char)list[1]->node_data, 'B');
			Assert::AreEqual((char)list[2]->node_data, 'C');
			Assert::AreEqual((char)list[3]->node_data, 'E');
			Assert::AreEqual((char)list[4]->node_data, 'F');
			Assert::AreEqual((char)list[5]->node_data, 'G');
			Assert::AreEqual((char)list[6]->node_data, 'H');
			Assert::AreEqual((char)list[7]->node_data, 'D');
			Assert::AreEqual((char)list[8]->node_data, 'I');
			Assert::AreEqual((char)list[9]->node_data, 'J');


		}

		TEST_METHOD(TreePostOrderIterative)
		{

			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			p2List<Tree_Node<char>*> list;

			tree.TreePostOrderIterative(&list);


			Assert::AreEqual((char)list[0]->node_data, 'B');
			Assert::AreEqual((char)list[1]->node_data, 'E');
			Assert::AreEqual((char)list[2]->node_data, 'G');
			Assert::AreEqual((char)list[3]->node_data, 'H');
			Assert::AreEqual((char)list[4]->node_data, 'F');
			Assert::AreEqual((char)list[5]->node_data, 'C');
			Assert::AreEqual((char)list[6]->node_data, 'J');
			Assert::AreEqual((char)list[7]->node_data, 'I');
			Assert::AreEqual((char)list[8]->node_data, 'D');
			Assert::AreEqual((char)list[9]->node_data, 'A');


		}

		/*TEST_METHOD(TreeInOrderIterative)
		{
		Tree<char> tree;
		Tree_Node<char>* father_1;
		Tree_Node<char>* father_2;

		father_1 = tree.Add_root('A');

		tree.Add_root('B');

		father_2 = tree.Add('C', father_1);

		father_1 = tree.Add('D', father_1);

		tree.Add('E', father_2);
		father_2 = tree.Add('F', father_2);
		tree.Add('G', father_2);
		tree.Add('H', father_2);

		father_1 = tree.Add('I', father_1);
		tree.Add('J', father_1);

		p2List<Tree_Node<char>*> list;

		Arbolito.TreeInOrderIterative(&list);


		Assert::AreEqual((char)list[0]->node_data, 'B');
		Assert::AreEqual((char)list[1]->node_data, 'A');
		Assert::AreEqual((char)list[2]->node_data, 'E');
		Assert::AreEqual((char)list[3]->node_data, 'C');
		Assert::AreEqual((char)list[4]->node_data, 'G');
		Assert::AreEqual((char)list[5]->node_data, 'F');
		Assert::AreEqual((char)list[6]->node_data, 'H');
		Assert::AreEqual((char)list[7]->node_data, 'D');
		Assert::AreEqual((char)list[8]->node_data, 'I');
		Assert::AreEqual((char)list[9]->node_data, 'J');

		}*/


		//--------------------------------------------------
		//Clear Method

		TEST_METHOD(TreeClearFromANode)
		{
			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;
			Tree_Node<char>* father_delete;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);
			father_delete = father_1;

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			tree.Clear(father_delete);

			p2List<Tree_Node<char>*> list;
			tree.root_node->Visit_All_Sons(&list);

			Assert::AreEqual((int)list.count(), 7);
			Assert::AreEqual((char)list[0]->node_data, 'A');
			Assert::AreEqual((char)list[1]->node_data, 'B');
			Assert::AreEqual((char)list[2]->node_data, 'C');
			Assert::AreEqual((char)list[3]->node_data, 'E');
			Assert::AreEqual((char)list[4]->node_data, 'F');
			Assert::AreEqual((char)list[5]->node_data, 'G');
			Assert::AreEqual((char)list[6]->node_data, 'H');
		}


		TEST_METHOD(TreeClearAll)
		{

			Tree<char> tree;
			Tree_Node<char>* father_1;
			Tree_Node<char>* father_2;
			Tree_Node<char>* father_delete;

			father_1 = tree.AddRoot('A');

			tree.AddRoot('B');

			father_2 = tree.AddChild('C', father_1);

			father_1 = tree.AddChild('D', father_1);
			father_delete = father_1;

			tree.AddChild('E', father_2);
			father_2 = tree.AddChild('F', father_2);
			tree.AddChild('G', father_2);
			tree.AddChild('H', father_2);

			father_1 = tree.AddChild('I', father_1);
			tree.AddChild('J', father_1);

			tree.Clear();

			p2List<Tree_Node<char>*> list;
			tree.root_node->Visit_All_Sons(&list);
			
			Assert::AreEqual((int)list.count(), 1);
			
		}

	};
}