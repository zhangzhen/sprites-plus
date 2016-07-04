#include "CustomSeqAligner.h"
#include "error.h"

#include <vector>
#include <algorithm>
#include <sstream>

#define max3(x,y,z) std::max(std::max(x,y), z)

typedef std::vector<int> DPCells;
typedef std::vector<DPCells> DPMatrix;

AlignmentResult CustomSeqAligner::Align(const std::string &seq1, const std::string &seq2, const ScoreParam &sParam)
{
    if(seq1.empty() || seq2.empty()) {
        error("CustomSeqAligner::Align error: empty input sequence");
    }

    // Initialize the scoring matrix
    size_t num_columns = seq1.size() + 1;
    size_t num_rows = seq2.size() + 1;

    DPMatrix score_matrix;
    score_matrix.resize(num_columns);
    for(size_t i = 0; i < score_matrix.size(); ++i)
        score_matrix[i].resize(num_rows);

    // Calculate scores
    for(size_t i = 1; i < num_columns; ++i) {
        for(size_t j = 1; j < num_rows; ++j) {
            // Calculate the score for entry (i,j)
            int idx_1 = i - 1;
            int idx_2 = j - 1;
            int diagonal = score_matrix[i-1][j-1] + sParam.MatchChar(seq1[idx_1], seq2[idx_2]);
            int up = score_matrix[i][j-1] + sParam.GetGapPenalty();
            int left = score_matrix[i-1][j] + sParam.GetGapPenalty();

            score_matrix[i][j] = std::max(0, max3(diagonal, up, left));
        }
    }

    // The location of the highest scoring match in the
    // last row is the maximum scoring overlap
    // for the pair of strings. We start the backtracking from
    // that cell
    int max_row_value = std::numeric_limits<int>::min();
    size_t max_row_index = 0;

    // Check every column of the last row
    // The first column is skipped to avoid empty alignments
    for(size_t i = 1; i < num_columns; ++i) {
        if(score_matrix[i][num_rows - 1] > max_row_value) {
            max_row_value = score_matrix[i][num_rows - 1];
            max_row_index = i;
        }
    }


        // Compute the location at which to start the backtrack
        size_t i = max_row_index;
        size_t j = num_rows - 1;
        int score = max_row_value;

        // Set the alignment endpoints to be the index of the last aligned base
        int match1_end = i - 1;
        int match2_end = j - 1;

    #ifdef DEBUG_OVERLAPPER
        printf("Endpoints selected: (%d %d) with score %d\n", match1_end, match1_end, score);
    #endif


        std::string cigar;
        while(i > 0 && j > 0 && score_matrix[i][j] > 0) {
            // Compute the possible previous locations of the path
            int idx_1 = i - 1;
            int idx_2 = j - 1;

            int diagonal = score_matrix[i - 1][j - 1] + sParam.MatchChar(seq1[idx_1], seq2[idx_2]);
            int up = score_matrix[i][j-1] + sParam.GetGapPenalty();
            int left = score_matrix[i-1][j] + sParam.GetGapPenalty();
//            int gap_pen = (j == num_rows - 1) ? 0 : sParam.GetGapPenalty();
//            int left = score_matrix[i-1][j] + gap_pen;

            // If there are multiple possible paths to this cell
            // we break ties in order of insertion,deletion,match
            // this helps left-justify matches for homopolymer runs
            // of unequal lengths
            if(score_matrix[i][j] == up) {
                cigar.push_back('I');
                j -= 1;
            } else if(score_matrix[i][j] == left) {
                cigar.push_back('D');
                i -= 1;
            } else {
                assert(score_matrix[i][j] == diagonal);
                cigar.push_back('M');
                i -= 1;
                j -= 1;
            }

        }

        // Set the alignment startpoints
            int match1_start = i;
            int match2_start = j;

//        std::string seq0 = "CTGCCCCAAATACAGCTACTGCCACCACCAAGGCGGCTGTTGGTGCCCTGCAGTCAACAGCCAGTCTCTTCGTGGTCTCACTCTCTCTTCTACATCTCTCC";
//        std::reverse(seq0.begin(), seq0.end());

        // Compact the expanded cigar string into the canonical run length encoding
        // The backtracking produces a cigar string in reversed order, flip it
        std::reverse(cigar.begin(), cigar.end());

        cigar = compactCigar(cigar);

            return AlignmentResult(seq1,
                                   seq2,
                                   Interval(match1_start, match1_end),
                                   Interval(match2_start, match2_end),
                                   score,
                                   cigar);

//        if (seq2 == seq0)
//            output.printAlignment(seq1, seq2);

}

// Compact an expanded CIGAR string into a regular cigar string
std::string compactCigar(const std::string& ecigar)
{
    if(ecigar.empty())
        return "";

    std::stringstream compact_cigar;
    char curr_symbol = ecigar[0];
    int curr_run = 1;
    for(size_t i = 1; i < ecigar.size(); ++i) {
        if(ecigar[i] == curr_symbol) {
            curr_run += 1;
        } else {
            compact_cigar << curr_run << curr_symbol;
            curr_symbol = ecigar[i];
            curr_run = 1;
        }
    }

    // Add last symbol/run
    compact_cigar << curr_run << curr_symbol;
    return compact_cigar.str();
}
