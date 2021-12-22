/* Your code here! */
#include <vector>
#include "dsets.h"

using namespace std;
void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        _elems.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    int a = elem;
    int temp = 0;
    while(_elems[a] > 0){
        a = _elems[a];      //set a as address of root
    }
    while(_elems[elem] > 0){
        temp = _elems[elem];    //temp is parent of current node
        _elems[elem] = a;       //set currnode parent as root
        elem = temp;            //set elem as prev parent node
    }
    return a;
}

void DisjointSets::setunion(int a, int b){
    while(_elems[a] > 0){
        a = _elems[a];
    }
    while(_elems[b] > 0){
        b = _elems[b];
    }

    if (a == b){
        return;
    }

    if(_elems[a] > _elems[b]){
        _elems[b] += _elems[a];
        _elems[a] = b;
    }else{
        _elems[a] += _elems[b];
        _elems[b] = a;
    }
}

int DisjointSets::size(int elem){
    while(_elems[elem] > 0){
        elem = _elems[elem];
    }
    return -_elems[elem];
}

vector<int> DisjointSets::output(){
    return _elems;
}

void DisjointSets::reset(){
    _elems.clear();
}