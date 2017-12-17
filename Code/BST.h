#ifndef MY_BST
#define MY_BST

template<class K, class V>
class BST{
	private:
		struct Node{
			K key;
			V value;
			Node *right, *left;
			//int count_right, count_left;
			int hight;
			
			Node(K _key, V _value){
				key = _key;
				value = _value;
				right = left = NULL;
				//count_right = count_left = 0;
				hight = 1;
			}
			~Node(){
				if(right) delete right;
				if(left) delete left;
			}
			
			void updateHight(){
				int h1 = (right == NULL) ? 0 : right->hight;
				int h2 = (left == NULL) ? 0 : left->hight;
				hight = max(h1, h2) + 1;
			}
			
			int getRightHight(){
				if(right){
					right->updateHight();
					return right->hight;
				}
				return 0;
			}
			
			int getLeftHight(){
				if(left){
					left->updateHight();
					return left->hight;
				}
				return 0;
			}
			
		};
		
		Node *root;
		void remove(K, Node*&);
		void set(K, V, Node*&);
		void edit(K, V, Node*);
		V get(K, Node*);
		bool containsKey(K, Node*);
		void balance(Node*&);
		void rotate_right(Node*&);
		void rotate_left(Node*&);
		void display(Node*);
		
	public:
		BST();
		~BST();
		void set(K, V);
		void insert(K, V);
		void modify(K, V);
		V get(K);
		void remove(K);
		bool containsKey(K);
		void display();
};

#include "BST.cpp"
#endif
