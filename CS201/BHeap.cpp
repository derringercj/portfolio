// This program is an implementation of a "lazy" binomial heap. Or, a data structure with the layout of a binomial heap that only consolidates on calls to extract min.
// Our heap also stores pointers to other nodes on the same "level" in the heap as other nodes even when their parents are not linked
#include <iostream>
#include <random>

using namespace std;

// Our node class stores our key and rank as well as pointers to any children of the node and the rpevious and next node in the heap
template <typename keytype>
class Node{
    public:
        int rank;
        keytype key;
        Node<keytype>* child;
        Node<keytype>* prev;
        Node<keytype>* next;

        // Constructor
        Node(keytype k){
            rank = 0;
            key = k;
            child = prev = next = NULL;
        }       
};

// Definition of BHeap class whose members add or remove nodes from the BHeap 
template <typename keytype>
class BHeap{
    public: 
        Node<keytype>* min;

        // Three constructors: One to create an empty heap, one that creates a heap from a given array of key values, as well as a copy constructor
        BHeap(){
            min = NULL;
        }
        BHeap(keytype arr[], int s){
            min = NULL;
            for(int i = 0; i < s; i++){
                insert(arr[i]);
            }
            consolidate();
        }
        
        // Copy constructor
        BHeap(const BHeap &old){
            this->min = old.min;
            Node<keytype>* itr = old.min;
        }
        
        // Destructor for our heap that only deallocates our min pointer if it exists, such as when there are actually nodes in the heap
        ~BHeap(){
            if(min){
                delete min;
            }
        }

        // Overloading = operator for our heap
        BHeap& operator=(const BHeap &rhs){
            if(this != &rhs){
                this->min = rhs.min;
            }
            return *this;
        }

        // Function to insert new nodes
        void insert(keytype k){
            // Allocate new node, and set that as our heap's min if there isn't one already
            Node<keytype>* newNode = new Node<keytype>(k);
            if(min == nullptr){
                min = newNode;
                min->next = newNode;
                min->prev = newNode;
                return;
            }
            else{
                //Standard add to doubly linked list to left of min
                min->prev->next = newNode;
                newNode->prev = min->prev;
                newNode->next = min;
                min->prev = newNode;
                //Updating min if necessary            
                if(newNode->key < min->key){
                    min = newNode;
                }
            }
        }

        // Return min value
        keytype peekKey(){
            return min->key;
        }

        // Function to iterate through Heap printing each structure's nodes and their key
        void printKey(){
            Node<keytype>* i = min;
            
            // Loop that iterates over all top rank nodes, with helper function to print children of top-level nodes
            do{
                cout << "B" << i->rank << ":" << endl;
                cout << i->key << " ";
                if(i->child != NULL){
                    printer(i->child);
                }
                if(i->next == NULL){
                    cout << "\n";
                }
                else{
                    cout << "\n\n";
                }
                i = i->next;
            }while(i != min);
        }

        // Helper function that prints current node and children or neighbors if they exist.
        void printer(Node<keytype> *currentNode) {
            if(currentNode == NULL){
                return;
            }
            cout << currentNode->key << " ";
            if(currentNode->child != NULL){
                printer(currentNode->child);
            }
            if(currentNode->next != NULL && currentNode->next->rank != 0 && currentNode->next != min){    
                printer(currentNode->next);
            }
        }

        // Function that combines two heaps into one
        void merge(BHeap<keytype>& H2){
            min->prev->next = H2.min;
            H2.min->prev->next = min;

            Node<keytype>* temp;
            temp = H2.min->prev;
            H2.min->prev = min->prev;
            min->prev = temp;
            
            if(H2.min->key < min->key){
                min = H2.min;
            }
        }

        // Function that removes min node from heap, consolidates the trees, and returns the min value
        keytype extractMin(){
            keytype returnValue = min->key;
            min = removeMin();
            consolidate();
            return returnValue;
        }
    
    private:
        // Function that removes the min node from a heap
        Node<keytype>* removeMin(){
            // Removing the min node and restructuring around children if children are present
            if(min->child != NULL){
                min->prev->next = min->child;
                min->next->prev = min->child->prev;
                min->child->prev->next = min->next;
                min->child->prev = min->prev;
                min = min->child;
            }
            // If there are no children, just connect adjacent modes to each other
            else{
                min->prev->next = min->next;
                min->next->prev = min->prev;
                min = min->next;
            }
            return min;
        }

        // Iterating over our trees, and combining them
        void consolidate(){
            Node<keytype>* ptr1;
            Node<keytype>* ptr2;
            Node<keytype>* ptr3;
            Node<keytype>* ptr4;
            int rank = 0;

            ptr1 = min;
            ptr4 = ptr1;
            Node<keytype>* ptrs[30];
            //Initializing pointer array to null
            for(int i = 0; i < 30; i++){
                ptrs[i] = NULL;
            }
            //For each node within our root list
            do{
                ptr4 = ptr4->next;
                rank = ptr1->rank;
                
                // While we have another node with the same degree as x
                while(ptrs[rank] != NULL){
                    ptr2 = ptrs[rank];
                    if(ptr1->key > ptr2->key){
                        ptr3 = ptr1;
                        ptr1 = ptr2;
                        ptr2 = ptr3;
                    }
                    if(ptr2 == min){
                        min = ptr1;
                    }
                    //Link the two nodes
                    HeapLink(ptr2, ptr1);
                    if(ptr1->next == ptr1){
                        min = ptr1;
                    }
                    // Since a new rank tree was created, we can clear the pointer
                    ptrs[rank] = NULL;
                    // Increment rank
                    rank++;
                }
                // Update the pointer array with x
                ptrs[rank] = ptr1;
                ptr1 = ptr1->next;
            } while(ptr4 != min);
            // Reconstruct root list from the pointer array
            min = NULL;
            for(int i = 0; i < 30; i++){
                if(ptrs[i] != NULL){
                    ptrs[i]->prev = ptrs[i];
                    ptrs[i]->next = ptrs[i];
                    if(min != NULL){
                        // If this is the first root to be added to new root list make it circular and set as minimum
                        min->prev->next = ptrs[i];
                        ptrs[i]->next = min;
                        ptrs[i]->prev = min->prev;
                        min->prev = ptrs[i];
                        if(ptrs[i]->key < min->key){
                            min = ptrs[i];
                        }
                    }
                    else{
                        min = ptrs[i];
                        min->prev = ptrs[i];
                        min->next = ptrs[i];
                    }
                    if(min == NULL){
                        min = ptrs[i];
                    }
                    else if(ptrs[i]->key < min->key){
                        min = ptrs[i];
                    }
                }
            }
        }
        // Function to link nodes when they're found to be neighbors from separate heaps
        void HeapLink(Node<keytype>* ptr2, Node<keytype>* ptr1){
            ptr2->prev->next = ptr2->next;
            ptr2->next->prev = ptr2->prev;
            if(ptr1->next == ptr1){
                min = ptr1;
            }
            ptr2->prev = ptr2;
            ptr2->next = ptr2;
            if(ptr1->child == NULL){
                ptr1->child = ptr2;
            }
            ptr2->prev = ptr1->child->prev;
            ptr2->next = ptr1->child;
            ((ptr1->child)->prev)->next = ptr2;
            (ptr1->child)->prev = ptr2;
            ptr1->rank++;
            
    }
};