#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node {
    int value;
    int left, right;
    int h;   // height
    int sz;  // subtree size

    Node(int v) : value(v), left(-1), right(-1), h(1), sz(1) {}
};

vector<Node> tree;
int ROOT = -1;

// Helpers
int height(int idx) { return (idx == -1) ? 0 : tree[idx].h; }
int sizeOf(int idx) { return (idx == -1) ? 0 : tree[idx].sz; }

void pull(int idx) {
    if (idx == -1) return;
    tree[idx].h = 1 + max(height(tree[idx].left), height(tree[idx].right));
    tree[idx].sz = 1 + sizeOf(tree[idx].left) + sizeOf(tree[idx].right);
}

int getBalance(int idx) {
    if (idx == -1) return 0;
    return height(tree[idx].left) - height(tree[idx].right);
}

// Rotations (update the root reference!)
void rightRotate(int &root) {
    if (root == -1 || tree[root].left == -1) return;
    int p = root;
    int x = tree[p].left;
    int t = tree[x].right;

    tree[x].right = p;
    tree[p].left = t;
    root = x;

    pull(p);
    pull(x);
}

void leftRotate(int &root) {
    if (root == -1 || tree[root].right == -1) return;
    int p = root;
    int x = tree[p].right;
    int t = tree[x].left;

    tree[x].left = p;
    tree[p].right = t;
    root = x;

    pull(p);
    pull(x);
}

void rebalance(int &root) {
    if (root == -1) return;
    pull(root);
    int bf = getBalance(root);

    if (bf > 1) {
        if (getBalance(tree[root].left) < 0) {
            cout << "Performing Left Rotation on " << tree[tree[root].left].value
                 << " before Right Rotation on " << tree[root].value << endl;
            leftRotate(tree[root].left);
        }
        cout << "Performing Right Rotation on " << tree[root].value << endl;
        rightRotate(root);
    } else if (bf < -1) {
        if (getBalance(tree[root].right) > 0) {
            cout << "Performing Right Rotation on " << tree[tree[root].right].value
                 << " before Left Rotation on " << tree[root].value << endl;
            rightRotate(tree[root].right);
        }
        cout << "Performing Left Rotation on " << tree[root].value << endl;
        leftRotate(root);
    }
    pull(root);
}

// BST insert + rebalance; root is by reference so parent links get updated
void insertAt(int &root, int idx) {
    if (root == -1) {
        root = idx;
        return;
    }
    if (tree[idx].value < tree[root].value) {
        cout << "Going left from " << tree[root].value << endl;
        insertAt(tree[root].left, idx);
    } else if (tree[idx].value > tree[root].value) {
        cout << "Going right from " << tree[root].value << endl;
        insertAt(tree[root].right, idx);
    } else {
        // duplicate: discard the just-pushed node
        tree.pop_back();
        return;
    }
    cout << "Fixing balance at " << tree[root].value << endl;
    rebalance(root);
}

void insert(int value) {
    tree.emplace_back(value);
    int idx = (int)tree.size() - 1;
    cout << "Inserting " << value << endl;
    insertAt(ROOT, idx);
}

bool find(int root, int value) {
    if (root == -1) return false;
    if (tree[root].value == value) return true;
    if (value < tree[root].value) return find(tree[root].left, value);
    return find(tree[root].right, value);
}

// 0-based order statistic
int kth(int root, int k) {
    if (root == -1) return -1;
    int leftSize = sizeOf(tree[root].left);
    if (k == leftSize) return tree[root].value;
    if (k < leftSize) return kth(tree[root].left, k);
    return kth(tree[root].right, k - leftSize - 1);
}

void inorder(int root) {
    if (root == -1) return;
    inorder(tree[root].left);
    cout << "node value: " << tree[root].value
         << " height: " << tree[root].h
         << " size: " << tree[root].sz << endl;
    inorder(tree[root].right);
}

int main() {
    for (int i = 10; i > 0; --i) {
        insert(i);
    }
    cout << "\nInorder traversal:\n";
    inorder(ROOT);

    cout << "\nFind 7: " << (find(ROOT, 7) ? "yes" : "no") << endl;
    cout << "kth(0): " << kth(ROOT, 0) << endl;     // smallest
    cout << "kth(5): " << kth(ROOT, 5) << endl;     // 6th smallest
    cout << "kth(9): " << kth(ROOT, 9) << endl;     // largest
    return 0;
}
