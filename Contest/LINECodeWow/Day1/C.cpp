#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> depth;
int depthIndex = -1;

void showCollapse() {
    if (depthIndex < 0) return;
    cout << "collapse";
    for (int i = 0; i <= depthIndex; ++i)
        cout << '_' << depth[i];
    cout << ':';
}

void showLink(const string& data) {
    showCollapse();
    cout << data.substr(0, 5) << ' ' << data.substr(5, data.size() - 6) << '\n';
}

void showImage(const string& data) {
    showCollapse();
    cout << data.substr(0, 6) << ' ' << data.substr(6, data.size() - 7) << '\n';
}

void showMedia(const string& data) {
    showCollapse();
    cout << data.substr(0, 6) << ' ' << data.substr(6, data.size() - 7) << '\n';
}

void showText(string& data) {
    //standard TEXT

    reverse(data.begin(), data.end());
    while (data.back() == ' ') data.pop_back();
    reverse(data.begin(), data.end());
    while (data.back() == ' ') data.pop_back();

    if (data.size()) {
        showCollapse();
        cout << "text: " << data << '\n';
    }
    data.clear();
}

int main() {

#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    string line;
    string current;
    while (getline(cin, line)) {
        int openPos = line.find("[[");
        int closePos = line.find("]]");
        int collapseClosePos = line.find("]]]");
        // find TEXT
        if (openPos == -1) openPos = line.size();
        if (collapseClosePos == -1) collapseClosePos = line.size();

        for (int i = 0; i < min(collapseClosePos, openPos); ++i)
            current += line[i];

        if (openPos != line.size() || collapseClosePos != line.size())
            showText(current);

        char charAtNext = ' ';
        if (openPos != line.size()) charAtNext = line[openPos + 2];
        if (charAtNext == '[') { // complex object
            depthIndex++;
            if (depthIndex >= depth.size())
                depth.push_back(1);
            else {
                depth[depthIndex]++; // new
                for (int i = depthIndex + 1; i < depth.size(); ++i)
                    depth[i] = 0;
            }
            showCollapse();
            cout << " start\n";
        } else if (charAtNext == 'i') { // image
            showImage(line.substr(openPos + 2, closePos - openPos - 1));
        } else if (charAtNext == 'l') { // link
            showLink(line.substr(openPos + 2, closePos - openPos - 1));
        } else if (charAtNext == 'm') { // media
            showMedia(line.substr(openPos + 2, closePos - openPos - 1));
        }

        if (collapseClosePos != line.size()) {
            showCollapse();
            depthIndex--;
            cout << " end\n";
        }
    }
    return 0;
}
