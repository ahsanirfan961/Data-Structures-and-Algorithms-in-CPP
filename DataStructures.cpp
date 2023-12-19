//
// Created by ahsan on 12/3/23.
//

#include "DataStructures.h"

// Implementation of Array Class

void Array::flipArray(int *array, int length, int i)
{
    i = (i==-1)?length-1:i;
    for(int j=0;true;j++, i--)
    {
        if(j==i || j+1==i)
            break;
        swap(array[j], array[i]);
    }
}

int Array::maxElement(const int *array, int length) {
    int max = array[0];
    for(int i=1;i<length;i++)
        if(array[i]>max)
            max = array[i];
    return max;
}

int Array::maxIndex(const int *array, int length) {
    int max = 0;
    for(int i=1;i<length;i++)
        if(array[i]>array[max])
            max = i;
    return max;
}

int Array::minIndex(const int *array, int length) {
    int min = 0;
    for(int i=1;i<length;i++)
        if(array[i]<array[min])
            min = i;
    return min;
}

void Array::sortedMerge(int *array, int start, int middle, int end) {
    int i=start,j=middle+1,k=0;
    int result[end-start+1];
    while(i<=middle && j<=end)
    {
        if(array[i]>array[j])
            result[k++] = array[j++];
        else
            result[k++] = array[i++];
    }

    while(i<=middle)
        result[k++] = array[i++];

    while(j<=end)
        result[k++] = array[j++];

    Array::copyArray(array, result, start, end);
}

void Array::copyArray(int *copiedTo, const int *copiedFrom, int fromIndex,int end) {
    for(int i=0;fromIndex<=end;i++)
        copiedTo[fromIndex++]=copiedFrom[i];
}

int Array::minElement(const int *array, int length) {
    int min = array[0];
    for(int i=1;i<length;i++)
        if(array[i]<min)
            min = array[i];
    return min;
}

// Implementation of Linked List Class

void SinglyLinkedList::pushBack(int data) {
    auto* q = new SinglyLinkedListNode(data);
    auto* dummy = new SinglyLinkedListNode();
    dummy->next = head;
    SinglyLinkedListNode* p = dummy;
    while(p->next!=nullptr)
        p=p->next;
    p->next = q;
    head = dummy->next;


}

int SinglyLinkedList::length() const {
    SinglyLinkedListNode* p = head;
    int c = 0;
    while(p!= nullptr)
    {
        p=p->next;
        c++;
    }
    return c;
}

// Implementation of queue class
Queue::Queue(int size): capacity(size), front(size), rear(size)
{
    array = new int[capacity+1];
    for(int i=0;i<=capacity;i++)
        array[i]=0;
}

bool Queue::isEmpty() const {
    return front==rear;
}

bool Queue::isFull() const {
    return front==(rear+1)%(capacity+1);
}

void Queue::enqueue(int data) {
    if(!isFull())
    {
        rear = (rear+1)%(capacity+1);
        array[rear] = data;
    } else
        cout<<"Queue is Full!"<<endl;
}

int Queue::dequeue() {
    if(!isEmpty())
    {
        front = (front+1)%(capacity+1);
        return array[front];
    }
    else
    {
        cout<<"Queue is Empty!"<<endl;
        return -1;
    }
}

void Queue::operator=(Queue const& queue) {
    front = queue.front;
    rear = queue.rear;
    capacity = queue.capacity;
    delete[] array;
    array = new int[capacity+1];
    for(int i=0;i<=capacity;i++)
        array[i] = queue.array[i];
}

int Queue::getSize() {
    return capacity;
}


// Implementation of Utilities Class

void Utility::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Implementation of Stack data structure
Stack::Stack(int size):top(-1), size(size), elements(0) {
    array = new int[size];
    for(int i=0;i<size;i++)
        array[i]=0;
}

bool Stack::isFull() const {
    return elements==size;
}

bool Stack::isEmpty() const {
    return elements==0;
}

void Stack::push(int data) {
    if(!isFull())
    {
        array[++top]=data;
        elements++;
    }
    else
        cout<<"Stack is full!"<<endl;
}

int Stack::pop() {
    if(!isEmpty())
    {
        elements--;
        return array[top--];
    }
    cout<<"Stack is empty!"<<endl;
    return -1;
}

int Stack::topElement() {
    if(!isEmpty())
        return array[top];
    cout<<"Stack is empty!"<<endl;
    return -1;
}

// Implementation of Binary Tree Node
BTNode::BTNode(int data) {
    this->data=data;
    left = nullptr;
    right = nullptr;
}

void BTNode::inOrder(BTNode *root) {
    if(root == nullptr)
        return;
    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
}

int BTNode::maxDepth(BTNode *root) {
    if(root== nullptr)
        return 0;
    return 1+max(maxDepth(root->left), maxDepth(root->right));
}

void BTNode::preOrder(BTNode *root) {
    if(root == nullptr)
        return;
    cout<<root->data<<" ";
    inOrder(root->left);
    inOrder(root->right);
}

