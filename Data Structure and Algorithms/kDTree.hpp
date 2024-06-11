#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{
    vector<int> data;
    int label;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = 0;
        this->left = left;
        this->right = right;
    }
    kDTreeNode(vector<int> data, int label, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->label = label;
        this->left = nullptr;
        this->right = nullptr;
    }

    friend ostream &operator<<(ostream &os, const kDTreeNode &node)
    {
        os << "(";
        for (int i = 0; i < node.data.size(); i++)
        {
            os << node.data[i];
            if (i != node.data.size() - 1)
            {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

};

class kDTree
{
private:
    int k;
    kDTreeNode *root;
    int count;
private:
    void clear(kDTreeNode *tmp);
    void rec_InorderTraversal(kDTreeNode* tmp) const;
    void rec_PreorderTraversal(kDTreeNode* tmp) const;
    void rec_PostorderTraversal(kDTreeNode* tmp) const;
    int rec_Height(kDTreeNode* tmp) const;
    int rec_Leaf(kDTreeNode* tmp) const; 
    int rec_nodeCount(kDTreeNode* tmp) const;
    bool rec_search(kDTreeNode* tmp,const vector<int> &point, int tier); 
    void rec_NearestNeighbour(kDTreeNode* tmp,const vector<int> &target, kDTreeNode*& best, int tier);
    void rec_KNearestNeighbour(kDTreeNode* tmp,const vector<int> &target,int k, vector<kDTreeNode*> &bestList, int tier);
    kDTreeNode* copy(const kDTreeNode* tmp);
    kDTreeNode* rec_Insert(kDTreeNode* tmp, const vector<int> &point, int tier);
    kDTreeNode* findkDTreeNodeMin(kDTreeNode* tmp, int alpha, int tier);
    kDTreeNode* rec_Remove(kDTreeNode* tmp, const vector<int> &point, int tier);
    kDTreeNode* rec_BuildTree(const vector<vector<int>> &pointList, int tier);
    kDTreeNode* rec_BuildTree(const vector<vector<int>> &pointList,const vector<int> &label, int tier)
    {
        if (pointList.size() == 0)
            return nullptr;
        int alpha = tier % k;
        int median = (pointList.size() - 1) / 2;
        vector<vector<int>> left; vector<vector<int>> right; vector<int> leftLabel; vector<int> rightLabel;
        int dataLabel;
        vector<int> data;
        vector<vector<int>> tmp = pointList;
        vector<int> tmpLabel = label;
        for (int i = 0; i < tmp.size(); i++)
        {
            for (int j = 0; j < tmp.size() - 1; j++)
            {
                if (tmp[j][alpha] > tmp[j + 1][alpha])
                {
                    swap(tmp[j + 1], tmp[j]);
                    swap(tmpLabel[j+1],  tmpLabel[j]);
                }
            }
        }
        while (median != 0 && median > 0 && tmp[median][alpha] == tmp[median - 1][alpha])
        {median--;}
        data = tmp[median];
        dataLabel = tmpLabel[median];
        for (int i = 0; i < median; i++)
        {
            left.push_back(tmp[i]);
            leftLabel.push_back( tmpLabel[i]);
        }
        for (int i = median + 1; i < pointList.size(); i++)
        {
            right.push_back(tmp[i]);
            rightLabel.push_back( tmpLabel[i]);
        }
        kDTreeNode *root = new kDTreeNode(data, dataLabel);
        root->left = rec_BuildTree(left, leftLabel, tier + 1);
        root->right = rec_BuildTree(right, rightLabel, tier + 1);
        return root;        
    }
public:
    kDTree(int k = 2);
    ~kDTree();
    const kDTree &operator=(const kDTree &other);
    kDTree(const kDTree &other);
    int nodeCount() const;
    int height() const;
    int leafCount() const;
    void inorderTraversal() const;
    void preorderTraversal() const;
    void postorderTraversal() const;
    void insert(const vector<int> &point);
    void remove(const vector<int> &point);
    bool search(const vector<int> &point);
    void buildTree(const vector<vector<int>> &pointList);
    void nearestNeighbour(const vector<int> &target, kDTreeNode*& best);
    void kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode*> &bestList);

    void buildTree(const vector<vector<int>> &pointList,const vector<int> &label)
    {
        this->count = pointList.size();
        this->root = this->rec_BuildTree(pointList, label, 0);
    }
    friend class kNN;
};

class kNN
{
private:
    int k;
    Dataset *X_train;
    Dataset *y_train;
    kDTree  kdtree;
public:
    kNN(int k = 5):k(k){};
    void fit(Dataset &X_train, Dataset &y_train)
    {
        this->X_train = &X_train;
        this->y_train = &y_train;
        if(X_train.data.size())
        {
            int dim = X_train.data.front().size();
            kdtree.k = dim;
            vector<vector<int>> pointList;
            vector<int> label;
            
            for (const auto& subList : X_train.data) {
                vector<int> subVec(subList.begin(), subList.end());
                pointList.push_back(subVec);
            }
            
            for (const auto& subList : y_train.data) {
                label.push_back(subList.front());
            }            
            kdtree.buildTree(pointList, label);
  
        }
    }
    Dataset predict(Dataset &X_test)
    {
        Dataset result; 
        result.columnName.push_back("label");
        for (const auto& subList : X_test.data) {
            // Chuyển đổi từ list<int> sang vector<int>
            vector<int> target(subList.begin(), subList.end());

            vector<kDTreeNode*> bestList;
            kdtree.kNearestNeighbour(target, this->k, bestList);

            vector<int> data(10, 0);
            for(auto i : bestList)
            {
                data[i->label] ++;
            }

            int index = 0;
            for(int i = 0; i < 10; i++)
            {
                if(data[index] < data[i]) index = i;
            }

            list<int> tmp;
            tmp.push_back(index);
            result.data.push_back(tmp);
        }
        
        return result;
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        int count = 0;
        
        list<list<int>> list1 = y_test.data;
        list<list<int>> list2 = y_pred.data;

        auto i1 = list1.begin();
        auto i2 = list2.begin();
        if (list1.size()==list2.size()) return 0;
        // Duyệt qua cả hai list đồng thời
        while (i1 != list1.end() && i2 != list2.end()) {
            // Kiểm tra nếu cả hai hàng chỉ có một phần tử và phần tử đó giống nhau
            if (*(i1->begin()) == *(i2->begin())) {
                count++;
            }
            // Tiếp tục với hàng tiếp theo
            ++i1;
            ++i2;
        }

        return count * 1.0 / y_test.data.size();
    }
void print_Y(const Dataset& y)
    {
        OUTPUT << y.columnName[0] << ": ";
        for (auto it : y.data)
        {
            OUTPUT << it.front() << " ";
        }
        OUTPUT << endl;

    }

};

// Please add more or modify as needed