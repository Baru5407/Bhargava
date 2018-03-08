#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int data;
	Node *left, *right;
};

// Prints level order traversal line by line
// using two queues.
void levelOrder(Node *root)
{
	queue<Node *> q1, q2;

	if (root == NULL)
		return;

	// Pushing first level node into first queue
	q1.push(root);

	// Executing loop till both the queues
	// become empty
	while (!q1.empty() || !q2.empty())
	{
		while (!q1.empty())
		{
			// Pushing left child of current node in
			// first queue into second queue
			if (q1.front()->left != NULL)
				q2.push(q1.front()->left);

			// pushing right child of current node
			// in first queue into second queue
			if (q1.front()->right != NULL)
				q2.push(q1.front()->right);

			cout << q1.front()->data << " ";
			q1.pop();
		}

		cout << "\n";

		while (!q2.empty())
		{
			// pushing left child of current node
			// in second queue into first queue
			if (q2.front()->left != NULL)
				q1.push(q2.front()->left);

			// pushing right child of current
			// node in second queue into first queue
			if (q2.front()->right != NULL)
				q1.push(q2.front()->right);

			cout << q2.front()->data << " ";
			q2.pop();
		}

		cout << "\n";
	}
}

// Utility function to create a new tree node
Node* newNode(int data)
{
	Node *temp = new Node;
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

// Driver program to test above functions
int main()
{
	Node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->right = newNode(6);

	levelOrder(root);
	return 0;
}
