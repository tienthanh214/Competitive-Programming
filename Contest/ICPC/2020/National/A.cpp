#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> ii;

const string sign[] = {"Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo",
                    "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces"};
const int day[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

map<string, int> mp;
vector<ii> low;
vector<ii> high;
vector<ii> res;
vector<int> cur;

int countDay(int m, int d) {
    int cnt = 0;
    for (int i = 1; i < m; ++i)
        cnt += day[i];
    //if (m <= 2) cnt += 366;
    return cnt + d;
}

void init() {
    mp["Mar"] = 3;
    mp["Apr"] = 4;
    mp["May"]   = 5;
    mp["Jun"]  = 6;
    mp["Jul"]  = 7;
    mp["Aug"] = 8;
    mp["Sep"] = 9;
    mp["Oct"] = 10;
    mp["Nov"] = 11;
    mp["Dec"] = 12;
    mp["Jan"] = 1;
    mp["Feb"] = 2;
    res.push_back({mp["Mar"], 21});
    res.push_back({mp["Apr"], 21});
    res.push_back({mp["May"], 21});
    res.push_back({mp["Jun"], 22});
    res.push_back({mp["Jul"], 23});
    res.push_back({mp["Aug"], 23});
    res.push_back({mp["Sep"], 22});
    res.push_back({mp["Oct"], 23});
    res.push_back({mp["Nov"], 23});
    res.push_back({mp["Dec"], 22});
    res.push_back({mp["Jan"], 21});
    res.push_back({mp["Feb"], 20});

    for (int i = 0; i < res.size(); ++i) {
       // cout << res[i].first << " " << res[i].second << " " << countDay(res[i].first, res[i].second) << endl;
        cur.push_back(countDay(res[i].first, res[i].second));
    }
    cur.push_back(*cur.begin());

}

int solve(int d, int m) {
   // cout << d << " " << m << " " << countDay(m, d) << endl;
    int cnt = countDay(m, d);
    for (int i = 0; i < 9; ++i)
        if (cur[i] <= cnt && cnt < cur[i + 1])
            return i;
    for (int i = 10; i <= 11; ++i)
        if (cur[i] <= cnt && cnt < cur[i + 1])
            return i;
    return 9;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    init();
    int TC; cin >> TC;
    while (TC--) {
        int d;
        string m;
        cin >> d >> m;
        cout << sign[solve(d, mp[m])] << endl;
    }
    return 0;
}
