struct Node
{
    char c;
    bool val;
    int ops;
    Node* left;
    Node* right;
    Node(char c);
};

Node::Node(char c): c(c), left(NULL), right(NULL)
{
}

class Solution {
public:
    int minOperationsToFlip(string expression) {
        Node* root = NULL;
        int k = 0;
        root = buildTree(expression, &k, root);
        evaluate(root);
        return root->ops;
    }
    
    void evaluate(Node* root)
    {
        if(root == NULL) return;
        if(root->c == '1')
        {
            root->val = true;
            root->ops = 1;
            return;
        }
        if(root->c == '0')
        {
            root->val = false;
            root->ops = 1;
            return;
        }
        evaluate(root->left);
        evaluate(root->right);
        if(root->c == '|')
        {
            root->val = root->left->val | root->right->val;
        }
        else
        {
            root->val = root->left->val & root->right->val;
        }
        
        if(root->left->val != root->right->val)
        {
            root->ops = 1;
            return;
        }
        
        int val = min(root->left->ops, root->right->ops);
        if(root->left->val == true)
        {
            root->ops = val + (root->c == '&' ? 0 : 1);
        }
        else
        {
            root->ops = val + (root->c == '|' ? 0 : 1);
        }
    }
    
    void printTree(Node* root)
    {
        queue<Node*> nodeQ;
        nodeQ.push(root);
        while(!nodeQ.empty())
        {
            Node* node = nodeQ.front();
            nodeQ.pop();
            if(node == NULL) cout << "null, ";
            else
            {
                cout << node->c << ", ";
                nodeQ.push(node->left);
                nodeQ.push(node->right);
            }
        }
    }
    
    Node* buildTree(string& expression, int* k, Node* root)
    {
        //cout << "work on " << *k << endl;
        int n = expression.length();
        if(*k >= n) return root;
        char c = expression[*k];
        if(c == '0' || c == '1')
        {
            Node* node = new Node(c);
            if(root == NULL)
            {
                root = node;
            }
            else
            {
                root->right = node;
            }
            *k = (*k) + 1;
            root = buildTree(expression, k, root);
            return root;
        }
        else if(c == '(')
        {
            *k = (*k) + 1;
            Node* node = buildTree(expression, k, NULL);
            if(root == NULL)
            {
                root = node;
            }
            else
            {
                root->right = node;
            }
            *k = (*k) + 1;
            root = buildTree(expression, k, root);
            return root;
        }
        else if(c == '&' || c == '|')
        {
            Node* node = new Node(c);
            node->left = root;
            *k = (*k) + 1;
            node = buildTree(expression, k, node);
            return node;
        }
        else
        {
            return root;
        }
    }
};
