#include <limits>
#include <iostream>

#include "block_matrix.hpp"

BlockMatrix::BlockMatrix()
  : Matrix (0, 0) {}

double &BlockMatrix::operator()(std::size_t i, std::size_t j) {
    if(indexes_in_range(i,j)){
        for(auto &block : blocks)
            if (indexes_in_block(i,j,block))
                return block(i - block.get_top_left_row(),j - block.get_top_left_col());
        Block block(i,j,i,j,{0});
        add_block(block);
        return blocks.back()(0,0);
    } else {
        std::cerr << "Not in range!" << std::endl;
        return operator()(0,0);
    }


}

double BlockMatrix::operator()(std::size_t i, std::size_t j) const{
    if (indexes_in_range(i,j)) {
        for (const auto block : blocks)
            if (indexes_in_block(i,j,block))
                return block(i - block.get_top_left_row(),j - block.get_top_left_col());
        return 0.0;
    } else
        return std::numeric_limits<double>::quiet_NaN();
}

void BlockMatrix::add_block(const Block &block) {
    blocks.push_back(block);
    n_rows = std::max(n_rows, block.get_bottom_right_row() + 1);
    n_cols = std::max(n_cols, block.get_bottom_right_col() + 1);
}

bool BlockMatrix::indexes_in_block(size_t i, size_t j, const Block &block) const {
    return i >= block.get_top_left_row() && i <= block.get_bottom_right_row() &&
    j >= block.get_top_left_col() && j <= block.get_bottom_right_col();
}

