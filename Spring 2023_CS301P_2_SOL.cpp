#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string name;
    int frequency;

public:
	public:
    // Default constructor
    Product() {
        name = "";
        frequency = 0;
    }
    // Constructor
    
    Product(const string& productName, int productFrequency) {
        name = productName;
        frequency = productFrequency;
    }

  
    string getName() const {
        return name;
    }

    int getFrequency() const {
        return frequency;
    }

    // Increment frequency by 1
    void incrementFrequency() {
        frequency++;
    }
};

class Heap {
private:
    int currentSize; // number of elements in heap
    Product array[100]; // the heap array, assuming maximum size of 100
    int capacity;

public:
    Heap(int size) {
        currentSize = 0;
        capacity = size;
    }

    void percolateDown(int hole) {
        int child;
        Product temp = array[hole];
        for (; hole * 2 <= currentSize; hole = child) {
            child = hole * 2;
            if (child != currentSize && array[child + 1].getFrequency() > array[child].getFrequency())
                child++;
            if (array[child].getFrequency() > temp.getFrequency())
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = temp;
    }

    void buildHeap(Product* anArray, int n) {
        for (int i = 0; i < n; i++)
            array[i + 1] = anArray[i];
        currentSize = n;
        for (int i = currentSize / 2; i > 0; i--)
            percolateDown(i);
    }

    void updateAndRebuildHeap(const string& productName) {
        int index = -1;
        for (int i = 1; i <= currentSize; i++) {
            if (array[i].getName() == productName) {
                index = i;
                break;
            }
        }
        if (index == -1)
            return;
        array[index].incrementFrequency();
        percolateDown(index);

        buildHeap(array + 1, currentSize);
    }

    void traverse() {
        for (int i = 1; i <= currentSize; i++)
            cout << array[i].getName() << "(" << array[i].getFrequency() << ") ";
        cout << endl;
    }

    Product getMax() {
        return array[1];
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == capacity;
    }
};

int main() {
    int size = 7;
    Heap heap(size);
    Product products[size] = {Product("P1", 15), Product("P2", 14), Product("P3", 13), Product("P4", 10), Product("P5", 16), Product("P6", 9), Product("P7", 12)}; 

    int choice, input = 1;
    string searchProduct;

    cout << "Current Products with their frequencies" << endl;
    cout << "P1 = 15, P2 = 14, P3 = 13, P4 = 10, P5 = 16, P6 = 9, P7 = 12" << endl;

    while (input != 0) {
        cout << "\n" << "Enter your choice: " << endl;
        cout << "Enter 1 to create Heap" << endl;
        cout << "Enter 2 to search for a product and update its frequency" << endl;
        cout << "Enter 3 to see the product with the highest frequency" << endl;
        cout << "Enter 0 to terminate the program" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                heap.buildHeap(products, 7);
                cout << "Heap created: ";
                heap.traverse();
                break;

            case 2: {
                cout << "Enter the product you want to search or type 'No' to exit" << endl;
                cin >> searchProduct;
                if (searchProduct == "No") {
                    break;
                } else {
                		if(heap.isEmpty()) {
	  	            cout <<endl<<"No element in heap yet!!" << endl;
	                   }
	                   else{
					   
                    heap.updateAndRebuildHeap(searchProduct);
                    cout << "Updated Heap: ";
                    heap.traverse();
                }
            }
                break;
            }

            case 3: {
            	if(heap.isEmpty()) {
		cout <<endl<<"No element in heap yet!!" << endl;
	               }
	               else{
				   
                Product maxProduct = heap.getMax();
                cout << "Top product: " << maxProduct.getName() << "(" << maxProduct.getFrequency() << ")" << endl;
                break;
            }
        }

            case 0:
                exit(0);
                break;

            default:
                cout << "Wrong option" << endl;
                break;
        }
    }

    return 0;
}

