#include "CustomSeqAligner.h"
#include "error.h"

#include <vector>
#include <algorithm>
#include <sstream>

typedef std::vector<int> DPCells;
typedef std::vector<DPCells> DPMatrix;

std::string InsertIndel(std::string s, size_t pos)
{
//    std::cout << s << std::endl;
    s.insert(pos, 1, '-');
    return s;
}

AlignmentResult CustomSeqAligner::Align(const std::string &v, const std::string &w, const ScoreParam &sParam)
{
    if(v.empty() || w.empty()) {
        error("CustomSeqAligner::Align error: empty input sequence");
    }

    // Initialize the scoring matrix
    size_t num_rows = v.size() + 1;
    size_t num_columns = w.size() + 1;

    DPMatrix score_matrix;
    score_matrix.resize(num_rows);
    for(size_t i = 0; i < score_matrix.size(); ++i)
        score_matrix[i].resize(num_columns);

    DPMatrix backtrack;
    backtrack.resize(num_rows);
    for(size_t i = 0; i < backtrack.size(); ++i)
        backtrack[i].resize(num_columns);

    // Calculate scores
    for(size_t i = 1; i < num_rows; ++i) {
        for(size_t j = 1; j < num_columns; ++j) {
            // Calculate the score for entry (i,j)
            int idx_1 = i - 1;
            int idx_2 = j - 1;
            int up = score_matrix[i-1][j] + sParam.GetGap();
            int left = score_matrix[i][j-1] + sParam.GetGap();
            int diagonal = score_matrix[i-1][j-1] + sParam.MatchChar(v[idx_1], w[idx_2]);

            std::vector<int> scores = {up, left, diagonal, 0};

            auto it = std::max_element(scores.begin(), scores.end());

            score_matrix[i][j] = *it;

            backtrack[i][j] = std::distance(scores.begin(), it);
        }
    }

    // The location of the highest scoring match in the
    // last row is the maximum scoring overlap
    // for the pair of strings. We start the backtracking from
    // that cell
    int max_value = std::numeric_limits<int>::min();
    size_t max_row_index = 0;

    // Check every column of the last row
    // The first column is skipped to avoid empty alignments
    for(size_t i = 1; i < num_rows; ++i) {
        if(score_matrix[i][num_columns - 1] > max_value) {
            max_value = score_matrix[i][num_columns - 1];
            max_row_index = i;
        }
    }


    // Compute the location at which to start the backtrack
    size_t i = max_row_index;
    size_t j = num_columns - 1;
    int score = max_value;

    std::string v_aligned = v.substr(0, i);
    std::string w_aligned = w.substr(0, j);

    // Set the alignment endpoints to be the index of the last aligned base
    int match1_end = i - 1;
    int match2_end = j - 1;

#ifdef DEBUG_OVERLAPPER
    printf("Endpoints selected: (%d %d) with score %d\n", match1_end, match1_end, score);
#endif


    while(backtrack[i][j] != 3 && i*j != 0) {

        if (backtrack[i][j] == 0)
        {
            i--;
            w_aligned = InsertIndel(w_aligned, j);
        }
        else if (backtrack[i][j] == 1)
        {
            j--;
            v_aligned = InsertIndel(v_aligned, i);
        }
        else if (backtrack[i][j] == 2)
        {
            i--;
            j--;
        }
    }

    v_aligned = v_aligned.substr(i);
    w_aligned = w_aligned.substr(j);

    // Set the alignment startpoints
    int match1_start = i;
    int match2_start = j;

    return AlignmentResult(v,
                           w,
                           score,
                           AlignmentFragment(v_aligned,
                                             w_aligned,
                                             Interval(match1_start, match1_end),
                                             Interval(match2_start, match2_end)));

}

