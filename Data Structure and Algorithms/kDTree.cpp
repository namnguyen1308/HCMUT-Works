#include "kDTree.hpp"
double dist(const vector<int> &point1, const vector<int> &point2)
    {   
         double sum = 0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    return sqrt(sum);
    }
void swap(vector<int> &a, vector<int> &b)
{
    vector<int> tmp = a;
    a = b;
    b = tmp;
}
void merge(vector<vector<int>>& points, int l, int m, int r, int tier) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
    vector<vector<int>> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i][tier] <= R[j][tier]) {
            points[k] = L[i];
            i++;
        } else {
            points[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        points[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        points[k] = R[j];
        j++;
        k++;
    }
}
void merge(vector<kDTreeNode*>& nodes, int l, int m, int r, const vector<int>& target) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<kDTreeNode*> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = nodes[l + i];
    for (j = 0; j < n2; j++)
        R[j] = nodes[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (dist(L[i]->data, target) <= dist(R[j]->data, target)) {
            nodes[k] = L[i];
            i++;
        } else {
            nodes[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        nodes[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        nodes[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<vector<int>>& points, int l, int r, int tier) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(points, l, m, tier);
        mergeSort(points, m + 1, r, tier);
        merge(points, l,m, r, tier);
    }
}
void mergeSort(vector<kDTreeNode*>& nodes, int l, int r, const vector<int>& target) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(nodes, l, m, target);
        mergeSort(nodes, m + 1, r, target);
        merge(nodes, l, m, r, target);
    }
}
kDTree::kDTree(int k)
{
    this->k = k;
    this->root = nullptr;
    this->count = 0;
}
kDTree::kDTree(const kDTree &other)
{
    this->k = other.k;
    this->count = other.count;
    this->root = this->copy(other.root);
}
kDTree::~kDTree()
{
    clear(root);
    root = nullptr;
}
const kDTree &kDTree::operator=(const kDTree &other)
{
    this->k = other.k;
    this->count = other.count;
    this->root = this->copy(other.root);
    return *this;
}
int kDTree::height() const
{
    return this->rec_Height(root);
}
int kDTree::nodeCount() const
{
    return this->rec_nodeCount(root);
}
int kDTree::leafCount() const
{
    return this->rec_Leaf(root);
}
void kDTree::inorderTraversal() const
{
    this->rec_InorderTraversal(root);
}
void kDTree::preorderTraversal() const
{
    this->rec_PreorderTraversal(root);
}
void kDTree::postorderTraversal() const
{
    this->rec_PostorderTraversal(root);
}
void kDTree::insert(const vector<int> &point)
{
    this->root = this->rec_Insert(root, point, 0);
    this->count++;
}
void kDTree::remove(const vector<int> &point)
{
    this->root=this->rec_Remove(root, point,0); 
}

bool kDTree::search(const vector<int> &point)
{
    return rec_search(root, point, 0);
}
void kDTree::buildTree(const vector<vector<int>> &pointList)
{
    this->count = pointList.size();
    this->root = this->rec_BuildTree(pointList, 0);
}
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *&best)
{
    best = nullptr;
    rec_NearestNeighbour(root, target, best, 0);
}
void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList)
{
    rec_KNearestNeighbour(root, target, k, bestList, 0);
    mergeSort(bestList,0,bestList.size()-1,target);
    bestList.resize(k);
}
void kDTree::clear(kDTreeNode *tmp)
{
    if (tmp)
    {
        clear(tmp->left);
        clear(tmp->right);
        delete tmp;
    }
}

kDTreeNode *kDTree::copy(const kDTreeNode *tmp)
{
    if (tmp == nullptr)
        return nullptr;
    kDTreeNode *left = this->copy(tmp->left);
    kDTreeNode *right = this->copy(tmp->right);
    return new kDTreeNode(tmp->data, left, right);
}

int kDTree::rec_Height(kDTreeNode *tmp) const
{
    if (tmp == nullptr)
        return 0;
        int maxleft=rec_Height(tmp->left);
        int maxright=rec_Height(tmp->right);
    return 1 + max(maxleft,maxright);
}

