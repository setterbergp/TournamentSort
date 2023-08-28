#include <iostream>
#include <array>
using namespace std;

// Tournament structure: Participants compete in the "leaf level" (lowest level) and the winners move on the "upper levels).
// In each upper level, winners compete until a "champion" can be crowned, who goes on to the "top level" (root level).

void printList(int arr[], int arrLength);
void tournamentSort(int arr[], int arrLength);

int main() {

    int arr[] = { 8, 34, 233, 21, 89, 13, 5, 2, 144, 3, 55, 1 };
    int arrLength = sizeof(arr) / sizeof(arr[0]);

    cout << "Start array: ";
    printList(arr, arrLength);

    tournamentSort(arr, arrLength);

    cout << "End array: ";
    printList(arr, arrLength);
    
    cout << endl;
    system("pause");
}

void printList(int arr[], int arrLength)
{
    // Output the array
    for (int i = 0; i < arrLength; i++) {
        cout << arr[i] << " ";
    }
}

void tournamentSort(int arr[], int arrLength)
{
    // Determine the size of the tournament tree
    int treeSize = 1;
    while (treeSize <= arrLength) {
        treeSize *= 2;
    }

    // Creates an array with the size of the total number of nodes (elements) in the tournament tree
    int size = (2 * treeSize);
    int* tree = new int[size];

    // Assigns each node in the tree with an "infinite" (max) value of datatype used
    for (int i = 0; i < size; i++) {
        tree[i] = numeric_limits<int>::max();
    }

    // Assigns elements from the unsorted array into the array with the total 
    for (int i = 0; i < arrLength; i++) {
        tree[treeSize + i] = arr[i];
    }

    // Build the tournament tree by selecting the minimum of each pair of number of nodes
    for (int i = treeSize - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    } cout << endl;

    // Extract elements from the tournament tree in ascending order
    int sortIndex = 0;
    while (sortIndex < arrLength) {

        // Assigns root to original array and assigns "infinite" to root
        arr[sortIndex++] = tree[1];
        tree[1] = numeric_limits<int>::max();

        // Replaces minimum value with "infinite"
        int node = 1;
        while (node < treeSize) {
            int leftChild = 2 * node;
            int rightChild = 2 * node + 1;

            // Node is assigned the index number of the lowest value
            node = (tree[leftChild] < tree[rightChild]) ? leftChild : rightChild;

            // Sets smallest number to "infinite"
            if (tree[leftChild] < tree[rightChild]) {
                tree[leftChild] = numeric_limits<int>::max();
            } else {
                tree[rightChild] = numeric_limits<int>::max();
            }
        }

        // Propagates the minimum of each pair of nodes
        for (int i = treeSize - 1; i >= 1; i--) {
            tree[i] = min(tree[2 * i], tree[2 * i + 1]);
        }
    }

    delete[] tree;
}