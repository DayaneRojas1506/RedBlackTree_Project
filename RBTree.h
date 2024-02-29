
enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBTree
{
    private:
        Node *root;
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorder(Node *&);
        void preorder(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *search(Node *&, int);
        Node *minValueNode(Node *&);
        void transplant(Node *&u, Node *&v);
        Node* insert(Node *&, Node *&);
        Node* deleteRBT(Node *&, int);


    public:
        RBTree();
        void searchValue(int);
        void insertValue(int);
        void deleteValue(int);
        void inorder();
        void preorder();
};


