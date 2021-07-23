#include"tree.h"
#include<map>



bool color(Node* n);


class rbt :
	Tree {
	void Insert(Node* current, Node* newNode);
	void InOrderLNR(Node* current);
	void InOrderRNL(Node* current);
	void PreOrderNLR(Node* current);
	void PreOrderNRL(Node* current);
	void PostOrderLRN(Node* current);
	void PostOrderRLN(Node* current);
	bool Search(Node* current, int val);
	Node* findParent(Node* current, Node* child);
	Node* findMax(Node* n);
	void fix(Node* child, Node* parent, Node* rootNode);
	void rotationLL(Node* parent, Node* grandParent);
	void recolor(Node* n);
	void rotationRL(Node* child, Node* parent);
	void rotationLR(Node* child, Node* parent);
	void rotationRR(Node* parent, Node* grandParent);
	void removeBB(Node* doubleBlack, Node* parent);
	void removeBBCase6(Node* doubleBlack, Node* parent);
	bool Remove(int val, Node* current);
	void searchDuplicateAndDelete(Node* current, map<int,int>& freq);
	void Destroy(Node* current);
public:

	void printRootNode()
	{
		cout << rootNode->val << " " << rootNode->color << endl;
		cout << "right " << rootNode->right->val << " " << rootNode->right->color << endl;
		cout << "left " << rootNode->left->val << " " << rootNode->left->color << endl;
	}
	rbt() {
		rootNode = nullptr;
	}

	void insert(int data)
	{
		Node* newNode = new Node;
		newNode->val = data;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->color = false;

		if (rootNode == nullptr)
		{
			rootNode = newNode;
			rootNode->color = true;
		}
		else
		{
			Insert(rootNode, newNode);
		}

	}
	

	void inOrderLNR()
	{
		InOrderLNR(rootNode);
	}
	void inOrderRNL()
	{
		InOrderRNL(rootNode);
	}


	void deleteDuplicated()
	{
		map<int, int> freq;

		searchDuplicateAndDelete(rootNode, freq);

		for (auto i : freq)
		{
			for (int j = 0; j < i.second - 1; j++)
			{
				remove(i.first);
			}
		}
	}

	void preOrderNLR()
	{
		PreOrderNLR(rootNode);
	}
	void preOderNRL()
	{
		PreOrderNRL(rootNode);
	}

	void postOrderLRN()
	{
		PostOrderLRN(rootNode);
	}
	void postOrderRLN()
	{
		PostOrderRLN(rootNode);
	}

	bool search(int val)
	{
		return Search(rootNode, val);
	}

	bool remove(int val)
	{
		return Remove(val, rootNode);
	}
	void printParent(int val)
	{
		Node* current = rootNode;

		if (val == rootNode->val)
		{
			cout << "Rootnode does not have any parent" << endl;
			return;
		}

		if (rootNode->val != val && search(val))
		{
			while (true)
			{
				if (val == current->val)
				{
					cout << "Parent of "<< current->val<<" is "<< findParent(rootNode, current)->val << endl;
					break;
				}

				if (val < current->val)
					current = current->left;
				else
					current = current->right;
			}
		}
			
	}

	void destroyTree()
	{
		Destroy(rootNode);
	}

};

