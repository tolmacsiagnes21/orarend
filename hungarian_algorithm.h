#include <vector>
#include <algorithm>
#include <limits>
#include <unordered_map>

class HungarianAlgorithm {
public:
    HungarianAlgorithm(const std::vector<std::vector<int>>& costMatrix);
    int maxMatching();
    const std::vector<int>& getMatching() const;

private:
    void augment();
    void add_to_tree(int x, int prevx);
    void update_labels();
    int n, m, max_match;
    std::vector<std::vector<int>> cost;
    std::vector<int> label_x, label_y, match_x, match_y, slack, slackx, prev;
    std::vector<bool> S, T; 
};
