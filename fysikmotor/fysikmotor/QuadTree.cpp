#include "QuadTree.h"

//functioons
void QuadTree::destroyQuadTree() //destroys quad tree, clears entities and destroys sub nodes
{
	nodes.clear();
	entities.clear();
}
void QuadTree::splitQuadTree() //splits the quadtree into four partitions/sub nodes
{
	if (entities.size() > maxEntitiesPerNode)
	{
		//attempt to split entites into sub nodes
	
		//create four sub nodes
		if (nodeLevel + 1 < maxNodeLevel)
		{
			QuadTree a(nodeLevel + 1, (minX + maxX) / 2, 0, (minY + maxY) / 2, 0), //top left node
				b(nodeLevel + 1, maxX, (minX + maxX) / 2, (minY + maxY) / 2, 0), //top right node
				c(nodeLevel + 1, (minX + maxX) / 2, 0, maxY, (minY + maxY) / 2), //bottom left node
				d(nodeLevel + 1, maxX, (minX + maxX) / 2, maxY, (minY + maxY) / 2); //bottom right node

			nodes.push_back(a);
			nodes.push_back(b);
			nodes.push_back(c);
			nodes.push_back(d);
		}

		//attempt to split entites in current node into the sub nodes created
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			int pos = getNodePos(entities[i]); //returns in what node it should be in

			if (pos != -1)
			{
				if (pos = NodePos::NW)
				{
					nodes[0].addEntity(entities[i]); //adds entiyy to node
					
				}
			}
		}
	}
}
void QuadTree::addEntity(Entity inputEntity); //adds entities to quadtree, edntity will trickle down to a designated leaf node
int QuadTree::getNodePos(const Entity& inputEntity) const; //returns in what sub node the entitiy belongs, -1 if it doesnt fit
std::vector<QuadTree>& QuadTree::getEntiesInProximity(const Entity& inputEntity); //returns all entieis that are in proximyu to colide with given entity

QuadTree::QuadTree(int inputNodeLevel, double XMax, double XMin, double YMax, double YMin)
	:
	nodeLevel(inputNodeLevel),
	maxX(XMax),
	minX(XMin),
	maxY(YMax),
	minY(YMin)
{
}
QuadTree::~QuadTree()
{
	destroyQuadTree();
}