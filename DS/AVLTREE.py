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

    def _updateheight(self, node):
        node.height = 1 + max(self._height(node.left), self._height(node.right))

    def _size(self, node):
        return 0 if node is None else node.size

    def _updatesize(self, node):
        node.size = 1 + self._size(node.left) + self._size(node.right)

    def _balancefactor(self, node):
        return 0 if node is None else self._height(node.right) - self._height(node.left)

    def insert(self, key):
        self.root = self._insert(self.root, key)

    def _insert(self, node, key):
        if node is None:
            return Node(key)
        elif key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        return self._balance(node)

    def _rotateright(self, node):
        x = node.left
        node.left = x.right
        x.right = node
        self._updateheight(node)
        self._updatesize(node)
        self._updateheight(x)
        self._updatesize(x)
        return x

    def _rotateleft(self, node):
        x = node.right
        node.right = x.left
        x.left = node
        self._updateheight(node)
        self._updatesize(node)
        self._updateheight(x)
        self._updatesize(x)
        return x

    def _balance(self, node):
        self._updateheight(node)
        self._updatesize(node)
        balancefactor = self._balancefactor(node)
        if balancefactor > 1:
            if self._balancefactor(node.right) < 0:
                node.right = self._rotateright(node.right)
            node = self._rotateleft(node)
        elif balancefactor < -1:
            if self._balancefactor(node.left) > 0:
                node.left = self._rotateleft(node.left)
            node = self._rotateright(node)
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
    avltree = AVLTree()
    avltree.insert(10)
    avltree.insert(40)
    avltree.insert(100)
    avltree.insert(5)
    avltree.insert(21)
    avltree.insert(14)
    print("Inorder Traversal:", avltree.inorder_traversal())
    print("Search 40: ", avltree.search(40) is not None)
    print("Search 50: ", avltree.search(50) is not None)
