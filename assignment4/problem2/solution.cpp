//////////////////////////////////////////////////////////
// Name 1:Sishi Cheng     Access ID:smc6823
// Name 2:Leran Ma        Access ID:lkm5463
// Name 3:Ivy Chen        Access ID:ikc5058

#include <iostream>
#include <cstring>

using namespace std;

int palindromic(const string &s) {
    int length[s.length()][s.length()];
    for (int i = 0; i < s.length(); ++i) {
        length[i][i] = 1;
    }

    for (int i = 1; i < s.length(); ++i) {
        length[i][i-1] = 0;
    }

    for (int d = 1; d < s.length(); ++d) {
        for (int i = 0; i < s.length()-d; ++i) {
            if (s[i] == s[i+d]){
                length[i][i+d] = length[i+1][i+d-1] + 2;
            }
            else{
                if (length[i][i+d-1] > length[i+1][i+d]) {
                    length[i][i+d] = length[i][i+d-1];
                }
                else{
                    length[i][i+d] = length[i+1][i+d];
                }
            }
        }
    }
    return length[0][s.length()-1];
}

int main() {

    string sequence;
    cin >> sequence;

    cout << palindromic(sequence);

}
