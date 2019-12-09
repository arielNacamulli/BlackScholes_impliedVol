#ifndef BLOCKMATRIX_H_
#define BLOCKMATRIX_H_

#include <vector>

#include "block.hpp"

class BlockMatrix: public Matrix{

private:
    std::vector<Block> blocks;

   bool indexes_in_block(size_t i, size_t j, const Block &block) const;

public:
  BlockMatrix();

  double & operator () (std::size_t i, std::size_t j);
  double operator () (std::size_t i, std::size_t j) const;

  void add_block(const Block &block);
};

#endif /* BLOCKMATRIX_H_ */
