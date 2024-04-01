#include "main.hpp"

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
//adding functions 
    virtual void getArray(T*array) const=0;
    virtual List<T> *subList(int start, int end) = 0;
    virtual void printStartToEnd(int start, int end) const = 0;
};

//
// class Image
template <typename T>
class Image : public List<T>
{
private:
    class Node
    {
    public:
        T pointer;
        Node *next;

    public:
        Node(T pointer, Node *next = nullptr) : pointer(pointer), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    Image()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~Image()
    {
        this->clear();
    }
    void push_back(T value)
    {
         Node*newnode=new Node(value);
          if(this->size ==0) {
        this->head=newnode;
        this->tail=newnode;
            
        }
        else {
            this->tail->next=newnode;
            this->tail=newnode;
        }
        
    this->size++;
    }
    void push_front(T value)
    {
         Node*newnode=new Node(value);
        newnode->next=NULL;
            if(this->size==0){
                this->head=newnode;
                this->tail=newnode;
            }else{
                newnode->next=head;
                this->head=newnode;
            }
            this->size++;
    }
    void insert(int index, T value)
    {
         if(index < 0 || index > size) return;
        if (size==0 || index==0){
            return push_front(value);  
    }
       else if (index == size) {
            return push_back(value);
            }
         else {
            Node*newnode=new Node(value);
            Node*tmp=this->head;
            for(int i=0;i<index-1;i++) tmp=tmp->next;
            newnode->next=tmp->next;
            tmp->next=newnode;
         }
        this->size++;
    }
    void remove(int index){
        if(index < 0 || index >= size) return;
 
         if (index == 0) {
        Node* temp = this->head;
       this-> head = this->head->next;
        delete temp;
    } else {
        Node* Prev =this-> head;
        for (int i = 0; i < index - 1; ++i) {
            Prev = Prev->next;
        }
        Node* deleteNode = Prev->next;
        Prev->next = deleteNode->next;
        if (index == size - 1) {
            tail = Prev;
        }
        delete deleteNode;
    }
    --size;
    }
    T &get(int index) const
    {
         if(index < 0 || index >= this->size)  throw std::out_of_range("get(): Out of range");
       
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->pointer;
        //
    }
    int length() const{
        return size;
        // 
    }
   