int kDTree::rec_Leaf(kDTreeNode *tmp) const
{
    if (tmp == nullptr)
        return 0;
    if (tmp->left == nullptr && tmp->right == nullptr)
        {return 1;}
    return rec_Leaf(tmp->left) + rec_Leaf(tmp->right);
}
int kDTree::rec_nodeCount(kDTreeNode *tmp) const
{
    if (tmp==nullptr) return 0;
    return 1+rec_nodeCount(tmp->left)+rec_nodeCount(tmp->right);
}
void kDTree::rec_InorderTraversal(kDTreeNode *tmp) const
{
    if (tmp == nullptr)
        return;
    rec_InorderTraversal(tmp->left);
    OUTPUT << *tmp << " ";
    rec_InorderTraversal(tmp->right);
}

void kDTree::rec_PreorderTraversal(kDTreeNode *tmp) const
{
    if (tmp == nullptr)
        return;
    OUTPUT << *tmp << " ";
    rec_PreorderTraversal(tmp->left);
    rec_PreorderTraversal(tmp->right);
}

void kDTree::rec_PostorderTraversal(kDTreeNode *tmp) const
{
    if (tmp == nullptr)
        return;
    rec_PostorderTraversal(tmp->left);
    rec_PostorderTraversal(tmp->right);
    OUTPUT << *tmp << " ";
}

kDTreeNode *kDTree::rec_Insert(kDTreeNode *tmp, const vector<int> &point, int tier)
{
    if (tmp==nullptr) return new kDTreeNode(point);
       int axis=tier%k;
        if (point[axis] < tmp->data[axis]) {
            tmp->left = rec_Insert(tmp->left, point, tier + 1);
        } else {
            tmp->right = rec_Insert(tmp->right, point, tier + 1);
        }
        return tmp;
}

bool kDTree::rec_search(kDTreeNode *tmp, const vector<int> &point, int tier)
{
    if (tmp == nullptr)
        return false;
    else if (tmp->data == point)
        return true;

    int alpha = tier % k;
    if (tmp->data[alpha] > point[alpha])
    {
        return rec_search(tmp->left, point, tier + 1);
    }
    else
    {
        return rec_search(tmp->right, point, tier + 1);
    }
}

kDTreeNode *kDTree::findkDTreeNodeMin(kDTreeNode *tmp, int dim, int tier)
{
    if (tmp == nullptr) return nullptr;

        int axis = tier % k;
        if (axis == dim) {
            if (tmp->left == nullptr) return tmp;
            return findkDTreeNodeMin(tmp->left, dim, tier + 1);
        }

        kDTreeNode* leftMin = findkDTreeNodeMin(tmp->left, dim, tier + 1);
        kDTreeNode* rightMin = findkDTreeNodeMin(tmp->right, dim, tier + 1);

        kDTreeNode* minNode = tmp;
        if (leftMin != nullptr && leftMin->data[dim] < minNode->data[dim]) {
            minNode = leftMin;
        }
        if (rightMin != nullptr && rightMin->data[dim] < minNode->data[dim]) {
            minNode = rightMin;
        }
        return minNode;
}

kDTreeNode *kDTree::rec_Remove(kDTreeNode *tmp, const vector<int> &point, int tier)
{
    if (tmp == nullptr)
        return nullptr;

    int alpha = tier % k;
    if (tmp->data == point)
    {
        if (tmp->left == nullptr && tmp->right == nullptr)
        {
            delete tmp;
            this->count--;
            return nullptr;
        }
        else if (tmp->right != nullptr)
        {
            kDTreeNode *x = findkDTreeNodeMin(tmp->right, alpha, tier + 1);
            tmp->data = x->data;
            tmp->right = rec_Remove(tmp->right, tmp->data, tier + 1);
        }
        else
        {
            kDTreeNode *x = findkDTreeNodeMin(tmp->left, alpha, tier + 1);
            tmp->data = x->data;
            tmp->right = rec_Remove(tmp->left, tmp->data, tier + 1);
            tmp->left = nullptr;
        }
    }
    else if (tmp->data[alpha] > point[alpha])
    {
        tmp->left = rec_Remove(tmp->left, point, tier + 1);
    }
    else
    {
        tmp->right = rec_Remove(tmp->right, point, tier + 1);
    }
    return tmp;
}

