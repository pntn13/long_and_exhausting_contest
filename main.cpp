#include <cassert>
#include <iostream>

using namespace std;

struct List {
    List() {}

    List(int _x): x(_x) {}

    ~List() {
        if (next != nullptr) {
            delete next;
        }
    }

    int x = 0;
    List* next = nullptr;
};

List* merge(List* a, List* b) {
    if (a == nullptr) {
        return b;
    }
    if (b == nullptr) {
        return a;
    }
    if (a->x > b->x) {
        swap(a, b);
    }
    List* res = new List(a->x);
    List* fin = res;
    for (auto i = a->next, j = b;;) {
        if (i == nullptr) {
            swap(i, j);
        }
        if (j == nullptr) {
            while (i != nullptr) {
                List* t = new List(i->x);
                fin->next = t;
                fin = t;
                i = i->next;
            }
            break;
        }
        if (i->x > j->x) {
            swap(i, j);
        }

        List* t = new List(i->x);
        fin->next = t;
        fin = t;
        i = i->next;
    }
    return res;
}

List* sort(List* a) {
    if (a->next == nullptr) {
        List* res = new List(a->x);
        return res;
    }
    auto fin = a;
    List* l = new List(fin->x);
    auto finl = l;
    fin = fin->next;
    List* r = new List(fin->x);
    fin = fin->next;
    auto finr = r;
    for (; fin != nullptr; fin = fin->next) {
        List* t = new List(fin->x);
        finl->next = t;
        finl = t;
        swap(l, r);
        swap(finl, finr);
    }
    List* sl = sort(l);
    List* sr = sort(r);
    List* res = merge(sl, sr);

    delete sl;
    delete sr;
    delete l;
    delete r;

    return res;
}

ostream& operator<<(ostream& out, List* a) {
    for (auto i = a; i != nullptr; i = i->next) {
        out << i->x << " ";
    }
    return out;
}

int main() {
    assert(freopen("input.txt", "r", stdin));

    int n;
    cin >> n;
    int x;
    cin >> x;
    List* a = new List(x);
    List* fin = a;
    for (int i = 1; i < n; ++i) {
        cin >> x;
        List* t = new List(x);
        fin->next = t;
        fin = t;
    }

    List* res = sort(a);
    cout << res << endl;
    delete res;
    delete a;
}