    void clear()
    {
        while (this->head) {
            Node* temp =this->head;
            this->head =this-> head->next;
            delete temp;
        }     
        this->head=this->tail=NULL;
        this->size=0;
    }
    void print() const
    {
        if (size == 0)
            return;
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }
    void reverse()
    {
        Node* prev = NULL;
        Node* tmp =this-> head;
    Node* next = NULL;

    while (tmp != NULL) {
        next = tmp->next;  
        tmp->next = prev;  
        prev = tmp;       
        tmp = next;
    }
       this-> tail=this->head;
        this->head = prev;
    }
    void printStartToEnd(int start, int end) const
    {
        Node *temp = head;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->pointer;
            else
                cout << temp->pointer << " ";
            temp = temp->next;
        }
    }
    List<T> *subList(int start, int end)
    {   
        List<T>*result=new Image<T>();
         if(this->size <= start)  
         {  
            return result;
         }
       Node*tmp=this->head;
       for(int i=0;i<start;i++) tmp=tmp->next;

       for(int i=start;i<this->size && i<end;i++){
        result->push_back(tmp->pointer);
        tmp=tmp->next;
       }
        return result;
    }
     void getArray(T*array) const override
    {
         Node* current = head;
    int index = 0;
    while (current != nullptr) {
        array[index++] = current->pointer;
        current = current->next;
    }
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *Collumn;
    // You may need to define more
public:
    Dataset()
    {
        this->Collumn = new Image<string>();
        this->data = new Image<List<int> *>();
    }
    ~Dataset()
    {
        delete data;
        delete Collumn;
    }
    Dataset(const Dataset &other)
    {
        this->Collumn = new Image<string>();
        this->data = new Image<List<int> *>();
 int dtlen = other.data->length(); 
    int nclen= other.Collumn->length();
    for (int i = 0; i < nclen; i++) {
        string tmp=other.Collumn->get(i);
        this->Collumn->push_back(tmp);
        }
        for (int i = 0; i < dtlen; i++) {
        List<int>* tmp = new Image<int>(); 
        for (int j = 0; j < other.data->get(i)->length(); j++) {
           int fact=other.data->get(i)->get(j);
           tmp->push_back(fact); 
        }
        this->data->push_back(tmp); 
    }
        // TODO: implement Task 2
    }
    Dataset &operator=(const Dataset &other)
    {
       if (this == &other) {
        return *this;
    }

    this->Collumn->clear();
    this->data->clear();

  
    for (int i = 0; i < other.Collumn->length(); ++i) {
        this->Collumn->push_back(other.Collumn->get(i));
    }

    // Copy data from other
    for (int i = 0; i < other.data->length(); ++i) {
        List<int>* row = new Image<int>(); 
        for (int j = 0; j < other.data->get(i)->length(); ++j) {
            row->push_back(other.data->get(i)->get(j));
        }
        this->data->push_back(row);
    }

    return *this;
    }
    List<List<int> *> *getData() const
    {
        return data;
    }
    bool loadFromCSV(const char *fileName)
    {
        ifstream file(fileName);
        if (file.is_open())
        {
            string s;
            int num;
            file >> s;
            for (int i = 0; i < s.length(); i++)
            {
                if (s[i] == ',')
                    s[i] = ' ';
            }
            stringstream ss(s);
            while (ss >> s)
                Collumn->push_back(s);
            while (file >> s)
            {
                for (int i = 0; i < s.length(); i++)
                {
                    if (s[i] == ',')
                        s[i] = ' ';
                }
                stringstream ss(s);
                List<int> *temp = new Image<int>();
                while (ss >> num)
                    temp->push_back(num);
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void getShape(int &nRows, int &nCols) const
    {   
        if(this->data->length()==0){
            nRows=0;
            nCols=0;
         } else if( this->Collumn->length()==0){
             nRows=0;
            nCols=0;
         } else{
            nRows=this->data->length();
            nCols=this->Collumn->length();
         }
    }
    void columns() const
    {
      int n=Collumn->length();
     for(int i=0;i<n;i++){
        if(i==n-1){
            cout<<this->Collumn->get(i);
        }else{
            cout<<this->Collumn->get(i)<< " ";
        }
      
     }
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
       if(nRows <= 0 || nCols <= 0) return;
         if(this->Collumn->length()<nCols) nCols=this->Collumn->length();
         if(this->data->length()<nRows) nRows=this->data->length();
         this->Collumn->printStartToEnd(0,nCols);
        for(int i=0;i<nRows;i++){
            cout << endl;
           this->data->get(i)->printStartToEnd(0,nCols);
           
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
       if (nRows <= 0 || nCols<= 0 ) return;
       int nclen=this->Collumn->length();
        int dtlen=this->data->length();
     if(this->data->length()==0 || this->data->get(0)->length()==0 ) {
        this->Collumn->printStartToEnd(this->Collumn->length()-nCols,this->Collumn->length());
        return; 
     }
        if (nclen<=nCols) nCols=nclen;
        if(dtlen<=nRows) nRows=dtlen;
        this->Collumn->printStartToEnd(nclen-nCols,nclen);
        for(int i=dtlen-nRows;i<dtlen;i++)
        {  
            cout<<endl;
            this->data->get(i)->printStartToEnd(nclen-nCols,nclen); 
            
        }
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        
       if (axis != 0 && axis != 1) {
        return false;
    }
   
    if (axis == 0) { 
        if (index < 0 || index >= data->length()) {
            return false; 
        }
        data->remove(index);
    } else { 
        int idx = -1;
        int label = Collumn->length();
        for (int i = 0; i < label; i++) {
            if (Collumn->get(i) == columns) {
                idx = i;
                break;
    }     }
        if (idx != -1) {
            Collumn->remove(idx);
            int dataLen = data->length();
            for (int i = 0; i < dataLen; i++) {
                data->get(i)->remove(idx);
            }
        } else {
            return false; 
        }  }
    return true;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
         Dataset result;
    if (this->Collumn->length()==0 || this->data->length()==0 || startCol<0|| startRow<0) return result;
    // if (startRow>endRow || endRow<-1) {throw std::out_of_range("get(): Out of range");}
    if(endRow < -1 || endCol < -1) {throw std::out_of_range("get(): Out of range");}
    if(endRow > -1 && startRow > endRow)
    {throw std::out_of_range("get(): Out of range");}
    if (endCol > -1 && startCol > endCol)
    {
        throw std::out_of_range("get(): Out of range");
    }
    if (endCol == -1 || endCol >= this->Collumn->length()) {
        endCol = this->Collumn->length() - 1;
    }   
    if (endRow == -1 || endRow >= this->data->length()) {  
        endRow = this->data->length() - 1;
    }
    if(startRow>this->data->length()-1 || startCol>this->data->get(0)->length()-1)
    {
        throw std::out_of_range("get(): Out of range");
    }
  
    if (startRow <= endRow && startCol <= endCol) {
        for (int i = startRow; i <= endRow; ++i) {
          List<int>*tmp= new Image<int>();
            tmp=this->data->get(i)->subList(startCol, endCol +1);
            result.data->push_back(tmp);
        }
        // Lấy tên cột từ cột startCol đến endCol
        for (int i = startCol; i <= endCol; ++i) {
            string tmp="";
            tmp=this->Collumn->get(i);
            result.Collumn->push_back(tmp);    
        }
    }
    return result;
    }

    double distanceEuclidean(const List<int> *x, const List<int> *y) const {
    if (x->length() != y->length()) {
        // Lists must have the same length to compute Euclidean distance
        return -1; // or throw an exception, depending on your design
    }

    int length = x->length(); // or y->length(), both are the same length
    int* arrayX = new int[length];
    int* arrayY = new int[length];

    // Fill arrays with elements from lists
    x->getArray(arrayX);
    y->getArray(arrayY);

    double sumOfSquares = 0.0;
    for (int i = 0; i < length; ++i) {
        double diff = arrayX[i] - arrayY[i];
        sumOfSquares += diff * diff;
    }

    delete[] arrayX;
    delete[] arrayY;

    return sqrt(sumOfSquares);
}

    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const
    {
        Dataset learn;
        if(this->data->length()==0||this->Collumn->length()==0) return learn;
        if(k > X_train.data->length()) throw std::out_of_range("get(): Out of range");
        learn.Collumn->push_back(Y_train.Collumn->get(0));
        for(int i=0;i<this->data->length();i++){
            double* dist=new double[X_train.data->length()];
            int*so=new int[Y_train.data->length()];
            for(int j=0;j<X_train.data->length();j++){
                dist[j]=this->distanceEuclidean(this->data->get(i),X_train.data->get(j));
                so[j]=Y_train.data->get(j)->get(0);
            }          
            for(int i=0;i<X_train.data->length()-1;i++){
                for(int j=0;j<X_train.data->length()-1;j++){
                    if(dist[j]>dist[j+1]){
                        double tmp=dist[j];
                        dist[j]=dist[j+1];
                        dist[j+1]=tmp;
                        tmp=so[j];
                        so[j]=so[j+1];
                        so[j+1]=tmp;
                    }
                }
            }
             int arr[10]={0};
             int doluong=0;
             if(k>Y_train.data->length()) {
                doluong=Y_train.data->length();
             } else {
                doluong=k;
             }
             for(int i=0;i<doluong;i++){
              arr[so[i]] +=1;
             }
             int maxIndex = 0; 

    for (int i = 1; i <10; ++i) {
        if (arr[i] > arr[maxIndex]) {     
            maxIndex = i; 
        }
    }
    List<int>*tmp=new Image<int>();
    tmp->push_back(maxIndex );
    learn.data->push_back(tmp);
        }
    return learn;
    }
    double score(const Dataset &y_predict) const
    {
        if (this->data->length()==0 || y_predict.data->length()==0||this->data->get(0)->length()==0)
        {
       return -1;
        }
        if(y_predict.data->length()!=this->data->length()) return -1;
        double result = 0;
        for (int i = 0; i < y_predict.data->length(); ++i)
        {
        if(this->data->get(i)->get(0)==y_predict.data->get(i)->get(0)) result++;
        }

        if (result==0) return 0;
        return result/static_cast<double>(y_predict.data->length());
    }

};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {   
        
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test);

// Please add more or modify as needed
