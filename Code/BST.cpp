
///initializing the tree
template<class K, class V>
BST<K, V>::BST(){
	root = NULL;
}

///the tree is deleted
template<class K, class V>
BST<K, V>::~BST(){
	if(root) delete root;
}

///if the key exists return edit the value if not insert it to my tree
template<class K, class V>
void BST<K, V>::set(K key, V val){
	if(containsKey(key)) edit(key, val, root); ///if the key exists edit it's value
	else set(key, val, root); ///if not create new node with that value
}

///insert new node to my tree
template<class K, class V>
void BST<K, V>::insert(K key, V val){
	if(containsKey(key)) throw string("Exception: key already exists"); ///if the node exists throw exception
	set(key, val, root); ///if doesn't exist set it
}

///modify the value of an existing key
template<class K, class V>
void BST<K, V>::modify(K key, V val){
	if(!containsKey(key)) throw string("Exception: key does not exist"); ///throws exception if the key doesn't exist
	edit(key, val, root); ///edit the value of this key
}

///take the key and return the value
template<class K, class V>
V BST<K, V>::get(K key){
	if(!containsKey(key)) throw string("Exception: key does not exist"); ///throws exception if the key doesn't exist
	return get(key, root);///return the value of the key
}

///remove a node from my tree if it exists
template<class K, class V>
void BST<K, V>::remove(K key){
	if(!containsKey(key)) throw string("Exception: key does not exist");///throws exception if the key doesn't exist
	remove(key, root);///remove the existing key
}

///check if the key is existing
template<class K, class V>
bool BST<K, V>::containsKey(K key){
	return containsKey(key, root);
}

///prints my tree
template<class K, class V>
void BST<K, V>::display(){
	if(root == NULL) cout << "<BST is empty>";
	display(root);
	cout << endl;
}

//===================[Real work starts from here]===================


///insert the new node to my tree
template<class K, class V>
void BST<K, V>::set(K key, V value, Node *&my_root){
	if(my_root == NULL){
		my_root = new Node(key, value); ///making a new node with the key and value when it reaches the right position to insert it
	}else if(key > my_root->key){
	    ///if the key is bigger than the key of my_root insert new node to the right subtree
		set(key, value, my_root->right);
	}else{
	    ///else the key is smaller than the key of my_root insert new node to the left subtree
		set(key, value, my_root->left);
	}
 ///every insert you do balance from the inserted node
	balance(my_root);
}


///edit the value of a key
template<class K, class V>
void BST<K, V>::edit(K key, V value, Node* my_root){
	if(my_root->key == key){ ///if it reaches the node you target to edit then edit
		my_root->value = value;
	}else if(key > my_root->key){
                            ///if the key is bigger than the key of my_root then edit it in right subtree
		edit(key, value, my_root->right);
	}else{
                            ///if the key is smaller than the key of my_root then edit it in left subtree
		edit(key, value, my_root->left);
	}
}

///return the value of a key
template<class K, class V>
V BST<K, V>::get(K key, Node *my_root){
	if(my_root->key == key) return my_root->value; ///if it reaches the the right node return its value
	else if(key > my_root->key) return get(key, my_root->right); ///if the key is bigger than the key of my_root get it from the right subtree
	return get(key, my_root->left); ///if the key is smaller than the key of my_root get it from the left subtree
}

