#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _node;
typedef struct _node Positon;
typedef struct _node {
	int value;
	Position left;
	Position right;
} Node;


int inorder(Position root) {
	if (root) {
		inorder(root->left);
		printf("%d", root->value);
		inorder(root->right);
	}
	return EXIT_SUCCESS;
}

int preorder(Position root) {
	if (root) {
		printf("%d", root->value);
		preorder(root->left);
		preorder(root->right);
	}
	return EXIT_SUCCESS;
}

int postorder(Position root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d", root->value);

	}
	return EXIT_SUCCESS;
}
Position search(Position root, int value) {
	if (root == NULL || root->value == value)
		return root;
	if (value < root->value)
		return search(root->left, value);
	return search(root->right, value);
}

Position deleteNode(Position root, int value) {
	if (root == NULL)
		return root;

	if(value < root->value)
		root->
}