I have a BST, and I have to make it into a two-way linked list on pre-order base. The function should change the pointers of each node in the tree so that the left pointer points to the previous member in the list, and the right pointer points to the next one. (The previous(left) of the root is NULL; likewise next of the last node(right) is NULL.)
I should return the head of the created DLL to print the list.

Obstacles: You can not use auxiliary functions and you have to change the pointers of the tree itself and not create a new list.
The implementation is in C.  


          4                               
        /   \       
       2      6    ---------> output of DLL: 4<->2<->1<->3<->6<->5<->7.         
     /  \     / \                         
    1    3   5   7       
                 


Here is my code; I hope someone would help me here.

    Node* converToPreOrder(Node* root)
    {
    	if (root == NULL) return root;
    		
    	static Node* head = NULL; 
    	static Node* prev = NULL; 
    	Node* temp = root;
    
    	if (prev == NULL) 
    		head = root;
    
    	if (root->right != NULL && root->left != NULL)
    		prev = root;
    
    	else
    	{
    		prev->right = root;
    		temp->left = prev;
    	}
    
    	converToPreOrder(root->left);
    	converToPreOrder(root->right);
    
    	return head;
    }