void rbt::Destroy(Node* current)
{
	if (current != nullptr)
	{
		Destroy(current->left);
		Destroy(current->right);

		//DELETING WHILE EXITING FROM NODE
		delete current;
		rootNode = nullptr;
	}
}
void rbt::searchDuplicateAndDelete(Node* current, map<int, int>& freq)
{
	
	if (current != nullptr)
	{
		//INCRASING FREQUENCY AGAINST VALUES
		freq[current->val] = freq[current->val]++;

		searchDuplicateAndDelete(current->left,freq);
		searchDuplicateAndDelete(current->right, freq);

	}
}
bool rbt::Remove(int val,Node* current)
{
	Node* parent; 
	
	if (current != rootNode)
		parent = findParent(rootNode, current);
	else
		parent = rootNode;

	Node* child = current;

	while (true)
	{
		//IF VALUE IS SMALL MOVING LEFT
		if (val < child->val)
		{
			parent = child;
			child = child->left;
		}//MOVING RIGHT IN CASE BIGGER VALUE
		else if(val > child->val)
		{
			parent = child;
			child = child->right;
		}

		//IF WE FOUND THE NODE TO BE DELETED
		if (val == child->val)
		{
			//leaf node
			if (child->left == nullptr && child->right == nullptr)
			{
				//if leaf node is red SIMPLY DELETING
				if (!child->color)
				{
					delete child;
					if (val <= parent->val)
						parent->left = nullptr;
					else
						parent->right = nullptr;
					child = nullptr;
					return true;
				}  //if leaf node if black
				else
				{	//BLACK LEAF NODE
					delete child;
					if (val <= parent->val)
						parent->left = nullptr;
					else
						parent->right = nullptr;
					child = nullptr;
					//FIXING DOUBLE BLACK ISSUE
					removeBB(child, parent);
					return true;
				}
			}
			else if(child == nullptr)
				break;	
			else if (child->left == nullptr || child->right == nullptr)		//IF NODE IS WITH ONE CHILD
			{
				//CHECKING WHICH SIDE HAVE CHILD
				if (child->left != nullptr)
				{
					if (val < parent->val)
					{
						parent->left = child->left;
						
					}
					else
					{
						parent->right = child->left;
						
					}
					// IF PARENT OR CHILD HAVE 1 BLACK AND 1 RED. PRESISTING BLACK COLOR
					if ((child->color && !child->left->color) || (!child->color && child->left->color))
						child->left->color = true;
					else  //IF CHILD OF BLACK NODE IS ALSO BLACK
					{
						if (parent->left == child->left)
						{
							removeBB(parent->left, parent);
						}
						else
						{
							removeBB(parent->right, parent);
						}
					}
				}
				else
				{
					if (val < parent->val)
					{
						parent->left = child->right;

					}
					else
					{
						parent->right = child->right;

					}
					if ((child->color && !child->right->color) || (!child->color && child->right->color))
						child->right->color = true;
					else
					{
						if (parent->left == child->right)
						{
							removeBB(parent->left, parent);
						}
						else
						{
							removeBB(parent->right, parent);
						}
					}
				}


				delete child;
				child = nullptr;
				return true;

			}
			else if(child->left != nullptr && child->right != nullptr)   //NODE HAVING BOTH CHILD
			{													//NOT DELETING THIS NODE JUST REPLACING VALUES AND CALLING FUNCTION AGAIN TO DELETED OTHER NODE WHOSE VALUE IS REPLACED
			
					Node* max = findMax(child->left);
					int temp = max->val;
					Remove(max->val, child->left);
					child->val = temp;
					return true;
	

			}
		}
	}
	return false;
}
void rbt::removeBB(Node* doubleBlack, Node* parent)
{
	Node* grandParent = nullptr;
	Node* temp;

	if (doubleBlack == rootNode)
		return;
	//to check siblling is right child
	if (doubleBlack == parent->left)
	{
		//checking if siblings and its childs is black
		if (color(parent->right) && color(parent->right->left) && color(parent->right->right))
		{   
			if (parent->color)
			{
				//shifting double black to its parent if its not rootNode
				if (parent != rootNode)
				{
					grandParent = findParent(rootNode, parent);
					removeBB(parent, grandParent);
				}
				parent->right->color = false;
			}
			else
			{
				parent->color = true;
				parent->right->color = false;
			}
		}
		else if (!color(parent->right))
		{
			parent->right->color = true;
			parent->color = false;

			if (parent != rootNode)
				grandParent = findParent(rootNode, parent);


			if (parent == grandParent->right)
			{
				grandParent->right = parent->right;
				temp = parent->right->left;
				grandParent->right->left = parent;
				parent->right = temp;

			}
			else // when parent is its left child
			{
				grandParent->left = parent->right;
				temp = parent->right->left;
				grandParent->left->left = parent;
				parent->right = temp;
			}

			//
			removeBB(parent->left, parent);
		}
		else if (color(parent->right) && !color(parent->right->right))
			removeBBCase6(parent->left, parent);
		else if (color(parent->right) && color(parent->right->right) && !color(parent->right->left))
		{
			parent->right->color = false;
			parent->right->left->color = true;

			temp = parent->right;
			parent->right = parent->right->left;
			temp->left = parent->right->right;
			parent->right->right = temp;

			removeBBCase6(parent->left, parent);
		}
		
	}
	else
	 {
		//checking if siblings and its childs is black
		if (color(parent->left) && color(parent->left->left) && color(parent->left->right))
		{
			if (parent->color)
			{
				if (parent != rootNode)
				{
					grandParent = findParent(rootNode, parent);
					removeBB(parent, grandParent);
				}
				parent->left->color = false;
			}
			else
			{
				parent->color = true;
				parent->left->color = false;
			}
		}
		else if (!color(parent->left))
		{
			parent->left->color = true;
			parent->color = false;

			if (parent != rootNode)
				grandParent = findParent(rootNode, parent);

			if (parent == grandParent->right)
			{
				grandParent->right = parent->left;
				temp = parent->left->right;
				grandParent->right->right = parent;
				parent->left = temp;

			}
			else // when parent is its left child
			{
				grandParent->left = parent->left;
				temp = parent->left->right;
				grandParent->left->right = parent;
				parent->left = temp;
			}

			removeBB(parent->right, parent);
		}
		else if (color(parent->left) && !color(parent->left->left))
			removeBBCase6(parent->right, parent);
		else if (color(parent->left) && color(parent->left->left) && !color(parent->left->right))
		{
			parent->left->color = false;
			parent->left->right->color = true;

			temp = parent->left;
			parent->left = parent->left->right;
			temp->right = parent->left->left;
			parent->left->left = temp;

			removeBBCase6(parent->right, parent);
		}
	}
}

