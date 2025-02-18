class Node:
    def __init__(self, key):
        self.key = key
        self.height = 0
        self.size = 1
        self.left = None
        self.right = None
        
class AVLTree:
    def __init__(self):
        self.root = None

    def _height(self, node):
        return -1 if node is None else node.height

    def _update_height(self, node):
        node.height = 1 + max(self._height(node.left), self._height(node.right))

    def _size(self, node):
        return 0 if node is None else node.size

    def _update_size(self, node):
        node.size = 1 + self._size(node.left) + self._size(node.right)

    def _balance_factor(self, node):
        return 0 if node is None else self._height(node.right) - self._height(node.left)

    def insert(self, key):
        self.root = self._insert(self.root, key)

    def delete(self, key):
        self.root = self._remove(self.root, key)

    def index(self, idx):
        return self._index(self.root, idx)

    def _index(self, node, idx):
        if node is None:
            return None
        left_size = self._size(node.left)
        if idx < left_size:
            return self._index(node.left, idx)
        elif idx == left_size:
            return node.key
        else:
            return self._index(node.right, idx - left_size - 1)

    def _insert(self, node, key):
        if node is None:
            return Node(key)
        elif key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        return self._balance(node)

    def _rotate_right(self, node):
        x = node.left
        node.left = x.right
        x.right = node
        self._update_height(node)
        self._update_size(node)
        self._update_height(x)
        self._update_size(x)
        return x

    def _rotate_left(self, node):
        x = node.right
        node.right = x.left
        x.left = node
        self._update_height(node)
        self._update_size(node)
        self._update_height(x)
        self._update_size(x)
        return x

    def _balance(self, node):
        self._update_height(node)
        self._update_size(node)
        balance_factor = self._balance_factor(node)
        if balance_factor > 1:
            if self._balance_factor(node.right) < 0:
                node.right = self._rotate_right(node.right)
            node = self._rotate_left(node)
        elif balance_factor < -1:
            if self._balance_factor(node.left) > 0:
                node.left = self._rotate_left(node.left)
            node = self._rotate_right(node)
        return node

    def _most_left_child(self, node):
        while node.left is not None:
            node = node.left
        return node

    def _remove(self, node, key):
        if node is None:
            return None
        elif key < node.key:
            node.left = self._remove(node.left, key)
        elif key > node.key:
            node.right = self._remove(node.right, key)
        else:
            if node.left is None or node.right is None:
                if node.left is None:
                    node = node.right
                else:
                    node = node.left
            else:
                temp_node = self._most_left_child(node.right)
                node.key = temp_node.key
                node.right = self._remove(node.right, temp_node.key)
        if node is not None:
            node = self._balance(node)
        return node

    def search(self, key):
        return self._search(self.root, key)

    def _search(self, node, key):
        if node is None or node.key == key:
            return node
        if key < node.key:
            return self._search(node.left, key)
        return self._search(node.right, key)

    def inorder_traversal(self):
        return self._inorder_traversal(self.root, [])

    def _inorder_traversal(self, node, result):
        if node:
            self._inorder_traversal(node.left, result)
            result.append(node.key)
            self._inorder_traversal(node.right, result)
        return result

if __name__ == "__main__":
    avl_tree = AVLTree()
    avl_tree.insert(10)
    avl_tree.insert(40)
    avl_tree.insert(100)
    avl_tree.insert(5)
    avl_tree.insert(21)
    avl_tree.insert(14)
    print("Inorder traversal:", avl_tree.inorder_traversal())
    print("Search 40: ", avl_tree.search(40) is not None)
    print("Search 50: ", avl_tree.search(50) is not None)
    avl_tree.delete(14)
    print("Inorder traversal after deletion:", avl_tree.inorder_traversal())
    for i in range(10):
        print(f'{i} is {avl_tree.index(i)}')
