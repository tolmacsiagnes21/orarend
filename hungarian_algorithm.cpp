#include "hungarian_algorithm.h"

HungarianAlgorithm::HungarianAlgorithm(const std::vector<std::vector<int>>& costMatrix)
    : n(costMatrix.size()), m(costMatrix[0].size()), cost(costMatrix) {
    max_match = 0;
    label_x.assign(n, 0);
    label_y.assign(m, 0);
    match_x.assign(n, -1);
    match_y.assign(m, -1);
    slack.assign(m, 0);
    slackx.assign(m, 0);
    prev.assign(m, -1);
    S.assign(n, false);  // Initialize S vector
    T.assign(m, false);  // Initialize T vector
}

int HungarianAlgorithm::maxMatching() {
    for (int i = 0; i < n; ++i) {
        label_x[i] = *std::max_element(cost[i].begin(), cost[i].end());
    }

    for (int i = 0; i < n; ++i) {
        augment();
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        if (match_x[i] != -1) {
            result += cost[i][match_x[i]];
        }
    }
    return result;
}

const std::vector<int>& HungarianAlgorithm::getMatching() const {
    return match_x;
}

void HungarianAlgorithm::augment() {
    if (max_match == n) return;

    int root = -1, wr = 0, rd = 0;
    std::vector<int> q(n, -1);
    S.assign(n, false);  // Reset S vector
    T.assign(m, false);  // Reset T vector

    for (int x = 0; x < n; ++x) {
        if (match_x[x] == -1) {
            q[wr++] = root = x;
            prev[root] = -2;
            S[root] = true;
            break;
        }
    }

    for (int y = 0; y < m; ++y) {
        slack[y] = label_x[root] + label_y[y] - cost[root][y];
        slackx[y] = root;
    }

    int x, y;
    while (true) {
        while (rd < wr) {
            x = q[rd++];
            for (y = 0; y < m; ++y) {
                if (cost[x][y] == label_x[x] + label_y[y] && !T[y]) {
                    if (match_y[y] == -1) break;
                    T[y] = true;
                    q[wr++] = match_y[y];
                    add_to_tree(match_y[y], x);
                }
            }
            if (y < m) break;
        }
        if (y < m) break;

        update_labels();
        wr = rd = 0;
        for (y = 0; y < m; ++y) {
            if (!T[y] && slack[y] == 0) {
                if (match_y[y] == -1) {
                    x = slackx[y];
                    break;
                } else {
                    T[y] = true;
                    if (!S[match_y[y]]) {
                        q[wr++] = match_y[y];
                        add_to_tree(match_y[y], slackx[y]);
                    }
                }
            }
        }
        if (y < m) break;
    }

    ++max_match;
    for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
        ty = match_x[cx];
        match_y[cy] = cx;
        match_x[cx] = cy;
    }
}

void HungarianAlgorithm::add_to_tree(int x, int prevx) {
    S[x] = true;
    prev[x] = prevx;
    for (int y = 0; y < m; ++y) {
        if (label_x[x] + label_y[y] - cost[x][y] < slack[y]) {
            slack[y] = label_x[x] + label_y[y] - cost[x][y];
            slackx[y] = x;
        }
    }
}

void HungarianAlgorithm::update_labels() {
    int delta = std::numeric_limits<int>::max();
    for (int y = 0; y < m; ++y) {
        if (!T[y]) {
            delta = std::min(delta, slack[y]);
        }
    }
    for (int x = 0; x < n; ++x) {
        if (S[x]) label_x[x] -= delta;
    }
    for (int y = 0; y < m; ++y) {
        if (T[y]) label_y[y] += delta;
        if (!T[y]) slack[y] -= delta;
    }
}


