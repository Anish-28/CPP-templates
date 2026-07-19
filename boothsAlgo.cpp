int booth(string& s) {
    int n = s.size();
    string t = s + s;

    int i = 0, j = 1, k = 0;

    while (i < n && j < n && k < n) {
        if (t[i + k] == t[j + k]) {
            k++;
        } else {
            if (t[i + k] < t[j + k])
                j += k + 1;
            else
                i += k + 1;

            if (i == j)
                j++;

            k = 0;
        }
    }

    return min(i, j);
}

string minimumRotation(string& s) {
    int pos = booth(s);
    return s.substr(pos) + s.substr(0, pos);
}