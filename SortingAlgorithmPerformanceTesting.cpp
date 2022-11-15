//
//Name: Harshil Patel
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
typedef std::chrono::high_resolution_clock Clock;


//Insertion Sort
void InsertionSort(int* arr, int arrSize){
    int j;
    int temp;
    //Start from the beginning of the array
    for (int i = 1; i < arrSize; i++){
        j = i;
        //Swapping arr[j] and arr[j-1] until arr[j] is less than all numbers after it
        while ((j > 0) && (arr[j] < arr[j - 1])){
            temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
            j -= 1;
        }
    }
}



//BubbleSort
void BubbleSort(int* arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}



//PercolateDown for HeapSort
void PercolateDown(int* arr, int currIndex, int arrSize){
    //Left child Index
    int childIndex = 2 * currIndex + 1;
    int currNumber = arr[currIndex];
    int max;
    int maxIndex;
    
    while (childIndex < arrSize){
        max = arr[currIndex];
        maxIndex = -1;
        int i = 0;
        //Find the max value index between the current index and its children
        while ((i < 2) && ((i + childIndex) < arrSize)){
            if (arr[i + childIndex] > max){
                max = arr[i + childIndex];
                maxIndex = i + childIndex;
            }
            i += 1;
        }
        
        //If the max value is equal to the current value, heap property is met, return function
        if (max == currNumber){
            return;
        }
        
        //If heap property is not fully met, swap arr[currIndex] and arr[maxIndex]
        int temp = arr[currIndex];
        arr[currIndex] = max;
        arr[maxIndex] = temp;
        
        //Find the new child index for the new currIndex
        currIndex = maxIndex;
        childIndex = 2 * currIndex + 1;
    }
}

//Heap Sort
void HeapSort(int* arr, int arrSize){
    int index = (arrSize / 2) - 1;
    int temp;
    //Perculate Down and turn the array into a heap array
    while (index >= 0){
        PercolateDown(arr, index, arrSize);
        index -= 1;
    }
    
    index = arrSize - 1;
    while (index > 0){
        //swap arr[0] and arr[index] in order to sort the array
        temp = arr[0];
        arr[0] = arr[index];
        arr[index] = temp;
        PercolateDown(arr, 0, index);
        index -= 1;
    }
}



//Partition function for QuickSort
int Partition(int* numbers, int startIndex, int endIndex) {
   // Select the middle value as the pivot.
   int midpoint = startIndex + (endIndex - startIndex) / 2;
   int pivot = numbers[midpoint];

   // low and high start at the ends of the partition
   // and move toward each other.
   int low = startIndex;
   int high = endIndex;

   bool done = false;
   while (!done) {
      // Increment low while numbers[low] < pivot
      while (numbers[low] < pivot) {
        low = low + 1;
      }

      // Decrement high while pivot < numbers[high]
      while (pivot < numbers[high]) {
         high = high - 1;
      }

      // If low and high have crossed each other, the loop
      // is done. If not, the elements are swapped, low is
      // incremented and high is decremented.
      if (low >= high) {
         done = true;
      }
      else {
         int temp = numbers[low];
         numbers[low] = numbers[high];
         numbers[high] = temp;
         low = low + 1;
         high = high - 1;
      }
   }

   // high is the last index in the left partition.
   return high;
}

//QuickSort
void QuickSort(int* numbers, int startIndex, int endIndex) {
   // Only sort if at least 2 elements exist
   if (endIndex <= startIndex) {
      return;
   }

   // Partition the array
   int high = Partition(numbers, startIndex, endIndex);

   // Recursively sort the left partition
   QuickSort(numbers, startIndex, high);

   // Recursively sort the right partition
   QuickSort(numbers, high + 1, endIndex);
}



// RADIX SORT FUNCTIONS
int RadixGetLength(int value) {
   if (value == 0) {
      return 1;
   }
      
   int digits = 0;
   while (value != 0) {
      digits++;
      value /= 10;
   }
   return digits;
}

// Returns the maximum length, in number of digits, out of all array elements
int RadixGetMaxLength(int* numbers, int numbersSize) {
   int maxDigits = 0;
   for (int i = 0; i < numbersSize; i++) {
      int digitCount = RadixGetLength(numbers[i]);
      if (digitCount > maxDigits) {
         maxDigits = digitCount;
      }
   }
   return maxDigits;
}


