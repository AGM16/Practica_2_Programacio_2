// ----------------------------------------------------
// Quadtree implementation --
// ----------------------------------------------------

#ifndef __P2QUADTREE_H__
#define __P2QUADTREE_H__

#include "Collider.h"
#include "p2DynArray.h"

#define QUADTREE_MAX_ITEMS 2


// Helper function to check if one rectangle complately contains another
bool Contains(const SDL_Rect& a, const SDL_Rect& b);
bool Intersects(const SDL_Rect& a, const SDL_Rect& b);

// Tree node -------------------------------------------------------
class p2QuadTreeNode
{

public:
	
	SDL_Rect                Nodes_child;
	SDL_Rect				rect;
	p2DynArray<Collider*>	objects;
	p2QuadTreeNode*			parent;
	p2QuadTreeNode*			childs[4];

public:

	p2QuadTreeNode(SDL_Rect r) : 
		rect(r),
		objects(QUADTREE_MAX_ITEMS)
	{
		parent = childs[0] = childs[1] = childs[2] = childs[3] = NULL;
		Nodes_child.h = rect.h / 2;
		Nodes_child.w = rect.w / 2;
		Nodes_child.x = rect.x;
		Nodes_child.y = rect.y;

	}

	~p2QuadTreeNode()
	{
		for(int i = 0; i < 4; ++i)
			if(childs[i] != NULL) delete childs[i];
	}
	 
	void Insert(Collider* col)
	{
		// TODO: Insertar un nou Collider al quadtree
		// En principi cada node por enmagatzemar QUADTREE_MAX_ITEMS nodes (encara que podrien ser més)
		// Si es detecten més, el node s'ha de tallar en quatre
		// Si es talla, a de redistribuir tots els seus colliders pels nous nodes (childs) sempre que pugui
		// Nota: un Collider pot estar a més de un node del quadtree
		// Nota: si un Collider intersecciona als quatre childs, deixar-lo al pare
		if (childs[0] == NULL && childs[1] == NULL && childs[2] == NULL && childs[3] == NULL)
		{
			
			if (objects.Count() >= QUADTREE_MAX_ITEMS)
			{
				
				childs[0] = new p2QuadTreeNode(Nodes_child);
				Nodes_child.x += Nodes_child.w;
				childs[1] = new p2QuadTreeNode(Nodes_child);
				Nodes_child.y += Nodes_child.h;
				Nodes_child.x -= Nodes_child.w;
				childs[2] = new p2QuadTreeNode(Nodes_child);
				Nodes_child.x += Nodes_child.w;
				childs[3] = new p2QuadTreeNode(Nodes_child);

				for (int a = 0; a < 4; a++)
				{
					childs[a]->parent = this;
				}

				p2DynArray<Collider*> Copy_Colliders = objects;

				objects.Clear();

				for (int i = 0; i < Copy_Colliders.Count(); i++)
				{
					Insert(Copy_Colliders[i]);
				}
				
			}
			
			else
			{
				objects.PushBack(col);
				
			}
		}
		
		if (childs[0] != NULL && childs[1] != NULL && childs[2] != NULL && childs[3] != NULL)
		{
			if (Intersects(childs[0]->rect, col->rect) == true && Intersects(childs[1]->rect, col->rect) == true && Intersects(childs[2]->rect, col->rect) == true && Intersects(childs[3]->rect, col->rect) == true)
			{
				objects.PushBack(col);
				return;
			}

			else{

				for (int n = 0; n < 4; n++)
				{
					if (Intersects(childs[n]->rect, col->rect) == true)
					{
						childs[n]->Insert(col);
					}
				}
			}
		}
			  
		
	}


	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		// TODO:
		// Omplir el array "nodes" amb tots els colliders candidats
		// de fer intersecció amb el rectangle r
		// retornar el número de intersección calculades en el procés
		// Nota: és una funció recursiva
		int num_intersections = 0; 
		int num_nodes_colliders = objects.Count();
		for (int n = 0; n < num_nodes_colliders; n++, num_intersections++)
		{
			nodes.PushBack(objects[n]);

		}
		if (childs[0] != NULL && childs[1] != NULL && childs[2] != NULL && childs[3] != NULL)
		{
			for (int n = 0; n < 4; n++)
			{
				if (Intersects(childs[n]->rect, rect))
				{
					num_intersections = num_intersections + childs[n]->CollectCandidates(nodes, rect);
				}

			}
		}
		return num_intersections;
	}


	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes) 
	{
		nodes.PushBack(this);

		for(int i = 0; i < 4; ++i)
			if(childs[i] != NULL) childs[i]->CollectRects(nodes);
	}


};

// Tree class -------------------------------------------------------
class p2QuadTree
{
public:

	// Constructor
	p2QuadTree() : root(NULL)
	{}

	// Destructor
	virtual ~p2QuadTree()
	{
		Clear();
	}

	void SetBoundaries(const SDL_Rect& r)
	{
		if(root != NULL)
			delete root;

		root = new p2QuadTreeNode(r);
	}

	void Insert(Collider* col)
	{
		if(root != NULL)
		{
			if(Intersects(root->rect, col->rect))
				root->Insert(col);
		}
	}

	void Clear()
	{
		if(root != NULL)
		{
			delete root;
			root = NULL;
		}
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		int tests = 1;
		if(root != NULL && Intersects(root->rect, r))
			tests = root->CollectCandidates(nodes, r);
		return tests;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes) const
	{
		if(root != NULL)
			root->CollectRects(nodes);
	}

public:

	p2QuadTreeNode*	root;

};

#endif // __p2QuadTree_H__