///removes a node from my tree then balance the tree
template<class K, class V>
void BST<K, V>::remove(K key, Node *&my_root){
	if(key < my_root->key){
            ///if the key is smaller than the key of my_root remove it from the left subtree
		remove(key ,my_root->left);

	}else if(key > my_root->key){
	     ///if the key is bigger than the key of my_root remove it from the right subtree
		remove(key , my_root->right);

	}else{

	    ///if it reaches the node then it checks the way it will delete it with
		if( (my_root->left == NULL) && (my_root->right == NULL) ){
		    ///if it a leaf delete it and make its value NULL
			delete my_root;
			my_root = NULL;
		}else if (my_root->right == NULL){
		    ///if it has a left child then
			Node *del = my_root; ///create a del pointer to point my root
			my_root = my_root->left;///make the tree points the left child

			del->left = del->right = NULL;///separate my root from the tree
			delete del; ///delete my root :(

		}else if (my_root->left == NULL){
            ///if it has a left right then
			Node *del = my_root; ///create a del pointer to point my root
			my_root = my_root->right;///make the tree points the left child

			del->left = del->right = NULL;///separate my root from the tree
			delete del;///delete my root :(
		}else{
		    ///it has a right and left child
			Node *temp = my_root->left; ///go to the left subtree
			while(temp->right != NULL) temp = temp->right; ///get the most right child of the left

            /// change my root to be the most right child of the left
			my_root->key = temp->key;
			my_root->value = temp->value;

			///remove the most right child of the left
			remove(temp->key, my_root->left);
			balance(my_root); ///balance the tree after deleting the node
		}
		return;
	}

	balance(my_root); ///when recurse balance each node on the tree
}

///balancing the tree
template<class K, class V>
void BST<K, V>::balance(Node *&my_root){

	my_root->updateHight(); ///updating the hight after insertion or deletion

	Node *initial_root = my_root; ///keep the value of my root to make a check the double rotate when occur
	int cleft = my_root->getLeftHight(); ///get the hight of the left subtree
	int cright = my_root->getRightHight();///get the hight of the right subtree
	while(abs(cright - cleft) > 1){ ///if it's not balanced then do the code of balancing
		if(cleft > cright) rotate_right(my_root); ///if the  left subtree bigger then rotate right
		else rotate_left(my_root);///if the  right subtree bigger then rotate left


        ///update the counters after rotations
		cleft = my_root->getLeftHight();
		cright = my_root->getRightHight();

      ///if you get an indication that there is a double rotation needed (left right) || (right left )
       ///rotate to make it normal unbalanced (left left || right right )
		if(my_root == initial_root){
			if(cleft > cright){
				rotate_left(my_root->left);
			}else{
				rotate_right(my_root->right);
			}
		}
	}

	my_root->updateHight(); ///update the hight after deletion
}



template<class K, class V>
void BST<K, V>::rotate_right(Node *&my_root){


	Node *new_root = my_root->left;  ///create a new node to point the left subtree
	Node *lost_child = new_root->right;///create a new node to point the right of the left subtree (lost child)

	new_root->right = my_root; ///making my root the right child to the new root
	my_root->left = lost_child;///giving the lost child to the old root as its left child

   ///updating the hight of my root and new root
	my_root->updateHight();
	new_root->updateHight();

	my_root = new_root; ///update the tree with the new root
}

template<class K, class V>
void BST<K, V>::rotate_left(Node *&my_root){

	Node *new_root = my_root->right; ///create a new node to point the right subtree
	Node *lost_child = new_root->left;///create a new node to point the left of the right subtree (lost child)


	new_root->left = my_root;///making my root the left child to the new root
	my_root->right = lost_child;///giving the lost child to the old root as its right child


   ///updating the hight of my root and new root
	my_root->updateHight();
	new_root->updateHight();

	my_root = new_root; ///update the tree with the new root
}


///checking if the key exists
template<class K, class V>
bool BST<K, V>::containsKey(K key, Node *my_root){
	if(my_root == NULL) return 0; ///if (not found || the tree is empty ) return 0
	if(my_root->key == key) return 1;///if it exists return 1
	if(key > my_root->key) return containsKey(key, my_root->right); ///if the key bigger than my_root then search it in the right subtree
	return containsKey(key, my_root->left); ///if the key smaller than my_root then search it in the left subtree
}

///print the tree

template<class K, class V>
void BST<K, V>::display(Node *my_root){
	if(my_root == NULL) return; ///base case (if it's empty || it reaches the end of tree)


/**==================///print inorder ===================**/

    ///if left child exists print
	if(my_root->left){
		cout << "[";
		display(my_root->left);
		cout << "],";
	}

    ///print the parent
	cout << my_root->key << ":\"" << my_root->value << "\"";

    ///if right child exists print
	if(my_root->right){
		cout << ",[";
		display(my_root->right);
		cout << "]";
	}
}

