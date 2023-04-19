#include <vector>
#include <string>

// 71. Simplify Path
class Solution71 {
public:
    std::string simplifyPath(std::string path) {
        std::vector<int> slashs = {0};
        int n = 1;
        for (int i = 1; i < path.size(); i++) {
            if (path[i] == '/') {
                if (path[i - 1] == '/')
                    continue;
                slashs.push_back(n);
            }
            if (path[i] == '.') {
                if (path[i - 1] == '.' && path[i - 2] == '/' && (i + 1 == path.size() || path[i + 1] == '/')) {
                    if (slashs.size() > 1)
                        slashs.pop_back();
                    n = slashs.back() + 1;
                    i++;
                    continue;
                }
                else if (path[i - 1] == '/' && (i + 1 == path.size() || path[i + 1] == '/')) {
                    n = slashs.back() + 1;
                    i++;
                    continue;
                }
            }

            path[n++] = path[i];
        }
        if (path[n - 1] == '/' && n > 1)
            n--;
        path.resize(n);
        return path;
    }
};
