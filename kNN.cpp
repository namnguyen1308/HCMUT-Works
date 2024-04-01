#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
        return;

    double numminDouble = 1.0e-15;
    int nRow = X.getData()->length();
    double row_Split = nRow * (1 - test_size);

    if (abs(round(row_Split) - row_Split) < numminDouble * nRow)
        row_Split = round(row_Split);

    X_train = X.extract(0, row_Split - 1, 0, -1);
    Y_train = Y.extract(0, row_Split - 1, 0, -1);

    X_test = X.extract(row_Split, -1, 0, -1);
    Y_test = Y.extract(row_Split, -1, 0, -1);
}