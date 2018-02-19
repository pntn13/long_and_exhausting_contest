#include <cassert>
#include <iostream>

using namespace std;

struct List {
    List() {}

    List(int _x): x(_x) {}

    ~List() {
        delete next;
    }

    int x = 0;
    List* next = nullptr;
};

struct MyList {
    List* begin = nullptr;
    List* end = nullptr;

    MyList() {}

    MyList(int _x) {
        List* t = new List(_x);
        begin = end = t;
    }

    MyList(List* l) {
        begin = l;
        while (l->next != nullptr) {
            l = l->next;
        }
        end = l;
    }

    ~MyList() {
        delete begin;
    }

    void push_back(int y) {
        if (begin == nullptr) {
            List* t = new List(y);
            begin = end = t;
            return;
        }
        List* t = new List(y);
        end->next = t;
        end = t;
    }

    void push_back(List* y) {
        y->next = nullptr;
        if (begin == nullptr) {
            begin = end = y;
            return;
        }
        end->next = y;
        end = y;
    }
};

ostream& operator<<(ostream& out, const MyList &a) {
    for (auto i = *a.begin;; i = *i.next) {
        out << i.x << " ";
        if (i.next == nullptr) {
            break;
        }
    }
    return out;
}

void merge(MyList& a, MyList& b, MyList& res) {
    bool aover = false, bover = false;
    while (!(aover && bover)) {
        if (!aover && (bover || a.begin->x <= b.begin->x)) {
            auto j = a.begin->next;
            res.push_back(a.begin);
            a.begin = j;
            if (a.begin == nullptr) {
                a.end = nullptr;
                aover = true;
            }
        } else {
            auto j = b.begin->next;
            res.push_back(b.begin);
            b.begin = j;
            if (b.begin == nullptr) {
                b.end = nullptr;
                bover = true;
            }
        }
    }
}

void sort(MyList& a) {
    if (a.begin == a.end) {
        return;
    }
    MyList l, r;
    bool flag = true;
    for (auto i = a.begin; i != nullptr;) {
        auto j = i->next;
        if (flag) {
            l.push_back(i);
        } else {
            r.push_back(i);
        }
        flag ^= 1;

        i = j;
    }
    a.begin = a.end = nullptr;
    sort(l);
    sort(r);
    merge(l, r, a);
}


int main() {
    assert(freopen("input.txt", "r", stdin));

    int n;
    cin >> n;

    MyList a;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    sort(a);
    cout << a << endl;
}
