#ifndef __SAMPLE_TESTCASE_H__

#define __SAMPLE_TESTCASE_H__

#include <iostream>
#include "util/ArrayLib.h"
#include "util/Point.h"
#include "util/sampleFunc.h"
#include "dsaheader.h"

#include "heap/Heap.h"

using namespace std;

/* ******* BEGIN Hash ******* */
int hashFunc(int& key, int tablesize) {
    return key % tablesize;
}

void simpleMap() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xmap<int, int> map(&hashFunc);
    for (int idx = 0; idx < 6; idx++) {
        map.put(keys[idx], values[idx]);
    }
    map.println();
    DLinkedList<int> list = map.clashes();
    list.println();

}

template<typename K>
int simpleHash(K& key, int capacity){
    return key%capacity;
}
void hashDemo1() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xmap<int, int> hash(&simpleHash<int>);
    for (int idx = 0; idx < 8; idx++) {
        hash.put(keys[idx], values[idx]);
    }
    hash.println();
}

int hashFunc(int*& item, int size) {
    return *item % size;
}

bool keyEQ(int*& lhs, int*& rhs) {
    return *lhs == *rhs;
}

void deleteKey(int *key) {
    delete key;
}

string key2str(int*& item) {
    stringstream os;
    os << *item;
    return os.str();
}

bool valueEQ(int*& lhs, int*& rhs) {
    return *lhs == *rhs;
}

string value2str(int*& item) {
    stringstream os;
    os << *item;
    return os.str();
}

void hashDemo2() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xmap<int, int*> hashMap(
            &simpleHash<int>,
            0.75,
            &valueEQ,
            &xmap<int, int*>::freeValue,
            0, //keyEQ
            0 //deleteKeys
            );
    for (int idx = 0; idx < 8; idx++) {
        hashMap.put(keys[idx], new int(values[idx]));
    }
    hashMap.println(0, &value2str);
}

void hashDemo3() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};

    xmap<int*, int*> hashMap(
            &hashFunc,
            0.75,
            &valueEQ,
            &xmap<int*, int*>::freeValue,
            &keyEQ,
            &xmap<int*, int*>::freeKey
            );
    for (int idx = 0; idx < 8; idx++) {
        hashMap.put(new int(keys[idx]), new int(values[idx]));
    }
    hashMap.println(&key2str, &value2str);
    int* pkey = new int(42);
    hashMap.remove(pkey, &deleteKey);
    delete pkey;
    hashMap.println(&key2str, &value2str);
}

void hashDemo4() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    Point * values[] = {
        new Point(2.3, 4.5), new Point(4.2, 6.7),
        new Point(5.2, 7.2), new Point(9.1, 1.8),
        new Point(8.9, 9.1), new Point(8.1, 3.1),
        new Point(3.3, 5.4), new Point(7.3, 4.2)
    };

    xmap<int*, Point*> hashMap(
            &hashFunc,
            0.75,
            &Point::pointEQ,
            &xmap<int*, Point*>::freeValue,
            &keyEQ,
            &xmap<int*, Point*>::freeKey
            );
    for (int idx = 0; idx < 8; idx++) {
        hashMap.put(new int(keys[idx]), values[idx]);
    }
    hashMap.println(&key2str, &point2str);
}

void hashDemo5() {
    int keys[] = {2, 12, 42, 72, 3, 45, 76, 30};
    int values[] = {35, 67, 100, 23, 68, 68, 72, 45};
    xmap<int, int> hash(&simpleHash<int>);
    for (int idx = 0; idx < 8; idx++) {
        hash.put(keys[idx], values[idx]);
    }

    DLinkedList<int> keyset = hash.keys();
    cout << "Keys: " << keyset.toString() << endl;
    DLinkedList<int> valueset = hash.values();
    cout << "Values: " << valueset.toString() << endl;
}