void rbt::removeBBCase6(Node* doubleBlack, Node* parent)
{
	bool tempColor;
	Node* temp = nullptr;
	Node* grandParent = nullptr;

	if (doubleBlack == parent->left)
	{

		parent->right->right->color = true;

		tempColor = parent->color;
		parent->color = parent->right->color;
		parent->right->color = tempColor;

		if (parent != rootNode)
		{
			grandParent = findParent(rootNode, parent);

			if (parent == grandParent->right)
			{
				grandParent->right = parent->right;
				parent->right = grandParent->right->left;
				grandParent->right->left = parent;
			}
			else
			{
				grandParent->left = parent->right;
				parent->right = grandParent->left->left;
				grandParent->left->left = parent;
			}
		}
		else
		{
			temp = rootNode;
			rootNode = rootNode->right;
			temp->right = rootNode->left;
			rootNode->left = temp;
		}

	}
	else
	{

		parent->left->left->color = true;

		tempColor = parent->color;
		parent->color = parent->left->color;
		parent->left->color = tempColor;

		if (parent != rootNode)
		{
			grandParent = findParent(rootNode, parent);

			if (parent == grandParent->right)
			{
				grandParent->right = parent->left;
				parent->left = grandParent->right->right;
				grandParent->right->right = parent;
			}
			else
			{
				grandParent->left = parent->left;
				parent->left = grandParent->left->right;
				grandParent->left->right = parent;
			}
		}
		else
		{
			temp = rootNode;
			rootNode = rootNode->left;
			temp->left = rootNode->right;
			rootNode->right = temp;
		}
	}
}
bool color(Node* n)
{
	if (n != nullptr)
		if (!n->color)
			return false;
		else
			return true;
	else
		return true;
}
Node* rbt::findMax(Node* n)
{
	if (n->right == nullptr)
		return n;
	else
		findMax(n->right);
}
void rbt::Insert(Node* current, Node* newNode)
{
	Node* parent;
	Node* grandParent;

	while (1)
	{
		if (newNode->val < current->val)
		{
			if (current->left == nullptr)
			{
				current->left = newNode;
				break;
			}

			else
				current = current->left;
		}
		else
		{
			if (current->right == nullptr)
			{
				current->right = newNode;
				break;
			}
			else
				current = current->right;
		}
	}


	if (current != rootNode)
		fix(newNode, current, rootNode);




}
void rbt::fix(Node* child, Node* parent, Node* rootNode)
{
	Node* grandParent = findParent(rootNode, parent);
	if (!child->color && !parent->color)
	{

		if (grandParent->right == parent)
		{
			if (grandParent->left != nullptr)
			{
				if (grandParent->left->color == false)
				{
					recolor(grandParent->left);
					recolor(grandParent->right);
					if (grandParent != rootNode)
						recolor(grandParent);
				}
				else
				{
					if (child == parent->right)
						rotationLL(parent, grandParent);
					else
						rotationRL(child, parent);
				}
			}
			else
			{
				if (child == parent->right)
					rotationLL(parent, grandParent);
				else
					rotationRL(child, parent);
			}
		}
		else
		{
			if (grandParent->right != nullptr)
			{
				if (grandParent->right->color == false)
				{
					recolor(grandParent->left);
					recolor(grandParent->right);
					if (grandParent != rootNode)
						recolor(grandParent);
				}
				else
				{
					if (child == parent->left)
						rotationRR(parent, grandParent);
					else
						rotationLR(child, parent);
				}
			}
			else
			{
				if (child == parent->left)
					rotationRR(parent, grandParent);
				else
					rotationLR(child, parent);
			}
		}
	}

	Node* parentOfGrandParent;
	
	if (grandParent != rootNode)
	{
		parentOfGrandParent = findParent(rootNode, grandParent);

		if (!grandParent->color && !parentOfGrandParent->color)
			fix(grandParent, parentOfGrandParent, rootNode);
	}

}

