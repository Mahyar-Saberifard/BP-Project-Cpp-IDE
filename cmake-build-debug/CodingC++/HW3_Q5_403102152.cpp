#include <iostream>

using namespace std;

int main() {
    int n, m, l;
    cin >> n >> m >> l;

    int bx = 0, by = 0;
    int min_bx = 0, max_bx = 0;
    int min_by = 0, max_by = 0;
    for (int i = 0; i < l; i++) {
        int x;
        cin >> x;
        if (x == 0) {
            by--;
            min_by = min(min_by, by);
        }
        else if (x == 1) {
            by++;
            max_by = max(max_by, by);
        }
        else if (x == 2) {
            bx--;
            min_bx = min(min_bx, bx);
        }
        else {
            bx++;
            max_bx = max(max_bx, bx);
        }

        if (max_bx - min_bx >= n) {
            if (bx == min_bx) 
                min_bx++;
            break;
        }
        if (max_by - min_by >= m) {
            if (by == min_by) 
                min_by++;
            break;
        }
    }

    cout << 1 - min_bx << ' ' << 1 - min_by << '\n';
}