void BTNode::postOrder(BTNode *root) {
    if(root == nullptr)
        return;
    inOrder(root->left);
    inOrder(root->right);
    cout<<root->data<<" ";
}

//Implementation of Binary Search Tree
BST::BST(int data) {
    root = new BTNode(data);
}

BST::BST(BTNode *ref) {
    root=ref;
}

void BST::insert(int data) {
    auto* q = new BTNode(data);
    if(root == nullptr)
        root = q;
    else
    {
        BTNode* current = root;
        BTNode* parent = current;
        while(current!= nullptr)
        {
            parent = current;
            if(data>current->data)
                current=current->right;
            else
                current=current->left;
        }
        if(data>parent->data)
            parent->right=q;
        else
            parent->left=q;
    }
}

void BST::inOrder() {
    BTNode::inOrder(root);
    cout<<endl;
}

int BST::depth() {
    return BTNode::maxDepth(root);
}

void BST::print() {
    Print::printBT(root);
    cout<<endl;
}

void BST::preOrder() {
    BTNode::preOrder(root);
    cout<<endl;
}

void BST::postOrder() {
    BTNode::postOrder(root);
    cout<<endl;
}

void BST::remove(int data) {
    BTNode* current = root;
    BTNode* parent = nullptr;
    while(current!= nullptr)
    {
        if(current->data==data)
            break;
        parent = current;
        if(data>current->data)
            current=current->right;
        else
            current=current->left;
    }
    if(current== nullptr)
        cout<<"Node with data: "<<data<<" does exit in the BST!"<<endl;
    else
    {
        if(current->left== nullptr && current->right == nullptr)
        {
            if(current==root)
                delete root;
            else
            {
                if(current->data > parent->data)
                    parent->right= nullptr;
                else
                    parent->left= nullptr;
                delete current;
            }
        } else if (current->left== nullptr || current->right == nullptr)
        {
            if(current->right== nullptr)
            {
                if(current==root)
                {
                    BTNode* temp = root->left;
                    delete root;
                    root = temp;
                }
                else
                {
                    if(current->data>parent->data)
                        parent->right=current->left;
                    else
                        parent->left = current->left;
                    delete current;
                }
            }
            else
            {
                if(current==root)
                {
                    BTNode* temp = root->right;
                    delete root;
                    root = temp;
                }
                else
                {
                    if(current->data>parent->data)
                        parent->right=current->right;
                    else
                        parent->left = current->right;
                    delete current;
                }
            }
        }
        else
        {
            // when a node has both children
            BST leftSubtree(current->left);
            int replace = leftSubtree.max();
            if(current==root)
                root->data=replace;
            else
                current->data=replace;
            leftSubtree.remove(replace);
        }
    }
}

int BST::max() {
    BTNode* current = root;
    while(current->right!= nullptr)
        current=current->right;
    return current->data;
}

int BST::min() {
    BTNode* current = root;
    while(current->left!= nullptr)
        current=current->left;
    return current->data;
}

bool BST::search(int data) {
    BTNode* current = root;
    while(current!= nullptr)
    {
        if(current->data==data)
            return true;
        if(data>current->data)
            current=current->right;
        else
            current=current->left;
    }
    return false;
}

// Implementation of Heap Data Structure
Heap::Heap(int maxSize, const string& heapProperty):maxSize(maxSize), size(0) {
    property = heapProperty=="max";
    array = new int[maxSize];
    for(int i=0;i<maxSize;i++)
        array[i]=0;
}

Heap::Heap(int maxSize):maxSize(maxSize), size(0), property(true)
{
    array = new int[maxSize];
    for(int i=0;i<maxSize;i++)
        array[i]=0;
}

Heap::~Heap() {
    delete array;
}

void Heap::heapify(int root) {
    int left = 2*root;
    int right = 2*root+1;

    if(property)
    {
        int largest = root;
        if(array[left]>array[largest] && left<size)
            largest=left;
        if(array[right]>array[largest] && right<size)
            largest=right;
        if(largest!=root)
        {
            Utility::swap(array[root], array[largest]);
            heapify(largest);
        }

    } else
    {
        int smallest = root;
        if(array[left]<array[smallest] && left<size)
            smallest=left;
        if(array[right]<array[smallest] && right<size)
            smallest=right;
        if(smallest!=root)
        {
            Utility::swap(array[root], array[smallest]);
            heapify(smallest);
        }
    }
}

Heap::Heap(int maxSize, const string &heapProperty, int *array, int length):maxSize(maxSize), size(length) {
    property=heapProperty=="max";
    this->array = new int[maxSize];
    for(int i=0;i<length;i++)
        this->array[i+1] = array[i];
    createHeap();
}

void Heap::createHeap() {
    int index = size;
    while(index>0)
        heapify(index--);
}

void Heap::print() {
    Print::printArray(array+1, size);
}