void rbt::rotationRR(Node* parent, Node* grandParent)
{
	Node* parentOfGrandParent = nullptr;

	if (grandParent != rootNode)
		parentOfGrandParent = findParent(rootNode, grandParent);

	Node* temp;

	//if grand parent is rootnode than we dont need its parent
	if (grandParent != rootNode)
	{
		if (parentOfGrandParent->right == grandParent)
		{
			parentOfGrandParent->right = parent;
			temp = parent->right;
			parent->right = grandParent;
			grandParent->left = temp;

			recolor(parent);
			recolor(grandParent);
		}
		else
		{

			parentOfGrandParent->left = parent;
			temp = parent->right;
			parent->right = grandParent;
			grandParent->left = temp;

			recolor(parent);
			recolor(grandParent);
		}
	}
	else
	{
		rootNode = parent;
		temp = rootNode->right;
		rootNode->right = grandParent;
		grandParent->left = temp;

		if (!rootNode->color)
			recolor(rootNode);

		recolor(grandParent);
	}

}
void rbt::rotationLL(Node* parent, Node* grandParent)
{
	Node* parentOfGrandParent= nullptr;
	Node* temp;

	if (grandParent != rootNode)
		parentOfGrandParent= findParent(rootNode, grandParent);
	if (grandParent == rootNode)
	{
		rootNode = grandParent->right;
		temp = rootNode->left;
		rootNode->left = grandParent;
		rootNode->left->right = temp;

		if (!rootNode->color)
			recolor(rootNode);
		recolor(rootNode->left);
	}
	else
	{
		if (parentOfGrandParent->right == grandParent)
		{
			temp = parentOfGrandParent->right;

			parentOfGrandParent->right = parent;
			temp->right = parent->left;
			parent->left = temp;
		}
		else
		{
			temp = parentOfGrandParent->left;

			parentOfGrandParent->left = parent;
			temp->right = parent->left;
			parent->left = temp;
		}
		recolor(parent);
		recolor(grandParent);
	}



}
void rbt::rotationRL(Node* child, Node* parent)
{
	Node* grandParent = findParent(rootNode, parent);

	Node* temp;

	grandParent->right = child;
	temp = child->right;
	child->right = parent;
	parent->left = temp;

	Node* parentOfGrandParent = nullptr;
	

	if (grandParent != rootNode)
		parentOfGrandParent = findParent(rootNode, grandParent);


	if (grandParent != rootNode)
	{
		if (parentOfGrandParent->right == grandParent)
		{
			parentOfGrandParent->right = child;
			temp = child->left;
			child->left = grandParent;
			grandParent->right = temp;
		}
		else
		{
			parentOfGrandParent->left = child;
			temp = child->left;
			child->left = grandParent;
			grandParent->right = temp;
		}

		recolor(child->left);
		recolor(child);

		if (parentOfGrandParent->color && grandParent->color)
			fix(grandParent, parentOfGrandParent, rootNode);
	}
	else
	{
		temp = child->left;
		rootNode = child;
		child->left = grandParent;
		grandParent->right = temp;

		if (!child->color)
			recolor(child);
		recolor(grandParent);
	}
	

}
void rbt::rotationLR(Node* child, Node* parent)
{
	Node* grandParent = findParent(rootNode, parent);
	Node* temp;

	grandParent->left = child;
	parent->right = child->left;
	child->left = parent;

	Node* parentOfGrandParent = nullptr; 

	if (grandParent != rootNode)
		parentOfGrandParent = findParent(rootNode, grandParent);

	if (grandParent != rootNode)
	{
		if (parentOfGrandParent->left == grandParent)
		{
			parentOfGrandParent->left = child;
			temp = child->right;
			child->right = grandParent;
			grandParent->left = temp;
		}
		else
		{
			parentOfGrandParent->right = child;
			temp = child->right;
			child->right = grandParent;
			grandParent->left = temp;
		}
		recolor(grandParent);
		recolor(child);
	}
	else
	{
		rootNode = child;
		temp = rootNode->right;
		rootNode->right = grandParent;
		grandParent->left = temp;

		recolor(grandParent);
		
		if (!child->color)
			recolor(child);
	}

}

