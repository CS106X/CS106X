#include "pqueue-vector.h"
using namespace std;

VectorPQueue::VectorPQueue() {}
VectorPQueue::~VectorPQueue() {}

const string& VectorPQueue::peek() const {
    string min = VectorPQueue::vec[0];
    int idx = 0;
    for (int i = 0; i < VectorPQueue::vec.size(); i++) {
        if (VectorPQueue::vec[i] < min) {
            min = VectorPQueue::vec[i];
            idx = i;
        }
    }
    return VectorPQueue::vec[idx];
}

string VectorPQueue::extractMin() {
    string min = VectorPQueue::vec[0];
    int idx = 0;
    for (int i = 0; i < VectorPQueue::vec.size(); i++) {
        if (VectorPQueue::vec[i] < min) {
            min = VectorPQueue::vec[i];
            idx = i;
        }
    }
    VectorPQueue::vec.remove(idx);
    PQueue::logSize--;
    return min;
}

void VectorPQueue::enqueue(const string& s) {
    VectorPQueue::vec.add(s);
    PQueue::logSize++;
}

VectorPQueue *VectorPQueue::merge(VectorPQueue * one, VectorPQueue * two) {
    VectorPQueue *vpq = new VectorPQueue();
    while (one->size() > 0) {
        vpq->enqueue(one->extractMin());
    }
    while (two->size() > 0)  {
        vpq->enqueue(two->extractMin());
    }
    return vpq;
}