void hashDemo6() {
    int count = 100;
    int *keys = genIntArray(count, 0, 199999, true, 42);
    xmap<int, int*> hash(&simpleHash<int>);
    for (int idx = 0; idx < count; idx++) {
        hash.put(keys[idx], 0);
    }
    //hash.println();

    DLinkedList<int> clashes = hash.clashes();
    int max = -1;
    for (DLinkedList<int>::Iterator it = clashes.begin(); it != clashes.end(); it++) {
        int item = *it;
        if (item > max) max = item;
    }

    cout << "table size: " << hash.getCapacity() << endl;
    cout << "current count: " << hash.size() << endl;
    cout << "real load factor: " << (float) hash.size() / hash.getCapacity() << endl;
    cout << "max #collisions: " << max << endl;
    delete []keys;
}
/* ******* END Hash ******* */

/* ******* BEGIN Heap ******* */
void heapDemo1(){
    int array[] = {50, 20, 15, 10, 8, 6, 7, 23}; 
    //min heap: [6, 10, 7, 23, 15, 20, 8, 50]
    //max heap: [50, 23, 15, 20, 8, 6, 7, 10]
    Heap<int> minHeap1;
    cout << "Min Heap: ";
    minHeap1.heapify(array, 8);
    cout << minHeap1.toString() << endl;
    
    Heap<int> minHeap2(minHeapComparator);
    cout << "Min Heap: ";
    minHeap2.heapify(array, 8);
    cout << minHeap2.toString() << endl;
    
    Heap<int> maxHeap(maxHeapComparator);
    cout << "Max Heap: ";
    maxHeap.heapify(array, 8);
    cout << maxHeap.toString() << endl;
}

void heapDemo2(){
    Point array[] = {
        Point(13.1, 12.4), Point(5.5, 4.5), Point(15.5, 14.5),
        Point(23.1, 12.4), Point(35.5, 14.5), Point(5.5, 34.5)
    };
    Heap<Point> minHeap1(minHeapComparator);
    cout << "Min Heap: ";
    minHeap1.heapify(array, 6);
    cout << minHeap1.toString(&point2str) << endl;
    
    Heap<Point> maxHeap(maxHeapComparator);
    cout << "Max Heap: ";
    maxHeap.heapify(array, 6);
    cout << maxHeap.toString(&point2str) << endl;
}

int myPointComparator(Point*&  lhs, Point*& rhs){
    if(lhs->radius() < rhs->radius()) return -1;
    else if(lhs->radius() > rhs->radius()) return +1;
    else return 0;
}
int myPointComparatorMAX(Point*&  lhs, Point*& rhs){
    if(lhs->radius() < rhs->radius()) return +1;
    else if(lhs->radius() > rhs->radius()) return -1;
    else return 0;
}

string myPoint2Str(Point*& point){
    stringstream os;
    os << "["   << setw(6) << setprecision(2) << point->getX() 
                << ", "
                << setw(6) << setprecision(2) << point->getY()
       << "]";
    return os.str();
}
void heapDemo3(){
    Point* array[] = {
        new Point(13.1, 12.4), new Point(5.5, 4.5), new Point(15.5, 14.5),
        new Point(23.1, 12.4), new Point(35.5, 14.5), new Point(5.5, 34.5)
    };
    Heap<Point*> heap(&myPointComparatorMAX, &Heap<Point*>::free);
    for(int idx=0; idx < 6; idx++) heap.push(array[idx]);
    heap.println(&myPoint2Str);
    
    for(Heap<Point*>::Iterator it = heap.begin(); it != heap.end(); it++){
        Point* point = *it;
        cout << point->radius() << ", ";
    }
    cout << endl;
}
/* ******* END Heap ******* */

void (*func_ptr[])() = {
    // Hash
    hashDemo1,
    hashDemo2,
    hashDemo3,
    hashDemo4,
    hashDemo5,
    hashDemo6,
    // Heap
    heapDemo1,
    heapDemo2,
    heapDemo3,
    // MLP
};

void run(int func_idx) {
    func_ptr[func_idx]();
}

void runAll() {
    for (int idx = 0; idx < sizeof(func_ptr) / sizeof(func_ptr[0]); idx++) {
        run(idx);
    }
}

#endif /* __SAMPLE_TESTCASE_H__ */