// radix sort
void RadixSort(int* numbers, int numbersSize) {
   vector<vector<int>*> buckets;
   for (int i = 0; i < 10; i++) {
      vector<int>* bucket = new vector<int>();
      buckets.push_back(bucket);
   }
      
   int copyBackIndex = 0;
      
   // Find the max length, in number of digits
   int maxDigits = RadixGetMaxLength(numbers, numbersSize);
      
   int pow10 = 1;
   for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++) {
      // Put numbers into buckets
      for (int i = 0; i < numbersSize; i++) {
         int num = numbers[i];
         int bucketIndex = (abs(num) / pow10) % 10;
         buckets[bucketIndex]->push_back(num);
      }
         
      // Copy buckets back into numbers array
      copyBackIndex = 0;
      for (int i = 0; i < 10; i++) {
         vector<int>& bucket = *buckets[i];
         for (int j = 0; j < bucket.size(); j++) {
            numbers[copyBackIndex] = bucket[j];
            copyBackIndex++;
         }
         bucket.clear();
      }
      
      pow10 *= 10;
   }
      
   vector<int> negatives;
   vector<int> nonNegatives;
   for (int i = 0; i < numbersSize; i++) {
      int num = numbers[i];
      if (num < 0) {
         negatives.push_back(num);
      }
      else {
         nonNegatives.push_back(num);
      }
   }
      
   // Copy sorted content to array - negatives in reverse, then non-negatives
   copyBackIndex = 0;
   for (int i = negatives.size() - 1; i >= 0; i--){
      numbers[copyBackIndex] = negatives[i];
      copyBackIndex++;
   }
   for (int i = 0; i < nonNegatives.size(); i++) {
      numbers[copyBackIndex] = nonNegatives[i];
      copyBackIndex++;
   }
   
   // Free each dynamically allocated bucket
   for (int i = 0; i < 10; i++) {
      delete buckets[i];
   }
}


//CountingSort
void CountingSort(int arr[], int n) {
    int* final = new int[n];
    int* count = new int[n];
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        final[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = final[i];
    }
}



//merge function for MergeSort
void merge(int array[], int const left, int const mid,
    int const right)
{
    auto const subArr1 = mid - left + 1;
    auto const subArr2 = right - mid;

    auto* leftArr = new int[subArr1];
    auto* rightArr = new int[subArr2];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArr1; i++)
        leftArr[i] = array[left + i];
    for (auto j = 0; j < subArr2; j++)
        rightArr[j] = array[mid + 1 + j];

    auto index1 = 0;
    auto index2 = 0;
    int combine = left;

    // Merge the temp arrays
    while (index1 < subArr1
        && index2 < subArr2) {
        if (leftArr[index1]
            <= rightArr[index2]) {
            array[combine]
                = leftArr[index1];
            index1++;
        }
        else {
            array[combine]
                = rightArr[index2];
            index2++;
        }
        combine++;
    }

    // Copy the remaining elements of left[]
    while (index1 < subArr1) {
        array[combine]
            = leftArr[index1];
        index1++;
        combine++;
    }

    // Copy the remaining elements of right[]
    while (index2 < subArr2) {
        array[combine]
            = rightArr[index2];
        index2++;
        combine++;
    }
    delete[] leftArr;
    delete[] rightArr;
}

void MergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    MergeSort(array, begin, mid);
    MergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}



//Display the Array
string ArrayToString(int* array, int arraySize) {
   // Special case for empty array
   if (0 == arraySize) {
      return string("[]");
   }
   
   // Start the string with the opening '[' and element 0
   string result = "[" + to_string(array[0]);
   
   // For each remaining element, append comma, space, and element
   for (int i = 1; i < arraySize; i++) {
      result += ", ";
      result += to_string(array[i]);
   }
   
   // Add closing ']' and return result
   result += "]";
   return result;
}


