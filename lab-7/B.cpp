#include <iostream>
#include <vector>
#include <map>

struct Node {
    long long pos;
    char next;
};

void LZ78(const std::string &s) {
    std::string buffer = "";
    std::map<std::string, long long> dict;
    std::vector<Node> ans;
    for (long long i = 0; i < s.size(); ++i) {
        if (dict.find(buffer + s[i]) != dict.end()) {
            buffer += s[i];
        } else {
            ans.push_back({dict[buffer], s[i]});
            dict[buffer + s[i]] = dict.size();
            buffer = "";
        }
    }
    if (!buffer.empty()) {
        char last_ch = '\0';
        ans.push_back({dict[buffer], last_ch});
    }
    for (long long i = 0; i < ans.size(); ++i) {
        std::cout << ans[i].pos << " " << ans[i].next << "\n";
    }
}

int main() {
    std::string enter_data;
    std::cin >> enter_data;
    LZ78(enter_data);
    std::cout << "\n";
}