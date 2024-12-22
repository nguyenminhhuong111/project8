#include <iostream>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};

// Hàm thêm node theo cây nhị phân tìm kiếm
void addnode(node*& root, int data) {
    if (!root) {
        root = new node{data, NULL, NULL};
        return;
    }
    if (data <= root->data)
        addnode(root->left, data);
    else
        addnode(root->right, data);
}

// Hàm tính chiều cao của 1 cây
int getHeight(node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Hàm tính chênh lệch chiều cao 2 nhánh của 1 node gốc
int distancenode(node* root) {
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

// Hàm xoay trái
node* rotateleft(node* a) {
    node* b = a->right;
    a->right = b->left;
    b->left = a;
    return b; // Trả về nút gốc mới
}

// Hàm xoay phải
node* rotateright(node* a) {
    node* b = a->left;
    a->left = b->right;
    b->right = a;
    return b; // Trả về nút gốc mới
}

// Hàm xoay kép (trái -> phải)
node* rotateleft_right(node* root) {
    root->left = rotateleft(root->left);
    return rotateright(root);
}

// Hàm xoay kép (phải -> trái)
node* rotateright_left(node* root) {
    root->right = rotateright(root->right);
    return rotateleft(root);
}

// Hàm cân bằng cây AVL
node* balanced(node* root) {
    if (!root)
        return root;
    
    // Cân bằng left-left
    if (distancenode(root) > 1 && distancenode(root->left) >= 0)
        return rotateright(root);
    
    // Cân bằng right-right
    if (distancenode(root) < -1 && distancenode(root->right) <= 0)
        return rotateleft(root);
    
    // Cân bằng left-right
    if (distancenode(root) > 1 && distancenode(root->left) < 0)
        return rotateleft_right(root);
    
    // Cân bằng right-left
    if (distancenode(root) < -1 && distancenode(root->right) > 0)
        return rotateright_left(root);

    return root; // Nếu không cần xoay, trả về chính nó
}

// Hàm duyệt cây theo thứ tự inorder
void inorder(node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    node* root = NULL;
    int a[12] = {17, 23, 201, 98, 67, 83, 13, 23, 10, 191, 84, 58};

    for (int i = 0; i < 12; i++) {
        addnode(root, a[i]);      // Thêm node mới
        root = balanced(root);   // Cân bằng luôn sau khi thêm node
    }

    inorder(root); // In cây theo thứ tự inorder
    return 0;
}