kDTreeNode *kDTree::rec_BuildTree(const vector<vector<int>> &pointList, int tier)
{
     if (pointList.size() == 0)
        return nullptr;
    int alpha = tier % this->k;
    int median = (pointList.size() - 1) / 2;
    vector<vector<int>> left;
    vector<vector<int>> right;
    vector<int> data;
    vector<vector<int>> temp = pointList;
    mergeSort(temp, 0,temp.size()-1,alpha);
    while (median != 0 && median > 0 && temp[median][alpha] == temp[median - 1][alpha])
    {
        median--;
    }

    data = temp[median];
    for (int i = 0; i < median; i++)
        left.push_back(temp[i]);
    for (int i = median + 1; i < pointList.size(); i++)
        right.push_back(temp[i]);

    kDTreeNode *root = new kDTreeNode(data);
    root->left = rec_BuildTree(left, tier + 1);
    root->right = rec_BuildTree(right, tier + 1);
    return root;
}

void kDTree::rec_NearestNeighbour(kDTreeNode *tmp, const vector<int> &target, kDTreeNode *&best, int tier)
{
    if (tmp == nullptr)
        return;

    int alpha = tier % k;
    int leftOrRight = 0;
    if (tmp->data[alpha] > target[alpha])
    {
        rec_NearestNeighbour(tmp->left, target, best, tier + 1);
        leftOrRight = 1;
    }
    else
    {
        rec_NearestNeighbour(tmp->right, target, best, tier + 1);
        leftOrRight = 2;
    }

    if (best == nullptr)
    {
        best = tmp;
        if (leftOrRight == 2)
            rec_NearestNeighbour(tmp->left, target, best, tier + 1);
        else if (leftOrRight == 1)
            rec_NearestNeighbour(tmp->right, target, best, tier + 1);
    }
    else
    {

        int R = abs(tmp->data[alpha] - target[alpha]) * abs(tmp->data[alpha] - target[alpha]);
        int d = 0;
        for (int i = 0; i < target.size(); i++)
        {
            d += (target[i] - tmp->data[i]) * (target[i] - tmp->data[i]);
        }

        int r = 0;
        for (int i = 0; i < target.size(); i++)
        {
            r += (target[i] - best->data[i]) * (target[i] - best->data[i]);
        }

        if (d < r)
        {
            best = tmp;
        }
        if (R < r)
        {
            if (leftOrRight == 2)
                rec_NearestNeighbour(tmp->left, target, best, tier + 1);
            else if (leftOrRight == 1)
                rec_NearestNeighbour(tmp->right, target, best, tier + 1);
        }
    }
    return;
}
void kDTree::rec_KNearestNeighbour(kDTreeNode *tmp, const vector<int> &target, int k, vector<kDTreeNode *> &bestList, int tier)
{
    if (tmp == nullptr)
        return;
    int alpha = tier % this->k;
    int leftOrRight = 0;
    if (tmp->data[alpha] > target[alpha])
    {
        rec_KNearestNeighbour(tmp->left, target, k, bestList, tier + 1);
        leftOrRight = 1;
    }
    else
    {
        rec_KNearestNeighbour(tmp->right, target, k, bestList, tier + 1);
        leftOrRight = 2;
    }

    if (bestList.size() < k)
    {
        bestList.push_back(tmp);
        if (leftOrRight == 2)
            rec_KNearestNeighbour(tmp->left, target, k, bestList, tier + 1);
        else if (leftOrRight == 1)
            rec_KNearestNeighbour(tmp->right, target, k, bestList, tier + 1);
    }
    else
    {
        double max_distance = -1;
        size_t max_distance_index = -1;
        for (size_t i = 0; i < bestList.size(); ++i)
        {
            int r = 0;
            for (int j = 0; j < target.size(); j++)
            {
                r += (target[j] - bestList[i]->data[j]) * (target[j] - bestList[i]->data[j]);
            }
            if (r >= max_distance)
            {
                max_distance = r;
                max_distance_index = i;
            }
        }
        int d = 0;
        for (int i = 0; i < target.size(); i++)
        {
            d += (tmp->data[i] - target[i]) * (tmp->data[i] - target[i]);
        }
        int R = abs(tmp->data[alpha] - target[alpha]) * abs(tmp->data[alpha] - target[alpha]) ;
        if (d < max_distance)
        {
            bestList.erase(bestList.begin() + max_distance_index);
            bestList.push_back(tmp);
        }

        if (R < max_distance)
        {
            if (leftOrRight == 2)
                rec_KNearestNeighbour(tmp->left, target, k, bestList, tier + 1);
            else if (leftOrRight == 1)
                rec_KNearestNeighbour(tmp->right, target, k, bestList, tier + 1);
        }
    }
    return;
}