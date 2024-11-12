# Some ideas for the Kleos engine

- Generate moves the engine can choose from
- Assign values to each pieces for evaluation
- Evaluation should consider piece positioning, control of center, king safety (maybe pawn structure and endgame evaluation too but those are pretty big and complex)
- Search algorithm: Minimax + AB pruning
- Transposition table to store previous evals to avoid redundant searches. Zobrist hashing for hashing the table with quick updates with XOR
- Might try out PVS (Principal Variation Search) instead of normal AB pruning
- Quiescence search to extend search for moves like captures, checks, and promotions. Helps avoid evaluating unstable positions early
- Bitboard representation seems to improve performance grealy. Might need check it out.