void rbt::recolor(Node* n)
{
	if (!n->color)
		n->color = true;
	else
		n->color = false;
}
void rbt::InOrderLNR(Node* current)
{
	if (current != nullptr)
	{
		InOrderLNR(current->left);
		cout << current->val << "  ";
		if (!current->color)
			cout << "Red" << endl;
		else
			cout << "Black" << endl;

		InOrderLNR(current->right);
	}
}
void rbt::InOrderRNL(Node* current)
{
	if (current != nullptr)
	{
		InOrderRNL(current->right);
		cout << current->val << "  ";
		if (!current->color)
			cout << "Red" << endl;
		else
			cout << "Black" << endl;
		InOrderRNL(current->left);
	}
}

void rbt::PreOrderNLR(Node* current)
{
	if (current != nullptr)
	{
		cout << current->val << "  ";
		if (!current->color)
			cout << "Red" << endl;
		else
			cout << "Black" << endl;
		PreOrderNLR(current->left);
		PreOrderNLR(current->right);
	}
}
void rbt::PreOrderNRL(Node* current)
{
	if (current != nullptr)
	{
		cout << current->val << "  ";
		if (!current->color)
			cout << "Red" << endl;
		else
			cout << "Black" << endl;
		PreOrderNRL(current->right);
		PreOrderNRL(current->left);
	}
}

void rbt::PostOrderLRN(Node* current)
{
	if (current != nullptr)
	{
		PostOrderLRN(current->left);
		PostOrderLRN(current->right);
		cout << current->val << "  ";
		if (!current->color)
			cout << "Red" << endl;
		else
			cout << "Black" << endl;
	}
}
void rbt::PostOrderRLN(Node* current)
{
	if (current != nullptr)
	{
		PostOrderRLN(current->right);
		PostOrderRLN(current->left);
		cout << current->val << "  ";
		if (!current->color)
			cout << "Red" << endl;
		else
			cout << "Black" << endl;
	}
}

bool rbt::Search(Node* current, int val)
{
	if (current != nullptr)
	{
		if (val == current->val)
			return true;
		else if (val < current->val)
			return Search(current->left, val);
		else
			return Search(current->right, val);
	}
	else
	{
		return false;
	}
}

Node* rbt::findParent(Node* current,Node* child)
{
	
	while (true)
	{
		if (current->left == child || current->right == child)
			return current;

		if (child->val < current->val)
			current = current->left;
		else
			current = current->right;	
	}

}

