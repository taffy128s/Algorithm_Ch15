#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#define UPLEFT  0
#define UP      1
#define LEFT    2

int LCS_length_first(std::string str1, std::string str2) {
    if (str2.size() < str1.size()) std::swap(str1, str2);
    str1 = " " + str1;
    str2 = " " + str2;
    /* Give the size and allocate the arrays. */
    int m = str2.size(), n = str1.size();
    int *arr1 = new int[n], *arr2 = new int[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = 0;
        arr2[i] = 0;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (str1[j] == str2[i]) {
                arr2[j] = arr1[j - 1] + 1;
            } else {
                arr2[j] = std::max(arr1[j], arr2[j - 1]);
            }
        }
        for (int j = 1; j < n; j++) {
            arr1[j] = arr2[j];
        }
    }
    return arr2[n - 1];
}

int LCS_length_second(std::string str1, std::string str2) {
    if (str2.size() < str1.size()) std::swap(str1, str2);
    str1 = " " + str1;
    str2 = " " + str2;
    /* Give the size and allocate the array. */
    int m = str2.size(), n = str1.size();
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = 0;
    for (int i = 1; i < m; i++) {
        int prev1 = 0;
        for (int j = 1; j < n; j++) {
            int prev2 = arr[j];
            if (str1[j] == str2[i]) {
                arr[j] = prev1 + 1;
            } else {
                arr[j] = std::max(arr[j - 1], arr[j]);
            }
            prev1 = prev2;
        }
    }
    return arr[n - 1];
}

std::list<char> LCS(std::string str1, std::string str2) {
    if (str2.size() < str1.size()) std::swap(str1, str2);
    str1 = " " + str1;
    str2 = " " + str2;
    /* Give the size and allocate the table. */
    int m = str2.size(), n = str1.size();
    int **table = new int*[m], **ref_memo = new int*[m];
    for (int i = 0; i < m; i++) {
        table[i] = new int[n];
        ref_memo[i] = new int[n];
    }
    /* Start */
    for (int i = 0; i < m; i++)
        table[i][0] = 0;
    for (int i = 0; i < n; i++)
        table[0][i] = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (str1[j] == str2[i]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                ref_memo[i][j] = UPLEFT;
            } else if (table[i - 1][j] > table[i][j - 1]) {
                table[i][j] = table[i - 1][j];
                ref_memo[i][j] = UP;
            } else {
                table[i][j] = table[i][j - 1];
                ref_memo[i][j] = LEFT;
            }
        }
    }
    /* Move element to list */
    std::list<char> l;
    int i = m - 1, j = n - 1;
    while (i > 0 && j > 0) {
        if (ref_memo[i][j] == UPLEFT) {
            l.push_front(str1[j]);
            i--;
            j--;
        } 
        else if (ref_memo[i][j] == UP) i--;
        else j--;
    }
    return l;
}

int main() {
    std::list<char> l = LCS("DORMITORY", "DIRTYROOM");
    for (auto i : l)
        std::cout << i;
    std::cout << std::endl;
    std::cout << LCS_length_first("DORMITORY", "DIRTYROOM") << std::endl;
    std::cout << LCS_length_second("DORMITORY", "DIRTYROOM") << std::endl;
    return 0;
}