//Run and output performance test values
void RunPerformanceTest(int randArray[], int randSize, int &totalInsertion, int &totalRadix, int &totalHeap, int &totalQuick, int &totalBubble, int &totalCounting, int &totalMerge){
    //Copy array for accurate data
    //This is to make sure we don't sort an already sorted array
    int InsertionArray[randSize];
    int RadixArray[randSize];
    int HeapArray[randSize];
    int QuickArray[randSize];
    int BubbleArray[randSize];
    int CountingArray[randSize];
    int MergeArray[randSize];
    
    for (int q = 0; q < randSize; q++){
        InsertionArray[q] = randArray[q];
        RadixArray[q] = randArray[q];
        HeapArray[q] = randArray[q];
        QuickArray[q] = randArray[q];
        BubbleArray[q] = randArray[q];
        CountingArray[q] = randArray[q];
        MergeArray[q] = randArray[q];
    }
    
    
    //Begin time tests for each sorting algorithm
    auto tradix1 = Clock::now();

    RadixSort(RadixArray,randSize);

    auto tradix2 = Clock::now();

    auto tinsertion1 = Clock::now();

    InsertionSort(InsertionArray,randSize);

    auto tinsertion2 = Clock::now();
    
    auto theap1 = Clock::now();

    HeapSort(HeapArray,randSize);

    auto theap2 = Clock::now();
    
    auto tquick1 = Clock::now();

    QuickSort(QuickArray, 0, randSize - 1);

    auto tquick2 = Clock::now();
    
    auto tbubble1 = Clock::now();

    BubbleSort(BubbleArray, randSize);

    auto tbubble2 = Clock::now();
    
    auto tcounting1 = Clock::now();

    CountingSort(CountingArray,randSize);

    auto tcounting2 = Clock::now();
    
    auto tmerge1 = Clock::now();

    MergeSort(MergeArray, 0, randSize - 1);

    auto tmerge2 = Clock::now();
    
    //Display the time for each sorting algorithm
    cout<<"Time taken for bubble sort: ";
    totalBubble += std::chrono::duration_cast<std::chrono::nanoseconds>(tbubble2 - tbubble1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(tbubble2 - tbubble1).count();
    cout<<" nanoseconds"<<endl;
    
    cout<<"Time taken for insertion sort: ";
    totalInsertion += std::chrono::duration_cast<std::chrono::nanoseconds>(tinsertion2 - tinsertion1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(tinsertion2 - tinsertion1).count();
    cout<<" nanoseconds"<<endl;
    
    cout<<"Time taken for merge sort: ";
    totalMerge += std::chrono::duration_cast<std::chrono::nanoseconds>(tmerge2 - tmerge1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(tmerge2 - tmerge1).count();
    cout<<" nanoseconds"<<endl;

    cout<<"Time taken for quick sort: ";
    totalQuick += std::chrono::duration_cast<std::chrono::nanoseconds>(tquick2 - tquick1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(tquick2 - tquick1).count();
    cout<<" nanoseconds"<<endl;

    cout<<"Time taken for heap sort: ";
    totalHeap += std::chrono::duration_cast<std::chrono::nanoseconds>(theap2 - theap1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(theap2 - theap1).count();
    cout<<" nanoseconds"<<endl;

    cout<<"Time taken for counting sort: ";
    totalCounting += std::chrono::duration_cast<std::chrono::nanoseconds>(tcounting2 - tcounting1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(tcounting2 - tcounting1).count();
    cout<<" nanoseconds"<<endl;

    cout<<"Time taken for radix sort: ";
    totalRadix += std::chrono::duration_cast<std::chrono::nanoseconds>(tradix2 - tradix1).count();
    cout<<std::chrono::duration_cast<std::chrono::nanoseconds>(tradix2 - tradix1).count();
    cout<<" nanoseconds"<<endl;

    
    //Display Sorted Array;
    cout << "SORTED: ";
    cout<<ArrayToString(RadixArray,randSize);
    cout << endl <<endl;

}

int main() {
    //Ask user for size of n
    int n;
    int numberOfTests;
    cout << "Enter the size of n (10, 100, 500, 5000, or 25000): ";
    cin >> n;
    cout << "Enter the number of tests you would like to run: ";
    cin >> numberOfTests;
    cout << endl;
    
    int randSize = n;
    int randArray[n];
    srand((unsigned) time(0));
    
    //Variable to total all the perfermance times of each sorting algorithm
    //used for average
    int totalInsertion = 0;
    int totalRadix = 0;
    int totalHeap = 0;
    int totalQuick = 0;
    int totalBubble = 0;
    int totalCounting = 0;
    int totalMerge = 0;
    
    for (int j = 0; j < numberOfTests; j++){
        //Create Random Unsorted Array
        for (int i = 0; i < n; i++) {
            randArray[i] = rand() % (2 * n + 1);
        }
        cout << "UNSORTED: ";
        cout<<ArrayToString(randArray,randSize);
        cout << endl;
        RunPerformanceTest(randArray, randSize, totalInsertion, totalRadix, totalHeap, totalQuick, totalBubble, totalCounting, totalMerge);
    }
    
    cout<<endl<<endl;
    
    //Compute the average time in 10 runs for each sorting algorithm
    cout<<"Bubble Sort Average: "<<totalBubble / numberOfTests<<endl;
    cout<<"Insertion Sort Average: "<<totalInsertion / numberOfTests<<endl;
    cout<<"Merge Sort Average: "<<totalMerge / numberOfTests<<endl;
    cout<<"Quick Sort Average: "<<totalQuick / numberOfTests<<endl;
    cout<<"Heap Sort Average: "<<totalHeap / numberOfTests<<endl;
    cout<<"Counting Sort Average: "<<totalCounting / numberOfTests<<endl;
    cout<<"Radix Sort Average: "<<totalRadix / numberOfTests<<endl<<endl;
    
    return 0;
}
